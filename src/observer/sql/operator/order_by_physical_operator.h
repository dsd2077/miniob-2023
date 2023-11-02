/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: 2023年10月24日20:16:40
 * @version:    1.0
 **/

#include "sql/operator/physical_operator.h"
#include "sql/stmt/select_stmt.h"
#include "storage/trx/trx.h"

class OrderByUnit;

class OrderByPhysicalOperator : public PhysicalOperator {
public:
  OrderByPhysicalOperator(std::vector<OrderByUnit *> &order_by_fields) : order_by_fields_(order_by_fields){};

  virtual ~OrderByPhysicalOperator();

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::ORDER_BY;
  }
  // 在open函数中拿到子节点的所有数据存放到data_中并排好序
  RC open(Trx *trx) override;
  RC next() override;     // 每次返回一个Record
  RC close() override;

  Tuple *current_tuple() override;
private:
  RC fetch_and_sort_table();

private:
  std::vector<OrderByUnit* > &order_by_fields_;
  std::vector<Tuple *>     data_;
  int                      current_tuple_index_;
  Trx *                     trx_;
};