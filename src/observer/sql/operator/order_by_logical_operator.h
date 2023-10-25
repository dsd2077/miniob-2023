/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: 2023年10月24日16:34:48
 * @version:    1.0
 **/

#include "sql/operator/logical_operator.h"
#include "src/observer/sql/stmt/select_stmt.h"

class OrderByLogicalOperator : public LogicalOperator {
public:
  OrderByLogicalOperator(const std::vector<OrderByUnit> &order_by_fields): order_by_fields_(order_by_fields){};
  virtual ~OrderByLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::ORDER_BY;
  }
  const std::vector<OrderByUnit> & order_by_fields() const {
    return order_by_fields_;
  }

private:
  std::vector<OrderByUnit> order_by_fields_;
};