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
// Created by Wangyunlai on 2021/5/12.
//

#pragma once

#include <string>
#include <vector>

#include "common/rc.h"

class TableMeta;
class FieldMeta;

namespace Json {
class Value;
}  // namespace Json

enum IndexType{
  COMMON_INDEX, // 普通索引
  UNIQUE_INDEX, // 唯一索引
};

/**
 * @brief 描述一个索引
 * @ingroup Index
 * @details 一个索引包含了表的哪些字段，索引的名称等。
 * 如果以后实现了多种类型的索引，还需要记录索引的类型，对应类型的一些元数据等
 */
class IndexMeta 
{
public:
  IndexMeta() = default;

  // RC init(const char *name, const FieldMeta &field);
  RC init(const char *name, std::vector<FieldMeta> &fields); // 重载初始化函数，适应多列场景
  void set_type(enum IndexType type);   // 设置索引类型

public:
  const char *name() const;
  // const char *field() const;
  void fields(std::vector<std::string> &fields_names) const;  // 多列索引的索引名给外部

  void desc(std::ostream &os) const;

public:
  void to_json(Json::Value &json_value) const;
  static RC from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index);

protected:
  std::string name_;   // index's name
  enum IndexType index_type_ = COMMON_INDEX; // index类型，默认是COMMON_INDEX
  std::vector<std::string> multi_fields_; // 多列索引的所有列名，T10，T11涉及到隐式多列索引，这里先暂时不记录类型
};
