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
// Created by Wangyunlai 2023/6/27
//

#pragma once

#include <string>
#include <vector>

/**
 * @brief 属性的类型
 * 
 */
 // TODO:语法解析如何将值的类型与AttrType联系起来的？最关键的问题，这个问题解决了，就可以回去睡觉了。
enum AttrType
{
  UNDEFINED,
  CHARS,          ///< 字符串类型
  INTS,           ///< 整数类型(4字节)
  DATES,          /// 坑 DATES必须在FLOATS之前
  FLOATS,         ///< 浮点数类型(4字节)
  BOOLEANS,       ///< boolean类型，当前不是由parser解析出来的，是程序内部使用的
  NULLS,
};

const char *attr_type_to_string(AttrType type);
AttrType attr_type_from_string(const char *s);

/**
 * @brief 属性的值
 * 
 */
class Value 
{
public:
  Value() = default;

  Value(AttrType attr_type, char *data, int length = 4) : attr_type_(attr_type)
  {
    this->set_data(data, length);
  }

  explicit Value(int val);
  explicit Value(float val);
  explicit Value(bool val);
  explicit Value(const char *s, int len = 0, bool is_date = false);

  Value(const Value &other) = default;
  Value &operator=(const Value &other) = default;

  void set_type(AttrType type)
  {
    this->attr_type_ = type;
  }
  void set_data(char *data, int length);
  void set_data(const char *data, int length)
  {
    this->set_data(const_cast<char *>(data), length);
  }
  void set_int(int val);
  void set_float(float val);
  void set_boolean(bool val);
  void set_string(const char *s, int len = 0);
  void set_date(const char *s);
  void set_date(int date);
  void set_value(const Value &value);
  bool is_null() const { return AttrType::NULLS == attr_type_; }

  bool in_cells(const std::vector<Value> &cells) const
  {
    for (auto &cell : cells) {
      if (compare(cell) == 0) {
        return true;
      }
    }
    return false;
  }

  // return false if is_null and null in cells
  bool not_in_cells(const std::vector<Value> &cells) const
  {
    for (auto &cell : cells) {
      if (compare(cell) == 0) {
        return false;
      }
    }
    return true;
  }

  void set_null() { this->attr_type_ = AttrType::NULLS; }

  std::string to_string() const;

  int compare(const Value &other) const;

  const char *data() const;
  int length() const
  {
    return length_;
  }

  AttrType attr_type() const
  {
    return attr_type_;
  }

public:
  /**
   * 获取对应的值
   * 如果当前的类型与期望获取的类型不符，就会执行转换操作
   */
  int get_int() const;
  float get_float() const;
  std::string get_string() const;
  bool get_boolean() const;
  bool check_date(int y, int m, int d); 

private:
  AttrType attr_type_ = UNDEFINED;
  int length_ = 0;

  union {
    int int_value_;
    float float_value_;
    bool bool_value_;
    int date_value_;
  } num_value_;
  std::string str_value_;
};