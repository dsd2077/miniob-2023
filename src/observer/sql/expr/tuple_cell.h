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
// Created by WangYunlai on 2022/6/7.
//

#pragma once

#include <cassert>
#include <iostream>
#include "storage/table/table.h"
#include "storage/field/field_meta.h"

class TupleCellSpec
{
public:
  TupleCellSpec(const char *table_name, const char *field_name,const char *alias = nullptr, AggrFuncType aggr_type = AggrFuncType::AGGR_FUNC_TYPE_NUM);
  TupleCellSpec(const char *alias);

  const char *table_name() const
  {
    return table_name_.c_str();
  }
  const char *field_name() const
  {
    return field_name_.c_str();
  }
  const char *alias() const
  {
    return alias_.c_str();
  }

  bool with_aggr() const { return aggr_type_ >= 0 && aggr_type_ < AggrFuncType::AGGR_FUNC_TYPE_NUM; }

  AggrFuncType get_aggr_type() const
  {
    assert(with_aggr());
    return aggr_type_;
  }

  bool equal(const TupleCellSpec &other) const
  {
    return table_name_ == other.table_name_ && field_name_ == other.field_name_ && aggr_type_ == other.aggr_type_;
  }

  bool equal_with_aggr_type(const TupleCellSpec &other) const { return equal(other) && aggr_type_ == other.aggr_type_; }

private:
  std::string table_name_;
  std::string field_name_;
  std::string alias_;
  AggrFuncType aggr_type_ = AggrFuncType::AGGR_FUNC_TYPE_NUM;
};
