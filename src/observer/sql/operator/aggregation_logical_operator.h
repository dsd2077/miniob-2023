//
// // Created by MaYunxiu on 2023/10/24.
//

#pragma once

#include <vector>
#include <memory>

#include "sql/operator/logical_operator.h"
#include "sql/expr/expression.h"
#include "storage/field/field.h"

/**
 * @brief aggregation 表示聚合运算
 * @ingroup LogicalOperator
 * @details 从表中获取数据后，可能需要过滤，投影，连接等等。
 */
class AggregationLogicalOperator : public LogicalOperator 
{
public:
  AggregationLogicalOperator(std::vector<std::unique_ptr<Expression>> expressions, const std::vector<AggregationType> &agg_types);
  virtual ~AggregationLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::AGGREGATION;
  }

  std::vector<std::unique_ptr<Expression>> &expressions()
  {
    return expressions_;
  }
  std::vector<AggregationType> &agg_types()
  {
    return agg_types_;
  }

  const std::vector<std::unique_ptr<Expression>> &expressions() const
  {
    return expressions_;
  }
private:
  std::vector<AggregationType> agg_types_;
};
