/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: 2023年10月25日21:41:00
 * @version:    1.0
 **/

#include "common/rc.h"
#include "sql/parser/parse_defs.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/expr/expression.h"

#include <unordered_map>


class OrderByUnit {
public:
  OrderByUnit() = default;

  ~OrderByUnit()
  {
    if (expr_) {
      delete expr_;
      expr_ = nullptr;
    }
  }

  void set_expr(FieldExpr *expr)
  {
    expr_ = expr;
  }

  FieldExpr *expr() const
  {
    return expr_;
  }

  OrderDirection direction() {
    return direction_;
  }

  void set_direction(OrderDirection direction)
  {
    direction_ = direction;
  }


private:
  FieldExpr *expr_ = nullptr;
  OrderDirection	direction_;
};


class OrderByStmt {
public:
  OrderByStmt() = default;
  virtual ~OrderByStmt();

public:
  std::vector<OrderByUnit *> &orderby_units() 
  {
    return orderby_units_;
  }

public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const std::vector<OrderByNode> & orderbys, OrderByStmt *&stmt);

  // the func used for creating orderby_stmt for groupby
  // static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
  //     const GroupBy *groupbys, int groupby_num, OrderByStmt *&stmt);

  static RC create_orderby_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const OrderByNode &orderby, OrderByUnit *&orderby_unit);

  // static RC create_orderby_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
  //     const GroupBy &groupby, OrderByUnit *&orderby_unit);

private:
  std::vector<OrderByUnit *> orderby_units_;
};



