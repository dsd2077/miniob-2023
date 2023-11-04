/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: 2023年11月04日21:35:57
 * @version:    1.0
 **/

#include "sql/operator/physical_operator.h"

class EmptyTableGetPhysicalOperator : public PhysicalOperator {
public:
  EmptyTableGetPhysicalOperator() = default;

  virtual ~EmptyTableGetPhysicalOperator() = default;

  virtual PhysicalOperatorType type() const override{
    return PhysicalOperatorType::EMPTY_TABLE_GET;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

private:
  RowTuple tuple_;
  bool is_first_ = true;
};