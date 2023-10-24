//
// Created by MaYunxiu on 2023/10/24.
//

#pragma once

#include "common/log/log.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"

/**
 * @brief 聚合物理算子
 * @ingroup PhysicalOperator
 */
class AggregationPhysicalOperator : public PhysicalOperator
{
public:
  AggregationPhysicalOperator(std::vector<std::unique_ptr<Expression>> &expressions): expressions_(std::move(expressions))
  {}

  virtual ~AggregationPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::AGGREGATION;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  // int cell_num() const
  // {
  //   // return tuple_.cell_num();
  // }


  void combine(Tuple* tuple, int count) {
    // ASSERT(values_.size() == append.size(), "combine size error");
    for (int i = 0; i < agg_types_.size(); i++) {
      switch (agg_types_[i]) {
        case AggregationType::NONE: {

        } break;
        case AggregationType::COUN_:
        case AggregationType::COUN_STAR: {
          std::unique_ptr<Expression> value_expr(new ValueExpr(Value(1)));
          ArithmeticExpr expr(ArithmeticExpr::Type::ADD, std::move(expressions_[i]), std::move(value_expr));
          Value value;
          expr.try_get_value(value);
          expressions_[i].reset(new ValueExpr(value));
        } break;
        case AggregationType::MIN: {
          Value value;
          agg_expressions_[i]->get_value(*tuple, value);
          if (count == 1) {
            expressions_[i].reset(new ValueExpr(value));
          } else {
            Value cur_value;
            expressions_[i]->try_get_value(cur_value);
            if (value.compare(cur_value) < 0) {
              expressions_[i].reset(new ValueExpr(value));
            }
          }
        } break;
        case AggregationType::MAX: {
          Value value;
          agg_expressions_[i]->get_value(*tuple, value);
          if (count == 1) {
            expressions_[i].reset(new ValueExpr(value));
          } else {
            Value cur_value;
            expressions_[i]->try_get_value(cur_value);
            if (value.compare(cur_value) > 0) {
              expressions_[i].reset(new ValueExpr(value));
            }
          }
        } break;
        case AggregationType::SUM:
        case AggregationType::AVG: {
          Value value;
          agg_expressions_[i]->get_value(*tuple, value);
          std::unique_ptr<Expression> value_expr(new ValueExpr(value));
          ArithmeticExpr expr(ArithmeticExpr::Type::ADD, std::move(expressions_[i]), std::move(value_expr));
          expr.try_get_value(value);
          expressions_[i].reset(new ValueExpr(value));
        } break;
        default: {
          ASSERT(false, "unknown aggregation type");
        } break;
      };
    }
  }

  Tuple *current_tuple() override;

  void add_agg_type(AggregationType agg_type)
  {
    agg_types_.emplace_back(agg_type);
  }

  std::vector<AggregationType> &agg_types()
  {
    return agg_types_;
  }

  std::vector<std::unique_ptr<Expression>> &agg_expressions() {
    return agg_expressions_;
  }


private:
  std::vector<std::unique_ptr<Expression>> expressions_; 
  std::vector<std::unique_ptr<Expression>> agg_expressions_; 
  std::vector<AggregationType> agg_types_;
  std::unique_ptr<Tuple> tuple_;
  bool is_first_ = true;
};
