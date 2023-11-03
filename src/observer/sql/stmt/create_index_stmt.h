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
// Created by Wangyunlai on 2023/4/25.
//

#pragma once

#include <string>

#include "sql/stmt/stmt.h"

struct CreateIndexSqlNode;
class Table;
class FieldMeta;

/**
 * @brief 创建索引的语句
 * @ingroup Statement
 */
class CreateIndexStmt : public Stmt
{
public:
  CreateIndexStmt(Table *table, std::vector<FieldMeta> &fields_meta, const std::string &index_name)
        : table_(table),
          index_name_(index_name)
  {
    for(int i = 0 ; i < fields_meta.size() ; i ++ ) {
      fields_meta_.emplace_back(fields_meta[i]);
    }
  }

  virtual ~CreateIndexStmt() = default;

  StmtType type() const override { return StmtType::CREATE_INDEX; }

  Table *table() const { return table_; }
  void field_meta(std::vector<FieldMeta> &res) const
  {
    for(int i = 0 ; i < fields_meta_.size() ; i ++ ) {
      res.emplace_back(fields_meta_[i]);
    }
  }
  const std::string &index_name() const { return index_name_; }

public:
  static RC create(Db *db, const CreateIndexSqlNode &create_index, Stmt *&stmt);

private:
  Table *table_ = nullptr;
  // const FieldMeta *field_meta_ = nullptr;
  std::vector<FieldMeta> fields_meta_; // 多列
  std::string index_name_;
};
