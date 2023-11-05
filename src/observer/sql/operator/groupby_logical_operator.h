/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     2023年10月31日19:56:14
 * @create_time: [TIMESTAMP]
 * @version:    1.0
 **/

#include "sql/operator/logical_operator.h"
#include "sql/stmt/groupby_stmt.h"

class GroupByLogicalOperator : public LogicalOperator {
public:
  GroupByLogicalOperator(const std::vector<GroupByUnit *> groupby_units, std::vector<AggrFuncExpression *> &agg_exprs,
      std::vector<FieldExpr *> &field_exprs)
      : groupby_units_(groupby_units), agg_exprs_(agg_exprs), field_exprs_(field_exprs)
  {}

  virtual ~GroupByLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::GROUP_BY; };

  const std::vector<GroupByUnit *> groupby_unit() {
    return groupby_units_;
  }

  std::vector<AggrFuncExpression *> agg_exprs() {
    return agg_exprs_;
  }

  std::vector<FieldExpr *> field_exprs() {
    return field_exprs_;
  }

private:
  const std::vector<GroupByUnit *> groupby_units_;
  std::vector<AggrFuncExpression *> agg_exprs_;
  std::vector<FieldExpr *> field_exprs_;
};