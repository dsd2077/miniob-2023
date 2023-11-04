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
#include "storage/table/table.h"

/**
 * @brief 更新逻辑算子
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, std::vector<Value> values, std::vector<std::string> attribute_name);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::UPDATE;
  }

  void attributes_names(std::vector<std::string> &res)
  {
    for(int i = 0 ; i < attributes_names_.size() ; i ++ ) {
      res.emplace_back(attributes_names_[i]);
    }
  }

  Table *table() const { return table_; }
  // const Value value() const { return values_; }
  // Value value() { return values_; }
  void values(std::vector<Value> &res) const {
    for(int i = 0 ; i < values_.size() ; i ++ ) {
      res.emplace_back(values_[i]);
    }
  }

private:
  Table *table_ = nullptr;
  // Value values_;
  // std::string attribute_name_;

  std::vector<Value> values_;
  std::vector<std::string> attributes_names_;
};