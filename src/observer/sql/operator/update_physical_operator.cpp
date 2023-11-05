/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: 2023年10月22日16:53:52
 * @version:    1.0
 **/

#include "common/log/log.h"
#include "sql/operator/update_physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "sql/stmt/update_stmt.h"

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  // 递归调用open，递归调用的目的就是将trx传给每一个算子
  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  trx_ = trx;
  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  PhysicalOperator *child = children_[0].get();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();      
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    auto get_cell_for_sub_query = [](const SubQueryExpression *expr, const Tuple &tuple, Value &cell) {
      expr->open_sub_query();
      RC rc = expr->get_value(tuple, cell);
      if (RC::RECORD_EOF == rc) {
        // e.g. a = select a  -> a = null
        cell.set_null();
      } else if (RC::SUCCESS == rc) {
        Value tmp_cell;
        if (RC::SUCCESS == (rc = expr->get_value(tuple, tmp_cell))) {
          // e.g. a = select a  -> a = (1, 2, 3)
          // std::cout << "Should not have rows more than 1" << std::endl;
          expr->close_sub_query();
          return RC::INTERNAL;
        }
      } else {
        expr->close_sub_query();
        return rc;
      }
      expr->close_sub_query();
      return RC::SUCCESS;
    };

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);     // update只能更新一张表，所以返回的一定是row_tuple
    Record &record = row_tuple->record();
    std::vector<Value> values;
    for (auto expr : update_stmt_->exprs()) {
      values.emplace_back(Value());
      if (ExprType::SUBQUERY == expr->type()) {
        SubQueryExpression * temp = dynamic_cast<SubQueryExpression*>(expr);
        rc = get_cell_for_sub_query(temp, *row_tuple, values.back());
        if (rc != RC::SUCCESS) {
          LOG_ERROR("find multi-row in sub-selection");
          return rc;
        }
      } else {
        expr->get_value(*row_tuple, values.back());
      }
    }
    rc = trx_->update_record(update_stmt_->table(), record, values, update_stmt_->attributes_names());
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to delete record: %s", strrc(rc));
      return rc;
    }
  }

  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }

  return RC::SUCCESS;
}
