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
// Created by Meiyi
//

#pragma once

#include <stddef.h>
#include <memory>
#include <vector>
#include <string>

#include "sql/parser/value.h"

class Expression;
/**
 * @defgroup SQLParser SQL Parser 
 */

/**
 * @brief 描述一个属性
 * @ingroup SQLParser
 * @details 属性，或者说字段(column, field)
 * Rel -> Relation
 * Attr -> Attribute
 */
struct RelAttrSqlNode
{
  std::string relation_name = "";   ///< relation name (may be NULL) 表名
  std::string attribute_name = "";  ///< attribute name              属性名
  Expression *  expr = nullptr;          /// 聚集函数 
  std::string alias = "";
};

struct Relation {
  std::string relation_name;
  std::string alias;
};

struct  RelAttr{
  std::string relation_name;   // relation name (may be NULL) 表名
  std::string attribute_name;  // attribute name              属性名
};

// class Expression;

/**
 * @brief 描述比较运算符
 * @ingroup SQLParser
 */
// 加_OP是防止关键字冲突
typedef enum {
  EQUAL_TO,     //"="            0
  LESS_EQUAL,   //"<="           1
  NOT_EQUAL,    //"<>"           2
  LESS_THAN,    //"<"            3
  GREAT_EQUAL,  //">="           4
  GREAT_THAN,   //">"            5
  LIKE_OP,      //"like"         6
  NOT_LIKE_OP,  //"not like"     7
  IS_NULL,      //"is null"      8
  IS_NOT_NULL,  //"is not null"  9
  IN_OP,        // sub_query IN      10
  NOT_IN,       // sub_query NOT IN  11
  EXISTS_OP,    // sub_query EXISTS  12
  NOT_EXISTS,   // sub_query NOT EXISTS  13
  AND_OP,       // condition and condition 14
  OR_OP,        // condition or condition 15
  NO_OP
} CompOp;

enum class ExprType 
{
  NONE,
  STAR,         ///< 星号，表示所有字段
  UNARY,        /// 单目表达式
  ATTR,         /// 属性字段，保存属性的表名和字段名
  FIELD,        ///< 字段。在实际执行时，根据行数据内容提取对应字段的值
  VALUE,        ///< 常量值
  CAST,         ///< 需要做类型转换的表达式
  COMPARISON,   ///< 需要做比较的表达式
  CONJUNCTION,  ///< 多个表达式使用同一种关系(AND或OR)来联结,用CONJUNCTION来存储where的所有条件
  ARITHMETIC,   ///< 算术运算
  AGGRFUNC,     /// 集合函数
  SUBQUERY,     ///子查询
  SUBLIST,      ///子查询列表
  FUNC,          ///函数
  EXP_TYPE_NUM ,  /// 
};

typedef enum { ADD_OP, SUB_OP, MUL_OP, DIV_OP, EXP_OP_NUM } ExpOp;
typedef enum { MAX, MIN, SUM, AVG, CNT,AGGR_FUNC_TYPE_NUM } AggrFuncType;
typedef enum { FUNC_LENGTH, FUNC_ROUND, FUNC_DATE_FORMAT, FUNC_TYPE_NUM } FuncType;
typedef enum { SUB_IN, SUB_NOT_IN, SUB_EXISTS, SUB_NOT_EXISTS, SUB_NORMAL, SUB_TYPE_NUM } SubQueryType;
typedef enum { ASC_, DESC_ } OrderDirection;

struct OrderByNode {
    RelAttrSqlNode attribute;
    OrderDirection direction;
};

struct InnerJoinNode {
  Relation          relation_name;
  Expression *      conditions = nullptr;    ///< 查询条件，使用AND串联起来多个条件 ConjunctionExpr
};

/**
 * @brief 描述一个select语句
 * @ingroup SQLParser
 * @details 一个正常的select语句描述起来比这个要复杂很多，这里做了简化。
 * 一个select语句由三部分组成，分别是select, from, where。
 * select部分表示要查询的字段，from部分表示要查询的表，where部分表示查询的条件。
 * 比如 from 中可以是多个表，也可以是另一个查询语句，这里仅仅支持表，也就是 relations。
 * where 条件 conditions，这里表示使用AND串联起来多个条件。正常的SQL语句会有OR，NOT等，
 * 甚至可以包含复杂的表达式。
 */
struct SelectSqlNode
{
  std::vector<RelAttrSqlNode>     attributes;    ///< attributes in select clause
  std::vector<Relation>           relations;     ///< 查询的表
  Expression *                    conditions = nullptr;     ///< 查询条件，使用AND串联起来多个条件
  std::vector<InnerJoinNode>      inner_join_clauses;
  std::vector<OrderByNode>        order_by_nodes;
  std::vector<RelAttr>            group_by;
};

/**
 * @brief 算术表达式计算的语法树
 * @ingroup SQLParser
 */
struct CalcSqlNode
{
  std::vector<Expression *> expressions;  ///< calc clause

  ~CalcSqlNode();
};

/**
 * @brief 描述一个insert语句
 * @ingroup SQLParser
 * @details 于Selects类似，也做了很多简化
 */
struct InsertSqlNode
{
  std::string        relation_name;  ///< Relation to insert into
  std::vector<Value> values;         ///< 要插入的值
};

/**
 * @brief 描述一个delete语句
 * @ingroup SQLParser
 */
struct DeleteSqlNode
{
  std::string                   relation_name;  ///< Relation to delete from
  Expression *                  conditions = nullptr;
};

/**
 * @brief 表示一个条件比较
 * @ingroup SQLParser
 * @details 条件比较就是SQL查询中的 where a>b 这种。
 * 一个条件比较是有两部分组成的，称为左边和右边。
 * 左边和右边理论上都可以是任意的数据，比如是字段（属性，列），也可以是数值常量。
 * 这个结构中记录的仅仅支持字段和值。
 */
struct ConditionSqlNode
{
  int             left_is_attr;    ///< TRUE if left-hand side is an attribute
                                   ///< 1时，操作符左边是属性名，0时，是属性值
  Value           left_value;      ///< left-hand side value if left_is_attr = FALSE
  RelAttrSqlNode  left_attr;       ///< left-hand side attribute
  CompOp          comp;            ///< comparison operator
  int             right_is_attr;   ///< TRUE if right-hand side is an attribute
                                   ///< 1时，操作符右边是属性名，0时，是属性值
  RelAttrSqlNode  right_attr;      ///< right-hand side attribute if right_is_attr = TRUE 右边的属性
  Value           right_value;     ///< right-hand side value if right_is_attr = FALSE
};

/**
 * @brief update set子句中的属性和值
 * @ingroup SQLParser
*/
struct SetSqlNode
{
  std::string       attribute_name; // update set子句的属性名
  Value             value;          // update set子句的属性值
};


/**
 * @brief 描述一个update语句
 * @ingroup SQLParser
 */
struct UpdateSqlNode
{
  std::string                   relation_name;         ///< Relation to update
  // std::string                   attribute_name;        ///< 更新的字段，仅支持一个字段
  // Value                         value;                 ///< 更新的值，仅支持一个字段
  std::vector<SetSqlNode>       set_cols;       ///< 更新的所有字段
  Expression*                  conditions = nullptr;
};
/**
 * @brief 描述一个属性
 * @ingroup SQLParser
 * @details 属性，或者说字段(column, field)
 * Rel -> Relation
 * Attr -> Attribute
 */
struct AttrInfoSqlNode
{
  AttrType    type;       ///< Type of attribute
  std::string name;       ///< Attribute name
  size_t      length;     ///< Length of attribute
  bool        nullable = false;     // 默认不可为空
};

/**
 * @brief 描述一个create table语句
 * @ingroup SQLParser
 * @details 这里也做了很多简化。
 */
struct CreateTableSqlNode
{
  std::string                  relation_name;         ///< Relation name
  std::vector<AttrInfoSqlNode> attr_infos;            ///< attributes
};

/**
 * @brief 描述一个drop table语句
 * @ingroup SQLParser
 */
struct DropTableSqlNode
{
  std::string relation_name;  ///< 要删除的表名
};

/**
 * @brief 描述一个create index语句
 * @ingroup SQLParser
 * @details 创建索引时，需要指定索引名，表名，字段名。
 * 正常的SQL语句中，一个索引可能包含了多个字段，这里仅支持一个字段。
 */
struct CreateIndexSqlNode
{
  std::string index_name;      ///< Index name
  std::string relation_name;   ///< Relation name
  // std::string attribute_name;  ///< Attribute name
  std::vector<RelAttrSqlNode> attributes_names;  ///< 多列索引
};

/**
 * @brief 描述一个drop index语句
 * @ingroup SQLParser
 */
struct DropIndexSqlNode
{
  std::string index_name;     ///< Index name
  std::string relation_name;  ///< Relation name
};

/**
 * T11
 * @brief 创建一个支持多列的唯一索引
 * @ingroup SQLParser
*/
struct CreateUniqueIndexSqlNode
{
  std::string index_name;                     ///< Index name
  std::string relation_name;                  ///< Relation name
  std::vector<RelAttrSqlNode> attributes_names;  ///< Attributes names
};

/**
 * @brief 描述一个desc table语句
 * @ingroup SQLParser
 * @details desc table 是查询表结构信息的语句
 */
struct DescTableSqlNode
{
  std::string relation_name;
};

/**
 * @brief 描述一个load data语句
 * @ingroup SQLParser
 * @details 从文件导入数据到表中。文件中的每一行就是一条数据，每行的数据类型、字段个数都与表保持一致
 */
struct LoadDataSqlNode
{
  std::string relation_name;
  std::string file_name;
};

/**
 * @brief 设置变量的值
 * @ingroup SQLParser
 * @note 当前还没有查询变量
 */
struct SetVariableSqlNode
{
  std::string name;
  Value       value;
};

class ParsedSqlNode;

/**
 * @brief 描述一个explain语句
 * @ingroup SQLParser
 * @details 会创建operator的语句，才能用explain输出执行计划。
 * 一个command就是一个语句，比如select语句，insert语句等。
 * 可能改成SqlCommand更合适。
 */
struct ExplainSqlNode
{
  std::unique_ptr<ParsedSqlNode> sql_node;
};

/**
 * @brief 解析SQL语句出现了错误
 * @ingroup SQLParser
 * @details 当前解析时并没有处理错误的行号和列号
 */
struct ErrorSqlNode
{
  std::string error_msg;
  int         line;
  int         column;
};

/**
 * @brief 表示一个SQL语句的类型
 * @ingroup SQLParser
 */
enum SqlCommandFlag
{
  SCF_ERROR = 0,
  SCF_CALC,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_CREATE_UNIQUE_INDEX,  // T11
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,        ///< 事务开始语句，可以在这里扩展只读事务
  SCF_COMMIT,
  SCF_CLOG_SYNC,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT,
  SCF_EXPLAIN,
  SCF_SET_VARIABLE, ///< 设置变量
};
/**
 * @brief 表示一个SQL语句
 * @ingroup SQLParser
 */
class ParsedSqlNode
{
public:
  enum SqlCommandFlag       flag;
  ErrorSqlNode              error;
  CalcSqlNode               calc;
  SelectSqlNode             selection;
  InsertSqlNode             insertion;
  DeleteSqlNode             deletion;
  UpdateSqlNode             update;
  CreateTableSqlNode        create_table;
  DropTableSqlNode          drop_table;
  CreateIndexSqlNode        create_index;
  CreateUniqueIndexSqlNode  create_unique_index;  // T11 创建唯一索引
  DropIndexSqlNode          drop_index;
  DescTableSqlNode          desc_table;
  LoadDataSqlNode           load_data;
  ExplainSqlNode            explain;
  SetVariableSqlNode        set_variable;

public:
  ParsedSqlNode();
  explicit ParsedSqlNode(SqlCommandFlag flag);
};

/**
 * @brief 表示语法解析后的数据
 * @ingroup SQLParser
 */
class ParsedSqlResult
{
public:
  void add_sql_node(std::unique_ptr<ParsedSqlNode> sql_node);
  std::vector<std::unique_ptr<ParsedSqlNode>> &sql_nodes()
  {
    return sql_nodes_;
  }

private:
  std::vector<std::unique_ptr<ParsedSqlNode>> sql_nodes_;  ///< 这里记录SQL命令。虽然看起来支持多个，但是当前仅处理一个
};
