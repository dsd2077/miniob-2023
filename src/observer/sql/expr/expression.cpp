/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/07/05.
//

#include "sql/expr/expression.h"
#include "common/lang/string.h"
#include "sql/expr/tuple.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "src/observer/sql/stmt/select_stmt.h"
#include "storage/db/db.h"
#include <iomanip>
#include <regex>

using namespace std;

RC FieldExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = tuple.find_cell(TupleCellSpec(table_name(), field_name()), value);
  try_get_negtive_value(value);
  return rc;
}
RC FieldExpr::init(const std::vector<Table *> &tables, const std::unordered_map<std::string, Table *> &table_map, Db *db) {
  // bool with_brace = expr->with_brace;       // 括号，什么时候需要考虑括号？
  // 没有表名字段
  if (common::is_blank(table_name_.c_str())) {
    if (tables.size() != 1) {
      LOG_WARN("invalid. I do not know the attr's table. attr=%s", field_name_.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }
    Table *table = tables[0];
    const FieldMeta *field_meta = table->table_meta().field(field_name_.c_str());
    if (nullptr == field_meta) {
      LOG_WARN("no such field. field=%s.%s", table->name(), field_name_.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }
    field_.set_table(table);
    field_.set_field(field_meta);
    table_name_ = table->name();
    field_name_ = field_meta->name();
    return RC::SUCCESS;
  } else {
    auto iter = table_map.find(table_name_.c_str());
    if (iter == table_map.end()) {
      LOG_WARN("no such table in from list: %s", table_name_.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }

    Table *table = iter->second;
    const FieldMeta *field_meta = table->table_meta().field(field_name_.c_str());
    if (nullptr == field_meta) {
      LOG_WARN("no such field. field=%s.%s", table->name(), field_name_.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }
    field_.set_table(table);
    field_.set_field(field_meta);
    table_name_ = table->name();
    field_name_ = field_meta->name();
    return RC::SUCCESS;
  }
}

void FieldExpr::get_fieldexprs_without_aggrfunc(Expression *expr, std::vector<FieldExpr *> &field_exprs)
{
  switch (expr->type()) {
    case ExprType::FIELD: {
      FieldExpr *exp = dynamic_cast<FieldExpr *>(expr);
      field_exprs.emplace_back(exp);
    break;
    }
    case ExprType::AGGRFUNC: {
      // const AggrFuncExpression *afexp = (const AggrFuncExpression *)expr;
      // get_fieldexprs_without_aggrfunc(&afexp->fieldexpr(), field_exprs);
      break;
    }
    case ExprType::ARITHMETIC: {
      ArithmeticExpr *exp = dynamic_cast<ArithmeticExpr *>(expr);
      get_fieldexprs_without_aggrfunc(exp->left().get(), field_exprs);
      get_fieldexprs_without_aggrfunc(exp->left().get(), field_exprs);
      break;
    }
    default:
      break;
  }
  return;
}

bool FieldExpr::in_expression(const Expression *expr) 
{
  switch (expr->type()) {
    case ExprType::FIELD: {
      return field_.equal(((const FieldExpr *)expr)->field_);
    }
    case ExprType::AGGRFUNC: {
      const AggrFuncExpression *afexp = (const AggrFuncExpression *)expr;
      return in_expression(&afexp->fieldexpr());
    }
    case ExprType::ARITHMETIC: {
      ArithmeticExpr *bexp = (ArithmeticExpr *)expr;
      return in_expression(bexp->left().get()) || in_expression(bexp->right().get());
    }
    default:
      break;
  }
  return false;
}

RC ValueExpr::get_value(const Tuple &tuple, Value &value) const
{
  value = value_;
  return RC::SUCCESS;
}

RC ValueExpr::init(
    const std::vector<Table *> &tables, const std::unordered_map<std::string, Table *> &table_map, Db *db)
{
  assert(ExprType::VALUE == type());
  if (value_.attr_type() == DATES && !common::is_valid_date(value_.get_int())) {
    return RC::INVALID_ARGUMENT;
  }

  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type)
    : child_(std::move(child)), cast_type_(cast_type)
{}

CastExpr::~CastExpr()
{}

RC CastExpr::cast(const Value &value, Value &cast_value) const
{
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }

  switch (cast_type_) {
    case BOOLEANS: {
      bool val = value.get_boolean();
      cast_value.set_boolean(val);
    } break;
    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported convert from type %d to %d", child_->value_type(), cast_type_);
    }
  }
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &cell) const
{
  RC rc = child_->get_value(tuple, cell);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(cell, cell);
}

RC CastExpr::try_get_value(Value &value) const
{
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, value);
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right))
{}

ComparisonExpr::~ComparisonExpr()
{}

RC ComparisonExpr::init(
    const std::vector<Table *> &tables, const std::unordered_map<std::string, Table *> &table_map, Db *db)
{
  assert(ExprType::COMPARISON == type());
  // bool with_brace = expr->with_brace;
  RC rc = left_->init(tables, table_map, db);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("BinaryExpression Create Left Expression Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
  }
  rc = check_sub_query(left_.get());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("ComparisonExpr Create Left SubqueryExpression Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
  }

  rc = right_->init(tables, table_map, db);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("BinaryExpression Create Right Expression Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
  }
  rc = check_sub_query(right_.get());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("ComparisonExpr Create Right SubqueryExpression Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC ComparisonExpr::check_sub_query(Expression *expr) {
  if (ExprType::SUBQUERY != expr->type()) {
    return RC::SUCCESS;
  }
  SubQueryExpression *tmp_expr = dynamic_cast<SubQueryExpression *>(expr);
  SelectStmt *tmp_stmt = tmp_expr->get_sub_query_stmt();
  switch (comp_) {
    case EXISTS_OP:
    case NOT_EXISTS: break;
    default: {
      if (tmp_stmt->projects().size() != 1) {
        return RC::SQL_SYNTAX;
      }
      break;
    }
  }
  return RC::SUCCESS;
}

RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{
  RC rc = RC::SUCCESS;
  int cmp_result = left.compare(right);
  result = false;
  switch (comp_) {
    case EQUAL_TO: {
      result = (0 == cmp_result);
    } break;
    case LESS_EQUAL: {
      result = (cmp_result <= 0);
    } break;
    case NOT_EQUAL: {
      result = (cmp_result != 0);
    } break;
    case LESS_THAN: {
      result = (cmp_result < 0);
    } break;
    case GREAT_EQUAL: {
      result = (cmp_result >= 0);
    } break;
    case GREAT_THAN: {
      result = (cmp_result > 0);
    } break;
    case LIKE_OP: {
      // LIKE: 不使用Value::compare的通用方法
      std::string right_str = right.get_string();
      std::string left_str = left.get_string();
      std::string re = "^";
      for(int i = 0 ; i < right_str.size() ; i ++ ) {
        if(right_str[i] == '%') {
          re += ".*";
        }else if(right_str[i] == '_') {
          re += ".";
        }else {
          re += right_str[i];
        }
      }
      re += "$";

      std::regex like_regex(re);  // like的正则表达式
      std::smatch matcher;
      result = std::regex_search(left_str, matcher, like_regex);  // 如果left_str符合right_str，那么将会返回正确结果
    }break;
    case NOT_LIKE_OP: {
      // NOT_LIKE: 不使用Value::compare的通用方法
      std::string right_str = right.get_string();
      std::string left_str = left.get_string();
      std::string re = "^";
      for(int i = 0 ; i < right_str.size() ; i ++ ) {
        if(right_str[i] == '%') {
          re += ".*";
        }else if(right_str[i] == '_') {
          re += ".";
        }else {
          re += right_str[i];
        }
      }
      re += "$";

      std::regex like_regex(re);  // like的正则表达式
      std::smatch matcher;
      result = !std::regex_search(left_str, matcher, like_regex);  // 如果left_str符合right_str，那么将会返回正确结果
    }break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp_);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

RC ComparisonExpr::try_get_value(Value &cell) const
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr *left_value_expr = static_cast<ValueExpr *>(left_.get());
    ValueExpr *right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell = left_value_expr->get_value();
    const Value &right_cell = right_value_expr->get_value();

    bool value = false;
    RC rc = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  Value left_value;
  Value right_value;
    // 0. for [not] exist
  if (CompOp::EXISTS_OP == comp_ || CompOp::NOT_EXISTS == comp_) {
    // assert(nullptr == left_expr);
    assert(ExprType::SUBQUERY == right_->type());
    SubQueryExpression *sub_query = static_cast<SubQueryExpression*>(right_.get());
    
    sub_query->open_sub_query();
    // TODO compound with parent tuple
    RC tmp_rc = sub_query->get_value(tuple, right_value);
    if (RC::SUCCESS != tmp_rc && RC::RECORD_EOF != tmp_rc) {
      return tmp_rc;
    }
    sub_query->close_sub_query();
    bool res = CompOp::EXISTS_OP == comp_ ? (RC::SUCCESS == tmp_rc) : (RC::RECORD_EOF == tmp_rc);
    value.set_boolean(res);
    try_get_negtive_value(value);
    return RC::SUCCESS;
  }

    // 1. for [not] in
  if (CompOp::IN_OP == comp_ || CompOp::NOT_IN == comp_) {
    rc = left_->get_value(tuple, left_value);
    if (RC::SUCCESS != rc) {
      return rc;
    }
    // 考虑none
    if (left_value.is_null()) {
      try_get_negtive_value(value);
      value.set_boolean(false);  // null don't in/not in any list
      return RC::SUCCESS;
    }
    std::vector<Value> right_values;
    right_values.emplace_back(Value());
    RC tmp_rc = RC::SUCCESS;
    if (ExprType::SUBQUERY == right_->type()) {
      SubQueryExpression *sub_query = static_cast<SubQueryExpression*>(right_.get());
      sub_query->open_sub_query();
      while (RC::SUCCESS == (tmp_rc = sub_query->get_value(tuple, right_values.back()))) {
        right_values.emplace_back(Value());
      }
      sub_query->close_sub_query();
      if (RC::RECORD_EOF != tmp_rc) {
        LOG_ERROR("[NOT] IN Get SubQuery Value Failed. RC = %d:%s", tmp_rc, strrc(tmp_rc));
        return tmp_rc;
      }
      right_values.pop_back();  // pop null cell for record_eof
    } else {
      assert(ExprType::SUBLIST == right_->type());
      ListExpression *sub_query = static_cast<ListExpression*>(right_.get());
      right_values = sub_query->get_tuple_cells();
    }
    // 考虑null值
    auto has_null = [](const std::vector<Value> &cells) {
      for (auto &cell : cells) {
        if (cell.is_null()) {
          return true;
        }
      }
      return false;
    };
    bool res = CompOp::IN_OP == comp_ ? left_value.in_cells(right_values)
                                      : (has_null(right_values) ? false : left_value.not_in_cells(right_values));
    try_get_negtive_value(value);
    value.set_boolean(res);
    return RC::SUCCESS;
  }

  auto get_cell_for_sub_query = [](const SubQueryExpression *expr, const Tuple &tuple, Value &cell) {
    expr->open_sub_query();
    RC rc = expr->get_value(tuple, cell);
    if (RC::RECORD_EOF == rc) {
      // e.g. a = select a  -> a = null
      cell.set_null();
    } else if (RC::SUCCESS == rc) {
      Value tmp_cell;
      if (RC::SUCCESS == (rc = expr->get_value(tuple, tmp_cell))) {
        // e.g. a = select a  -> a = (1, 2, 3)
        // std::cout << "Should not have rows more than 1" << std::endl;
        expr->close_sub_query();
        return RC::INTERNAL;
      }
    } else {
      expr->close_sub_query();
      return rc;
    }
    expr->close_sub_query();
    return RC::SUCCESS;
  };

  if (ExprType::SUBQUERY == left_->type()) {
    SubQueryExpression *left_sub_query = static_cast<SubQueryExpression *>(left_.get());
    if (RC::SUCCESS != (rc = get_cell_for_sub_query(left_sub_query, tuple, left_value))) {
      LOG_ERROR("Predicate get left cell for sub_query failed. RC = %d:%s", rc, strrc(rc));
      return rc;
    }
  } else {
    if (RC::SUCCESS != (rc = left_->get_value(tuple, left_value))) {
      LOG_ERROR("Predicate get left cell failed. RC = %d:%s", rc, strrc(rc));
      return rc;
    }
  }

  if (ExprType::SUBQUERY == right_->type()) {
    SubQueryExpression *right_sub_query = static_cast<SubQueryExpression *>(right_.get());
    if (RC::SUCCESS != (rc = get_cell_for_sub_query(right_sub_query, tuple, right_value))) {
      LOG_ERROR("Predicate get right cell for sub_query failed. RC = %d:%s", rc, strrc(rc));
      return rc;
    }
  } else {
    if (RC::SUCCESS != (rc = right_->get_value(tuple, right_value))) {      // 要怎么拿到parent_tuple?
      LOG_ERROR("Predicate get right cell failed. RC = %d:%s", rc, strrc(rc));
      return rc;
    }
  }

  // 0. for is [not] null
  if (CompOp::IS_NULL == comp_) {
    assert(right_value.is_null());
    bool res = left_value.is_null();
    try_get_negtive_value(value);
    value.set_boolean(res);
    return RC::SUCCESS;
  }
  if (CompOp::IS_NOT_NULL == comp_) {
    assert(right_value.is_null());
    bool res = !left_value.is_null();
    try_get_negtive_value(value);
    value.set_boolean(res);
    return RC::SUCCESS;
  }

    // 1. check null
  if (left_value.is_null() || right_value.is_null()) {
    value.set_boolean(false);
    return RC::SUCCESS;
  }

  bool bool_value = false;
  rc = compare_value(left_value, right_value, bool_value);
  if (rc == RC::SUCCESS) {
    try_get_negtive_value(value);
    value.set_boolean(bool_value);
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

RC ConjunctionExpr::init(const std::vector<Table *> &tables, const std::unordered_map<std::string, Table *> &table_map, Db *db) {
  // doing nothing
  return RC::SUCCESS;
}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    try_get_negtive_value(value);
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {      // child全部是ComparisonExpr
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      try_get_negtive_value(value);
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  try_get_negtive_value(value);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
    : arithmetic_type_(type), left_(left), right_(right)
{}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right))
{}

AttrType ArithmeticExpr::value_type() const
{
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::INTS &&
      right_->value_type() == AttrType::INTS &&
      arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }
  
  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  AttrType target_type;
  if (left_value.attr_type() == AttrType::INTS && right_value.attr_type() == AttrType::INTS &&
      arithmetic_type_ != Type::DIV) {
    target_type = AttrType::INTS;
  } else {
    target_type = AttrType::FLOATS;
  }

  switch (arithmetic_type_) {
    case Type::ADD: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() + right_value.get_int());
      } else {
        value.set_float(left_value.get_float() + right_value.get_float());
      }
    } break;

    case Type::SUB: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() - right_value.get_int());
      } else {
        value.set_float(left_value.get_float() - right_value.get_float());
      }
    } break;

    case Type::MUL: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() * right_value.get_int());
      } else {
        value.set_float(left_value.get_float() * right_value.get_float());
      }
    } break;

    case Type::DIV: {
      if (target_type == AttrType::INTS) {
        if (right_value.get_int() == 0) {
          // NOTE: 设置为整数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为整数最大值。
          value.set_int(numeric_limits<int>::max());
          value.set_null();
        } else {
          value.set_int(left_value.get_int() / right_value.get_int());
        }
      } else {
        if (right_value.get_float() > -EPSILON && right_value.get_float() < EPSILON) {
          // NOTE: 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
          value.set_float(numeric_limits<float>::max());
          value.set_null();
        } else {
          value.set_float(left_value.get_float() / right_value.get_float());
        }
      }
    } break;

    case Type::NEGATIVE: {
      if (target_type == AttrType::INTS) {
        value.set_int(-left_value.get_int());
      } else {
        value.set_float(-left_value.get_float());
      }
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  assert(left_value.attr_type() != DATES && right_value.attr_type() != DATES);
  assert(left_value.attr_type() != CHARS && right_value.attr_type() != CHARS);
  if (left_value.is_null() || right_value.is_null()) {
    value.set_null();
    return RC::SUCCESS;
  }

  rc =  calc_value(left_value, right_value, value);
  try_get_negtive_value(value);
  return rc;
}

RC ArithmeticExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

////////////////////////////////////////////////////////////////////////////////

// SubQueryExpression
RC SubQueryExpression::init(const std::vector<Table *> &tables, const std::unordered_map<std::string, Table *> &table_map, Db *db) {
  assert(ExprType::SUBQUERY == type());

  Stmt *tmp_stmt = nullptr;
  RC rc = SelectStmt::create(db, parsed_sql_node_->selection , table_map, tmp_stmt);
  if (RC::SUCCESS != rc) {
    LOG_ERROR("SubQueryExpression Create SelectStmt Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
  }
  sub_stmt_ = static_cast<SelectStmt* >(tmp_stmt);
  return RC::SUCCESS;
}

RC SubQueryExpression::open_sub_query() const
{
  assert(nullptr != physical_oper_);     
  return physical_oper_->open(nullptr);   
}

RC SubQueryExpression::get_value(const Tuple &tuple, Value &final_cell) const
{
  assert(nullptr != physical_oper_);
  physical_oper_->set_parent_tuple(&tuple);  // set parent tuple
  return get_value(final_cell);
}

RC SubQueryExpression::get_value(Value &final_cell) const
{
  RC rc = physical_oper_->next();
  if (RC::RECORD_EOF == rc) {
    final_cell.set_null();
  }
  if (RC::SUCCESS != rc) {
    return rc;
  }
  Tuple *child_tuple = physical_oper_->current_tuple();
  if (nullptr == child_tuple) {
    LOG_WARN("failed to get current record. rc=%s", strrc(rc));
    return RC::INTERNAL;
  }
  rc = child_tuple->cell_at(0, final_cell);  // 返回的tuple一定只有一列
  return rc;
}

RC SubQueryExpression::close_sub_query() const
{
  assert(nullptr != physical_oper_);
  return physical_oper_->close();
}

////////////////////////////////////////////////////////////////////////////////
// AggrFuncType

RC AggrFuncExpression::init(const std::vector<Table *> &tables, const std::unordered_map<std::string, Table *> &table_map, Db *db)
{
  RC rc = RC::SUCCESS;
  if (field_ != nullptr) {
    rc = field_->init(tables, table_map, db);
  } else {
    auto t = tables[0]->table_meta();
    field_ = new FieldExpr(tables[0], tables[0]->table_meta().field(1));
  }
  return rc;
}

RC AggrFuncExpression::get_value(const Tuple &tuple, Value &cell) const 
{
  TupleCellSpec temp(field_->table_name(), field_->field_name(), nullptr, type_);
  RC rc =  tuple.find_cell(temp, cell);
  try_get_negtive_value(cell);
  return rc;
}

void AggrFuncExpression::get_aggrfuncexprs(Expression *expr, std::vector<AggrFuncExpression *> &aggrfunc_exprs) 
{
  switch (expr->type()) {
    case ExprType::AGGRFUNC: {
      // 坑！！！！！卡了一个下午
      // AggrFuncExpression *expr = dynamic_cast<AggrFuncExpression *>(expr);
      // aggrfunc_exprs.emplace_back(expr);

      aggrfunc_exprs.push_back(dynamic_cast<AggrFuncExpression *>(expr));
      auto type = aggrfunc_exprs[0]->type();
      break;
    }
    case ExprType::ARITHMETIC: {
      ArithmeticExpr *arith_expr = dynamic_cast<ArithmeticExpr *>(expr);
      get_aggrfuncexprs(arith_expr->left().get(), aggrfunc_exprs);
      get_aggrfuncexprs(arith_expr->right().get(), aggrfunc_exprs);
      break;
    }
    default:
      break;
  }
  return;
}



////////////////////////////////////////////////////////////////////////////////
// AggrFuncType
RC FuncExpression::get_func_length_value(const Tuple &tuple, Value &final_cell) const
{
  Expression *param_expr = *params_expr_.begin();
  Value param_cell;
  param_expr->get_value(tuple, param_cell);
  // unsupported not chars
  if (param_cell.attr_type() != CHARS) {
    return RC::INTERNAL;
  }
  std::string result = param_cell.get_string();
  final_cell.set_int(result.size());
  return RC::SUCCESS;
}

RC FuncExpression::get_func_round_value(const Tuple &tuple, Value &final_cell) const
{
  if (param_size_ > 1) {
    Expression *param_expr = params_expr_[0];
    Expression *param_expr_precision = params_expr_[1];
    Value param_expr_cell;
    Value param_expr_precision_cell;
    param_expr->get_value(tuple, param_expr_cell);
    param_expr_precision->get_value(tuple, param_expr_precision_cell);
    if (param_expr_cell.attr_type() != FLOATS) {
      return RC::INTERNAL;
    }
    if (param_expr_precision_cell.attr_type() != INTS) {
      return RC::INTERNAL;
    }
    float cell_float = param_expr_cell.get_float();
    int cell_precision = param_expr_precision_cell.get_int();
    auto inner_round = [](float f, int precision) {
      // std::cout << "Before: " << std::setprecision(12) << f << std::endl;
      std::stringstream ss;
      ss << std::fixed << std::setprecision(precision) << f;
      ss >> f;
      // std::cout << "After: " << std::setprecision(12) << f << std::endl;
      return f;
    };
    *(uint32_t *)&cell_float += 1;        // TODO：这行代码的作用
    cell_float = inner_round(cell_float, cell_precision);
    // std::cout << cell_float << std::endl;
    float *result_float = new float(cell_float);
    final_cell.set_float(cell_float);
  } else {
    Expression *param_expr = *params_expr_.begin();
    Value param_expr_cell;
    param_expr->get_value(tuple, param_expr_cell);
    if (param_expr_cell.attr_type() != FLOATS) {
      return RC::INTERNAL;
    }
    float cell_float = param_expr_cell.get_float();
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << cell_float;
    ss >> cell_float;
    final_cell.set_float(cell_float);
  }
  return RC::SUCCESS;
}

RC FuncExpression::get_func_data_format_value(const Tuple &tuple, Value &final_cell) const
{
  Expression *date_expr = params_expr_[0];
  Expression *format_expr = params_expr_[1];
  Value date_expr_cell;
  Value format_expr_cell;
  date_expr->get_value(tuple, date_expr_cell);
  format_expr->get_value(tuple, format_expr_cell);
  if (date_expr_cell.attr_type() != DATES) {
    return RC::INTERNAL;
  }
  if (format_expr_cell.attr_type() != CHARS) {
    return RC::INTERNAL;
  }
  int cell_date = date_expr_cell.get_int();
  std::string cell_format_string = format_expr_cell.get_string();
  const char *cell_format_chars = cell_format_string.c_str();
  std::string result_date_str;
  int year = cell_date / 10000;
  int month = (cell_date / 100) % 100;
  int day = cell_date % 100;
  for (size_t i = 0; i < strlen(cell_format_chars); i++) {
    // A ~ z
    if (65 <= cell_format_chars[i] && cell_format_chars[i] <= 122) {
      switch (cell_format_chars[i]) {
        case 'Y': {
          char tmp[5];
          sprintf(tmp, "%d", year);
          result_date_str += tmp;
          break;
        }
        case 'y': {
          char tmp[5];
          sprintf(tmp, "%d", year % 100);
          if (0 <= (year % 100) && (year % 100) <= 9) {
            result_date_str += "0";
          }
          result_date_str += tmp;
          break;
        }
        case 'M': {
          switch (month) {
            case 1: {
              result_date_str += "January";
              break;
            }
            case 2: {
              result_date_str += "February";
              break;
            }
            case 3: {
              result_date_str += "March";
              break;
            }
            case 4: {
              result_date_str += "April";
              break;
            }
            case 5: {
              result_date_str += "May";
              break;
            }
            case 6: {
              result_date_str += "June";
              break;
            }
            case 7: {
              result_date_str += "July";
              break;
            }
            case 8: {
              result_date_str += "August";
              break;
            }
            case 9: {
              result_date_str += "September";
              break;
            }
            case 10: {
              result_date_str += "October";
              break;
            }
            case 11: {
              result_date_str += "November";
              break;
            }
            case 12: {
              result_date_str += "December";
              break;
            }
            default: {
              return RC::INTERNAL;
              break;
            }
          }
          break;
        }
        case 'm': {
          char tmp[3];
          sprintf(tmp, "%d", month);
          if (0 <= month && month <= 9) {
            result_date_str += "0";
          }
          result_date_str += tmp;
          break;
        }
        case 'D': {
          char tmp[3];
          sprintf(tmp, "%d", day);
          if (10 <= day && day <= 20) {
            result_date_str += tmp;
            result_date_str += "th";
          } else {
            switch (day % 10) {
              case 1: {
                result_date_str += tmp;
                result_date_str += "st";
                break;
              }
              case 2: {
                result_date_str += tmp;
                result_date_str += "nd";
                break;
              }
              case 3: {
                result_date_str += tmp;
                result_date_str += "rd";
                break;
              }
              default: {
                result_date_str += tmp;
                result_date_str += "th";
                break;
              }
            }
          }
          break;
        }
        case 'd': {
          char tmp[3];
          sprintf(tmp, "%d", day);
          if (0 <= day && day <= 9) {
            result_date_str += "0";
          }
          result_date_str += tmp;
          break;
        }
        default: {
          result_date_str += cell_format_chars[i];
          break;
        }
      }
    } else if (cell_format_chars[i] != '%') {
      result_date_str += cell_format_chars[i];
    }
  }
  // std::cout << result_date_str << std::endl;
  final_cell.set_string(result_date_str.c_str(), result_date_str.size());
  return RC::SUCCESS;
}

RC FuncExpression::init(
    const std::vector<Table *> &tables, const std::unordered_map<std::string, Table *> &table_map, Db *db)
{
  RC rc = RC::SUCCESS;
  for (auto expr : params_expr_) {
    rc = expr->init(tables, table_map, db);
  }
  return rc;
}