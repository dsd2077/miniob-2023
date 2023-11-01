/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: 2023年10月30日13:49:42
 * @version:    1.0
 **/

#include "sql/operator/physical_operator.h"
#include "sql/stmt/groupby_stmt.h"

class GroupByPhysicalOperator : public PhysicalOperator {
public:
  GroupByPhysicalOperator(std::vector<GroupByUnit *>groupby_units, const std::vector<AggrFuncExpression *> &aggr_exprs,
      const std::vector<FieldExpr *> &field_exprs)
      : groupby_units_(groupby_units)
  {
    tuple_.init(aggr_exprs, field_exprs);
  }

  virtual ~GroupByPhysicalOperator() = default;

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

  PhysicalOperatorType type() const override{
    return PhysicalOperatorType::GROUP_BY;
  }

  void print_info();

private:
  bool is_first_ = true;
  bool is_new_group_ = true;
  bool is_record_eof_ = false;

  // not own this
  std::vector<GroupByUnit *> groupby_units_;

  std::vector<Value> pre_values_;  // its size equal to groupby_units.size
  GroupTuple tuple_;
};