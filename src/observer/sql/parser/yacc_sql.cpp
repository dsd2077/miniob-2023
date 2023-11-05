/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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


#line 116 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_CALC = 9,                       /* CALC  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_ASC = 12,                       /* ASC  */
  YYSYMBOL_SHOW = 13,                      /* SHOW  */
  YYSYMBOL_SYNC = 14,                      /* SYNC  */
  YYSYMBOL_INSERT = 15,                    /* INSERT  */
  YYSYMBOL_DELETE = 16,                    /* DELETE  */
  YYSYMBOL_UPDATE = 17,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 18,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 19,                    /* RBRACE  */
  YYSYMBOL_COMMA = 20,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 21,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 22,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 23,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 24,                     /* INT_T  */
  YYSYMBOL_STRING_T = 25,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 26,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 27,                    /* DATE_T  */
  YYSYMBOL_HELP = 28,                      /* HELP  */
  YYSYMBOL_EXIT = 29,                      /* EXIT  */
  YYSYMBOL_DOT = 30,                       /* DOT  */
  YYSYMBOL_INTO = 31,                      /* INTO  */
  YYSYMBOL_VALUES = 32,                    /* VALUES  */
  YYSYMBOL_FROM = 33,                      /* FROM  */
  YYSYMBOL_WHERE = 34,                     /* WHERE  */
  YYSYMBOL_AND = 35,                       /* AND  */
  YYSYMBOL_SET = 36,                       /* SET  */
  YYSYMBOL_ON = 37,                        /* ON  */
  YYSYMBOL_LOAD = 38,                      /* LOAD  */
  YYSYMBOL_DATA = 39,                      /* DATA  */
  YYSYMBOL_INFILE = 40,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 41,                   /* EXPLAIN  */
  YYSYMBOL_EQ = 42,                        /* EQ  */
  YYSYMBOL_LT = 43,                        /* LT  */
  YYSYMBOL_GT = 44,                        /* GT  */
  YYSYMBOL_LE = 45,                        /* LE  */
  YYSYMBOL_GE = 46,                        /* GE  */
  YYSYMBOL_NE = 47,                        /* NE  */
  YYSYMBOL_INNER = 48,                     /* INNER  */
  YYSYMBOL_SUB = 49,                       /* SUB  */
  YYSYMBOL_JOIN = 50,                      /* JOIN  */
  YYSYMBOL_ORDER = 51,                     /* ORDER  */
  YYSYMBOL_BY = 52,                        /* BY  */
  YYSYMBOL_OR = 53,                        /* OR  */
  YYSYMBOL_IN = 54,                        /* IN  */
  YYSYMBOL_EXISTS = 55,                    /* EXISTS  */
  YYSYMBOL_IS = 56,                        /* IS  */
  YYSYMBOL_NOT = 57,                       /* NOT  */
  YYSYMBOL_NULL_VALUE = 58,                /* NULL_VALUE  */
  YYSYMBOL_LIKE_T = 59,                    /* LIKE_T  */
  YYSYMBOL_NOT_LIKE_T = 60,                /* NOT_LIKE_T  */
  YYSYMBOL_AS = 61,                        /* AS  */
  YYSYMBOL_AGGR_MAX = 62,                  /* AGGR_MAX  */
  YYSYMBOL_AGGR_MIN = 63,                  /* AGGR_MIN  */
  YYSYMBOL_AGGR_SUM = 64,                  /* AGGR_SUM  */
  YYSYMBOL_AGGR_AVG = 65,                  /* AGGR_AVG  */
  YYSYMBOL_AGGR_COUNT = 66,                /* AGGR_COUNT  */
  YYSYMBOL_UNIQUE = 67,                    /* UNIQUE  */
  YYSYMBOL_LENGTH = 68,                    /* LENGTH  */
  YYSYMBOL_ROUND = 69,                     /* ROUND  */
  YYSYMBOL_DATE_FORMAT = 70,               /* DATE_FORMAT  */
  YYSYMBOL_GROUP = 71,                     /* GROUP  */
  YYSYMBOL_HAVING = 72,                    /* HAVING  */
  YYSYMBOL_TEXT = 73,                      /* TEXT  */
  YYSYMBOL_NUMBER = 74,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 75,                     /* FLOAT  */
  YYSYMBOL_ID = 76,                        /* ID  */
  YYSYMBOL_DATE = 77,                      /* DATE  */
  YYSYMBOL_SSS = 78,                       /* SSS  */
  YYSYMBOL_79_ = 79,                       /* '+'  */
  YYSYMBOL_80_ = 80,                       /* '-'  */
  YYSYMBOL_81_ = 81,                       /* '*'  */
  YYSYMBOL_82_ = 82,                       /* '/'  */
  YYSYMBOL_UMINUS = 83,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 84,                  /* $accept  */
  YYSYMBOL_commands = 85,                  /* commands  */
  YYSYMBOL_command_wrapper = 86,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 87,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 88,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 89,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 90,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 91,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 92,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 93,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 94,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 95,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 96,         /* create_index_stmt  */
  YYSYMBOL_create_unique_index_stmt = 97,  /* create_unique_index_stmt  */
  YYSYMBOL_drop_index_stmt = 98,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 99,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 100,            /* attr_def_list  */
  YYSYMBOL_attr_def = 101,                 /* attr_def  */
  YYSYMBOL_number = 102,                   /* number  */
  YYSYMBOL_type = 103,                     /* type  */
  YYSYMBOL_insert_stmt = 104,              /* insert_stmt  */
  YYSYMBOL_value_list = 105,               /* value_list  */
  YYSYMBOL_value = 106,                    /* value  */
  YYSYMBOL_delete_stmt = 107,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 108,              /* update_stmt  */
  YYSYMBOL_set_attr_list = 109,            /* set_attr_list  */
  YYSYMBOL_select_stmt = 110,              /* select_stmt  */
  YYSYMBOL_group_by = 111,                 /* group_by  */
  YYSYMBOL_having = 112,                   /* having  */
  YYSYMBOL_having_condition_list = 113,    /* having_condition_list  */
  YYSYMBOL_having_condition = 114,         /* having_condition  */
  YYSYMBOL_calc_stmt = 115,                /* calc_stmt  */
  YYSYMBOL_expression_list = 116,          /* expression_list  */
  YYSYMBOL_arithmetic_expr = 117,          /* arithmetic_expr  */
  YYSYMBOL_rel_attr = 118,                 /* rel_attr  */
  YYSYMBOL_rel_attr_list = 119,            /* rel_attr_list  */
  YYSYMBOL_attr_list_index = 120,          /* attr_list_index  */
  YYSYMBOL_select_attr = 121,              /* select_attr  */
  YYSYMBOL_rel_attr_item = 122,            /* rel_attr_item  */
  YYSYMBOL_attr_list = 123,                /* attr_list  */
  YYSYMBOL_from = 124,                     /* from  */
  YYSYMBOL_rel_list = 125,                 /* rel_list  */
  YYSYMBOL_rel_item = 126,                 /* rel_item  */
  YYSYMBOL_inner_join_list = 127,          /* inner_join_list  */
  YYSYMBOL_join_clause = 128,              /* join_clause  */
  YYSYMBOL_join_conditions = 129,          /* join_conditions  */
  YYSYMBOL_order_direction = 130,          /* order_direction  */
  YYSYMBOL_order_by_item = 131,            /* order_by_item  */
  YYSYMBOL_order_by_list = 132,            /* order_by_list  */
  YYSYMBOL_order_by = 133,                 /* order_by  */
  YYSYMBOL_where = 134,                    /* where  */
  YYSYMBOL_condition_list = 135,           /* condition_list  */
  YYSYMBOL_condition = 136,                /* condition  */
  YYSYMBOL_add_expr = 137,                 /* add_expr  */
  YYSYMBOL_mul_expr = 138,                 /* mul_expr  */
  YYSYMBOL_unary_expr = 139,               /* unary_expr  */
  YYSYMBOL_aggr_func_expr = 140,           /* aggr_func_expr  */
  YYSYMBOL_aggr_func_type = 141,           /* aggr_func_type  */
  YYSYMBOL_sub_select_expr = 142,          /* sub_select_expr  */
  YYSYMBOL_sub_select_list = 143,          /* sub_select_list  */
  YYSYMBOL_func_expr = 144,                /* func_expr  */
  YYSYMBOL_comp_op = 145,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 146,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 147,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 148,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 149             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  87
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   377

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  171
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  326

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   334


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    81,    79,     2,    80,     2,    82,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    83
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   256,   256,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   288,   294,   299,   305,   311,   317,
     323,   330,   336,   344,   365,   385,   395,   414,   417,   430,
     438,   446,   454,   463,   471,   479,   491,   495,   496,   497,
     498,   501,   516,   519,   531,   535,   547,   552,   560,   571,
     596,   599,   616,   623,   668,   671,   676,   688,   691,   702,
     705,   716,   723,   733,   738,   750,   753,   756,   759,   762,
     766,   769,   777,   782,   792,   795,   805,   808,   821,   826,
     839,   844,   849,   853,   858,   867,   870,   881,   887,   896,
     899,   909,   913,   918,   933,   936,   947,   957,   960,   965,
     975,   978,   982,   988,  1001,  1005,  1014,  1017,  1024,  1027,
    1033,  1038,  1044,  1054,  1057,  1060,  1063,  1066,  1071,  1080,
    1083,  1086,  1093,  1096,  1099,  1106,  1109,  1112,  1115,  1119,
    1122,  1125,  1128,  1131,  1138,  1143,  1148,  1156,  1159,  1162,
    1165,  1172,  1214,  1229,  1232,  1235,  1238,  1244,  1245,  1246,
    1247,  1248,  1249,  1250,  1251,  1252,  1253,  1257,  1270,  1278,
    1288,  1289
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "CALC", "SELECT", "DESC", "ASC",
  "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE",
  "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "EQ",
  "LT", "GT", "LE", "GE", "NE", "INNER", "SUB", "JOIN", "ORDER", "BY",
  "OR", "IN", "EXISTS", "IS", "NOT", "NULL_VALUE", "LIKE_T", "NOT_LIKE_T",
  "AS", "AGGR_MAX", "AGGR_MIN", "AGGR_SUM", "AGGR_AVG", "AGGR_COUNT",
  "UNIQUE", "LENGTH", "ROUND", "DATE_FORMAT", "GROUP", "HAVING", "TEXT",
  "NUMBER", "FLOAT", "ID", "DATE", "SSS", "'+'", "'-'", "'*'", "'/'",
  "UMINUS", "$accept", "commands", "command_wrapper", "exit_stmt",
  "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "create_unique_index_stmt", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "number", "type",
  "insert_stmt", "value_list", "value", "delete_stmt", "update_stmt",
  "set_attr_list", "select_stmt", "group_by", "having",
  "having_condition_list", "having_condition", "calc_stmt",
  "expression_list", "arithmetic_expr", "rel_attr", "rel_attr_list",
  "attr_list_index", "select_attr", "rel_attr_item", "attr_list", "from",
  "rel_list", "rel_item", "inner_join_list", "join_clause",
  "join_conditions", "order_direction", "order_by_item", "order_by_list",
  "order_by", "where", "condition_list", "condition", "add_expr",
  "mul_expr", "unary_expr", "aggr_func_expr", "aggr_func_type",
  "sub_select_expr", "sub_select_list", "func_expr", "comp_op",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-242)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-53)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     273,     0,    23,    90,    58,   -53,    26,  -242,    12,    24,
     -28,  -242,  -242,  -242,  -242,  -242,   -16,    61,   273,    62,
      92,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,    21,    33,    94,    40,    43,    90,  -242,  -242,
    -242,  -242,    90,  -242,  -242,    97,     9,   172,  -242,  -242,
    -242,  -242,   111,   130,   148,   151,    95,  -242,  -242,     4,
     132,   -35,    56,  -242,  -242,   155,  -242,  -242,  -242,  -242,
    -242,   104,   116,   153,   154,   158,  -242,  -242,  -242,  -242,
     182,   178,   150,  -242,   191,    11,  -242,    90,    90,    90,
      90,    90,    58,   209,   168,    15,  -242,    81,   172,   172,
     172,   -41,  -242,   169,    58,  -242,   172,   176,  -242,   172,
     172,   172,   172,   211,   210,   184,   107,   185,   186,   188,
     214,   189,  -242,  -242,   113,   113,  -242,  -242,   246,   204,
     107,   262,  -242,   266,    82,   122,     1,   -11,  -242,  -242,
     -29,   244,   277,   132,    56,  -242,    56,  -242,  -242,   123,
     275,   142,  -242,   257,  -242,   272,   -14,   284,   287,   230,
    -242,   169,   288,  -242,  -242,  -242,  -242,  -242,   172,   172,
     234,  -242,   263,   210,   244,   169,  -242,  -242,  -242,   107,
     172,   260,  -242,   -17,   212,   107,   306,  -242,  -242,  -242,
    -242,  -242,    -3,   186,   303,   248,   307,   244,  -242,   134,
     144,  -242,   169,   255,  -242,   277,   288,   -33,   172,   142,
     142,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,   167,
     276,  -242,  -242,   172,   311,   251,   258,   278,  -242,   284,
    -242,   305,   317,   248,   210,  -242,  -242,   301,   289,   267,
    -242,   321,   -33,  -242,  -242,   285,  -242,   172,   -33,   268,
     210,  -242,  -242,   323,  -242,  -242,   269,   248,   327,   317,
     255,   142,  -242,   248,   172,   296,  -242,  -242,   -33,   308,
    -242,   173,  -242,   317,  -242,   329,   267,   314,   331,   319,
     274,   300,   352,   107,   298,  -242,  -242,  -242,   296,   142,
     248,  -242,   172,  -242,   172,   248,  -242,   311,  -242,   338,
    -242,   331,   319,   -33,   221,   339,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,   248,  -242
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     170,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    13,    14,     8,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,    54,    55,
      56,    57,     0,    81,    72,    73,     0,     0,   147,   148,
     149,   150,     0,     0,     0,     0,   136,    90,   135,     0,
      88,    92,   129,   132,   140,     0,   141,   142,   139,    32,
      31,     0,     0,     0,     0,     0,   168,     1,   171,     2,
       0,     0,     0,    30,     0,     0,    80,     0,     0,     0,
       0,     0,     0,   136,   135,     0,   143,     0,     0,     0,
       0,     0,    62,     0,     0,    89,     0,     0,    94,     0,
       0,     0,     0,     0,   118,     0,     0,     0,     0,     0,
       0,     0,    79,    74,    75,    76,    77,    78,     0,     0,
       0,     0,   138,     0,     0,     0,     0,     0,   137,    91,
     101,   104,    97,    95,   131,    93,   130,   133,   134,     0,
       0,     0,    58,     0,   169,     0,     0,    37,     0,     0,
      35,     0,    52,   152,   146,   145,   153,   154,     0,     0,
       0,   102,     0,   118,   104,     0,    98,    96,   144,     0,
       0,     0,   119,   120,     0,     0,     0,    47,    49,    50,
      48,    40,    43,     0,     0,     0,     0,   104,    53,     0,
       0,   103,     0,    64,   105,    99,    52,   127,     0,     0,
       0,   157,   158,   159,   160,   161,   162,   165,   166,     0,
       0,   163,   164,     0,    60,     0,     0,     0,    45,    37,
      36,    82,    86,     0,   118,   155,   156,   107,     0,    67,
     100,     0,   128,   121,   122,     0,   124,     0,   123,     0,
     118,   167,    46,     0,    44,    38,     0,     0,     0,    86,
      64,     0,   106,     0,     0,   116,    51,   125,   126,     0,
      59,    39,    83,    86,    33,     0,    67,   108,    65,    69,
       0,     0,     0,     0,     0,    42,    87,    34,   116,     0,
       0,    66,     0,    68,     0,     0,    63,    60,    41,     0,
     109,    84,    69,    71,   112,   114,   117,    61,   151,    85,
      70,   110,   111,   113,     0,   115
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -242,  -242,   340,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,   121,   159,  -242,  -242,
    -242,  -167,    14,  -242,  -242,    54,  -242,    93,    78,    53,
      64,  -242,   270,   175,  -204,    57,  -241,   271,   256,   216,
     200,   157,  -161,  -162,  -242,  -242,  -242,  -242,    50,    77,
    -179,  -217,   105,    -4,   -63,   -32,  -242,  -242,  -242,  -242,
    -242,    87,  -242,  -242,  -242,  -242
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,   204,   167,   263,   202,
      34,   141,    68,    35,    36,   260,    37,   249,   275,   303,
     289,    38,    54,    55,   314,   301,   268,    69,    70,   115,
     151,   186,   152,   183,   184,   272,   323,   315,   316,   292,
     162,   192,   193,   194,    72,    73,    74,    75,    76,    77,
      78,   233,    39,    40,    41,    89
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,   242,   253,   254,   213,   208,    42,   112,    43,   179,
     197,   198,   199,   200,   116,   236,   116,    53,   219,   102,
     177,   178,   214,    79,   215,   106,   117,    56,   285,    45,
     132,    46,   180,    80,   142,   148,   220,   113,   116,   269,
     149,   118,   296,    81,   119,   244,   119,   181,    83,   251,
     116,   247,   105,   154,   237,   238,   156,    82,    57,   201,
      84,    53,    87,   283,   116,   270,    53,    44,   119,   288,
     104,    58,    59,    60,    61,    62,    56,    63,    64,    65,
     119,   280,   310,    48,    49,   103,    50,    51,   157,   158,
      98,    99,   100,   101,   119,    88,   311,    90,    71,    56,
      85,   175,    92,   144,   145,   146,   147,    57,    47,    91,
      71,    53,    53,    53,    53,    53,    93,    97,   159,    94,
      58,    59,    60,    61,    62,   111,    63,    64,    65,   107,
      57,   116,    48,    49,    66,    50,    51,   120,   121,    67,
     164,   176,   188,    58,    59,    60,    61,    62,   108,    63,
      64,    65,   114,   245,   172,    48,    49,   103,    50,    51,
      56,   119,   143,   246,    48,    49,   109,    50,    51,   110,
      52,   116,   116,   122,   209,   210,    98,    99,   100,   101,
     123,    48,    49,   116,    50,    51,   217,   -52,   140,   125,
      56,    57,   124,   116,   100,   101,   126,   190,   127,   191,
     128,   119,   119,   216,    58,    59,    60,    61,    62,   234,
      63,    64,    65,   119,   252,   129,    48,    49,   103,    50,
      51,    57,    95,   119,   255,   256,   130,    96,   131,   258,
     294,   295,   321,   322,    58,    59,    60,    61,    62,   139,
      63,    64,    65,   160,   161,   150,    48,    49,   103,    50,
      51,   169,   155,   278,   221,   222,   223,   224,   225,   226,
     163,   116,   166,   165,   168,   170,   227,   228,   229,   230,
     290,   231,   232,   134,   135,   136,   137,     1,     2,   171,
     148,   173,     3,     4,     5,   174,     6,     7,     8,     9,
      10,   119,   182,   189,    11,    12,    13,   185,   290,   195,
     313,    14,    15,   196,   203,   205,   206,   307,   140,    16,
     211,    17,   235,   212,    18,   218,   221,   222,   223,   224,
     225,   226,   240,   116,   241,   243,   248,   261,   227,   228,
     257,   259,   262,   231,   232,   266,   264,   267,   271,   274,
     276,   273,   281,   277,   279,   282,   284,   291,   297,   299,
     293,   300,   305,   119,   302,   306,   308,   318,    86,   324,
     265,   317,   239,   286,   298,   320,   312,   133,   319,   187,
     153,   207,   250,   138,   325,   309,   287,   304
};

static const yytype_int16 yycheck[] =
{
       4,   205,   219,   220,   183,   172,     6,     3,     8,    20,
      24,    25,    26,    27,    49,    18,    49,     3,    35,    10,
      19,    20,   184,    76,   185,    57,    61,    18,   269,     6,
      19,     8,    61,     7,    19,    76,    53,    33,    49,   243,
      81,    76,   283,    31,    79,   207,    79,    76,    76,   216,
      49,   212,    56,   116,    57,    58,   119,    33,    49,    73,
      76,    47,     0,   267,    49,   244,    52,    67,    79,   273,
      56,    62,    63,    64,    65,    66,    18,    68,    69,    70,
      79,   260,   299,    74,    75,    76,    77,    78,   120,   121,
      79,    80,    81,    82,    79,     3,   300,    76,   102,    18,
      39,    19,     8,   107,   108,   109,   110,    49,    18,    76,
     114,    97,    98,    99,   100,   101,    76,    20,   122,    76,
      62,    63,    64,    65,    66,    30,    68,    69,    70,    18,
      49,    49,    74,    75,    76,    77,    78,    81,    82,    81,
     126,    19,    19,    62,    63,    64,    65,    66,    18,    68,
      69,    70,    20,    19,   140,    74,    75,    76,    77,    78,
      18,    79,    81,    19,    74,    75,    18,    77,    78,    18,
      80,    49,    49,    18,   178,   179,    79,    80,    81,    82,
      76,    74,    75,    49,    77,    78,   190,    19,    20,    36,
      18,    49,    76,    49,    81,    82,    42,    55,    40,    57,
      18,    79,    79,   189,    62,    63,    64,    65,    66,   195,
      68,    69,    70,    79,   218,    37,    74,    75,    76,    77,
      78,    49,    47,    79,    57,    58,    76,    52,    37,   233,
      57,    58,    11,    12,    62,    63,    64,    65,    66,    30,
      68,    69,    70,    32,    34,    76,    74,    75,    76,    77,
      78,    37,    76,   257,    42,    43,    44,    45,    46,    47,
      76,    49,    76,    78,    76,    76,    54,    55,    56,    57,
     274,    59,    60,    98,    99,   100,   101,     4,     5,    33,
      76,    19,     9,    10,    11,    19,    13,    14,    15,    16,
      17,    79,    48,    18,    21,    22,    23,    20,   302,    42,
     304,    28,    29,    31,    20,    18,    76,   293,    20,    36,
      76,    38,     6,    50,    41,    55,    42,    43,    44,    45,
      46,    47,    19,    49,    76,    18,    71,    76,    54,    55,
      54,    20,    74,    59,    60,    30,    58,    20,    37,    72,
      19,    52,    19,    58,    76,    76,    19,    51,    19,    35,
      42,    20,    52,    79,    35,     3,    58,    19,    18,    20,
     239,   307,   203,   270,   286,   312,   302,    97,   311,   153,
     114,   171,   215,   102,   324,   298,   271,   290
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    13,    14,    15,    16,
      17,    21,    22,    23,    28,    29,    36,    38,    41,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   104,   107,   108,   110,   115,   146,
     147,   148,     6,     8,    67,     6,     8,    18,    74,    75,
      77,    78,    80,   106,   116,   117,    18,    49,    62,    63,
      64,    65,    66,    68,    69,    70,    76,    81,   106,   121,
     122,   137,   138,   139,   140,   141,   142,   143,   144,    76,
       7,    31,    33,    76,    76,    39,    86,     0,     3,   149,
      76,    76,     8,    76,    76,   117,   117,    20,    79,    80,
      81,    82,    10,    76,   106,   137,   139,    18,    18,    18,
      18,    30,     3,    33,    20,   123,    49,    61,    76,    79,
      81,    82,    18,    76,    76,    36,    42,    40,    18,    37,
      76,    37,    19,   116,   117,   117,   117,   117,   121,    30,
      20,   105,    19,    81,   137,   137,   137,   137,    76,    81,
      76,   124,   126,   122,   138,    76,   138,   139,   139,   137,
      32,    34,   134,    76,   106,    78,    76,   101,    76,    37,
      76,    33,   106,    19,    19,    19,    19,    19,    20,    20,
      61,    76,    48,   127,   128,    20,   125,   123,    19,    18,
      55,    57,   135,   136,   137,    42,    31,    24,    25,    26,
      27,    73,   103,    20,   100,    18,    76,   124,   105,   137,
     137,    76,    50,   134,   127,   126,   106,   137,    55,    35,
      53,    42,    43,    44,    45,    46,    47,    54,    55,    56,
      57,    59,    60,   145,   106,     6,    18,    57,    58,   101,
      19,    76,   118,    18,   127,    19,    19,   126,    71,   111,
     125,   105,   137,   135,   135,    57,    58,    54,   137,    20,
     109,    76,    74,   102,    58,   100,    30,    20,   120,   118,
     134,    37,   129,    52,    72,   112,    19,    58,   137,    76,
     134,    19,    76,   118,    19,   120,   111,   136,   118,   114,
     137,    51,   133,    42,    57,    58,   120,    19,   112,    35,
      20,   119,    35,   113,   145,    52,     3,   106,    58,   133,
     135,   118,   114,   137,   118,   131,   132,   109,    19,   119,
     113,    11,    12,   130,    20,   132
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    85,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   100,   101,
     101,   101,   101,   101,   101,   101,   102,   103,   103,   103,
     103,   104,   105,   105,   106,   106,   106,   106,   107,   108,
     109,   109,   110,   110,   111,   111,   111,   112,   112,   113,
     113,   114,   115,   116,   116,   117,   117,   117,   117,   117,
     117,   117,   118,   118,   119,   119,   120,   120,   121,   121,
     122,   122,   122,   122,   122,   123,   123,   124,   124,   125,
     125,   126,   126,   126,   127,   127,   128,   129,   129,   129,
     130,   130,   130,   131,   132,   132,   133,   133,   134,   134,
     135,   135,   135,   136,   136,   136,   136,   136,   136,   137,
     137,   137,   138,   138,   138,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   140,   140,   140,   141,   141,   141,
     141,   142,   143,   144,   144,   144,   144,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   146,   147,   148,
     149,   149
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     9,    10,     5,     7,     0,     3,     5,
       2,     7,     6,     2,     4,     3,     1,     1,     1,     1,
       1,     8,     0,     3,     1,     1,     1,     1,     4,     8,
       0,     5,     3,    10,     0,     3,     4,     0,     3,     0,
       3,     3,     2,     1,     3,     3,     3,     3,     3,     3,
       2,     1,     1,     3,     0,     3,     0,     3,     1,     2,
       1,     3,     1,     3,     2,     0,     3,     1,     2,     0,
       3,     1,     2,     3,     0,     2,     4,     0,     2,     4,
       1,     1,     0,     2,     1,     3,     0,     3,     0,     2,
       1,     3,     3,     3,     3,     4,     4,     2,     3,     1,
       3,     3,     1,     3,     3,     1,     1,     3,     3,     1,
       1,     1,     1,     2,     4,     4,     4,     1,     1,     1,
       1,    11,     4,     4,     4,     6,     6,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     7,     2,     4,
       0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 257 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1908 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 288 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1917 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 294 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1925 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 299 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1933 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 305 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1941 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 311 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1949 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 317 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1957 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 323 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1967 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 330 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1975 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 336 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1985 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE rel_attr attr_list_index RBRACE  */
#line 345 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);

      std::vector<RelAttrSqlNode> *attrs = (yyvsp[-1].attr_list);
      if(attrs == nullptr) {
        attrs = new std::vector<RelAttrSqlNode>;
      }
      create_index.attributes_names.swap(*attrs);
      create_index.attributes_names.emplace_back(*(yyvsp[-2].rel_attr_item));
      std::reverse(create_index.attributes_names.begin(), create_index.attributes_names.end());
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].rel_attr_item));
    }
#line 2007 "yacc_sql.cpp"
    break;

  case 34: /* create_unique_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE rel_attr attr_list_index RBRACE  */
#line 366 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_UNIQUE_INDEX);
      CreateUniqueIndexSqlNode &create_unique_index = (yyval.sql_node)->create_unique_index;
      create_unique_index.index_name = (yyvsp[-6].string);
      create_unique_index.relation_name = (yyvsp[-4].string);

      std::vector<RelAttrSqlNode> *attrs = (yyvsp[-1].attr_list);
      if(attrs == nullptr) {
        attrs = new std::vector<RelAttrSqlNode>;
      }
      create_unique_index.attributes_names.swap(*attrs);
      create_unique_index.attributes_names.emplace_back(*(yyvsp[-2].rel_attr_item));
      std::reverse(create_unique_index.attributes_names.begin(), create_unique_index.attributes_names.end());
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].rel_attr_item));
    }
#line 2029 "yacc_sql.cpp"
    break;

  case 35: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 386 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2041 "yacc_sql.cpp"
    break;

  case 36: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 396 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 2061 "yacc_sql.cpp"
    break;

  case 37: /* attr_def_list: %empty  */
#line 414 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2069 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 418 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));  // 按照语法树递归执行，最后一个attr将会放到vector的第一个位置，所以在调用attr_def_list的部分需要reverse
      delete (yyvsp[-1].attr_info);
    }
#line 2083 "yacc_sql.cpp"
    break;

  case 39: /* attr_def: ID type LBRACE number RBRACE  */
#line 431 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      free((yyvsp[-4].string));
    }
#line 2095 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID TEXT  */
#line 439 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = CHARS;
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4094;
      free((yyvsp[-1].string));
		}
#line 2107 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type LBRACE number RBRACE NOT NULL_VALUE  */
#line 447 "yacc_sql.y"
                {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      free((yyvsp[-6].string));
		}
#line 2119 "yacc_sql.cpp"
    break;

  case 42: /* attr_def: ID type LBRACE number RBRACE NULL_VALUE  */
#line 455 "yacc_sql.y"
                {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-5].string));
		}
#line 2132 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type  */
#line 464 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      free((yyvsp[-1].string));
    }
#line 2144 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type NOT NULL_VALUE  */
#line 472 "yacc_sql.y"
                {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      free((yyvsp[-3].string));
		}
#line 2156 "yacc_sql.cpp"
    break;

  case 45: /* attr_def: ID type NULL_VALUE  */
#line 480 "yacc_sql.y"
                {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-2].string));
		}
#line 2169 "yacc_sql.cpp"
    break;

  case 46: /* number: NUMBER  */
#line 491 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2175 "yacc_sql.cpp"
    break;

  case 47: /* type: INT_T  */
#line 495 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2181 "yacc_sql.cpp"
    break;

  case 48: /* type: DATE_T  */
#line 496 "yacc_sql.y"
                {(yyval.number)=DATES;}
#line 2187 "yacc_sql.cpp"
    break;

  case 49: /* type: STRING_T  */
#line 497 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2193 "yacc_sql.cpp"
    break;

  case 50: /* type: FLOAT_T  */
#line 498 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2199 "yacc_sql.cpp"
    break;

  case 51: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 502 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
    }
#line 2214 "yacc_sql.cpp"
    break;

  case 52: /* value_list: %empty  */
#line 516 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2222 "yacc_sql.cpp"
    break;

  case 53: /* value_list: COMMA value value_list  */
#line 519 "yacc_sql.y"
                              {   
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2236 "yacc_sql.cpp"
    break;

  case 54: /* value: NUMBER  */
#line 531 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2245 "yacc_sql.cpp"
    break;

  case 55: /* value: FLOAT  */
#line 535 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2254 "yacc_sql.cpp"
    break;

  case 56: /* value: DATE  */
#line 547 "yacc_sql.y"
           {    // T1修改点
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp, 0, true);    // 构建Date类型的Value
      free(tmp);
    }
#line 2264 "yacc_sql.cpp"
    break;

  case 57: /* value: SSS  */
#line 552 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2274 "yacc_sql.cpp"
    break;

  case 58: /* delete_stmt: DELETE FROM ID where  */
#line 561 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2287 "yacc_sql.cpp"
    break;

  case 59: /* update_stmt: UPDATE ID SET ID EQ value set_attr_list where  */
#line 572 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-6].string);

      SetSqlNode *col = new SetSqlNode;
      col->attribute_name = (yyvsp[-4].string);
      col->value = *(yyvsp[-2].value);
      
      std::vector<SetSqlNode> *sets = (yyvsp[-1].set_attrs);
      if (nullptr != (yyvsp[-1].set_attrs)) {
        (yyval.sql_node)->update.set_cols.swap(*sets);
      }
      (yyval.sql_node)->update.set_cols.emplace_back(*col);

      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->update.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
    }
#line 2312 "yacc_sql.cpp"
    break;

  case 60: /* set_attr_list: %empty  */
#line 596 "yacc_sql.y"
    {
      (yyval.set_attrs) = nullptr;
    }
#line 2320 "yacc_sql.cpp"
    break;

  case 61: /* set_attr_list: COMMA ID EQ value set_attr_list  */
#line 600 "yacc_sql.y"
    {
      (yyval.set_attrs) = new std::vector<SetSqlNode>;
      SetSqlNode *col = new SetSqlNode;
      col->attribute_name = (yyvsp[-3].string);
      col->value = *(yyvsp[-1].value);
      
      std::vector<SetSqlNode> *sets = (yyvsp[0].set_attrs);
      if(nullptr != sets) {
        (yyval.set_attrs)->swap(*sets);
      }
      (yyval.set_attrs)->emplace_back(*col);
      free((yyvsp[-3].string));
    }
#line 2338 "yacc_sql.cpp"
    break;

  case 62: /* select_stmt: SELECT select_attr SEMICOLON  */
#line 616 "yacc_sql.y"
                                 {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-1].attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-1].attr_list));
        delete (yyvsp[-1].attr_list);
      }
    }
#line 2350 "yacc_sql.cpp"
    break;

  case 63: /* select_stmt: SELECT select_attr FROM from inner_join_list where group_by having order_by SEMICOLON  */
#line 624 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-8].attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-8].attr_list));
        delete (yyvsp[-8].attr_list);
      }
      // std::reverse($$->selection.attributes.begin(), $$->selection.attributes.end());   // 为什么这里要反转？因为select_attr的写法是反着的。

      if ((yyvsp[-6].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-6].relation_list));
        delete (yyvsp[-6].relation_list);
      }
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());   // 为什么这里要反转？因为select_attr的写法是反着的。

      if ((yyvsp[-5].inner_join_list) != nullptr) {
        (yyval.sql_node)->selection.inner_join_clauses.swap(*(yyvsp[-5].inner_join_list));
        delete (yyvsp[-5].inner_join_list);
      }
      std::reverse((yyval.sql_node)->selection.inner_join_clauses.begin(), (yyval.sql_node)->selection.inner_join_clauses.end());   

      if ((yyvsp[-4].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions = (yyvsp[-4].expression);
      }

      if ((yyvsp[-3].attr_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-3].attr_list));
        delete (yyvsp[-3].attr_list);
      }
      std::reverse((yyval.sql_node)->selection.group_by.begin(), (yyval.sql_node)->selection.group_by.end());   

      if ((yyvsp[-2].expression) != nullptr) {
        (yyval.sql_node)->selection.havings = (yyvsp[-2].expression);
      }

      if ((yyvsp[-1].order_by_list) != nullptr) {
        (yyval.sql_node)->selection.order_by_nodes.swap(*(yyvsp[-1].order_by_list));
        delete (yyvsp[-1].order_by_list);
      }
      std::reverse((yyval.sql_node)->selection.order_by_nodes.begin(), (yyval.sql_node)->selection.order_by_nodes.end());   

    }
#line 2396 "yacc_sql.cpp"
    break;

  case 64: /* group_by: %empty  */
#line 668 "yacc_sql.y"
                    {
    (yyval.attr_list) = nullptr;
  }
#line 2404 "yacc_sql.cpp"
    break;

  case 65: /* group_by: GROUP BY rel_attr  */
#line 671 "yacc_sql.y"
                            {
    (yyval.attr_list) = new std::vector<RelAttrSqlNode>;
    (yyval.attr_list)->emplace_back(*(yyvsp[0].rel_attr_item));
    delete (yyvsp[0].rel_attr_item);
	}
#line 2414 "yacc_sql.cpp"
    break;

  case 66: /* group_by: GROUP BY rel_attr rel_attr_list  */
#line 676 "yacc_sql.y"
                                    {
    std::vector<RelAttrSqlNode> *temp = (yyvsp[0].attr_list);
    if (nullptr == temp) {
      temp = new std::vector<RelAttrSqlNode>;
    }
    temp->emplace_back(*(yyvsp[-1].rel_attr_item));
    delete (yyvsp[-1].rel_attr_item);
    (yyval.attr_list) = temp;
  }
#line 2428 "yacc_sql.cpp"
    break;

  case 67: /* having: %empty  */
#line 688 "yacc_sql.y"
               { 
    (yyval.expression) = nullptr;
  }
#line 2436 "yacc_sql.cpp"
    break;

  case 68: /* having: HAVING having_condition having_condition_list  */
#line 691 "yacc_sql.y"
                                                  {	
    ConjunctionExpr *con_expr = dynamic_cast<ConjunctionExpr *>((yyvsp[0].expression));
    if (nullptr == con_expr) {
      con_expr = new ConjunctionExpr();
    }
    con_expr->add_condition((yyvsp[-1].expression));
    (yyval.expression) = con_expr;
  }
#line 2449 "yacc_sql.cpp"
    break;

  case 69: /* having_condition_list: %empty  */
#line 702 "yacc_sql.y"
              {
    (yyval.expression) = nullptr;
  }
#line 2457 "yacc_sql.cpp"
    break;

  case 70: /* having_condition_list: AND having_condition having_condition_list  */
#line 705 "yacc_sql.y"
                                               {
    ConjunctionExpr *con_expr = dynamic_cast<ConjunctionExpr *>((yyvsp[0].expression));
    if (nullptr == con_expr) {
      con_expr = new ConjunctionExpr();
    }
    con_expr->add_condition((yyvsp[-1].expression));
    (yyval.expression) = con_expr;
  }
#line 2470 "yacc_sql.cpp"
    break;

  case 71: /* having_condition: add_expr comp_op add_expr  */
#line 716 "yacc_sql.y"
                           {
    ComparisonExpr *comp_expr = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    (yyval.expression) = comp_expr;
  }
#line 2479 "yacc_sql.cpp"
    break;

  case 72: /* calc_stmt: CALC expression_list  */
#line 724 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2490 "yacc_sql.cpp"
    break;

  case 73: /* expression_list: arithmetic_expr  */
#line 734 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2499 "yacc_sql.cpp"
    break;

  case 74: /* expression_list: arithmetic_expr COMMA expression_list  */
#line 739 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2512 "yacc_sql.cpp"
    break;

  case 75: /* arithmetic_expr: arithmetic_expr '+' arithmetic_expr  */
#line 750 "yacc_sql.y"
                                        {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2520 "yacc_sql.cpp"
    break;

  case 76: /* arithmetic_expr: arithmetic_expr '-' arithmetic_expr  */
#line 753 "yacc_sql.y"
                                          {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2528 "yacc_sql.cpp"
    break;

  case 77: /* arithmetic_expr: arithmetic_expr '*' arithmetic_expr  */
#line 756 "yacc_sql.y"
                                          {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2536 "yacc_sql.cpp"
    break;

  case 78: /* arithmetic_expr: arithmetic_expr '/' arithmetic_expr  */
#line 759 "yacc_sql.y"
                                          {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2544 "yacc_sql.cpp"
    break;

  case 79: /* arithmetic_expr: LBRACE arithmetic_expr RBRACE  */
#line 762 "yacc_sql.y"
                                    {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2553 "yacc_sql.cpp"
    break;

  case 80: /* arithmetic_expr: '-' arithmetic_expr  */
#line 766 "yacc_sql.y"
                                       {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2561 "yacc_sql.cpp"
    break;

  case 81: /* arithmetic_expr: value  */
#line 769 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2571 "yacc_sql.cpp"
    break;

  case 82: /* rel_attr: ID  */
#line 777 "yacc_sql.y"
       {
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2581 "yacc_sql.cpp"
    break;

  case 83: /* rel_attr: ID DOT ID  */
#line 782 "yacc_sql.y"
                {
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr_item)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2593 "yacc_sql.cpp"
    break;

  case 84: /* rel_attr_list: %empty  */
#line 792 "yacc_sql.y"
  {
    (yyval.attr_list) = nullptr;
  }
#line 2601 "yacc_sql.cpp"
    break;

  case 85: /* rel_attr_list: COMMA rel_attr rel_attr_list  */
#line 795 "yacc_sql.y"
                                 {
    std::vector<RelAttrSqlNode> *temp = (yyvsp[0].attr_list);
    if (nullptr == temp) {
      temp = new std::vector<RelAttrSqlNode>;
    }
    temp->emplace_back(*(yyvsp[-1].rel_attr_item));
    (yyval.attr_list) = temp;
  }
#line 2614 "yacc_sql.cpp"
    break;

  case 86: /* attr_list_index: %empty  */
#line 805 "yacc_sql.y"
  {
    (yyval.attr_list) = nullptr;
  }
#line 2622 "yacc_sql.cpp"
    break;

  case 87: /* attr_list_index: COMMA rel_attr attr_list_index  */
#line 808 "yacc_sql.y"
                                   {
    std:vector<RelAttrSqlNode> *temp = (yyvsp[0].attr_list);
    if (temp == nullptr) {
      temp = new std::vector<RelAttrSqlNode>;
    }
    temp->emplace_back(*(yyvsp[-1].rel_attr_item));
    (yyval.attr_list) = temp;
    free (yyvsp[-1].rel_attr_item);
  }
#line 2636 "yacc_sql.cpp"
    break;

  case 88: /* select_attr: rel_attr_item  */
#line 821 "yacc_sql.y"
                {
    (yyval.attr_list) = new std::vector<RelAttrSqlNode>;
    (yyval.attr_list)->emplace_back(*(yyvsp[0].rel_attr_item));
    delete (yyvsp[0].rel_attr_item);
  }
#line 2646 "yacc_sql.cpp"
    break;

  case 89: /* select_attr: rel_attr_item attr_list  */
#line 826 "yacc_sql.y"
                            {
    std::vector<RelAttrSqlNode> *temp = (yyvsp[0].attr_list);
    if (temp == nullptr) {
      temp = new std::vector<RelAttrSqlNode>;
    } 
    temp->emplace_back(*(yyvsp[-1].rel_attr_item));
    (yyval.attr_list) = temp;
    delete (yyvsp[-1].rel_attr_item);
  }
#line 2660 "yacc_sql.cpp"
    break;

  case 90: /* rel_attr_item: '*'  */
#line 839 "yacc_sql.y"
        {  
      (yyval.rel_attr_item) = new RelAttrSqlNode ;
      (yyval.rel_attr_item)->relation_name  = "";
      (yyval.rel_attr_item)->attribute_name = "*";
		}
#line 2670 "yacc_sql.cpp"
    break;

  case 91: /* rel_attr_item: ID DOT '*'  */
#line 844 "yacc_sql.y"
                 {
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->relation_name = (yyvsp[-2].string);
      (yyval.rel_attr_item)->attribute_name = "*";
    }
#line 2680 "yacc_sql.cpp"
    break;

  case 92: /* rel_attr_item: add_expr  */
#line 849 "yacc_sql.y"
               {       
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->expr = (yyvsp[0].expression);
    }
#line 2689 "yacc_sql.cpp"
    break;

  case 93: /* rel_attr_item: add_expr AS ID  */
#line 853 "yacc_sql.y"
                     {   // 只有单列和聚集函数才能取别名
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->expr = (yyvsp[-2].expression);
      (yyval.rel_attr_item)->alias = (yyvsp[0].string);
    }
#line 2699 "yacc_sql.cpp"
    break;

  case 94: /* rel_attr_item: add_expr ID  */
#line 858 "yacc_sql.y"
                  {
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->expr = (yyvsp[-1].expression);
      (yyval.rel_attr_item)->alias = (yyvsp[0].string);
    }
#line 2709 "yacc_sql.cpp"
    break;

  case 95: /* attr_list: %empty  */
#line 867 "yacc_sql.y"
    {
      (yyval.attr_list) = nullptr;
    }
#line 2717 "yacc_sql.cpp"
    break;

  case 96: /* attr_list: COMMA rel_attr_item attr_list  */
#line 870 "yacc_sql.y"
                                    {
      std::vector<RelAttrSqlNode> *temp = (yyvsp[0].attr_list);
      if (temp == nullptr) {
        temp = new std::vector<RelAttrSqlNode>;
      } 
      temp->emplace_back(*(yyvsp[-1].rel_attr_item));
      (yyval.attr_list) = temp;
    }
#line 2730 "yacc_sql.cpp"
    break;

  case 97: /* from: rel_item  */
#line 882 "yacc_sql.y"
  {
    (yyval.relation_list) = new std::vector<Relation>;
    (yyval.relation_list)->emplace_back(*(yyvsp[0].relation_item));
    delete (yyvsp[0].relation_item);
  }
#line 2740 "yacc_sql.cpp"
    break;

  case 98: /* from: rel_item rel_list  */
#line 888 "yacc_sql.y"
  {
    (yyval.relation_list) = (yyvsp[0].relation_list);
    (yyval.relation_list)->emplace_back(*(yyvsp[-1].relation_item));
    delete (yyvsp[-1].relation_item);
  }
#line 2750 "yacc_sql.cpp"
    break;

  case 99: /* rel_list: %empty  */
#line 896 "yacc_sql.y"
  {
    (yyval.relation_list) = nullptr;
  }
#line 2758 "yacc_sql.cpp"
    break;

  case 100: /* rel_list: COMMA rel_item rel_list  */
#line 899 "yacc_sql.y"
                            {	
    std::vector<Relation> * temp = (yyvsp[0].relation_list);
    if (temp == nullptr) {
      temp = new std::vector<Relation>;
      temp->emplace_back(*(yyvsp[-1].relation_item));
    }
    (yyval.relation_list) = temp;
  }
#line 2771 "yacc_sql.cpp"
    break;

  case 101: /* rel_item: ID  */
#line 909 "yacc_sql.y"
     {
    (yyval.relation_item) = new Relation;
    (yyval.relation_item)->relation_name = (yyvsp[0].string);
  }
#line 2780 "yacc_sql.cpp"
    break;

  case 102: /* rel_item: ID ID  */
#line 913 "yacc_sql.y"
         {       
    (yyval.relation_item) = new Relation;
    (yyval.relation_item)->relation_name = (yyvsp[-1].string);
    (yyval.relation_item)->alias = (yyvsp[0].string);
  }
#line 2790 "yacc_sql.cpp"
    break;

  case 103: /* rel_item: ID AS ID  */
#line 918 "yacc_sql.y"
            {
    (yyval.relation_item) = new Relation;
    (yyval.relation_item)->relation_name = (yyvsp[-2].string);
    (yyval.relation_item)->alias = (yyvsp[0].string);
  }
#line 2800 "yacc_sql.cpp"
    break;

  case 104: /* inner_join_list: %empty  */
#line 933 "yacc_sql.y"
    {
        (yyval.inner_join_list) = nullptr;
    }
#line 2808 "yacc_sql.cpp"
    break;

  case 105: /* inner_join_list: join_clause inner_join_list  */
#line 936 "yacc_sql.y"
                                  {
        if((yyvsp[0].inner_join_list) != nullptr) {
            (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
        } else {
            (yyval.inner_join_list) = new std::vector<InnerJoinNode>;
        }
        (yyval.inner_join_list)->push_back(*(yyvsp[-1].join_clause));
    }
#line 2821 "yacc_sql.cpp"
    break;

  case 106: /* join_clause: INNER JOIN rel_item join_conditions  */
#line 947 "yacc_sql.y"
                                        {
        (yyval.join_clause) = new InnerJoinNode;
        (yyval.join_clause)->relation_name = *(yyvsp[-1].relation_item);
        (yyval.join_clause)->conditions = (yyvsp[0].join_conditions);
        delete (yyvsp[-1].relation_item);
    }
#line 2832 "yacc_sql.cpp"
    break;

  case 107: /* join_conditions: %empty  */
#line 957 "yacc_sql.y"
    {
      (yyval.join_conditions) = nullptr;
    }
#line 2840 "yacc_sql.cpp"
    break;

  case 108: /* join_conditions: ON condition  */
#line 960 "yacc_sql.y"
                   {    // 如果有on关键字，则至少必须有一个condition
      ConjunctionExpr *temp = new ConjunctionExpr();
      temp->add_condition((yyvsp[0].expression));
      (yyval.join_conditions) = temp;
    }
#line 2850 "yacc_sql.cpp"
    break;

  case 109: /* join_conditions: ON condition AND condition_list  */
#line 965 "yacc_sql.y"
                                      {     
      ConjunctionExpr *base = static_cast<ConjunctionExpr *>((yyvsp[0].expression));
      assert(base != nullptr);
      base->add_condition((yyvsp[-2].expression));
      (yyval.join_conditions) = base;
    }
#line 2861 "yacc_sql.cpp"
    break;

  case 110: /* order_direction: DESC  */
#line 975 "yacc_sql.y"
         {
        (yyval.order_direction) = OrderDirection::DESC_;
    }
#line 2869 "yacc_sql.cpp"
    break;

  case 111: /* order_direction: ASC  */
#line 978 "yacc_sql.y"
          {
        (yyval.order_direction) = OrderDirection::ASC_;
    }
#line 2877 "yacc_sql.cpp"
    break;

  case 112: /* order_direction: %empty  */
#line 982 "yacc_sql.y"
    {
        (yyval.order_direction) = OrderDirection::ASC_;
    }
#line 2885 "yacc_sql.cpp"
    break;

  case 113: /* order_by_item: rel_attr order_direction  */
#line 988 "yacc_sql.y"
                             {
        (yyval.order_by_item) = new OrderByNode;
        (yyval.order_by_item)->attribute = *(yyvsp[-1].rel_attr_item);
        (yyval.order_by_item)->direction = (yyvsp[0].order_direction);
        delete (yyvsp[-1].rel_attr_item);
    }
#line 2896 "yacc_sql.cpp"
    break;

  case 114: /* order_by_list: order_by_item  */
#line 1001 "yacc_sql.y"
                  {
        (yyval.order_by_list) = new std::vector<OrderByNode>;
        (yyval.order_by_list)->push_back(*(yyvsp[0].order_by_item));
    }
#line 2905 "yacc_sql.cpp"
    break;

  case 115: /* order_by_list: order_by_item COMMA order_by_list  */
#line 1005 "yacc_sql.y"
                                        {
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
        (yyval.order_by_list)->emplace_back(*(yyvsp[-2].order_by_item));
        delete (yyvsp[-2].order_by_item);
    }
#line 2915 "yacc_sql.cpp"
    break;

  case 116: /* order_by: %empty  */
#line 1014 "yacc_sql.y"
    {
        (yyval.order_by_list) = nullptr;
    }
#line 2923 "yacc_sql.cpp"
    break;

  case 117: /* order_by: ORDER BY order_by_list  */
#line 1017 "yacc_sql.y"
                             {
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 2931 "yacc_sql.cpp"
    break;

  case 118: /* where: %empty  */
#line 1024 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
  }
#line 2939 "yacc_sql.cpp"
    break;

  case 119: /* where: WHERE condition_list  */
#line 1027 "yacc_sql.y"
                         {      
    (yyval.expression) = (yyvsp[0].expression);
  }
#line 2947 "yacc_sql.cpp"
    break;

  case 120: /* condition_list: condition  */
#line 1033 "yacc_sql.y"
              {
      ConjunctionExpr *temp = new ConjunctionExpr();
      temp->add_condition((yyvsp[0].expression));
      (yyval.expression) = temp;
    }
#line 2957 "yacc_sql.cpp"
    break;

  case 121: /* condition_list: condition AND condition_list  */
#line 1038 "yacc_sql.y"
                                   {        
      ConjunctionExpr *base = static_cast<ConjunctionExpr *>((yyvsp[0].expression));
      assert(base != nullptr);
      base->add_condition((yyvsp[-2].expression));
      (yyval.expression) = base;
    }
#line 2968 "yacc_sql.cpp"
    break;

  case 122: /* condition_list: condition OR condition_list  */
#line 1044 "yacc_sql.y"
                                  {        
      ConjunctionExpr *base = static_cast<ConjunctionExpr *>((yyvsp[0].expression));
      assert(base != nullptr);
      base->add_condition((yyvsp[-2].expression));
      base->set_conjunction_type(ConjunctionExpr::Type::OR);
      (yyval.expression) = base;
    }
#line 2980 "yacc_sql.cpp"
    break;

  case 123: /* condition: add_expr comp_op add_expr  */
#line 1054 "yacc_sql.y"
                             {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2988 "yacc_sql.cpp"
    break;

  case 124: /* condition: add_expr IS NULL_VALUE  */
#line 1057 "yacc_sql.y"
                             {
      // TODO
    }
#line 2996 "yacc_sql.cpp"
    break;

  case 125: /* condition: add_expr IS NOT NULL_VALUE  */
#line 1060 "yacc_sql.y"
                                 {
      // TODO:
    }
#line 3004 "yacc_sql.cpp"
    break;

  case 126: /* condition: add_expr NOT IN add_expr  */
#line 1063 "yacc_sql.y"
                               {
      (yyval.expression) = new ComparisonExpr(CompOp::NOT_IN, (yyvsp[-3].expression), (yyvsp[0].expression));
    }
#line 3012 "yacc_sql.cpp"
    break;

  case 127: /* condition: EXISTS add_expr  */
#line 1066 "yacc_sql.y"
                      {
      Value temp_value = Value(1);      // 创建一个临时对象当做表达式
      ValueExpr *value_expr = new ValueExpr(temp_value);
      (yyval.expression) = new ComparisonExpr(CompOp::EXISTS_OP, value_expr, (yyvsp[0].expression));
    }
#line 3022 "yacc_sql.cpp"
    break;

  case 128: /* condition: NOT EXISTS add_expr  */
#line 1071 "yacc_sql.y"
                          {
      Value temp_value = Value(1);      // 创建一个临时对象当做表达式
      ValueExpr *value_expr = new ValueExpr(temp_value);
      (yyval.expression) = new ComparisonExpr(CompOp::NOT_EXISTS, value_expr, (yyvsp[0].expression));
    }
#line 3032 "yacc_sql.cpp"
    break;

  case 129: /* add_expr: mul_expr  */
#line 1080 "yacc_sql.y"
             {
      (yyval.expression) = (yyvsp[0].expression); 
    }
#line 3040 "yacc_sql.cpp"
    break;

  case 130: /* add_expr: add_expr '+' mul_expr  */
#line 1083 "yacc_sql.y"
                            {
      (yyval.expression) = new ArithmeticExpr(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 3048 "yacc_sql.cpp"
    break;

  case 131: /* add_expr: add_expr SUB mul_expr  */
#line 1086 "yacc_sql.y"
                            {
      (yyval.expression) = new ArithmeticExpr(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 3056 "yacc_sql.cpp"
    break;

  case 132: /* mul_expr: unary_expr  */
#line 1093 "yacc_sql.y"
               {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3064 "yacc_sql.cpp"
    break;

  case 133: /* mul_expr: mul_expr '*' unary_expr  */
#line 1096 "yacc_sql.y"
                              {
      (yyval.expression) = new ArithmeticExpr(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 3072 "yacc_sql.cpp"
    break;

  case 134: /* mul_expr: mul_expr '/' unary_expr  */
#line 1099 "yacc_sql.y"
                              {
      (yyval.expression) = new ArithmeticExpr(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 3080 "yacc_sql.cpp"
    break;

  case 135: /* unary_expr: value  */
#line 1106 "yacc_sql.y"
          {     
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
    }
#line 3088 "yacc_sql.cpp"
    break;

  case 136: /* unary_expr: ID  */
#line 1109 "yacc_sql.y"
         {
      (yyval.expression) = new FieldExpr((yyvsp[0].string));
    }
#line 3096 "yacc_sql.cpp"
    break;

  case 137: /* unary_expr: ID DOT ID  */
#line 1112 "yacc_sql.y"
                {
      (yyval.expression) = new FieldExpr((yyvsp[0].string), (yyvsp[-2].string));
    }
#line 3104 "yacc_sql.cpp"
    break;

  case 138: /* unary_expr: LBRACE add_expr RBRACE  */
#line 1115 "yacc_sql.y"
                             {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_with_brace();
    }
#line 3113 "yacc_sql.cpp"
    break;

  case 139: /* unary_expr: func_expr  */
#line 1119 "yacc_sql.y"
                {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3121 "yacc_sql.cpp"
    break;

  case 140: /* unary_expr: aggr_func_expr  */
#line 1122 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3129 "yacc_sql.cpp"
    break;

  case 141: /* unary_expr: sub_select_expr  */
#line 1125 "yacc_sql.y"
                      {
       (yyval.expression) = (yyvsp[0].expression);
    }
#line 3137 "yacc_sql.cpp"
    break;

  case 142: /* unary_expr: sub_select_list  */
#line 1128 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 3145 "yacc_sql.cpp"
    break;

  case 143: /* unary_expr: SUB unary_expr  */
#line 1131 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
      (yyval.expression)->set_negtive();
    }
#line 3154 "yacc_sql.cpp"
    break;

  case 144: /* aggr_func_expr: aggr_func_type LBRACE add_expr RBRACE  */
#line 1139 "yacc_sql.y"
  {
    assert(ExprType::FIELD == (yyvsp[-1].expression)->type());
    (yyval.expression) = new AggrFuncExpression((yyvsp[-3].aggr_func_type), static_cast<FieldExpr*>((yyvsp[-1].expression)));
  }
#line 3163 "yacc_sql.cpp"
    break;

  case 145: /* aggr_func_expr: AGGR_COUNT LBRACE add_expr RBRACE  */
#line 1144 "yacc_sql.y"
  {
    assert(ExprType::FIELD == (yyvsp[-1].expression)->type());
    (yyval.expression) = new AggrFuncExpression(AggrFuncType::CNT, static_cast<FieldExpr*>((yyvsp[-1].expression)));
  }
#line 3172 "yacc_sql.cpp"
    break;

  case 146: /* aggr_func_expr: AGGR_COUNT LBRACE '*' RBRACE  */
#line 1149 "yacc_sql.y"
  {
    ValueExpr *temp = new ValueExpr(Value("*"));
    (yyval.expression) = new AggrFuncExpression(AggrFuncType::CNT, temp);
  }
#line 3181 "yacc_sql.cpp"
    break;

  case 147: /* aggr_func_type: AGGR_MAX  */
#line 1156 "yacc_sql.y"
             {
      (yyval.aggr_func_type) = AggrFuncType::MAX;
    }
#line 3189 "yacc_sql.cpp"
    break;

  case 148: /* aggr_func_type: AGGR_MIN  */
#line 1159 "yacc_sql.y"
               {
      (yyval.aggr_func_type) = AggrFuncType::MIN;
    }
#line 3197 "yacc_sql.cpp"
    break;

  case 149: /* aggr_func_type: AGGR_SUM  */
#line 1162 "yacc_sql.y"
               {
      (yyval.aggr_func_type) = AggrFuncType::SUM;
    }
#line 3205 "yacc_sql.cpp"
    break;

  case 150: /* aggr_func_type: AGGR_AVG  */
#line 1165 "yacc_sql.y"
               {
      (yyval.aggr_func_type) = AggrFuncType::AVG;
    }
#line 3213 "yacc_sql.cpp"
    break;

  case 151: /* sub_select_expr: LBRACE SELECT select_attr FROM from inner_join_list where group_by having order_by RBRACE  */
#line 1173 "yacc_sql.y"
  {
    ParsedSqlNode *temp= new ParsedSqlNode(SCF_SELECT);
    if ((yyvsp[-8].attr_list) != nullptr) {
      temp->selection.attributes.swap(*(yyvsp[-8].attr_list));
      delete (yyvsp[-8].attr_list);
    }
    if ((yyvsp[-6].relation_list) != nullptr) {
      temp->selection.relations.swap(*(yyvsp[-6].relation_list));
      delete (yyvsp[-6].relation_list);
    }
    std::reverse(temp->selection.relations.begin(), temp->selection.relations.end());   // 为什么这里要反转？因为select_attr的写法是反着的。
    if ((yyvsp[-5].inner_join_list) != nullptr) {
      temp->selection.inner_join_clauses.swap(*(yyvsp[-5].inner_join_list));
      delete (yyvsp[-5].inner_join_list);
    }
    std::reverse(temp->selection.inner_join_clauses.begin(), temp->selection.inner_join_clauses.end());   

    if ((yyvsp[-4].expression) != nullptr) {
      temp->selection.conditions = (yyvsp[-4].expression);
    }

    if ((yyvsp[-3].attr_list) != nullptr) {
      temp->selection.group_by.swap(*(yyvsp[-3].attr_list));
      delete (yyvsp[-3].attr_list);
    }
    std::reverse(temp->selection.group_by.begin(), temp->selection.group_by.end());   

    if ((yyvsp[-2].expression) != nullptr) {
      temp->selection.havings = (yyvsp[-2].expression);
    }

    if ((yyvsp[-1].order_by_list) != nullptr) {
      temp->selection.order_by_nodes.swap(*(yyvsp[-1].order_by_list));
      delete (yyvsp[-1].order_by_list);
    }
    SubQueryExpression *res = new SubQueryExpression(temp);
    (yyval.expression) = res;
  }
#line 3256 "yacc_sql.cpp"
    break;

  case 152: /* sub_select_list: LBRACE value value_list RBRACE  */
#line 1215 "yacc_sql.y"
    {
      std::vector<Value> *temp = (yyvsp[-1].value_list);
      if (temp != nullptr) {
        temp->push_back(*(yyvsp[-2].value));
      } else {
        temp = new std::vector<Value>{*(yyvsp[-2].value)};
      }

      (yyval.expression) = new ListExpression(*temp);
      (yyval.expression)->set_with_brace();
    }
#line 3272 "yacc_sql.cpp"
    break;

  case 153: /* func_expr: LENGTH LBRACE add_expr RBRACE  */
#line 1229 "yacc_sql.y"
                                {
    (yyval.expression) = new FuncExpression(FUNC_LENGTH, 1, (yyvsp[-1].expression), nullptr, true);
  }
#line 3280 "yacc_sql.cpp"
    break;

  case 154: /* func_expr: ROUND LBRACE add_expr RBRACE  */
#line 1232 "yacc_sql.y"
                                 {
    (yyval.expression) = new FuncExpression(FUNC_ROUND, 1, (yyvsp[-1].expression), nullptr, true);
  }
#line 3288 "yacc_sql.cpp"
    break;

  case 155: /* func_expr: ROUND LBRACE add_expr COMMA add_expr RBRACE  */
#line 1235 "yacc_sql.y"
                                                {
    (yyval.expression) = new FuncExpression(FUNC_ROUND, 2, (yyvsp[-3].expression), (yyvsp[-1].expression), true);
  }
#line 3296 "yacc_sql.cpp"
    break;

  case 156: /* func_expr: DATE_FORMAT LBRACE add_expr COMMA add_expr RBRACE  */
#line 1238 "yacc_sql.y"
                                                      {
    (yyval.expression) = new FuncExpression(FUNC_DATE_FORMAT, 2, (yyvsp[-3].expression), (yyvsp[-1].expression), true);
  }
#line 3304 "yacc_sql.cpp"
    break;

  case 157: /* comp_op: EQ  */
#line 1244 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3310 "yacc_sql.cpp"
    break;

  case 158: /* comp_op: LT  */
#line 1245 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3316 "yacc_sql.cpp"
    break;

  case 159: /* comp_op: GT  */
#line 1246 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3322 "yacc_sql.cpp"
    break;

  case 160: /* comp_op: LE  */
#line 1247 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3328 "yacc_sql.cpp"
    break;

  case 161: /* comp_op: GE  */
#line 1248 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3334 "yacc_sql.cpp"
    break;

  case 162: /* comp_op: NE  */
#line 1249 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3340 "yacc_sql.cpp"
    break;

  case 163: /* comp_op: LIKE_T  */
#line 1250 "yacc_sql.y"
             { (yyval.comp) = LIKE_OP; }
#line 3346 "yacc_sql.cpp"
    break;

  case 164: /* comp_op: NOT_LIKE_T  */
#line 1251 "yacc_sql.y"
                 {(yyval.comp) = NOT_LIKE_OP; }
#line 3352 "yacc_sql.cpp"
    break;

  case 165: /* comp_op: IN  */
#line 1252 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3358 "yacc_sql.cpp"
    break;

  case 166: /* comp_op: EXISTS  */
#line 1253 "yacc_sql.y"
             {(yyval.comp) = EXISTS_OP; }
#line 3364 "yacc_sql.cpp"
    break;

  case 167: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1258 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3378 "yacc_sql.cpp"
    break;

  case 168: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1271 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3387 "yacc_sql.cpp"
    break;

  case 169: /* set_variable_stmt: SET ID EQ value  */
#line 1279 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3399 "yacc_sql.cpp"
    break;


#line 3403 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1291 "yacc_sql.y"

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
