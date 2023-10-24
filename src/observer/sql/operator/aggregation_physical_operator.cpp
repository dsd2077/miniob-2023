//
// Created by MaYunXiu 2023/10/24.
//

#include "common/log/log.h"
#include "sql/operator/aggregation_physical_operator.h"
#include "sql/parser/value.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include <memory>

RC AggregationPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  int count = 0;
  while (RC::SUCCESS == child->next()) {
    Tuple *cur_tuple = child->current_tuple();
    combine(cur_tuple, ++count); 
  }
  if (count > 0) {
    for (int i = 0; i < agg_types_.size(); i++) {
      if (agg_types_[i] == AggregationType::AVG) {
        Value value;
        expressions_[i]->try_get_value(value);
        auto count_expr = std::make_unique<ValueExpr>(Value(count));
        ArithmeticExpr expr(ArithmeticExpr::Type::DIV, std::move(expressions_[i]), std::move(count_expr));
        expr.try_get_value(value);
        expressions_[i].reset(new ValueExpr(value));
      }
    }
  }

  return RC::SUCCESS;
}

RC AggregationPhysicalOperator::next()
{
  if (is_first_) {
    is_first_ = false;
    return RC::SUCCESS;
  }
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  return children_[0]->next();
}

RC AggregationPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
Tuple *AggregationPhysicalOperator::current_tuple()
{
  tuple_.reset(new ExpressionTuple(expressions_));
  return tuple_.get();
}

