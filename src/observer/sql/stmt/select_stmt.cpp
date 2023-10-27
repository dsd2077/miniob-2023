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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/order_by_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <cassert>

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, const std::unordered_map<std::string, Table *> &parent_table_map, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;

  std::vector<std::string>relations(select_sql.relations);
  // 存在inner join,需要将inner join表拿出来
  if (!select_sql.inner_join_clauses.empty()) {
    for (auto &inner_join_node : select_sql.inner_join_clauses) {
      relations.emplace_back(inner_join_node.relation_name);
    }
  }

  for (size_t i = 0; i < relations.size(); i++) {
    const char *table_name = relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

  // collect query fields in `select` statement
  std::vector<Field> query_fields;
  for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];
    // select * from 
    // 取出所有表的属性
    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      for (Table *table : tables) {     
        wildcard_fields(table, query_fields);
      }
    } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();
      // select *.* from 为啥会有这种情况？
      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          wildcard_fields(table, query_fields);
        }
      } else { // select table.attr from
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {   // select tablename.* from
          wildcard_fields(table, query_fields);
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          query_fields.push_back(Field(table, field_meta));
        }
      }
    } else {    // select attr from...
      if (tables.size() != 1) {     // 只有一张表时才能直接取字段，否则必须通过tablename.attr
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      query_fields.push_back(Field(table, field_meta));
    }
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  // default_table的作用:
  // 当选择的属性不提供表名时，从默认表中选取（也就是只有一张表时才能那么做）
  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // 创建inner_join FilterStmt
  RC rc = RC::SUCCESS;
  std::unordered_map<std::string, Table *> temp_table_map = table_map;
  temp_table_map.insert(parent_table_map.begin(), parent_table_map.end());      
  FilterStmt *inner_join_filter_stmt = nullptr;

  // 将所有inner join子句中的条件聚集到一个ConjunctionExpr中
  ConjunctionExpr *inner_join_conditions = nullptr;
  for (int i = 0; i < select_sql.inner_join_clauses.size(); i++) {
    auto inner_join_node = select_sql.inner_join_clauses[i];
    if (inner_join_node.conditions == nullptr) continue;
    auto ty = inner_join_node.conditions->type();     // 不是空指针，又拿不到type?
    ConjunctionExpr *temp = dynamic_cast<ConjunctionExpr *>(inner_join_node.conditions);
    assert(temp != nullptr);
    if (inner_join_conditions == nullptr) {
      inner_join_conditions = temp;
      continue;
    }
    for (auto &expr : temp->children()) {
      inner_join_conditions->add_condition(expr);
    }
  }
  if (inner_join_conditions != nullptr) {
    rc = FilterStmt::create(db, default_table, &temp_table_map, inner_join_conditions, inner_join_filter_stmt);
  }
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct inner join filter stmt");
    return rc;
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  if (select_sql.conditions != nullptr) {
    rc = FilterStmt::create(db, default_table, &table_map, select_sql.conditions, filter_stmt);
  }
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // 创建order by子句
  OrderByStmt *orderby_stmt = nullptr;
  rc = OrderByStmt::create(db, default_table, &table_map, select_sql.order_by_nodes, orderby_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct order by stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->inner_join_filter_stmt_ = inner_join_filter_stmt;
  select_stmt->orderby_stmt_ = orderby_stmt;
  stmt = select_stmt;
  return RC::SUCCESS;
}
