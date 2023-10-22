/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: 2023年10月22日15:56:20
 * @version:    1.0
 **/

#pragma once

#include <vector>

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"

/**
 * @brief 更新逻辑算子
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, Value values, std::string attribute_name);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::UPDATE;
  }

  std::string attribute_name()
  {
    return attribute_name_;
  }

  Table *table() const { return table_; }
  const Value value() const { return values_; }
  Value value() { return values_; }

private:
  Table *table_ = nullptr;
  Value values_;
  std::string attribute_name_;
};