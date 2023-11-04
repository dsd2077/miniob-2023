/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: 2023年11月04日21:37:30
 * @version:    1.0
 **/

#include "sql/operator/empty_table_get_physical_oper.h"

RC EmptyTableGetPhysicalOperator::open(Trx *trx)
{
  return RC::SUCCESS;
}

RC EmptyTableGetPhysicalOperator::next()
{
  if (is_first_) {
    is_first_ = false;
    return RC::SUCCESS;
  }
  return RC::RECORD_EOF;
}

RC EmptyTableGetPhysicalOperator::close()
{
  return RC::SUCCESS;
}

Tuple *EmptyTableGetPhysicalOperator::current_tuple()
{
  return &tuple_;
}
