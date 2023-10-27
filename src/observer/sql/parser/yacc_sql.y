
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  // ParsedSqlNode在哪里定义的？——parse_defs.h
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
// TODO:这里的token是什么含义？
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        DESC
        ASC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T    // T1修改点
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        EQ
        LT
        GT
        LE
        GE
        NE
        INNER
        JOIN
        ORDER
        BY 
        OR
        IN
        EXISTS
        IS
        NOT
        NULL_VALUE
        LIKE_T
        NOT_LIKE_T


/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
// 每次匹配到一个语法规则之后生成结果的类型
%union {
  ParsedSqlNode *                   sql_node;
  Value *                           value;
  CompOp                            comp;
  RelAttrSqlNode *                  rel_attr;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  std::vector<Expression *> *       expression_list;
  std::vector<Value> *              value_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  std::vector<std::string> *        relation_list;
  char *                            string;
  int                               number;
  float                             floats;
  InnerJoinNode *                   join_clause;
  Expression *                      join_conditions;          
  std::vector<InnerJoinNode> *      inner_join_list;
  OrderDirection               order_direction;
  OrderByNode *                     order_by_item;
  std::vector<OrderByNode> *        order_by_list;
}

// TODO:这四个TOKEN的含义？
%token <number> NUMBER  
%token <floats> FLOAT
%token <string> ID      
%token <string> DATE    // T1修改点
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type            // 返回类型(定义在上面的union中)————解析类型（下面定义）
%type <value>               value
%type <number>              number
%type <comp>                comp_op
%type <rel_attr>            rel_attr
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <rel_attr_list>       select_attr
%type <relation_list>       rel_list
%type <rel_attr_list>       attr_list
%type <expression_list>     expression_list
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt     
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands      // 最终生成的结果
//inner join related
%type <inner_join_list>     inner_join_list;
%type <join_clause>         join_clause
%type <join_conditions>     join_conditions
%type <order_by_list>       order_by
%type <order_by_list>       order_by_list
%type <order_by_item>       order_by_item
%type <order_direction>     order_direction
%type <expression>          where
%type <expression>          unary_expr
%type <expression>          condition
%type <expression>          condition_list
%type <expression>          sub_select_expr
%type <expression>          arithmetic_expr
%type <expression>          sub_select_list
%type <expression>          add_expr
%type <expression>          mul_expr




%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

// 后面是具体的解析规则
commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      create_index.attribute_name = $7;
      free($3);
      free($5);
      free($7);
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE 
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      free($1);
    }
    | ID type
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      free($1);
    }
    ;
number:
    NUMBER {$$ = $1;}
    ;
// TODO:关键点：这里进行类型映射
type:
    INT_T      { $$=INTS; }
    | DATE_T    {$$=DATES;}   // T1修改点
    | STRING_T { $$=CHARS; }
    | FLOAT_T  { $$=FLOATS; }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE 
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($7 != nullptr) {
        $$->insertion.values.swap(*$7);
      }
      $$->insertion.values.emplace_back(*$6);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $6;
    }
    ;

// TODO:找到了，value的值在这里修改
value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA value value_list  {   
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;

value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    | DATE {    // T1修改点
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp, 0, true);    // 构建Date类型的Value
      free(tmp);
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
    }
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions = $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      $$->update.attribute_name = $4;
      $$->update.value = *$6;
      if ($7 != nullptr) {
        $$->update.conditions = $7;
      }
      free($2);
      free($4);
    }
    ;
select_stmt:        /*  select 语句的语法解析树*/
    SELECT select_attr FROM ID rel_list inner_join_list where order_by
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.attributes.swap(*$2);
        delete $2;
      }
      if ($5 != nullptr) {
        $$->selection.relations.swap(*$5);
        delete $5;
      }
      $$->selection.relations.push_back($4);
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());   // 为什么这里要反转？因为select_attr的写法是反着的。
      free($4);

      if ($6 != nullptr) {
        $$->selection.inner_join_clauses.swap(*$6);
        delete $6;
      }
      std::reverse($$->selection.inner_join_clauses.begin(), $$->selection.inner_join_clauses.end());   

      if ($7 != nullptr) {
        $$->selection.conditions = $7;
      }

      if ($8 != nullptr) {
        $$->selection.order_by_nodes.swap(*$8);
        delete $8;
      }
      // std::reverse($$->selection.order_by_nodes.begin(), $$->selection.order_by_nodes.end());   

    }
    ;



calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      std::reverse($2->begin(), $2->end());
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    arithmetic_expr
    {
      $$ = new std::vector<Expression*>;
      $$->emplace_back($1);
    }
    | arithmetic_expr COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Expression *>;
      }
      $$->emplace_back($1);
    }
    ;

arithmetic_expr:
    arithmetic_expr '+' arithmetic_expr {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | arithmetic_expr '-' arithmetic_expr {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | arithmetic_expr '*' arithmetic_expr {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | arithmetic_expr '/' arithmetic_expr {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE arithmetic_expr RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' arithmetic_expr %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    ;

select_attr:
    '*' {
      $$ = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      $$->emplace_back(attr);
    }
    | rel_attr attr_list {
      if ($2 != nullptr) {
        $$ = $2;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }
    ;

rel_attr:
    ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    ;

attr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA rel_attr attr_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }

      $$->emplace_back(*$2);
      delete $2;
    }
    ;

rel_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID rel_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::string>;
      }

      $$->push_back($2);
      free($2);
    }
    ;

/**
 *dengshudong添加的语法规则
*/

// inner join语法规则
inner_join_list:  // 返回std::vector<InnerJoinNode> *
    /* empty */
    {
        $$ = nullptr;
    }
    | join_clause inner_join_list {
        if($2 != nullptr) {
            $$ = $2;
        } else {
            $$ = new std::vector<InnerJoinNode>;
        }
        $$->push_back(*$1);
    }
    ;

join_clause:   // 返回InnerJoinNode * 
    INNER JOIN ID join_conditions {
        $$ = new InnerJoinNode;
        $$->relation_name = $3;
        $$->conditions = $4;
    }
    ;

join_conditions:      // 返回ConjunctionExpr* 可能为空
    // inner join可以没有on子句
    {
      $$ = nullptr;
    }
    | ON condition {    // 如果有on关键字，则至少必须有一个condition
      ConjunctionExpr *temp = new ConjunctionExpr();
      temp->add_condition($2);
      $$ = temp;
    }
    | ON condition AND condition_list {     
      ConjunctionExpr *base = static_cast<ConjunctionExpr *>($4);
      assert(base != nullptr);
      base->add_condition($2);
      $$ = base;
    }
    ;

// order by语法规则
order_direction:
    DESC {
        $$ = OrderDirection::DESC_;
    }
    | ASC {
        $$ = OrderDirection::ASC_;
    }
    | /* empty, default to ascending */
    {
        $$ = OrderDirection::ASC_;
    }
    ;

order_by_item:
    rel_attr order_direction {
        $$ = new OrderByNode;
        $$->attribute = *$1;
        $$->direction = $2;
        delete $1;
    }
    ;

order_by_list:
    // 这里不能为空，为空就有问题
    // {
    // $$ = nullptr
    // }
    order_by_item {
        $$ = new std::vector<OrderByNode>;
        $$->push_back(*$1);
    }
    | order_by_item COMMA order_by_list {
        $$ = $3;
        $$->emplace_back(*$1);
        delete $1;
    }
    ;

order_by:
    /* empty */ 
    {
        $$ = nullptr;
    } 
    | ORDER BY order_by_list {
        $$ = $3;
    }
    ;

/**
 *dengshudong添加的语法规则end
*/

where:     // 返回Expression *
  /* empty */ 
  {
    $$ = nullptr;
  }
  | WHERE condition_list {      
    $$ = $2;
  }
  ;


condition_list:   // 返回ConjunctionExpr*
    condition {
      ConjunctionExpr *temp = new ConjunctionExpr();
      temp->add_condition($1);
      $$ = temp;
    }
    | condition AND condition_list {        
      ConjunctionExpr *base = static_cast<ConjunctionExpr *>($3);
      assert(base != nullptr);
      base->add_condition($1);
      $$ = base;
    }
    | condition OR condition_list {        
      ConjunctionExpr *base = static_cast<ConjunctionExpr *>($3);
      base->add_condition($1);
      base->set_conjunction_type(ConjunctionExpr::Type::OR);
      $$ = base;
    }
    ;

condition:      // 返回ComparisonExpr
    add_expr comp_op add_expr{
      $$ = new ComparisonExpr($2, $1, $3);
    }
    | add_expr IS NULL_VALUE {
      // TODO
    }
    | add_expr IS NOT NULL_VALUE {
      // TODO:
    }
    | add_expr NOT IN add_expr {
      $$ = new ComparisonExpr(CompOp::NOT_IN, $1, $4);
    }
    | EXISTS add_expr {
      Value temp_value = Value(1);      // 创建一个临时对象当做表达式
      ValueExpr *value_expr = new ValueExpr(temp_value);
      $$ = new ComparisonExpr(CompOp::EXISTS_OP, value_expr, $2);
    }
    | NOT EXISTS add_expr {
      Value temp_value = Value(1);      // 创建一个临时对象当做表达式
      ValueExpr *value_expr = new ValueExpr(temp_value);
      $$ = new ComparisonExpr(CompOp::NOT_EXISTS, value_expr, $3);
    }
    ;

// 第二优先级表达式：第一优先级表达式/加法、减法
add_expr:
    mul_expr { $$ = $1; }    
    | add_expr '+' mul_expr {
      $$ = new ArithmeticExpr(ArithmeticExpr::Type::ADD, $1, $3);
    }
    | add_expr '-' mul_expr {
      $$ = new ArithmeticExpr(ArithmeticExpr::Type::SUB, $1, $3);
    }
    ;

// 第一优先级表达式包括：单目、乘法、除法
mul_expr:
    unary_expr {
      $$ = $1;
    }
    | mul_expr '*' unary_expr {
      $$ = new ArithmeticExpr(ArithmeticExpr::Type::MUL, $1, $3);
    }
    | mul_expr '/' unary_expr {
      $$ = new ArithmeticExpr(ArithmeticExpr::Type::DIV, $1, $3);
    }
    ;

// 单目表达式
unary_expr:
    value {
      $$ = new ValueExpr(*$1);
    }
    | ID {
      $$ = new FieldExpr($1);
    }
    | ID DOT ID {
      $$ = new FieldExpr($3, $1);
    }
    | LBRACE add_expr RBRACE {
      $$ = $2;
    }
    // | func_expr {
    //   $$ = $1;
    // }
    // | aggr_func_expr {
    //   $$ = $1;
    // }
    | sub_select_expr {
       $$ = $1;
    }
    | sub_select_list{
      $$ = $1;
    }
    ;

sub_select_expr:
  LBRACE select_stmt RBRACE 
  {
    // SubQueryExpression
    $$ = new SubQueryExpression($2);
  }
  ;

sub_select_list:
    LBRACE value value_list RBRACE
    {
      std::vector<Value> *temp = $3;
      if (temp != nullptr) {
        temp->push_back(*$2);
      } else {
        temp = new std::vector<Value>{*$2};
      }

      $$ = new ListExpression(*temp);
    }
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE_T { $$ = LIKE; }
    | NOT_LIKE_T {$$ = NOT_LIKE; }
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
