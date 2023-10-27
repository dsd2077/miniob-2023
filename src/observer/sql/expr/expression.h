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

#pragma once

#include <string.h>
#include <memory>
#include <string>

#include "storage/db/db.h"
#include "storage/field/field.h"
#include "sql/parser/value.h"
#include "common/log/log.h"

class Tuple;
class SelectStmt;
class ProjectPhysicalOperator;

/**
 * @defgroup Expression
 * @brief 表达式
 */

/**
 * @brief 表达式类型
 * @ingroup Expression
 */


/**
 * @brief 表达式的抽象描述
 * @ingroup Expression
 * @details 在SQL的元素中，任何需要得出值的元素都可以使用表达式来描述
 * 比如获取某个字段的值、比较运算、类型转换
 * 当然还有一些当前没有实现的表达式，比如算术运算。
 *
 * 通常表达式的值，是在真实的算子运算过程中，拿到具体的tuple后
 * 才能计算出来真实的值。但是有些表达式可能就表示某一个固定的
 * 值，比如ValueExpr。
 */
class Expression 
{
public:
  Expression() = default;
  virtual ~Expression() = default;

  virtual RC init(const std::vector<Table *> &tables, const std::unordered_map<std::string, Table *> &table_map, Db *db){
    return RC::SUCCESS;
  };

  /**
   * @brief 根据具体的tuple，来计算当前表达式的值。tuple有可能是一个具体某个表的行数据
   */
  virtual RC get_value(const Tuple &tuple, Value &value) const = 0;

  /**
   * @brief 在没有实际运行的情况下，也就是无法获取tuple的情况下，尝试获取表达式的值
   * @details 有些表达式的值是固定的，比如ValueExpr，这种情况下可以直接获取值
   */
  virtual RC try_get_value(Value &value) const
  {
    return RC::UNIMPLENMENT;
  }

  /**
   * @brief 表达式的类型
   * 可以根据表达式类型来转换为具体的子类
   */
  virtual ExprType type() const = 0;

  /**
   * @brief 表达式值的类型
   * @details 一个表达式运算出结果后，只有一个值
   */
  virtual AttrType value_type() const = 0;

  /**
   * @brief 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容
   */
  virtual std::string name() const { return name_; }
  virtual void set_name(std::string name) { name_ = name; }

private:
  std::string  name_;     
};

/**
 * @brief 字段表达式
 * @ingroup Expression
 */
class FieldExpr : public Expression 
{
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field)
  {}
  FieldExpr(const Field &field) : field_(field)
  {}
  FieldExpr(const std::string &field_name, std::string table_name = "")
      :field_name_(field_name), table_name_(table_name)
  {}

  RC init(const std::vector<Table *> &tables, const std::unordered_map<std::string, Table *> &table_map, Db *db=nullptr) override;

  virtual ~FieldExpr() = default;

  ExprType type() const override { return ExprType::FIELD; }
  AttrType value_type() const override { return field_.attr_type(); }

  Field &field() { return field_; }

  const Field &field() const { return field_; }

  const char *table_name() const { return field_.table_name(); }

  const char *field_name() const { return field_.field_name(); }

  RC get_value(const Tuple &tuple, Value &value) const override;


private:
  Field field_;
  std::string table_name_;
  std::string field_name_;
};

/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
class ValueExpr : public Expression 
{
public:
  ValueExpr() = default;
  explicit ValueExpr(const Value &value) : value_(value)
  {}

  virtual ~ValueExpr() = default;

  RC init(const std::vector<Table *> &tables, const std::unordered_map<std::string, Table *> &table_map, Db *db=nullptr) override;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override { value = value_; return RC::SUCCESS; }


  ExprType type() const override { return ExprType::VALUE; }

  AttrType value_type() const override { return value_.attr_type(); }

  void get_value(Value &value) const { value = value_; }

  const Value &get_value() const { return value_; }

  static RC create_expression(const Expression *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp = NO_OP, Db *db = nullptr);

private:
  Value value_;
};

// class AttrExpr : public Expression {
// public:
//   AttrExpr(const std::string &field_name , std::string table_name = "") : field_name_(field_name), table_name_(table_name){}
//   RC get_value(const Tuple &tuple, Value &value) const override;  // 这个函数好像在别的地方实现了

//   ExprType type() const override { return ExprType::ATTR; }

//   AttrType value_type() const override { return CHARS; }

// private:
//   std::string table_name_;
//   std::string field_name_;
// };

/**
 * @brief 类型转换表达式
 * @ingroup Expression
 */
class CastExpr : public Expression 
{
public:
  CastExpr(std::unique_ptr<Expression> child, AttrType cast_type);
  virtual ~CastExpr();

  ExprType type() const override
  {
    return ExprType::EXP_TYPE_NUM;
  }
  RC get_value(const Tuple &tuple, Value &value) const override;

  RC try_get_value(Value &value) const override;

  AttrType value_type() const override { return cast_type_; }

  std::unique_ptr<Expression> &child() { return child_; }

private:
  RC cast(const Value &value, Value &cast_value) const;

private:
  std::unique_ptr<Expression> child_;  ///< 从这个表达式转换
  AttrType cast_type_;  ///< 想要转换成这个类型
};

/**
 * @brief 比较表达式
 * @ingroup Expression
 */
class ComparisonExpr : public Expression 
{
public:
  ComparisonExpr(CompOp comp, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  ComparisonExpr(CompOp comp, Expression *left, Expression *right) : comp_(comp), left_(left), right_(right) {}

  virtual ~ComparisonExpr();

  RC init(const std::vector<Table *> &tables, const std::unordered_map<std::string, Table *> &table_map, Db *db=nullptr) override;

  ExprType type() const override { return ExprType::COMPARISON; }

  RC get_value(const Tuple &tuple, Value &value) const override;

  AttrType value_type() const override { return BOOLEANS; }

  CompOp comp() const { return comp_; }

  std::unique_ptr<Expression> &left()  { return left_;  }
  std::unique_ptr<Expression> &right() { return right_; }

  static RC create_expression(const Expression *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp = NO_OP, Db *db = nullptr);

  /**
   * 尝试在没有tuple的情况下获取当前表达式的值
   * 在优化的时候，可能会使用到
   */
  RC try_get_value(Value &value) const override;

  /**
   * compare the two tuple cells
   * @param value the result of comparison
   */
  RC compare_value(const Value &left, const Value &right, bool &value) const;

private:
  CompOp comp_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

/**
 * @brief 联结表达式
 * @ingroup Expression
 * 多个表达式使用同一种关系(AND或OR)来联结
 * 当前miniob仅有AND操作
 */

class ConjunctionExpr : public Expression 
{
public:
enum class Type
{
  AND,
  OR,
};

public:
  ConjunctionExpr() = default;
  virtual ~ConjunctionExpr() = default;

  RC init(const std::vector<Table *> &tables, const std::unordered_map<std::string, Table *> &table_map, Db *db=nullptr) override;

  ExprType type() const override { return ExprType::CONJUNCTION; }

  AttrType value_type() const override { return BOOLEANS; }

  RC get_value(const Tuple &tuple, Value &value) const override;

  void set_conjunction_type(Type type) { conjunction_type_ = type; }

  Type conjunction_type() const { return conjunction_type_; }
  int condition_size() {return children_.size();};

  void add_condition(Expression* condition) {
    children_.emplace_back(condition);      
  }
  void add_condition(std::unique_ptr<Expression> &condition) {
    children_.push_back(std::move(condition));      
  }

  std::vector<std::unique_ptr<Expression>> &children() { return children_; }

private:
  Type conjunction_type_ = Type::AND;
  std::vector<std::unique_ptr<Expression>> children_;     // 内部都是ComparisonExpr 
};

/**
 * @brief 算术表达式
 * @ingroup Expression
 */
class ArithmeticExpr : public Expression 
{
public:
  enum class Type {
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATIVE,
  };

public:
  ArithmeticExpr(Type type, Expression *left, Expression *right);
  ArithmeticExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ArithmeticExpr() = default;

  ExprType type() const override { return ExprType::ARITHMETIC; }

  AttrType value_type() const override;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override;

  Type arithmetic_type() const { return arithmetic_type_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

private:
  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;
  
private:
  Type arithmetic_type_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

class SubQueryExpression : public Expression {
public:
  SubQueryExpression() = default;
  virtual ~SubQueryExpression() = default;

  SubQueryExpression(ParsedSqlNode *parsed_sql_node): parsed_sql_node_(parsed_sql_node){};

  RC init(const std::vector<Table *> &tables, const std::unordered_map<std::string, Table *> &table_map, Db *db) override;

  ExprType type() const override
  {
    return ExprType::SUBQUERY;
  }
  RC get_value(const Tuple &tuple, Value &value) const override;
  AttrType value_type() const override { return BOOLEANS; }

  void set_sub_query_stmt(SelectStmt *sub_stmt)
  {
    sub_stmt_ = sub_stmt;
  }

  SelectStmt *get_sub_query_stmt() const
  {
    return sub_stmt_;
  }

  void set_sub_query_top_oper(ProjectPhysicalOperator *oper)
  {
    sub_top_oper_ = oper;
  }

  ProjectPhysicalOperator *get_sub_query_top_oper() const
  {
    return sub_top_oper_;
  }

  RC open_sub_query() const;
  RC close_sub_query() const;

  static RC create_expression(const Expression *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp = NO_OP, Db *db = nullptr);

private:
  ParsedSqlNode *parsed_sql_node_ = nullptr;      // 存储select语句的相关信息
  SelectStmt *sub_stmt_ = nullptr;
  ProjectPhysicalOperator *sub_top_oper_ = nullptr;
};

class ListExpression : public Expression {
public:
  ListExpression() = default;

  virtual ~ListExpression() = default;

  ListExpression(std::vector<Value> &values): values_(values){};

  RC get_value(const Tuple &tuple, Value &cell) const override
  {
    return RC::UNIMPLENMENT;
  }

  ExprType type() const override
  {
    return ExprType::SUBLIST;
  }

  AttrType value_type() const override { return values_[0].attr_type(); }

  void set_tuple_cells(Value values[], int value_length)
  {
    // TupleCell tuple_cell;
    // for (int i = 0; i < value_length; i++) {
    //   tuple_cell.set_type(values[i].type);
    //   tuple_cell.set_length(-1);
    //   tuple_cell.set_data((char *)values[i].data);  // maybe null
    //   if (values[i].type == CHARS) {
    //     tuple_cell.set_length(strlen((const char *)values[i].data));
    //   }
    //   tuple_cells_.emplace_back(tuple_cell);
    // }
  }

  const std::vector<Value> get_tuple_cells() const
  {
    return values_;
  }

private:
  std::vector<Value> values_;
};

