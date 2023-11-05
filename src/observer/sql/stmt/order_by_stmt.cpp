/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: 2023年10月25日21:45:14
 * @version:    1.0
 **/

#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/order_by_stmt.h"
#include "sql/expr/expression.h"
#include "common/log/log.h"

OrderByStmt::~OrderByStmt()
{
  for (OrderByUnit *unit : orderby_units_) {
    delete unit;
  }
  orderby_units_.clear();
}

RC OrderByStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const std::vector<OrderByNode> &orderbys, OrderByStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  if (orderbys.size() == 0) return rc;

  OrderByStmt *tmp_stmt = new OrderByStmt();
  for (int i = 0; i < orderbys.size(); i++) {
    OrderByUnit *orderby_unit = nullptr;      // orderby_unit指向的是一块堆上的内存
    rc = create_orderby_unit(db, default_table, tables, orderbys[i], orderby_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->orderby_units_.push_back(orderby_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC OrderByStmt::create_orderby_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const OrderByNode &orderby, OrderByUnit *&orderby_unit)
{
  RC rc = RC::SUCCESS;

  OrderDirection sort_type = orderby.direction;

  Table *table = nullptr;
  const FieldMeta *field = nullptr;
  // 这里已经进行了类型检查
  rc = get_table_and_field(db, default_table, tables, orderby.attribute, table, field);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot find attr");
    return rc;
  }
  FieldExpr *expr = new FieldExpr(table, field);
  orderby_unit = new OrderByUnit;
  orderby_unit->set_direction(sort_type);
  orderby_unit->set_expr(expr);
  return rc;
}

