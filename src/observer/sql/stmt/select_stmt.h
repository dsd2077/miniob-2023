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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <vector>
#include <memory>

#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

// 采用类的前置申明的好处?
class FieldMeta;
class FilterStmt;
class OrderByStmt;
class GroupByStmt;
class Db;
class Table;


/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt 
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override
  {
    return StmtType::SELECT;
  }

public:
  static RC create(Db *db, const SelectSqlNode &select_sql,const std::unordered_map<std::string, Table *> &parent_table_map, Stmt *&stmt);

public:
  const std::vector<Table *> &tables() const { return tables_; }

  const std::vector<Expression *> &projects() const { return query_fields_; }

  OrderByStmt *orderby_stmt() const { return orderby_stmt_; }
  GroupByStmt *groupby_stmt() const { return groupby_stmt_; }
  OrderByStmt *orderby_stmt_for_groupby() const { return orderby_stmt_for_groupby_; }
  FilterStmt *filter_stmt() const { return filter_stmt_; }
  FilterStmt *having_stmt() const { return having_stmt_; }
  FilterStmt *inner_join_filter_stmt() const { return inner_join_filter_stmt_; }

private:
  std::vector<Expression *> query_fields_;     // select_stmt的析构函数会自动释放vector中的指针,但是这个指针交给了project_logical_operator-->project_physical_operator
  std::vector<Table *> tables_;
  FilterStmt * filter_stmt_            = nullptr;
  OrderByStmt *orderby_stmt_           = nullptr;
  FilterStmt * inner_join_filter_stmt_ = nullptr;
  GroupByStmt *groupby_stmt_           = nullptr;
  FilterStmt * having_stmt_            = nullptr;
  OrderByStmt *orderby_stmt_for_groupby_ = nullptr;

  // TODO:
  // HavingStmt *having_stmt_ = nullptr;
  // OrderByStmt *orderby_stmt_for_groupby_ = nullptr;
};
