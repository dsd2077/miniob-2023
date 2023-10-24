//
// Created by MaYunxiu on 2023/10/24.
//

#include "sql/operator/aggregation_logical_operator.h"

AggregationLogicalOperator::AggregationLogicalOperator(std::vector<std::unique_ptr<Expression>> expressions, const std::vector<AggregationType> &agg_types)
:agg_types_(agg_types)
{
  expressions_ = std::move(expressions);
}
