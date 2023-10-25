/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: [TIMESTAMP]
 * @version:    1.0
 **/

#include "sql/operator/order_by_physical_operator.h"

RC OrderByPhysicalOperator::open(Trx *trx) {
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  // 递归调用open，递归调用的目的就是将trx传给每一个算子
  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  trx_ = trx;

  // 循环从孩子节点获取数据
  PhysicalOperator *oper = children_.front().get();

  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple* tuple = oper->current_tuple()->clone();
    data_.push_back(tuple);
  }
  for (auto &t: data_) {
    auto temp = t->to_string();
    int i = 1;
  }

  // 排序
  for (auto &order_by_unit: order_by_fields_) {
    auto table_name = order_by_unit.field().table()->name();
    auto field_name = order_by_unit.field().field_name();
    auto tuple_schema = TupleCellSpec(table_name, field_name);
    auto direction = order_by_unit.direction();

    // 需要TupleCellSpec参数,但是我保存的是Field，通过Field字段能否拿到TupleCellSpec参数？
    std::sort(data_.begin(), data_.end(), [&](Tuple *left, Tuple *right) {
      Value left_value;
      left->find_cell(tuple_schema, left_value);
      Value right_value;
      right->find_cell(tuple_schema, right_value);
      int res = left_value.compare(right_value);
      if (direction == OrderDirection::ASC) {
        return res < 0;
      }
      return res > 0;
    });
  }

  current_tuple_index_ = -1;
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::next() {
  if (current_tuple_index_ == data_.size() -1) {
    return RC::RECORD_EOF;
  }
  current_tuple_index_++;
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::close() {
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}

Tuple * OrderByPhysicalOperator::current_tuple() {
  assert(0 <= current_tuple_index_ < data_.size());
  return data_[current_tuple_index_];
}