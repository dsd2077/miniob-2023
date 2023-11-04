/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: 2023年10月22日16:56:46
 * @version:    1.0
 **/

#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, std::vector<Value> values, std::vector<std::string> attributes_names) 
: table_(table), values_(values), attributes_names_(attributes_names)
{}