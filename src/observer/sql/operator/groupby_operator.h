/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: 2023年10月30日11:49:22
 * @version:    1.0
 **/

#pragma once

#include "sql/expr/expression.h"
#include "sql/operator/logical_operator.h"
#include "sql/expr/tuple.h"
#include "sql/stmt/groupby_stmt.h"

class GroupByLogicalOperator : public LogicalOperator {
public:
  GroupByOperator(GroupByStmt *groupby_stmt, const std::vector<AggrFuncExpression *> &aggr_exprs,
      const std::vector<FieldExpr *> &field_exprs)
      : groupby_stmt_(groupby_stmt)
  {
    tuple_.init(aggr_exprs, field_exprs);
  }

  virtual ~GroupByOperator() = default;


  void print_info();

  void set_groupby_stmt(GroupByStmt *groupby_stmt)
  {
    groupby_stmt_ = groupby_stmt;
  }

private:
  bool is_first_ = true;
  bool is_new_group_ = true;
  bool is_record_eof_ = false;

  // not own this
  GroupByStmt *groupby_stmt_ = nullptr;
};