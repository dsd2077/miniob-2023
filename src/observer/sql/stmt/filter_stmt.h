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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include <vector>
#include <unordered_map>
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/expression.h"

class Db;
class Table;
class FieldMeta;

/**
 * @brief Filter/谓词/过滤语句
 * @ingroup Statement
 */

class FilterStmt 
{
public:
  FilterStmt() = default;
  ~FilterStmt() = default;

public:
  std::unique_ptr<Expression>& predicate() 
  {
    return predicate_;
  }

  void set_predicate(Expression *predicate) {
    predicate_ = std::unique_ptr<Expression>(predicate);
  }

  // ConjunctionExpr::Type conjunction_type() const { return predicate_->type(); }

  // void set_conjunction_type(ConjunctionExpr::Type type) { type_ = type; }

public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *table_map,
      Expression *conditions, FilterStmt *&stmt);

private:
  std::unique_ptr<Expression> predicate_;   // ConjunctionExpr
};

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field);
