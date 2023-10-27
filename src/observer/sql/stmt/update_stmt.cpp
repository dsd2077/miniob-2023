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
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"

UpdateStmt::UpdateStmt(Table *table, FilterStmt *filter_stmt, Value value, std::string attribute_name)
    : table_(table), filter_stmt_(filter_stmt), value_(value), attribute_name_(attribute_name)
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

  // check the fields number
  Value value = update.value;
  const TableMeta &table_meta = table->table_meta();

  // check fields type
  // 要根据属性的名字取获取对应的field_meta
  const FieldMeta *field_meta = table_meta.field(update.attribute_name.c_str());
  if (nullptr == field_meta) {
    LOG_WARN("field =%s not exist in table=%s", update.attribute_name.c_str(), table_name);
    return RC::FILE_NOT_EXIST;
  }
  const AttrType field_type = field_meta->type();
  const AttrType value_type = value.attr_type();
  if (field_type == DATES && !common::is_valid_date(value.get_int())) {
    return RC::INVALID_ARGUMENT;
  }
  if (field_type != value_type) {
    LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
          table_name, field_meta->name(), field_type, value_type);
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  // table_map的作用?
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(
      db, table, &table_map, update.conditions, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // everything alright
  stmt = new UpdateStmt(table, filter_stmt, value, update.attribute_name);
  return RC::SUCCESS;
}
