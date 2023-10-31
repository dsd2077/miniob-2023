/**
 * T11: 创建唯一索引的statement
*/

#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"

struct CreateUniqueIndexSqlNode;
class Table;
class FieldMeta;

class CreateUniqueIndexStmt: public Stmt
{
public:
    CreateUniqueIndexStmt(Table *table, std::vector<const FieldMeta*> fields_metas, const std::string &index_name)
            :table_(table),
            fields_metas_(fields_metas),
            index_name_(index_name)
    {}

    virtual ~CreateUniqueIndexStmt() = default;

    StmtType type() const override { return StmtType::CREATE_UNIQUE_INDEX; }

    Table *table() const { return table_; }
    void fields_metas(std::vector<const FieldMeta *> &res) const { 
        for(int i = 0 ; i < fields_metas_.size() ; i ++ ) {
            res.push_back(fields_metas_[i]);
        }
    }
    const std::string &index_name() const { return index_name_;}

public:
    static RC create_stmt(Db *db, CreateUniqueIndexSqlNode &sql_node, Stmt *&stmt);

private:
    Table *table_ = nullptr;
    std::vector<const FieldMeta*> fields_metas_;
    std::string index_name_;
};