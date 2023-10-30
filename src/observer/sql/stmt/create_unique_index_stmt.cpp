#pragma once

#include "sql/stmt/create_unique_index_stmt.h"
#include "storage/table/table.h"
#include "storage/db/db.h"
#include "common/lang/string.h"
#include "common/log/log.h"

using namespace std;
using namespace common;

RC CreateUniqueIndexStmt::create_stmt(Db *db, CreateUniqueIndexSqlNode &create_unique_index, Stmt *&stmt) {

    // 1. 根据relation_name_找表
    stmt = nullptr;

    const char *table_name = create_unique_index.relation_name.c_str();
    // 检查表名和索引名
    if(is_blank(table_name) || is_blank(create_unique_index.index_name.c_str())) {
        LOG_WARN("invalid argument. db=%p, table_name=%p, index_name=%s", db, table_name, create_unique_index.index_name.c_str());
        return RC::INVALID_ARGUMENT;
    }
    // 检查每个属性列名
    for(int i = 0 ; i < create_unique_index.attributes_names.size() ; i ++ ) {
        if(is_blank(create_unique_index.attributes_names[i].c_str())) {
            LOG_WARN("invalid argument. db=%p, table_name=%p, index_name=%s, attribute_name=%s", 
                db, table_name, create_unique_index.index_name.c_str(), create_unique_index.attributes_names[i].c_str());
            return RC::INVALID_ARGUMENT;
        }
    }

    // check whether the table exists
    Table *table = db->find_table(table_name);
    if (nullptr == table) {
        LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
        return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    // 查询所有属性对应的field_meta信息
    std::vector<const FieldMeta*> fields_metas;
    for(int i = 0 ; i < create_unique_index.attributes_names.size() ; i ++ ) {
        const FieldMeta *mid_field_meta = table->table_meta().field(create_unique_index.attributes_names[i].c_str());
        if(nullptr == mid_field_meta) {
            LOG_WARN("no such field in table. db=%s, table=%s, field name=%s", 
                db->name(), table_name, create_unique_index.attributes_names[i].c_str());
            return RC::SCHEMA_FIELD_NOT_EXIST;   
        }
        fields_metas.push_back(mid_field_meta);
    }

    // 检查索引是否已经存在（索引名冲突）
    Index *index = table->find_index(create_unique_index.index_name.c_str());
    if (nullptr != index) {
        LOG_WARN("index with name(%s) already exists. table name=%s", create_unique_index.index_name.c_str(), table_name);
        return RC::SCHEMA_INDEX_NAME_REPEAT;
    }

    stmt = new CreateUniqueIndexStmt(table, fields_metas, create_unique_index.index_name);
    return RC::SUCCESS;
}