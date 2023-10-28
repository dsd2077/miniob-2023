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
#include "src/observer/sql/stmt/select_stmt.h"
#include "storage/db/db.h"
#include <regex>

using namespace std;

RC FieldExpr::get_value(const Tuple &tuple, Value &value) const
{
  return tuple.find_cell(TupleCellSpec(table_name(), field_name()), value);
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

    // TODO:表别名
    // if (table_name_ != std::string(table->name())) {
    //   if (tables.size() != 1) {
    //     set_name(table_name_ + "." + field_name_);
    //   }
    // }

    return RC::SUCCESS;
  }
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
  rc = right_->init(tables, table_map, db);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("BinaryExpression Create Right Expression Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
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

  // 0. for is [not] null
  if (CompOp::IS_NULL == comp_) {
    assert(right_value.is_null());
    bool res = left_value.is_null();
    value.set_boolean(res);
    return RC::SUCCESS;
  }
  if (CompOp::IS_NOT_NULL == comp_) {
    assert(right_value.is_null());
    bool res = !left_value.is_null();
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
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
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

  const AttrType target_type = value_type();

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
        } else {
          value.set_int(left_value.get_int() / right_value.get_int());
        }
      } else {
        if (right_value.get_float() > -EPSILON && right_value.get_float() < EPSILON) {
          // NOTE: 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
          value.set_float(numeric_limits<float>::max());
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
  return calc_value(left_value, right_value, value);
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
  // TODO:这一步在做什么？——暂时先不考虑
  // switch (comp) {
  //   case EXISTS_OP:
  //   case NOT_EXISTS:
  //     break;
  //   default: {
  //     if (((SelectStmt *)tmp_stmt)->projects().size() != 1) {      
  //       return RC::SQL_SYNTAX;
  //     }
  //     break;
  //   }
  sub_stmt_ = static_cast<SelectStmt* >(tmp_stmt);
  return RC::SUCCESS;
}

RC SubQueryExpression::open_sub_query() const
{
  assert(nullptr != sub_top_oper_);
  return sub_top_oper_->open(nullptr);   // TODO:
}

RC SubQueryExpression::get_value(const Tuple &tuple, Value &final_cell) const
{
  assert(nullptr != sub_top_oper_);
  sub_top_oper_->set_parent_tuple(&tuple);  // set parent tuple
  return get_value(final_cell);
}

RC SubQueryExpression::get_value(Value &final_cell) const
{
  RC rc = sub_top_oper_->next();
  if (RC::RECORD_EOF == rc) {
    final_cell.set_null();
  }
  if (RC::SUCCESS != rc) {
    return rc;
  }
  Tuple *child_tuple = sub_top_oper_->current_tuple();
  if (nullptr == child_tuple) {
    LOG_WARN("failed to get current record. rc=%s", strrc(rc));
    return RC::INTERNAL;
  }
  rc = child_tuple->cell_at(0, final_cell);  // only need the first cell
  return rc;
}

RC SubQueryExpression::close_sub_query() const
{
  assert(nullptr != sub_top_oper_);
  return sub_top_oper_->close();
}