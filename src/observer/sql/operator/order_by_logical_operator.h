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


class OrderByUnit;

// order by的逻辑算子只是将order_by_fields从order_by_stmt中取了出来
// 虽然没有什么用，但是为了统一代码，还是写了一个
class OrderByLogicalOperator : public LogicalOperator {
public:
  OrderByLogicalOperator(std::vector<OrderByUnit*> &order_by_fields): order_by_fields_(order_by_fields){};
  virtual ~OrderByLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::ORDER_BY; }

  std::vector<OrderByUnit*> & order_by_fields() {
    return order_by_fields_;
  }

private:
  std::vector<OrderByUnit*> &order_by_fields_;    //OrderByUnit的指针全部放在select_stmt->order_by_stmt->orderby_units中
};