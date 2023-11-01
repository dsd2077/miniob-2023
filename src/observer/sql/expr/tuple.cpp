/**
 * @brief:      A brief description of the file's purpose and main functionalities.
 * @details:    A more detailed description, if necessary.
 * 
 * @author:     dengshudong 
 * @create_time: 2023年11月01日08:10:39
 * @version:    1.0
 **/

 #include "sql/expr/tuple.h"
#include "sql/parser/parse_defs.h"

void GroupTuple::do_aggregate_first()
{
  assert(aggr_results_.size() == aggr_exprs_.size());
  assert(aggr_exprs_.size() == all_null_.size());
  assert(aggr_exprs_.size() == counts_.size());
  assert(field_results_.size() == field_exprs_.size());
  // first row in current group
  for (size_t i = 0; i < all_null_.size(); ++i) {
    all_null_[i] = true;
    counts_[i]   = 0;
  }
  for (size_t i = 0; i < aggr_exprs_.size(); ++i) {
    AggrFuncExpression *expr = aggr_exprs_[i];
    if (expr->get_aggr_func_type() != AggrFuncType::CNT) {
      expr->get_value(*tuple_, aggr_results_[i]);
    }
    if (!aggr_results_[i].is_null()) {
      all_null_[i] = false;
      counts_[i]++;
    }
  }
  for (size_t i = 0; i < field_exprs_.size(); ++i) {
    field_exprs_[i]->get_value(*tuple_, field_results_[i]);
  }
}

void GroupTuple::do_aggregate()
{
  Value tmp;
  for (size_t i = 0; i < aggr_exprs_.size(); ++i) {
    const AggrFuncExpression *expr = aggr_exprs_[i];
    if (expr->get_aggr_func_type() != AggrFuncType::CNT) {
      expr->get_value(*tuple_, tmp);
    }
    if (tmp.is_null()) {  // cannot do any aggregate for NULL
      continue;
    }
    all_null_[i] = false;
    counts_[i]++;
    if (AggrFuncType::CNT == expr->get_aggr_func_type()) {
      continue;
    }
    // NOTE: aggr_results_[i] maybe null. tmp is not null
    if (aggr_results_[i].is_null()) {
      aggr_results_[i] = tmp;
    }
    switch (expr->get_aggr_func_type()) {
      case AggrFuncType::MIN: aggr_results_[i] = Value::min(aggr_results_[i], tmp); break;
      case AggrFuncType::MAX: aggr_results_[i] = Value::max(aggr_results_[i], tmp); break;
      case AggrFuncType::SUM:
      case AggrFuncType::AVG: aggr_results_[i] = Value::add(aggr_results_[i], tmp); break;
      default: LOG_ERROR("Unsupported AggrFuncType"); break;
    }
  }
}

void GroupTuple::do_aggregate_done()
{
  for (size_t i = 0; i < aggr_exprs_.size(); ++i) {
    const AggrFuncExpression *expr = aggr_exprs_[i];
    Value &res  = aggr_results_[i];
    // if all null, result is null
    if (all_null_[i] && AggrFuncType::CNT != expr->get_aggr_func_type()) {
      aggr_results_[i].set_null();
      continue;
    }
    switch (expr->get_aggr_func_type()) {
      case AggrFuncType::CNT: {
        res.set_type(AttrType::INTS);
        res.set_int(counts_[i]);
        // res.modify_data((char *)&count_);
        break;
      }
      case AggrFuncType::AVG: {
        res = Value::div(res, Value(AttrType::INTS, (char *)&counts_[i]));  // malloc memory in div
        break;
      }
      default: break;
    }
  }
}
