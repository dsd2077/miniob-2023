/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: 2023年11月04日21:33:04
 * @version:    1.0
 **/

#include "sql/expr/expression.h"
#include "sql/operator/logical_operator.h"

class EmptyTableGetLogicalOperator : public LogicalOperator {
public:
  EmptyTableGetLogicalOperator() = default;
  virtual ~EmptyTableGetLogicalOperator() = default;

  virtual LogicalOperatorType type() const {
    return LogicalOperatorType::EMPTY_TABLE_GET;
  }
};