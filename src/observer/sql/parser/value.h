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

#include <cmath>
#include <string>
#include <vector>

/**
 * @brief 属性的类型
 * 
 */
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
  bool is_null() const { 
    if (AttrType::NULLS == attr_type_ || (AttrType::CHARS == attr_type_ && str_value_ == "NULL")) {
      return true;
    }
    return false;
  }

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

  // check_null仅用于从磁盘中读取数据时，作为NULL的判定标准
  void check_null() {
    bool is_null = false;
    switch (attr_type_) {
      case FLOATS: {
        if (std::abs(get_float() - 16777216) < 1e-6) {
          is_null = true;
        }
      } break;
      case CHARS: {
        if (str_value_ == "NULL") {
          is_null = true;
        }
      } break;
      default: {
        if (get_int() == 16777216) {
          is_null = true;
        } 
      }
    }
    if (is_null) {
      set_null();
    }
  }

  void set_null() {
    str_value_       = "NULL";
    int_value_       = 16777216;
    float_value_ = 16777216;
    this->attr_type_ = AttrType::NULLS;
  }

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

  static const Value &min(const Value &a, const Value &b)
  {
    if (a.is_null()) {
      return b;  // even if b is also null
    }
    return a.compare(b) <= 0 ? a : b;
  }

  static const Value &max(const Value &a, const Value &b)
  {
    if (a.is_null()) {
      return b;  // even if b is also null
    }
    return a.compare(b) >= 0 ? a : b;
  }
  bool operator!=(const Value &other) const
  {
    return 0 != compare(other);
  }

  bool operator<(const Value &other) const
  {
    return 0 > compare(other);
  }

  bool operator>(const Value &other) const
  {
    return 0 < compare(other);
  }

  static const Value add(const Value &left, const Value &right);
  static const Value sub(const Value &left, const Value &right);
  static const Value mul(const Value &left, const Value &right);
  static const Value div(const Value &left, const Value &right);

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
  void set_negtive();

private:
  AttrType attr_type_ = UNDEFINED;
  int length_ = 0;

  int         int_value_;
  float       float_value_;
  bool        bool_value_;
  std::string str_value_;
};