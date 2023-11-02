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
#include "sql/parser/parse_defs.h"
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

static void wildcard_fields(Table *table, std::vector<Expression*> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    if (table_meta.field(i)->visible()) {
      field_metas.emplace_back(new FieldExpr(table, table_meta.field(i)));
    }
  }
}

void gen_project_name(const Expression *expr, bool is_single_table, std::string &result_name)
{

  if (!expr->name().empty()) {
    result_name = expr->name();
    return;
  }

  // if (expr->with_brace()) {
  //   result_name += '(';
  // }
  switch (expr->type()) {
    case ExprType::FIELD: {
      FieldExpr *fexpr = (FieldExpr *)expr;
      const Field &field = fexpr->field();
      if (!is_single_table) {
        result_name += std::string(field.table_name()) + '.' + std::string(field.field_name());
      } else {
        result_name += std::string(field.field_name());
      }
      break;
    }
    case ExprType::VALUE: {
      ValueExpr *vexpr = (ValueExpr *)expr;
      Value cell;
      vexpr->get_value(cell);
      std::stringstream ss;
      std::string str = cell.to_string();
      result_name += str;
      break;
    }
    // case ExprType::ARITHMETIC: {
    //   ArithmeticExpr *bexpr = (ArithmeticExpr *)expr;
    //   if (bexpr->is_minus()) {
    //     result_name += '-';
    //   } else {
    //     gen_project_name(bexpr->get_left(), is_single_table, result_name);
    //     result_name += bexpr->get_op_char();
    //   }
    //   gen_project_name(bexpr->get_right(), is_single_table, result_name);
    //   break;
    // }
    case ExprType::AGGRFUNC: {
      AggrFuncExpression *afexpr = (AggrFuncExpression *)expr;
      result_name += afexpr->get_func_name();
      result_name += '(';
      if (afexpr->is_param_value()) {
        gen_project_name(afexpr->get_param_value(), is_single_table, result_name);
      } else {
        const Field &field = afexpr->field();
        if (!is_single_table) {   // 多表输出必须使用tablename.fieldname
          result_name += std::string(field.table_name()) + '.' + std::string(field.field_name());
        } else {
          result_name += std::string(field.field_name());
        }
      }
      result_name += ')';
      break;
    }
    // case ExprType::FUNC: {
    //   FuncExpression *fexpr = (FuncExpression *)expr;
    //   switch (fexpr->get_func_type()) {
    //     case FUNC_LENGTH: {
    //       result_name += "length(";
    //       gen_project_name(fexpr->get_params()[0], is_single_table, result_name);
    //       result_name += ")";
    //       break;
    //     }
    //     case FUNC_ROUND: {
    //       result_name += "round(";
    //       if (fexpr->get_param_size() > 1) {
    //         gen_project_name(fexpr->get_params()[0], is_single_table, result_name);
    //         result_name += ",";
    //         gen_project_name(fexpr->get_params()[1], is_single_table, result_name);
    //       } else {
    //         gen_project_name(fexpr->get_params()[0], is_single_table, result_name);
    //       }
    //       result_name += ")";
    //       break;
    //     }
    //     case FUNC_DATE_FORMAT: {
    //       result_name += "date_format(";
    //       gen_project_name(fexpr->get_params()[0], is_single_table, result_name);
    //       result_name += ",";
    //       gen_project_name(fexpr->get_params()[1], is_single_table, result_name);
    //       result_name += ")";
    //       break;
    //     }
    //     default:
    //       break;
    //   }
    // }
    default:
      break;
  }
  // if (expr->with_brace()) {
  //   result_name += ')';
  // }
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
  std::unordered_map<Table *, std::string> alias_map;

  std::vector<Relation>relations(select_sql.relations);
  // 存在inner join,将inner join表拿出来
  if (!select_sql.inner_join_clauses.empty()) {
    for (auto &inner_join_node : select_sql.inner_join_clauses) {
      relations.emplace_back(inner_join_node.relation_name);
    }
  }

  for (size_t i = 0; i < relations.size(); i++) {
    std::string table_name = relations[i].relation_name;
    std::string alias_name = relations[i].alias;
    if ("" == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name.c_str());
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name.c_str());
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    // duplicate alias
    if ("" != alias_name) {
      if (0 != table_map.count(alias_name)) {
        return RC::SQL_SYNTAX;
      }
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
    if ("" != alias_name) {
      table_map.insert(std::pair<std::string, Table *>(alias_name, table));
      alias_map.insert(std::pair<Table *, std::string>(table, alias_name));
    }
  }

  // collect query fields in `select` statement
  std::vector<Expression *> query_fields;
  for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];
    // select * from 
    // 取出所有表的属性
    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      for (Table *table : tables) {     
        // wildcard_fields(table, query_fields);
        auto it2 = alias_map.find(table);
        std::string table_name = table->name();
        if (it2 != alias_map.end()) {
          table_name = it2->second;
        }
        const TableMeta &table_meta = table->table_meta();
        const int field_num = table_meta.field_num();
        for (int i = table_meta.sys_field_num(); i < field_num; i++) {
          if (table_meta.field(i)->visible()) {
            FieldExpr *tmp_field = new FieldExpr(table, table_meta.field(i));
            std::string alias;
            if (tables.size() == 1) {
              alias = std::string(table_meta.field(i)->name());
            } else {
              alias = std::string(table_name) + '.' + std::string(table_meta.field(i)->name());
            }
            tmp_field->set_name(alias);
            tmp_field->init(tables, table_map);
            query_fields.emplace_back(tmp_field);
          }
        }
      }
    // select tablename.* from 
    } else if (!common::is_blank(relation_attr.relation_name.c_str()) && 
              0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      const char *table_name = relation_attr.relation_name.c_str();
      if (0 == strcmp(table_name, "*")) {   // *.*
        for (Table *table : tables) {
          wildcard_fields(table, query_fields);
        }
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        Table *table = iter->second;
        const TableMeta &table_meta = table->table_meta();
        const int field_num = table_meta.field_num();
        for (int i = table_meta.sys_field_num(); i < field_num; i++) {
          if (table_meta.field(i)->visible()) {
            FieldExpr *tmp_field = new FieldExpr(table, table_meta.field(i));
            std::string alias;
            if (tables.size() == 1) {
              alias = std::string(table_meta.field(i)->name());
            } else {
              alias = std::string(table_name) + '.' + std::string(table_meta.field(i)->name());
            }
            tmp_field->set_name(alias);
            query_fields.emplace_back(tmp_field);
          }
        }
      }
    } else {    // expression
      Expression *expr = relation_attr.expr;
      RC rc = expr->init(tables, table_map, db);      
      if (rc != RC::SUCCESS) {
        return rc;
      }

      if (relation_attr.alias != "") {
        expr->set_name(relation_attr.alias);
      } else {
        std::string project_name;
        gen_project_name(expr, tables.size() == 1, project_name);
        expr->set_name(project_name);
      }
      query_fields.emplace_back(expr);
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
    auto ty = inner_join_node.conditions->type();     
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
    rc = FilterStmt::create(db, default_table, &temp_table_map, select_sql.conditions, filter_stmt);
  }
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // 创建order by子句
  OrderByStmt *orderby_stmt = nullptr;
  if (!select_sql.order_by_nodes.empty()) {
    rc = OrderByStmt::create(db, default_table, &table_map, select_sql.order_by_nodes, orderby_stmt);
  }
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
