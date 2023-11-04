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

#include "common/rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <cassert>

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *table_map,
  Expression *conditions, FilterStmt *&stmt)
{
RC rc = RC::SUCCESS;
  ConjunctionExpr* conjunction_expr = dynamic_cast<ConjunctionExpr*>(conditions);
  assert(conditions != nullptr);

  if (conjunction_expr->condition_size() == 0) return rc;

  FilterStmt *tmp_stmt = new FilterStmt();

  for (auto &expr : conjunction_expr->children()) {
    // 初始化子表达式
    rc = expr->init(std::vector<Table *>{default_table}, *table_map, db);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to init expression");
      return rc;
    }
  }
  // 根表达式的所有权交给filter_stmt,如果conjunction_expr中有子查询表达式，
  // 在为子表达式创建filter_stmt时会将子表达式的所有权转移给另外一个filter_stmt
  tmp_stmt->set_predicate(conjunction_expr);      

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(std::string(attr.relation_name));
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}