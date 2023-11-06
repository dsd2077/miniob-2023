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

#include "sql/stmt/update_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"

// UpdateStmt::UpdateStmt(Table *table, FilterStmt *filter_stmt, 
//     std::vector<Value> values, std::vector<std::string> attributes_names)
//     : table_(table), filter_stmt_(filter_stmt), values_(values), attributes_names_(attributes_names)
// {}

UpdateStmt::UpdateStmt(Table *table, std::vector<std::string> &attr_names, std::vector<Expression *> &exprs,
    std::vector<const FieldMeta *> &fields, FilterStmt *filter_stmt)
    : table_(table), attributes_names_(attr_names), exprs_(exprs), fields_(fields), filter_stmt_(filter_stmt)
{}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d",db);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::vector<std::string> attr_names;
  std::vector<Expression *> expressions;
  std::vector<const FieldMeta *> fields;
  const TableMeta &table_meta = table->table_meta();
  for (size_t i = 0; i < update.set_cols.size(); i++) {
    bool field_exist = false;
    std::string attr_name = update.set_cols[i].attribute_name;
    if ("" == attr_name) {
      LOG_WARN("invalid argument. attribute_name=%p", attr_name.c_str());
      return RC::INVALID_ARGUMENT;
    }

    Expression *expr = update.set_cols[i].expr;
    // 找到要更新的属性列
    for (int j = 0; j < table_meta.field_num(); j++) {
      const FieldMeta *field_meta = table_meta.field(j);
      const char *field_name = field_meta->name();
      if (0 != strcmp(field_name, attr_name.c_str())) {
        continue;
      }
      field_exist = true;

      const std::unordered_map<std::string, Table *> table_map;
      const std::vector<Table *> tables;
      RC rc = expr->init(tables, table_map, db);
      if (RC::SUCCESS != rc) {
        LOG_ERROR("init subQueryExpression Failed");
        return rc;
      }
      expressions.emplace_back(expr);
      fields.emplace_back(field_meta);
      break;
    }

    if (!field_exist) {
      LOG_WARN("Field %s.%s is not exist", table_name, attr_name.c_str());
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    attr_names.emplace_back(attr_name);
  }

  // table_map的作用?
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC rc = RC::SUCCESS;
  if (update.conditions != nullptr) {
    rc = FilterStmt::create(db, table, &table_map, update.conditions, filter_stmt);
  }

  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // everything alright
  stmt = new UpdateStmt(table, attr_names, expressions, fields, filter_stmt);
  return RC::SUCCESS;
}
