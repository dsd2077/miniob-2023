
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
        SUB
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
        AS
        AGGR_MAX
        AGGR_MIN
        AGGR_SUM
        AGGR_AVG
        AGGR_COUNT
        UNIQUE  // T11
        LENGTH
        ROUND
        DATE_FORMAT
        GROUP
        HAVING



/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
// 每次匹配到一个语法规则之后生成结果的类型
%union {
  ParsedSqlNode *                   sql_node;
  CompOp                            comp;

  AttrInfoSqlNode *                 attr_info;
  std::vector<AttrInfoSqlNode> *    attr_infos;

  Expression *                      expression;
  std::vector<Expression *> *       expression_list;

  Value *                           value;
  std::vector<Value> *              value_list;

  RelAttrSqlNode *                  rel_attr_item;
  std::vector<RelAttrSqlNode> *     attr_list;

  Relation *                        relation_item;
  std::vector<Relation> *           relation_list;

  std::vector<SetSqlNode> *         set_attrs;

  char *                            string;
  int                               number;
  float                             floats;
  InnerJoinNode *                   join_clause;
  Expression *                      join_conditions;          
  std::vector<InnerJoinNode> *      inner_join_list;
  OrderDirection                    order_direction;
  OrderByNode *                     order_by_item;
  std::vector<OrderByNode> *        order_by_list;
  AggrFuncType                      aggr_func_type;
}

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
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list

%type <relation_list>       from
%type <relation_list>       rel_list
%type <relation_item>       rel_item

%type <attr_list>           select_attr
%type <attr_list>           attr_list
%type <rel_attr_item>       rel_attr_item

%type <rel_attr_item>       rel_attr
%type <attr_list>           rel_attr_list

%type <attr_list>           attr_list_index

%type <expression_list>     expression_list
%type <set_attrs>           set_attr_list
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
%type <sql_node>            create_unique_index_stmt  // T11
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
%type <expression>          add_expr
%type <expression>          mul_expr
%type <expression>          condition
%type <expression>          condition_list
%type <expression>          sub_select_expr
%type <expression>          arithmetic_expr
%type <expression>          sub_select_list
%type <expression>          aggr_func_expr
%type <expression>          func_expr
%type <aggr_func_type>      aggr_func_type
%type <attr_list>           group_by
%type <expression>          having 
%type <expression>          having_condition_list 
%type <expression>          having_condition



%left '+' '-'
%left '*' '/'
%right SUB // 给一元减号定义高优先级
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
  | create_unique_index_stmt
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
    CREATE INDEX ID ON ID LBRACE rel_attr attr_list_index RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;

      std::vector<RelAttrSqlNode> *attrs = $8;
      if(attrs == nullptr) {
        attrs = new std::vector<RelAttrSqlNode>;
      }
      create_index.attributes_names.swap(*attrs);
      create_index.attributes_names.emplace_back(*$7);
      std::reverse(create_index.attributes_names.begin(), create_index.attributes_names.end());
      free($3);
      free($5);
      free($7);
    }
    ;

create_unique_index_stmt: /*create unique index 语句的语法解析树，和create index的完全一样，unique在stmt到逻辑算子部分开始发挥作用*/
    CREATE UNIQUE INDEX ID ON ID LBRACE rel_attr attr_list_index RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_UNIQUE_INDEX);
      CreateUniqueIndexSqlNode &create_unique_index = $$->create_unique_index;
      create_unique_index.index_name = $4;
      create_unique_index.relation_name = $6;

      std::vector<RelAttrSqlNode> *attrs = $9;
      if(attrs == nullptr) {
        attrs = new std::vector<RelAttrSqlNode>;
      }
      create_unique_index.attributes_names.swap(*attrs);
      create_unique_index.attributes_names.emplace_back(*$8);
      std::reverse(create_unique_index.attributes_names.begin(), create_unique_index.attributes_names.end());
      free($4);
      free($6);
      free($8);
    }

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
      $$->emplace_back(*$2);  // 按照语法树递归执行，最后一个attr将会放到vector的第一个位置，所以在调用attr_def_list的部分需要reverse
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE    // name char(50)
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      free($1);
    }
    |ID type LBRACE number RBRACE NOT NULL_VALUE
		{
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      free($1);
		}
    |ID type LBRACE number RBRACE NULL_VALUE
		{
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = true;
      free($1);
		}
    | ID type                       // age float
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      free($1);
    }
    |ID type NOT NULL_VALUE
		{
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      free($1);
		}
    |ID type NULL_VALUE
		{
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->nullable = true;
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
    //| SUB NUMBER %prec SUB {
    //  $$ = new Value(-(int)$2);
    //  @$ = @1;
    //}
    //| SUB FLOAT %prec SUB {
    //  $$ = new Value(-(float)$2);
    //  @$ = @1;
    //}
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
    UPDATE ID SET ID EQ value set_attr_list where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;

      SetSqlNode *col = new SetSqlNode;
      col->attribute_name = $4;
      col->value = *$6;
      
      std::vector<SetSqlNode> *sets = $7;
      if (nullptr != $7) {
        $$->update.set_cols.swap(*sets);
      }
      $$->update.set_cols.emplace_back(*col);

      if ($8 != nullptr) {
        $$->update.conditions = $8;
      }
      free($2);
      free($4);
    }
    ;

set_attr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID EQ value set_attr_list
    {
      $$ = new std::vector<SetSqlNode>;
      SetSqlNode *col = new SetSqlNode;
      col->attribute_name = $2;
      col->value = *$4;
      
      std::vector<SetSqlNode> *sets = $5;
      if(nullptr != sets) {
        $$->swap(*sets);
      }
      $$->emplace_back(*col);
      free($2);
    }
    ;

select_stmt:        /*  select 语句的语法解析树*/
    SELECT select_attr SEMICOLON {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.attributes.swap(*$2);
        delete $2;
      }
    }
    | SELECT select_attr FROM from inner_join_list where group_by having order_by SEMICOLON
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.attributes.swap(*$2);
        delete $2;
      }
      // std::reverse($$->selection.attributes.begin(), $$->selection.attributes.end());   // 为什么这里要反转？因为select_attr的写法是反着的。

      if ($4 != nullptr) {
        $$->selection.relations.swap(*$4);
        delete $4;
      }
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());   // 为什么这里要反转？因为select_attr的写法是反着的。

      if ($5 != nullptr) {
        $$->selection.inner_join_clauses.swap(*$5);
        delete $5;
      }
      std::reverse($$->selection.inner_join_clauses.begin(), $$->selection.inner_join_clauses.end());   

      if ($6 != nullptr) {
        $$->selection.conditions = $6;
      }

      if ($7 != nullptr) {
        $$->selection.group_by.swap(*$7);
        delete $7;
      }
      std::reverse($$->selection.group_by.begin(), $$->selection.group_by.end());   

      if ($8 != nullptr) {
        $$->selection.havings = $8;
      }

      if ($9 != nullptr) {
        $$->selection.order_by_nodes.swap(*$9);
        delete $9;
      }
      std::reverse($$->selection.order_by_nodes.begin(), $$->selection.order_by_nodes.end());   

    }
    ;

group_by:
	/* empty */ {
    $$ = nullptr;
  }
	| GROUP BY rel_attr {
    $$ = new std::vector<RelAttrSqlNode>;
    $$->emplace_back(*$3);
    delete $3;
	}
  | GROUP BY rel_attr rel_attr_list {
    std::vector<RelAttrSqlNode> *temp = $4;
    if (nullptr == temp) {
      temp = new std::vector<RelAttrSqlNode>;
    }
    temp->emplace_back(*$3);
    delete $3;
    $$ = temp;
  }
	;

having:   // 返回ConjunctionExpr*
  /* empty */  { 
    $$ = nullptr;
  }
  | HAVING having_condition having_condition_list {	
    ConjunctionExpr *con_expr = dynamic_cast<ConjunctionExpr *>($3);
    if (nullptr == con_expr) {
      con_expr = new ConjunctionExpr();
    }
    con_expr->add_condition($2);
    $$ = con_expr;
  }
  ;

having_condition_list:    // 返回ConjunctionExpr*
  /* empty */ {
    $$ = nullptr;
  }
  | AND having_condition having_condition_list {
    ConjunctionExpr *con_expr = dynamic_cast<ConjunctionExpr *>($3);
    if (nullptr == con_expr) {
      con_expr = new ConjunctionExpr();
    }
    con_expr->add_condition($2);
    $$ = con_expr;
  }
  ;

having_condition:   // 返回Expression*
  add_expr comp_op add_expr{
    ComparisonExpr *comp_expr = new ComparisonExpr($2, $1, $3);
    $$ = comp_expr;
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

rel_attr:     // 返回RelAttrSqlNode*
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

rel_attr_list:
  {
    $$ = nullptr;
  }
  | COMMA rel_attr rel_attr_list {
    std::vector<RelAttrSqlNode> *temp = $3;
    if (nullptr == temp) {
      temp = new std::vector<RelAttrSqlNode>;
    }
    temp->emplace_back(*$2);
    $$ = temp;
  }

attr_list_index:
  {
    $$ = nullptr;
  }
  | COMMA rel_attr attr_list_index {
    std:vector<RelAttrSqlNode> *temp = $3;
    if (temp == nullptr) {
      temp = new std::vector<RelAttrSqlNode>;
    }
    temp->emplace_back(*$2);
    $$ = temp;
    free $2;
  }
  ;

    
select_attr:
  rel_attr_item {
    $$ = new std::vector<RelAttrSqlNode>;
    $$->emplace_back(*$1);
    delete $1;
  }
  | rel_attr_item attr_list {
    std::vector<RelAttrSqlNode> *temp = $2;
    if (temp == nullptr) {
      temp = new std::vector<RelAttrSqlNode>;
    } 
    temp->emplace_back(*$1);
    $$ = temp;
    delete $1;
  }

// 返回std::vector<RelAttrSqlNode> *
// 支持聚集函数、表达式 
rel_attr_item:        // 返回RelAttrSqlNode*
    '*' {  
      $$ = new RelAttrSqlNode ;
      $$->relation_name  = "";
      $$->attribute_name = "*";
		}
    | ID DOT '*' {
      $$ = new RelAttrSqlNode;
      $$->relation_name = $1;
      $$->attribute_name = "*";
    }
    | add_expr {       
      $$ = new RelAttrSqlNode;
      $$->expr = $1;
    }
    | add_expr AS ID {   // 只有单列和聚集函数才能取别名
      $$ = new RelAttrSqlNode;
      $$->expr = $1;
      $$->alias = $3;
    }
    | add_expr ID {
      $$ = new RelAttrSqlNode;
      $$->expr = $1;
      $$->alias = $2;
    }
    ;

attr_list:      // 返回std::vector<RelAttrSqlNode> *
    /* empty */ 
    {
      $$ = nullptr;
    }
    | COMMA rel_attr_item attr_list {
      std::vector<RelAttrSqlNode> *temp = $3;
      if (temp == nullptr) {
        temp = new std::vector<RelAttrSqlNode>;
      } 
      temp->emplace_back(*$2);
      $$ = temp;
    }
  	;

from:
  rel_item 
  {
    $$ = new std::vector<Relation>;
    $$->emplace_back(*$1);
    delete $1;
  }
  | rel_item rel_list 
  {
    $$ = $2;
    $$->emplace_back(*$1);
    delete $1;
  }

rel_list:     // 返回std::vector<Relation> * 
  /* empty */ 
  {
    $$ = nullptr;
  }
  | COMMA rel_item rel_list {	
    std::vector<Relation> * temp = $3;
    if (temp == nullptr) {
      temp = new std::vector<Relation>;
      temp->emplace_back(*$2);
    }
    $$ = temp;
  }
  
rel_item:   // 返回 Relation *
  ID {
    $$ = new Relation;
    $$->relation_name = $1;
  }
  |ID ID {       
    $$ = new Relation;
    $$->relation_name = $1;
    $$->alias = $2;
  }
  |ID AS ID {
    $$ = new Relation;
    $$->relation_name = $1;
    $$->alias = $3;
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
    INNER JOIN rel_item join_conditions {
        $$ = new InnerJoinNode;
        $$->relation_name = *$3;
        $$->conditions = $4;
        delete $3;
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
      assert(base != nullptr);
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
    mul_expr {
      $$ = $1; 
    }    
    | add_expr '+' mul_expr {
      $$ = new ArithmeticExpr(ArithmeticExpr::Type::ADD, $1, $3);
    }
    | add_expr SUB mul_expr {
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
      $$->set_with_brace();
    }
    | func_expr {
      $$ = $1;
    }
    | aggr_func_expr {
      $$ = $1;
    }
    | sub_select_expr {
       $$ = $1;
    }
    | sub_select_list{
      $$ = $1;
    }
    | SUB unary_expr {
      $$ = $2;
      $$->set_negtive();
    }
    ;

aggr_func_expr:
  aggr_func_type LBRACE add_expr RBRACE
  {
    assert(ExprType::FIELD == $3->type());
    $$ = new AggrFuncExpression($1, static_cast<FieldExpr*>($3));
  }
  | AGGR_COUNT LBRACE add_expr RBRACE
  {
    assert(ExprType::FIELD == $3->type());
    $$ = new AggrFuncExpression(AggrFuncType::CNT, static_cast<FieldExpr*>($3));
  }
  | AGGR_COUNT LBRACE '*' RBRACE
  {
    ValueExpr *temp = new ValueExpr(Value("*"));
    $$ = new AggrFuncExpression(AggrFuncType::CNT, temp);
  }
  ;

aggr_func_type:
    AGGR_MAX {
      $$ = AggrFuncType::MAX;
    }
    | AGGR_MIN {
      $$ = AggrFuncType::MIN;
    }
    | AGGR_SUM {
      $$ = AggrFuncType::SUM;
    }
    | AGGR_AVG {
      $$ = AggrFuncType::AVG;
    }
    ;


sub_select_expr:
  LBRACE SELECT select_attr FROM from inner_join_list where group_by having order_by RBRACE 
  {
    ParsedSqlNode *temp= new ParsedSqlNode(SCF_SELECT);
    if ($3 != nullptr) {
      temp->selection.attributes.swap(*$3);
      delete $3;
    }
    if ($5 != nullptr) {
      temp->selection.relations.swap(*$5);
      delete $5;
    }
    std::reverse(temp->selection.relations.begin(), temp->selection.relations.end());   // 为什么这里要反转？因为select_attr的写法是反着的。
    if ($6 != nullptr) {
      temp->selection.inner_join_clauses.swap(*$6);
      delete $6;
    }
    std::reverse(temp->selection.inner_join_clauses.begin(), temp->selection.inner_join_clauses.end());   

    if ($7 != nullptr) {
      temp->selection.conditions = $7;
    }

    if ($8 != nullptr) {
      temp->selection.group_by.swap(*$8);
      delete $8;
    }
    std::reverse(temp->selection.group_by.begin(), temp->selection.group_by.end());   

    if ($9 != nullptr) {
      temp->selection.havings = $9;
    }

    if ($10 != nullptr) {
      temp->selection.order_by_nodes.swap(*$10);
      delete $10;
    }
    SubQueryExpression *res = new SubQueryExpression(temp);
    $$ = res;
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
      $$->set_with_brace();
    }
    ;

func_expr:
  LENGTH LBRACE add_expr RBRACE {
    $$ = new FuncExpression(FUNC_LENGTH, 1, $3, nullptr, true);
  }
  | ROUND LBRACE add_expr RBRACE {
    $$ = new FuncExpression(FUNC_ROUND, 1, $3, nullptr, true);
  }
  | ROUND LBRACE add_expr COMMA add_expr RBRACE {
    $$ = new FuncExpression(FUNC_ROUND, 2, $3, $5, true);
  }
  | DATE_FORMAT LBRACE add_expr COMMA add_expr RBRACE {
    $$ = new FuncExpression(FUNC_DATE_FORMAT, 2, $3, $5, true);
  }
  ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE_T { $$ = LIKE_OP; }
    | NOT_LIKE_T {$$ = NOT_LIKE_OP; }
    | IN { $$ = IN_OP; }
    | EXISTS {$$ = EXISTS_OP; }
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
