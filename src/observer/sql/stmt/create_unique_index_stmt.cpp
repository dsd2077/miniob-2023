#pragma once

#include "sql/stmt/create_unique_index_stmt.h"
#include "storage/table/table.h"
#include "storage/db/db.h"
#include "common/lang/string.h"
#include "common/log/log.h"

using namespace std;
using namespace common;

RC CreateUniqueIndexStmt::create(Db *db, CreateUniqueIndexSqlNode &create_unique_index, Stmt *&stmt) {

    // 1. 根据relation_name_找表
    stmt = nullptr;

    const char *table_name = create_unique_index.relation_name.c_str();
    // 检查表名和索引名
    if(is_blank(table_name) || is_blank(create_unique_index.index_name.c_str()) || create_unique_index.attributes_names.size() == 0) {
        LOG_WARN("invalid argument. db=%p, table_name=%p, index_name=%s", db, table_name, create_unique_index.index_name.c_str());
        return RC::INVALID_ARGUMENT;
    }
    // 检查每个属性列名
    for(int i = 0 ; i < create_unique_index.attributes_names.size() ; i ++ ) {
        if(is_blank(create_unique_index.attributes_names[i].attribute_name.c_str())) {
            LOG_WARN("invalid argument. db=%p, table_name=%p, index_name=%s, attribute_name=%s", 
                db, table_name, create_unique_index.index_name.c_str(), create_unique_index.attributes_names[i].attribute_name.c_str());
            return RC::INVALID_ARGUMENT;
        }
    }

    // check whether the table exists
    Table *table = db->find_table(table_name);
    if (nullptr == table) {
        LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
        return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    std::vector<std::string> attrs_names;
    for(int i = 0 ; i < create_unique_index.attributes_names.size() ; i ++ ) {
        attrs_names.emplace_back(create_unique_index.attributes_names[i].attribute_name);
    }

    std::vector<FieldMeta> fields;
    table->table_meta().fields_by_attrs(fields, attrs_names);
    if(fields.size() != attrs_names.size()) {   // attrs_names中存在非法列名（表中不存在这些列）
        LOG_WARN("no such field in table. db=%s, table=%s, field name=%s ...", 
             db->name(), table_name, create_unique_index.attributes_names[0].attribute_name.c_str());
        return RC::SCHEMA_FIELD_NOT_EXIST;   
    }

    // 查询所有属性对应的field_meta信息
    // std::vector<FieldMeta> fields_metas;
    // for(int i = 0 ; i < create_unique_index.attributes_names.size() ; i ++ ) {
    //     const FieldMeta *mid_field_meta = table->table_meta().field(create_unique_index.attributes_names[i].c_str());
    //     if(nullptr == mid_field_meta) {
    //         LOG_WARN("no such field in table. db=%s, table=%s, field name=%s", 
    //             db->name(), table_name, create_unique_index.attributes_names[i].c_str());
    //         return RC::SCHEMA_FIELD_NOT_EXIST;   
    //     }
    //     fields_metas.push_back(mid_field_meta);
    // }

    // 检查索引是否已经存在（索引名冲突）
    Index *index = table->find_index(create_unique_index.index_name.c_str());
    if (nullptr != index) {
        LOG_WARN("index with name(%s) already exists. table name=%s", create_unique_index.index_name.c_str(), table_name);
        return RC::SCHEMA_INDEX_NAME_REPEAT;
    }

    stmt = new CreateUniqueIndexStmt(table, fields, create_unique_index.index_name);    // 创建唯一索引unique
    return RC::SUCCESS;
}