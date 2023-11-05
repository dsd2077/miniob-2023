/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: 2023年11月05日10:36:26
 * @version:    1.0
 **/

#include "sql/operator/order_by_physical_operator.h"
#include "sql/stmt/order_by_stmt.h"

RC OrderByPhysicalOperator::open(Trx *trx) {
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  // 递归调用open，递归调用的目的就是将trx传给每一个算子
  RC rc = children_[0]->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  rc = fetch_and_sort_table();

  return rc;
}

RC OrderByPhysicalOperator::fetch_and_sort_table()
{
  RC rc = RC::SUCCESS;

  int index = 0;
  typedef std::pair<std::vector<Value>, int> CmpPair;
  std::vector<CmpPair> pair_sort_table;
  std::vector<Value> pair_cell;     // 拿到排序字段的值

  while (RC::SUCCESS == (rc = children_[0]->next())) {
    // construct pair sort table
    // 1 cons vector<cell>
    pair_cell.clear();
    for (const OrderByUnit *unit : order_by_fields_) {
      Expression *expr = unit->expr();
      Value cell;
      expr->get_value(*children_[0]->current_tuple(), cell);
      pair_cell.emplace_back(cell);
    }

    // 2 cons pair
    // 3 cons pair vector
    pair_sort_table.emplace_back(std::make_pair(pair_cell, index++));

    // store child records
    CompoundRecord cpd_rcd;   // “一行”记录
    children_[0]->current_tuple()->get_record(cpd_rcd);

    // need to deep copy the rcd and push back to rht
    // remember to delete them in dtor
    for (auto &rcd_ptr : cpd_rcd) {
      rcd_ptr = new Record(*rcd_ptr);
    }
    st_.emplace_back(cpd_rcd);    
  }
  // st_中存储了所有的行记录
  // pair_sort_table存储了所有需要排序字段的值

  if (RC::RECORD_EOF != rc) {
    LOG_ERROR("Fetch Table Error In SortOperator. RC: %d", rc);
    return rc;
  }
  rc = RC::SUCCESS;
  LOG_INFO("Fetch Table Success In SortOperator");
  // print_info();

  // then sort table
  bool order[order_by_fields_.size()];  // specify 1 asc or 2 desc
  for (std::vector<OrderByUnit *>::size_type i = 0; i < order_by_fields_.size(); ++i) {
    order[i] = order_by_fields_[i]->direction() == OrderDirection::ASC_;
  }
  // consider null
  auto cmp = [&order](const CmpPair &a, const CmpPair &b) {
    auto &cells_a = a.first;
    auto &cells_b = b.first;
    assert(cells_a.size() == cells_b.size());
    for (size_t i = 0; i < cells_a.size(); ++i) {
      auto &cell_a = cells_a[i];
      auto &cell_b = cells_b[i];
      if (cell_a.is_null() && cell_b.is_null()) {
        continue;
      }
      if (cell_a.is_null()) {
        return order[i] ? true : false;
      }
      if (cell_b.is_null()) {
        return order[i] ? false : true;
      }
      if (cell_a != cell_b) {
        return order[i] ? cell_a < cell_b : cell_a > cell_b;
      }
    }
    return false;  // completely same
  };

  std::sort(pair_sort_table.begin(), pair_sort_table.end(), cmp);

  LOG_INFO("Sort Table Success In SortOperator");

  // fill ordered_idx_
  for (size_t i = 0; i < pair_sort_table.size(); ++i) {
    ordered_idx_.emplace_back(pair_sort_table[i].second);
  }
  it_ = ordered_idx_.begin();

  return rc;  // return RC::SUCCESS
}

RC OrderByPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;

  if (ordered_idx_.end() != it_) {
    // NOTE: PAY ATTENTION HERE
    children_[0]->current_tuple()->set_record(st_[*it_]);
    it_++;
    return RC::SUCCESS;
  }

  return RC::RECORD_EOF;
}

RC OrderByPhysicalOperator::close() {
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}

Tuple *OrderByPhysicalOperator::current_tuple()
{
  return children_[0]->current_tuple();
}

OrderByPhysicalOperator::~OrderByPhysicalOperator() {
  for (auto &cpd_rcd : st_) {
    for (auto rcd : cpd_rcd) {
      delete rcd;
    }
  }
}
