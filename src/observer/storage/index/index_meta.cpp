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
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");

// RC IndexMeta::init(const char *name, const FieldMeta &field)
// {
//   if (common::is_blank(name)) {
//     LOG_ERROR("Failed to init index, name is empty.");
//     return RC::INVALID_ARGUMENT;
//   }

//   name_ = name;
//   field_ = field.name();
//   return RC::SUCCESS;
// }

RC IndexMeta::init(const char *name, std::vector<FieldMeta> &fields)
{
  if(common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }
  name_ = name;
  for(int i = 0 ; i < fields.size() ; i ++ ) {
    multi_fields_.emplace_back(fields[i].name());
    // multi_fields_[i] = fields[i].name();
  }
  return RC::SUCCESS;
}

void IndexMeta::set_type(enum IndexType type)
{
  index_type_ = type;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME] = name_;
  std::string fields_names_str = "";
  for(int i = 0 ; i < multi_fields_.size() ; i ++ ) {
    if(i > 0) {
      fields_names_str += ",";
    }
    fields_names_str += multi_fields_[i];
  }
  json_value[FIELD_FIELD_NAME] = fields_names_str;  // 多列
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!field_value.isString()) {
    LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
        name_value.asCString(),
        field_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  const char *fields_names_str = field_value.toStyledString().c_str();
  int len = strlen(fields_names_str);
  std::string field_name = "";
  std::vector<std::string> fields_names;
  std::vector<FieldMeta> fields_metas;
  for(int i = 0 ; i < len ; i ++ ) {
    if(fields_names_str[i] == ',') {
      fields_names.emplace_back(field_name);
      field_name = "";
    }
    field_name += fields_names_str[i];
  }

  table.fields_by_attrs(fields_metas, fields_names);  // 找出字段元信息
  // const FieldMeta *field = table.field(field_value.asCString());
  if (fields_metas.size() == 0 || fields_metas.size() < fields_names.size()) {
    // LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
    LOG_ERROR("Deserialize index [%s]: fields lack.");
    return RC::SCHEMA_FIELD_MISSING;
  }

  return index.init(name_value.asCString(), fields_metas);
}

const char *IndexMeta::name() const
{
  return name_.c_str();
}

// const char *IndexMeta::field() const
// {
//   return field_.c_str();
// }

// 多列索引的列名
void IndexMeta::fields(std::vector<std::string> &fields_names) const
{
  for(int i = 0 ; i < multi_fields_.size() ; i ++ ) {
    fields_names.emplace_back(multi_fields_[i]);
  } 
}

void IndexMeta::desc(std::ostream &os) const
{
  os << "index name=" << name_ << ", fields=";
  for(int i = 0 ; i < multi_fields_.size() ; i ++ ) {
    if(i > 0) {
      os << ",";
    }
    os << multi_fields_[i];
  }
}