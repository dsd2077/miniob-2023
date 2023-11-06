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

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field_meta.h"
#include <string>

class Table;
class FilterStmt;

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt 
{
public:
  UpdateStmt() = default;
  UpdateStmt(Table *table, FilterStmt *filter_stmt, std::vector<Value> values, std::vector<std::string> attributes_names);
  UpdateStmt(Table *table, std::vector<std::string> &attr_names, std::vector<Expression *> &exprs,
      std::vector<const FieldMeta *> &fields, FilterStmt *filter_stmt);

  StmtType type() const override
  {
    return StmtType::UPDATE;
  }

  FilterStmt *filter_stmt() const
  {
    return filter_stmt_;
  }

public:
  static RC create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt);

public:
  Table *table() const
  {
    return table_;
  }

  void attributes_names(std::vector<std::string> &res) 
  {
    for(int i = 0 ; i < attributes_names_.size() ; i ++ ) {
      res.emplace_back(attributes_names_[i]);
    }
  }
  std::vector<Expression *> &exprs() { return exprs_; }
  std::vector<const FieldMeta *> & fields() { return fields_; }
  std::vector<std::string> &attributes_names() {return attributes_names_; }

private:
  Table *table_ = nullptr;
  FilterStmt *filter_stmt_ = nullptr;
  // Value value_;
  // std::string attribute_name_;
  std::vector<Expression *> exprs_;
  std::vector<const FieldMeta *> fields_;
  std::vector<std::string> attributes_names_;
};
