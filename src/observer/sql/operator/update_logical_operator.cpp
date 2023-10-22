/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: 2023年10月22日16:56:46
 * @version:    1.0
 **/

#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, Value values, std::string attribute_name) 
: table_(table), values_(values), attribute_name_(attribute_name)
{}