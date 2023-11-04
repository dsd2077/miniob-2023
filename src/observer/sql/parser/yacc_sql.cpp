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
  YYSYMBOL_NUMBER = 71,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 72,                     /* FLOAT  */
  YYSYMBOL_ID = 73,                        /* ID  */
  YYSYMBOL_DATE = 74,                      /* DATE  */
  YYSYMBOL_SSS = 75,                       /* SSS  */
  YYSYMBOL_76_ = 76,                       /* '+'  */
  YYSYMBOL_77_ = 77,                       /* '-'  */
  YYSYMBOL_78_ = 78,                       /* '*'  */
  YYSYMBOL_79_ = 79,                       /* '/'  */
  YYSYMBOL_UMINUS = 80,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 81,                  /* $accept  */
  YYSYMBOL_commands = 82,                  /* commands  */
  YYSYMBOL_command_wrapper = 83,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 84,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 85,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 86,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 87,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 88,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 89,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 90,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 91,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 92,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 93,         /* create_index_stmt  */
  YYSYMBOL_create_unique_index_stmt = 94,  /* create_unique_index_stmt  */
  YYSYMBOL_drop_index_stmt = 95,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 96,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 97,             /* attr_def_list  */
  YYSYMBOL_attr_def = 98,                  /* attr_def  */
  YYSYMBOL_number = 99,                    /* number  */
  YYSYMBOL_type = 100,                     /* type  */
  YYSYMBOL_insert_stmt = 101,              /* insert_stmt  */
  YYSYMBOL_value_list = 102,               /* value_list  */
  YYSYMBOL_value = 103,                    /* value  */
  YYSYMBOL_delete_stmt = 104,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 105,              /* update_stmt  */
  YYSYMBOL_set_attr_list = 106,            /* set_attr_list  */
  YYSYMBOL_select_stmt = 107,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 108,                /* calc_stmt  */
  YYSYMBOL_expression_list = 109,          /* expression_list  */
  YYSYMBOL_arithmetic_expr = 110,          /* arithmetic_expr  */
  YYSYMBOL_rel_attr = 111,                 /* rel_attr  */
  YYSYMBOL_attr_list_index = 112,          /* attr_list_index  */
  YYSYMBOL_select_attr = 113,              /* select_attr  */
  YYSYMBOL_rel_attr_item = 114,            /* rel_attr_item  */
  YYSYMBOL_attr_list = 115,                /* attr_list  */
  YYSYMBOL_from = 116,                     /* from  */
  YYSYMBOL_rel_list = 117,                 /* rel_list  */
  YYSYMBOL_rel_item = 118,                 /* rel_item  */
  YYSYMBOL_inner_join_list = 119,          /* inner_join_list  */
  YYSYMBOL_join_clause = 120,              /* join_clause  */
  YYSYMBOL_join_conditions = 121,          /* join_conditions  */
  YYSYMBOL_order_direction = 122,          /* order_direction  */
  YYSYMBOL_order_by_item = 123,            /* order_by_item  */
  YYSYMBOL_order_by_list = 124,            /* order_by_list  */
  YYSYMBOL_order_by = 125,                 /* order_by  */
  YYSYMBOL_where = 126,                    /* where  */
  YYSYMBOL_condition_list = 127,           /* condition_list  */
  YYSYMBOL_condition = 128,                /* condition  */
  YYSYMBOL_add_expr = 129,                 /* add_expr  */
  YYSYMBOL_mul_expr = 130,                 /* mul_expr  */
  YYSYMBOL_unary_expr = 131,               /* unary_expr  */
  YYSYMBOL_aggr_func_expr = 132,           /* aggr_func_expr  */
  YYSYMBOL_aggr_func_type = 133,           /* aggr_func_type  */
  YYSYMBOL_sub_select_expr = 134,          /* sub_select_expr  */
  YYSYMBOL_sub_select_list = 135,          /* sub_select_list  */
  YYSYMBOL_func_expr = 136,                /* func_expr  */
  YYSYMBOL_comp_op = 137,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 138,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 139,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 140,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 141             /* opt_semicolon  */
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
#define YYLAST   340

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  160
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  297

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   331


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
       2,     2,    78,    76,     2,    77,     2,    79,     2,     2,
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
      75,    80
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   245,   245,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   277,   283,   288,   294,   300,   306,
     312,   319,   325,   333,   354,   374,   384,   403,   406,   419,
     427,   435,   444,   452,   460,   472,   476,   477,   478,   479,
     482,   497,   500,   512,   516,   528,   533,   541,   552,   577,
     580,   597,   604,   639,   649,   654,   666,   669,   672,   675,
     678,   682,   685,   693,   698,   707,   710,   723,   728,   741,
     746,   751,   755,   760,   769,   772,   783,   789,   798,   801,
     811,   815,   820,   835,   838,   849,   859,   862,   867,   877,
     880,   884,   890,   903,   907,   916,   919,   930,   933,   939,
     944,   950,   960,   963,   966,   969,   972,   977,   986,   989,
     992,   999,  1002,  1005,  1012,  1015,  1018,  1021,  1025,  1028,
    1031,  1034,  1037,  1044,  1049,  1054,  1062,  1065,  1068,  1071,
    1078,  1086,  1101,  1104,  1107,  1110,  1116,  1117,  1118,  1119,
    1120,  1121,  1122,  1123,  1124,  1125,  1129,  1142,  1150,  1160,
    1161
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
  "UNIQUE", "LENGTH", "ROUND", "DATE_FORMAT", "NUMBER", "FLOAT", "ID",
  "DATE", "SSS", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept",
  "commands", "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt",
  "begin_stmt", "commit_stmt", "rollback_stmt", "drop_table_stmt",
  "show_tables_stmt", "desc_table_stmt", "create_index_stmt",
  "create_unique_index_stmt", "drop_index_stmt", "create_table_stmt",
  "attr_def_list", "attr_def", "number", "type", "insert_stmt",
  "value_list", "value", "delete_stmt", "update_stmt", "set_attr_list",
  "select_stmt", "calc_stmt", "expression_list", "arithmetic_expr",
  "rel_attr", "attr_list_index", "select_attr", "rel_attr_item",
  "attr_list", "from", "rel_list", "rel_item", "inner_join_list",
  "join_clause", "join_conditions", "order_direction", "order_by_item",
  "order_by_list", "order_by", "where", "condition_list", "condition",
  "add_expr", "mul_expr", "unary_expr", "aggr_func_expr", "aggr_func_type",
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

#define YYTABLE_NINF (-52)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     259,     4,    18,    10,    68,   -55,    33,  -242,    -6,    41,
     -30,  -242,  -242,  -242,  -242,  -242,   -13,    44,   259,    92,
      99,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,    43,    45,   113,    55,    89,    10,  -242,  -242,
    -242,  -242,    10,  -242,  -242,    12,    -7,   160,  -242,  -242,
    -242,  -242,   129,   153,   162,   173,    84,  -242,  -242,   144,
     187,   -40,   -48,  -242,  -242,   179,  -242,  -242,  -242,  -242,
    -242,   135,   145,   181,   178,   196,  -242,  -242,  -242,  -242,
     201,   184,   164,  -242,   202,     1,  -242,    10,    10,    10,
      10,    10,   208,    27,   221,    74,  -242,    95,   160,   160,
     160,   -51,   168,    68,  -242,   160,   169,  -242,   160,   160,
     160,   160,   211,   210,   172,    29,   171,   174,   175,   212,
     180,  -242,  -242,   -27,   -27,  -242,  -242,   182,    29,   232,
    -242,  -242,   233,    80,    96,    -4,   100,  -242,  -242,   -44,
     206,   236,   187,   -48,  -242,   -48,  -242,  -242,   105,   243,
     130,  -242,   220,  -242,   234,   189,   246,   249,   198,  -242,
     257,  -242,  -242,  -242,  -242,  -242,   160,   160,   205,  -242,
     235,   210,   206,   168,  -242,  -242,  -242,    29,   160,   228,
    -242,   -16,   247,    29,   278,  -242,  -242,  -242,  -242,    94,
     174,   267,   225,   281,  -242,   106,   134,  -242,   168,   254,
    -242,   236,   257,   -41,   160,   130,   130,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,    52,   255,  -242,  -242,   160,
     288,   237,   240,   256,  -242,   246,  -242,   282,   293,   225,
    -242,  -242,   279,   263,  -242,  -242,   298,   -41,  -242,  -242,
     260,  -242,   160,   -41,   248,   210,  -242,  -242,   300,  -242,
    -242,   251,   225,   301,   293,   130,  -242,   225,  -242,  -242,
     -41,   280,  -242,    69,  -242,   293,  -242,   306,   291,   177,
     307,  -242,    29,   270,  -242,  -242,  -242,   130,  -242,  -242,
    -242,   225,   288,  -242,  -242,  -242,  -242
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     159,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    13,    14,     8,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,    53,    54,
      55,    56,     0,    72,    63,    64,     0,     0,   136,   137,
     138,   139,     0,     0,     0,     0,   125,    79,   124,    61,
      77,    81,   118,   121,   129,     0,   130,   131,   128,    32,
      31,     0,     0,     0,     0,     0,   157,     1,   160,     2,
       0,     0,     0,    30,     0,     0,    71,     0,     0,     0,
       0,     0,   125,   124,     0,     0,   132,     0,     0,     0,
       0,     0,     0,     0,    78,     0,     0,    83,     0,     0,
       0,     0,     0,   107,     0,     0,     0,     0,     0,     0,
       0,    70,    65,    66,    67,    68,    69,     0,     0,     0,
     140,   127,     0,     0,     0,     0,     0,   126,    80,    90,
      93,    86,    84,   120,    82,   119,   122,   123,     0,     0,
       0,    57,     0,   158,     0,     0,    37,     0,     0,    35,
      51,   141,   135,   134,   142,   143,     0,     0,     0,    91,
       0,   107,    93,     0,    87,    85,   133,     0,     0,     0,
     108,   109,     0,     0,     0,    46,    48,    49,    47,    42,
       0,     0,     0,     0,    52,     0,     0,    92,     0,   105,
      94,    88,    51,   116,     0,     0,     0,   146,   147,   148,
     149,   150,   151,   154,   155,     0,     0,   152,   153,     0,
      59,     0,     0,     0,    44,    37,    36,    73,    75,     0,
     144,   145,    96,     0,    62,    89,     0,   117,   110,   111,
       0,   113,     0,   112,     0,   107,   156,    45,     0,    43,
      38,     0,     0,     0,    75,     0,    95,     0,    50,   114,
     115,     0,    58,    39,    74,    75,    33,     0,    97,   101,
     103,   106,     0,     0,    41,    76,    34,     0,    99,   100,
     102,     0,    59,    40,    98,   104,    60
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -242,  -242,   311,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,    97,   131,  -242,  -242,
    -242,  -164,    -3,  -242,  -242,    38,   277,  -242,   238,   159,
    -189,  -241,  -242,   223,   185,  -242,   123,  -169,   156,  -242,
    -242,  -242,  -242,    48,  -242,  -180,  -211,    75,    -2,   -77,
     -50,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,   201,   166,   258,   199,
      34,   139,    68,    35,    36,   255,    37,    38,    54,    55,
     279,   263,    69,    70,   114,   150,   184,   151,   181,   182,
     266,   290,   280,   281,   244,   161,   190,   191,   192,    72,
      73,    74,    75,    76,    77,    78,   229,    39,    40,    41,
      89
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,   209,    71,     4,   248,   249,   204,   106,   115,   115,
      42,    56,    43,   238,   211,   175,   176,   178,    79,   215,
     131,   116,   147,   277,    45,    81,    46,   148,    47,   179,
     119,   120,    97,   117,   285,   118,   118,   216,   153,   242,
      80,   155,    57,    83,    53,   115,   -51,   138,   246,    53,
     264,   100,   101,   103,   105,    58,    59,    60,    61,    62,
      84,    63,    64,    65,    48,    49,   102,    50,    51,   156,
     157,    44,   118,   275,    82,   272,   294,    98,    99,   100,
     101,    48,    49,    85,    50,    51,    56,    52,    98,    99,
     100,   101,    87,   141,    53,    53,    53,    53,    53,   173,
      48,    49,    88,    50,    51,   143,   144,   145,   146,   250,
     251,    71,   232,    56,   111,   174,    90,    57,    91,   158,
     177,    92,   163,   115,   186,   240,   283,   284,    93,   115,
      58,    59,    60,    61,    62,   170,    63,    64,    65,    48,
      49,    66,    50,    51,    57,   115,    67,   107,    56,   115,
     118,   233,   234,   241,   115,   115,   118,    58,    59,    60,
      61,    62,    94,    63,    64,    65,    48,    49,   102,    50,
      51,   108,   118,   142,   205,   206,   118,   112,    56,    57,
     109,   118,   118,   115,   212,   188,   213,   189,   288,   289,
     230,   110,    58,    59,    60,    61,    62,   121,    63,    64,
      65,    48,    49,   102,    50,    51,    95,   113,   122,    57,
     118,    96,   247,   195,   196,   197,   198,   124,   123,   127,
     125,   128,    58,    59,    60,    61,    62,   253,    63,    64,
      65,    48,    49,   102,    50,    51,   126,   129,   137,   130,
     140,   149,   154,   159,   160,   162,   164,   165,   167,   168,
     270,   171,   172,   169,   180,   147,   183,   133,   134,   135,
     136,   187,   193,     1,     2,   194,   200,   202,     3,     4,
       5,   203,     6,     7,     8,     9,    10,   138,   207,   292,
      11,    12,    13,   214,   231,   208,   236,    14,    15,   217,
     218,   219,   220,   221,   222,    16,   115,    17,   237,   239,
      18,   223,   224,   225,   226,   243,   227,   228,   254,   252,
     256,   257,   261,   262,   259,   267,   265,   268,   269,   273,
     276,   271,   282,   118,   274,   286,   287,   291,   293,    86,
     296,   235,   260,   104,   245,   132,   152,   185,   210,   295,
     278
};

static const yytype_int16 yycheck[] =
{
       3,   181,     4,    10,   215,   216,   170,    57,    49,    49,
       6,    18,     8,   202,   183,    19,    20,    61,    73,    35,
      19,    61,    73,   264,     6,    31,     8,    78,    18,    73,
      78,    79,    20,    73,   275,    76,    76,    53,   115,   208,
       7,   118,    49,    73,    47,    49,    19,    20,   212,    52,
     239,    78,    79,    56,    56,    62,    63,    64,    65,    66,
      73,    68,    69,    70,    71,    72,    73,    74,    75,   119,
     120,    67,    76,   262,    33,   255,   287,    76,    77,    78,
      79,    71,    72,    39,    74,    75,    18,    77,    76,    77,
      78,    79,     0,    19,    97,    98,    99,   100,   101,    19,
      71,    72,     3,    74,    75,   107,   108,   109,   110,    57,
      58,   113,    18,    18,    30,    19,    73,    49,    73,   121,
      20,     8,   125,    49,    19,    19,    57,    58,    73,    49,
      62,    63,    64,    65,    66,   138,    68,    69,    70,    71,
      72,    73,    74,    75,    49,    49,    78,    18,    18,    49,
      76,    57,    58,    19,    49,    49,    76,    62,    63,    64,
      65,    66,    73,    68,    69,    70,    71,    72,    73,    74,
      75,    18,    76,    78,   176,   177,    76,    33,    18,    49,
      18,    76,    76,    49,   187,    55,   188,    57,    11,    12,
     193,    18,    62,    63,    64,    65,    66,    18,    68,    69,
      70,    71,    72,    73,    74,    75,    47,    20,    73,    49,
      76,    52,   214,    24,    25,    26,    27,    36,    73,    18,
      42,    37,    62,    63,    64,    65,    66,   229,    68,    69,
      70,    71,    72,    73,    74,    75,    40,    73,    30,    37,
      19,    73,    73,    32,    34,    73,    75,    73,    73,    37,
     252,    19,    19,    73,    48,    73,    20,    98,    99,   100,
     101,    18,    42,     4,     5,    31,    20,    18,     9,    10,
      11,    73,    13,    14,    15,    16,    17,    20,    73,   282,
      21,    22,    23,    55,     6,    50,    19,    28,    29,    42,
      43,    44,    45,    46,    47,    36,    49,    38,    73,    18,
      41,    54,    55,    56,    57,    51,    59,    60,    20,    54,
      73,    71,    30,    20,    58,    52,    37,    19,    58,    19,
      19,    73,    42,    76,    73,    19,    35,    20,    58,    18,
     292,   200,   235,    56,   211,    97,   113,   152,   182,   291,
     265
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    13,    14,    15,    16,
      17,    21,    22,    23,    28,    29,    36,    38,    41,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,   101,   104,   105,   107,   108,   138,
     139,   140,     6,     8,    67,     6,     8,    18,    71,    72,
      74,    75,    77,   103,   109,   110,    18,    49,    62,    63,
      64,    65,    66,    68,    69,    70,    73,    78,   103,   113,
     114,   129,   130,   131,   132,   133,   134,   135,   136,    73,
       7,    31,    33,    73,    73,    39,    83,     0,     3,   141,
      73,    73,     8,    73,    73,   110,   110,    20,    76,    77,
      78,    79,    73,   103,   107,   129,   131,    18,    18,    18,
      18,    30,    33,    20,   115,    49,    61,    73,    76,    78,
      79,    18,    73,    73,    36,    42,    40,    18,    37,    73,
      37,    19,   109,   110,   110,   110,   110,    30,    20,   102,
      19,    19,    78,   129,   129,   129,   129,    73,    78,    73,
     116,   118,   114,   130,    73,   130,   131,   131,   129,    32,
      34,   126,    73,   103,    75,    73,    98,    73,    37,    73,
     103,    19,    19,    19,    19,    19,    20,    20,    61,    73,
      48,   119,   120,    20,   117,   115,    19,    18,    55,    57,
     127,   128,   129,    42,    31,    24,    25,    26,    27,   100,
      20,    97,    18,    73,   102,   129,   129,    73,    50,   126,
     119,   118,   103,   129,    55,    35,    53,    42,    43,    44,
      45,    46,    47,    54,    55,    56,    57,    59,    60,   137,
     103,     6,    18,    57,    58,    98,    19,    73,   111,    18,
      19,    19,   118,    51,   125,   117,   102,   129,   127,   127,
      57,    58,    54,   129,    20,   106,    73,    71,    99,    58,
      97,    30,    20,   112,   111,    37,   121,    52,    19,    58,
     129,    73,   126,    19,    73,   111,    19,   112,   128,   111,
     123,   124,    42,    57,    58,   112,    19,    35,    11,    12,
     122,    20,   103,    58,   127,   124,   106
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    97,    98,
      98,    98,    98,    98,    98,    99,   100,   100,   100,   100,
     101,   102,   102,   103,   103,   103,   103,   104,   105,   106,
     106,   107,   107,   108,   109,   109,   110,   110,   110,   110,
     110,   110,   110,   111,   111,   112,   112,   113,   113,   114,
     114,   114,   114,   114,   115,   115,   116,   116,   117,   117,
     118,   118,   118,   119,   119,   120,   121,   121,   121,   122,
     122,   122,   123,   124,   124,   125,   125,   126,   126,   127,
     127,   127,   128,   128,   128,   128,   128,   128,   129,   129,
     129,   130,   130,   130,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   132,   132,   132,   133,   133,   133,   133,
     134,   135,   136,   136,   136,   136,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   138,   139,   140,   141,
     141
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     9,    10,     5,     7,     0,     3,     5,
       7,     6,     2,     4,     3,     1,     1,     1,     1,     1,
       8,     0,     3,     1,     1,     1,     1,     4,     8,     0,
       5,     2,     7,     2,     1,     3,     3,     3,     3,     3,
       3,     2,     1,     1,     3,     0,     3,     1,     2,     1,
       3,     1,     3,     2,     0,     3,     1,     2,     0,     3,
       1,     2,     3,     0,     2,     4,     0,     2,     4,     1,
       1,     0,     2,     1,     3,     0,     3,     0,     2,     1,
       3,     3,     3,     3,     4,     4,     2,     3,     1,     3,
       3,     1,     3,     3,     1,     1,     3,     3,     1,     1,
       1,     1,     2,     4,     4,     4,     1,     1,     1,     1,
       3,     4,     4,     4,     6,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     7,     2,     4,     0,
       1
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
#line 246 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1880 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 277 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1889 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 283 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1897 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 288 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1905 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 294 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1913 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 300 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1921 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 306 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1929 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 312 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1939 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 319 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1947 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 325 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1957 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE rel_attr attr_list_index RBRACE  */
#line 334 "yacc_sql.y"
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
#line 1979 "yacc_sql.cpp"
    break;

  case 34: /* create_unique_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE rel_attr attr_list_index RBRACE  */
#line 355 "yacc_sql.y"
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
#line 2001 "yacc_sql.cpp"
    break;

  case 35: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 375 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2013 "yacc_sql.cpp"
    break;

  case 36: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 385 "yacc_sql.y"
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
#line 2033 "yacc_sql.cpp"
    break;

  case 37: /* attr_def_list: %empty  */
#line 403 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2041 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 407 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));  // 按照语法树递归执行，最后一个attr将会放到vector的第一个位置，所以在调用attr_def_list的部分需要reverse
      delete (yyvsp[-1].attr_info);
    }
#line 2055 "yacc_sql.cpp"
    break;

  case 39: /* attr_def: ID type LBRACE number RBRACE  */
#line 420 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      free((yyvsp[-4].string));
    }
#line 2067 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE NOT NULL_VALUE  */
#line 428 "yacc_sql.y"
                {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      free((yyvsp[-6].string));
		}
#line 2079 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type LBRACE number RBRACE NULL_VALUE  */
#line 436 "yacc_sql.y"
                {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-5].string));
		}
#line 2092 "yacc_sql.cpp"
    break;

  case 42: /* attr_def: ID type  */
#line 445 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      free((yyvsp[-1].string));
    }
#line 2104 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type NOT NULL_VALUE  */
#line 453 "yacc_sql.y"
                {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      free((yyvsp[-3].string));
		}
#line 2116 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type NULL_VALUE  */
#line 461 "yacc_sql.y"
                {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-2].string));
		}
#line 2129 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 472 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2135 "yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 476 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2141 "yacc_sql.cpp"
    break;

  case 47: /* type: DATE_T  */
#line 477 "yacc_sql.y"
                {(yyval.number)=DATES;}
#line 2147 "yacc_sql.cpp"
    break;

  case 48: /* type: STRING_T  */
#line 478 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2153 "yacc_sql.cpp"
    break;

  case 49: /* type: FLOAT_T  */
#line 479 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2159 "yacc_sql.cpp"
    break;

  case 50: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 483 "yacc_sql.y"
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
#line 2174 "yacc_sql.cpp"
    break;

  case 51: /* value_list: %empty  */
#line 497 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2182 "yacc_sql.cpp"
    break;

  case 52: /* value_list: COMMA value value_list  */
#line 500 "yacc_sql.y"
                              {   
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2196 "yacc_sql.cpp"
    break;

  case 53: /* value: NUMBER  */
#line 512 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2205 "yacc_sql.cpp"
    break;

  case 54: /* value: FLOAT  */
#line 516 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2214 "yacc_sql.cpp"
    break;

  case 55: /* value: DATE  */
#line 528 "yacc_sql.y"
           {    // T1修改点
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp, 0, true);    // 构建Date类型的Value
      free(tmp);
    }
#line 2224 "yacc_sql.cpp"
    break;

  case 56: /* value: SSS  */
#line 533 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2234 "yacc_sql.cpp"
    break;

  case 57: /* delete_stmt: DELETE FROM ID where  */
#line 542 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2247 "yacc_sql.cpp"
    break;

  case 58: /* update_stmt: UPDATE ID SET ID EQ value set_attr_list where  */
#line 553 "yacc_sql.y"
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
#line 2272 "yacc_sql.cpp"
    break;

  case 59: /* set_attr_list: %empty  */
#line 577 "yacc_sql.y"
    {
      (yyval.set_attrs) = nullptr;
    }
#line 2280 "yacc_sql.cpp"
    break;

  case 60: /* set_attr_list: COMMA ID EQ value set_attr_list  */
#line 581 "yacc_sql.y"
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
#line 2298 "yacc_sql.cpp"
    break;

  case 61: /* select_stmt: SELECT select_attr  */
#line 597 "yacc_sql.y"
                       {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[0].attr_list));
        delete (yyvsp[0].attr_list);
      }
    }
#line 2310 "yacc_sql.cpp"
    break;

  case 62: /* select_stmt: SELECT select_attr FROM from inner_join_list where order_by  */
#line 605 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-5].attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-5].attr_list));
        delete (yyvsp[-5].attr_list);
      }
      // std::reverse($$->selection.attributes.begin(), $$->selection.attributes.end());   // 为什么这里要反转？因为select_attr的写法是反着的。

      if ((yyvsp[-3].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-3].relation_list));
        delete (yyvsp[-3].relation_list);
      }
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());   // 为什么这里要反转？因为select_attr的写法是反着的。

      if ((yyvsp[-2].inner_join_list) != nullptr) {
        (yyval.sql_node)->selection.inner_join_clauses.swap(*(yyvsp[-2].inner_join_list));
        delete (yyvsp[-2].inner_join_list);
      }
      std::reverse((yyval.sql_node)->selection.inner_join_clauses.begin(), (yyval.sql_node)->selection.inner_join_clauses.end());   

      if ((yyvsp[-1].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions = (yyvsp[-1].expression);
      }

      if ((yyvsp[0].order_by_list) != nullptr) {
        (yyval.sql_node)->selection.order_by_nodes.swap(*(yyvsp[0].order_by_list));
        delete (yyvsp[0].order_by_list);
      }
      // std::reverse($$->selection.order_by_nodes.begin(), $$->selection.order_by_nodes.end());   

    }
#line 2346 "yacc_sql.cpp"
    break;

  case 63: /* calc_stmt: CALC expression_list  */
#line 640 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2357 "yacc_sql.cpp"
    break;

  case 64: /* expression_list: arithmetic_expr  */
#line 650 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2366 "yacc_sql.cpp"
    break;

  case 65: /* expression_list: arithmetic_expr COMMA expression_list  */
#line 655 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2379 "yacc_sql.cpp"
    break;

  case 66: /* arithmetic_expr: arithmetic_expr '+' arithmetic_expr  */
#line 666 "yacc_sql.y"
                                        {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2387 "yacc_sql.cpp"
    break;

  case 67: /* arithmetic_expr: arithmetic_expr '-' arithmetic_expr  */
#line 669 "yacc_sql.y"
                                          {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2395 "yacc_sql.cpp"
    break;

  case 68: /* arithmetic_expr: arithmetic_expr '*' arithmetic_expr  */
#line 672 "yacc_sql.y"
                                          {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2403 "yacc_sql.cpp"
    break;

  case 69: /* arithmetic_expr: arithmetic_expr '/' arithmetic_expr  */
#line 675 "yacc_sql.y"
                                          {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2411 "yacc_sql.cpp"
    break;

  case 70: /* arithmetic_expr: LBRACE arithmetic_expr RBRACE  */
#line 678 "yacc_sql.y"
                                    {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2420 "yacc_sql.cpp"
    break;

  case 71: /* arithmetic_expr: '-' arithmetic_expr  */
#line 682 "yacc_sql.y"
                                       {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2428 "yacc_sql.cpp"
    break;

  case 72: /* arithmetic_expr: value  */
#line 685 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2438 "yacc_sql.cpp"
    break;

  case 73: /* rel_attr: ID  */
#line 693 "yacc_sql.y"
       {
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2448 "yacc_sql.cpp"
    break;

  case 74: /* rel_attr: ID DOT ID  */
#line 698 "yacc_sql.y"
                {
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr_item)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2460 "yacc_sql.cpp"
    break;

  case 75: /* attr_list_index: %empty  */
#line 707 "yacc_sql.y"
  {
    (yyval.attr_list) = nullptr;
  }
#line 2468 "yacc_sql.cpp"
    break;

  case 76: /* attr_list_index: COMMA rel_attr attr_list_index  */
#line 710 "yacc_sql.y"
                                   {
    std:vector<RelAttrSqlNode> *temp = (yyvsp[0].attr_list);
    if (temp == nullptr) {
      temp = new std::vector<RelAttrSqlNode>;
    }
    temp->emplace_back(*(yyvsp[-1].rel_attr_item));
    (yyval.attr_list) = temp;
    free (yyvsp[-1].rel_attr_item);
  }
#line 2482 "yacc_sql.cpp"
    break;

  case 77: /* select_attr: rel_attr_item  */
#line 723 "yacc_sql.y"
                {
    (yyval.attr_list) = new std::vector<RelAttrSqlNode>;
    (yyval.attr_list)->emplace_back(*(yyvsp[0].rel_attr_item));
    delete (yyvsp[0].rel_attr_item);
  }
#line 2492 "yacc_sql.cpp"
    break;

  case 78: /* select_attr: rel_attr_item attr_list  */
#line 728 "yacc_sql.y"
                            {
    std::vector<RelAttrSqlNode> *temp = (yyvsp[0].attr_list);
    if (temp == nullptr) {
      temp = new std::vector<RelAttrSqlNode>;
    } 
    temp->emplace_back(*(yyvsp[-1].rel_attr_item));
    (yyval.attr_list) = temp;
    delete (yyvsp[-1].rel_attr_item);
  }
#line 2506 "yacc_sql.cpp"
    break;

  case 79: /* rel_attr_item: '*'  */
#line 741 "yacc_sql.y"
        {  
      (yyval.rel_attr_item) = new RelAttrSqlNode ;
      (yyval.rel_attr_item)->relation_name  = "";
      (yyval.rel_attr_item)->attribute_name = "*";
		}
#line 2516 "yacc_sql.cpp"
    break;

  case 80: /* rel_attr_item: ID DOT '*'  */
#line 746 "yacc_sql.y"
                 {
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->relation_name = (yyvsp[-2].string);
      (yyval.rel_attr_item)->attribute_name = "*";
    }
#line 2526 "yacc_sql.cpp"
    break;

  case 81: /* rel_attr_item: add_expr  */
#line 751 "yacc_sql.y"
               {       
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->expr = (yyvsp[0].expression);
    }
#line 2535 "yacc_sql.cpp"
    break;

  case 82: /* rel_attr_item: add_expr AS ID  */
#line 755 "yacc_sql.y"
                     {   // 只有单列和聚集函数才能取别名
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->expr = (yyvsp[-2].expression);
      (yyval.rel_attr_item)->alias = (yyvsp[0].string);
    }
#line 2545 "yacc_sql.cpp"
    break;

  case 83: /* rel_attr_item: add_expr ID  */
#line 760 "yacc_sql.y"
                  {
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->expr = (yyvsp[-1].expression);
      (yyval.rel_attr_item)->alias = (yyvsp[0].string);
    }
#line 2555 "yacc_sql.cpp"
    break;

  case 84: /* attr_list: %empty  */
#line 769 "yacc_sql.y"
    {
      (yyval.attr_list) = nullptr;
    }
#line 2563 "yacc_sql.cpp"
    break;

  case 85: /* attr_list: COMMA rel_attr_item attr_list  */
#line 772 "yacc_sql.y"
                                    {
      std::vector<RelAttrSqlNode> *temp = (yyvsp[0].attr_list);
      if (temp == nullptr) {
        temp = new std::vector<RelAttrSqlNode>;
      } 
      temp->emplace_back(*(yyvsp[-1].rel_attr_item));
      (yyval.attr_list) = temp;
    }
#line 2576 "yacc_sql.cpp"
    break;

  case 86: /* from: rel_item  */
#line 784 "yacc_sql.y"
  {
    (yyval.relation_list) = new std::vector<Relation>;
    (yyval.relation_list)->emplace_back(*(yyvsp[0].relation_item));
    delete (yyvsp[0].relation_item);
  }
#line 2586 "yacc_sql.cpp"
    break;

  case 87: /* from: rel_item rel_list  */
#line 790 "yacc_sql.y"
  {
    (yyval.relation_list) = (yyvsp[0].relation_list);
    (yyval.relation_list)->emplace_back(*(yyvsp[-1].relation_item));
    delete (yyvsp[-1].relation_item);
  }
#line 2596 "yacc_sql.cpp"
    break;

  case 88: /* rel_list: %empty  */
#line 798 "yacc_sql.y"
  {
    (yyval.relation_list) = nullptr;
  }
#line 2604 "yacc_sql.cpp"
    break;

  case 89: /* rel_list: COMMA rel_item rel_list  */
#line 801 "yacc_sql.y"
                            {	
    std::vector<Relation> * temp = (yyvsp[0].relation_list);
    if (temp == nullptr) {
      temp = new std::vector<Relation>;
      temp->emplace_back(*(yyvsp[-1].relation_item));
    }
    (yyval.relation_list) = temp;
  }
#line 2617 "yacc_sql.cpp"
    break;

  case 90: /* rel_item: ID  */
#line 811 "yacc_sql.y"
     {
    (yyval.relation_item) = new Relation;
    (yyval.relation_item)->relation_name = (yyvsp[0].string);
  }
#line 2626 "yacc_sql.cpp"
    break;

  case 91: /* rel_item: ID ID  */
#line 815 "yacc_sql.y"
         {       
    (yyval.relation_item) = new Relation;
    (yyval.relation_item)->relation_name = (yyvsp[-1].string);
    (yyval.relation_item)->alias = (yyvsp[0].string);
  }
#line 2636 "yacc_sql.cpp"
    break;

  case 92: /* rel_item: ID AS ID  */
#line 820 "yacc_sql.y"
            {
    (yyval.relation_item) = new Relation;
    (yyval.relation_item)->relation_name = (yyvsp[-2].string);
    (yyval.relation_item)->alias = (yyvsp[0].string);
  }
#line 2646 "yacc_sql.cpp"
    break;

  case 93: /* inner_join_list: %empty  */
#line 835 "yacc_sql.y"
    {
        (yyval.inner_join_list) = nullptr;
    }
#line 2654 "yacc_sql.cpp"
    break;

  case 94: /* inner_join_list: join_clause inner_join_list  */
#line 838 "yacc_sql.y"
                                  {
        if((yyvsp[0].inner_join_list) != nullptr) {
            (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
        } else {
            (yyval.inner_join_list) = new std::vector<InnerJoinNode>;
        }
        (yyval.inner_join_list)->push_back(*(yyvsp[-1].join_clause));
    }
#line 2667 "yacc_sql.cpp"
    break;

  case 95: /* join_clause: INNER JOIN rel_item join_conditions  */
#line 849 "yacc_sql.y"
                                        {
        (yyval.join_clause) = new InnerJoinNode;
        (yyval.join_clause)->relation_name = *(yyvsp[-1].relation_item);
        (yyval.join_clause)->conditions = (yyvsp[0].join_conditions);
        delete (yyvsp[-1].relation_item);
    }
#line 2678 "yacc_sql.cpp"
    break;

  case 96: /* join_conditions: %empty  */
#line 859 "yacc_sql.y"
    {
      (yyval.join_conditions) = nullptr;
    }
#line 2686 "yacc_sql.cpp"
    break;

  case 97: /* join_conditions: ON condition  */
#line 862 "yacc_sql.y"
                   {    // 如果有on关键字，则至少必须有一个condition
      ConjunctionExpr *temp = new ConjunctionExpr();
      temp->add_condition((yyvsp[0].expression));
      (yyval.join_conditions) = temp;
    }
#line 2696 "yacc_sql.cpp"
    break;

  case 98: /* join_conditions: ON condition AND condition_list  */
#line 867 "yacc_sql.y"
                                      {     
      ConjunctionExpr *base = static_cast<ConjunctionExpr *>((yyvsp[0].expression));
      assert(base != nullptr);
      base->add_condition((yyvsp[-2].expression));
      (yyval.join_conditions) = base;
    }
#line 2707 "yacc_sql.cpp"
    break;

  case 99: /* order_direction: DESC  */
#line 877 "yacc_sql.y"
         {
        (yyval.order_direction) = OrderDirection::DESC_;
    }
#line 2715 "yacc_sql.cpp"
    break;

  case 100: /* order_direction: ASC  */
#line 880 "yacc_sql.y"
          {
        (yyval.order_direction) = OrderDirection::ASC_;
    }
#line 2723 "yacc_sql.cpp"
    break;

  case 101: /* order_direction: %empty  */
#line 884 "yacc_sql.y"
    {
        (yyval.order_direction) = OrderDirection::ASC_;
    }
#line 2731 "yacc_sql.cpp"
    break;

  case 102: /* order_by_item: rel_attr order_direction  */
#line 890 "yacc_sql.y"
                             {
        (yyval.order_by_item) = new OrderByNode;
        (yyval.order_by_item)->attribute = *(yyvsp[-1].rel_attr_item);
        (yyval.order_by_item)->direction = (yyvsp[0].order_direction);
        delete (yyvsp[-1].rel_attr_item);
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 103: /* order_by_list: order_by_item  */
#line 903 "yacc_sql.y"
                  {
        (yyval.order_by_list) = new std::vector<OrderByNode>;
        (yyval.order_by_list)->push_back(*(yyvsp[0].order_by_item));
    }
#line 2751 "yacc_sql.cpp"
    break;

  case 104: /* order_by_list: order_by_item COMMA order_by_list  */
#line 907 "yacc_sql.y"
                                        {
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
        (yyval.order_by_list)->emplace_back(*(yyvsp[-2].order_by_item));
        delete (yyvsp[-2].order_by_item);
    }
#line 2761 "yacc_sql.cpp"
    break;

  case 105: /* order_by: %empty  */
#line 916 "yacc_sql.y"
    {
        (yyval.order_by_list) = nullptr;
    }
#line 2769 "yacc_sql.cpp"
    break;

  case 106: /* order_by: ORDER BY order_by_list  */
#line 919 "yacc_sql.y"
                             {
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 2777 "yacc_sql.cpp"
    break;

  case 107: /* where: %empty  */
#line 930 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
  }
#line 2785 "yacc_sql.cpp"
    break;

  case 108: /* where: WHERE condition_list  */
#line 933 "yacc_sql.y"
                         {      
    (yyval.expression) = (yyvsp[0].expression);
  }
#line 2793 "yacc_sql.cpp"
    break;

  case 109: /* condition_list: condition  */
#line 939 "yacc_sql.y"
              {
      ConjunctionExpr *temp = new ConjunctionExpr();
      temp->add_condition((yyvsp[0].expression));
      (yyval.expression) = temp;
    }
#line 2803 "yacc_sql.cpp"
    break;

  case 110: /* condition_list: condition AND condition_list  */
#line 944 "yacc_sql.y"
                                   {        
      ConjunctionExpr *base = static_cast<ConjunctionExpr *>((yyvsp[0].expression));
      assert(base != nullptr);
      base->add_condition((yyvsp[-2].expression));
      (yyval.expression) = base;
    }
#line 2814 "yacc_sql.cpp"
    break;

  case 111: /* condition_list: condition OR condition_list  */
#line 950 "yacc_sql.y"
                                  {        
      ConjunctionExpr *base = static_cast<ConjunctionExpr *>((yyvsp[0].expression));
      assert(base != nullptr);
      base->add_condition((yyvsp[-2].expression));
      base->set_conjunction_type(ConjunctionExpr::Type::OR);
      (yyval.expression) = base;
    }
#line 2826 "yacc_sql.cpp"
    break;

  case 112: /* condition: add_expr comp_op add_expr  */
#line 960 "yacc_sql.y"
                             {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2834 "yacc_sql.cpp"
    break;

  case 113: /* condition: add_expr IS NULL_VALUE  */
#line 963 "yacc_sql.y"
                             {
      // TODO
    }
#line 2842 "yacc_sql.cpp"
    break;

  case 114: /* condition: add_expr IS NOT NULL_VALUE  */
#line 966 "yacc_sql.y"
                                 {
      // TODO:
    }
#line 2850 "yacc_sql.cpp"
    break;

  case 115: /* condition: add_expr NOT IN add_expr  */
#line 969 "yacc_sql.y"
                               {
      (yyval.expression) = new ComparisonExpr(CompOp::NOT_IN, (yyvsp[-3].expression), (yyvsp[0].expression));
    }
#line 2858 "yacc_sql.cpp"
    break;

  case 116: /* condition: EXISTS add_expr  */
#line 972 "yacc_sql.y"
                      {
      Value temp_value = Value(1);      // 创建一个临时对象当做表达式
      ValueExpr *value_expr = new ValueExpr(temp_value);
      (yyval.expression) = new ComparisonExpr(CompOp::EXISTS_OP, value_expr, (yyvsp[0].expression));
    }
#line 2868 "yacc_sql.cpp"
    break;

  case 117: /* condition: NOT EXISTS add_expr  */
#line 977 "yacc_sql.y"
                          {
      Value temp_value = Value(1);      // 创建一个临时对象当做表达式
      ValueExpr *value_expr = new ValueExpr(temp_value);
      (yyval.expression) = new ComparisonExpr(CompOp::NOT_EXISTS, value_expr, (yyvsp[0].expression));
    }
#line 2878 "yacc_sql.cpp"
    break;

  case 118: /* add_expr: mul_expr  */
#line 986 "yacc_sql.y"
             {
      (yyval.expression) = (yyvsp[0].expression); 
    }
#line 2886 "yacc_sql.cpp"
    break;

  case 119: /* add_expr: add_expr '+' mul_expr  */
#line 989 "yacc_sql.y"
                            {
      (yyval.expression) = new ArithmeticExpr(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2894 "yacc_sql.cpp"
    break;

  case 120: /* add_expr: add_expr SUB mul_expr  */
#line 992 "yacc_sql.y"
                            {
      (yyval.expression) = new ArithmeticExpr(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2902 "yacc_sql.cpp"
    break;

  case 121: /* mul_expr: unary_expr  */
#line 999 "yacc_sql.y"
               {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2910 "yacc_sql.cpp"
    break;

  case 122: /* mul_expr: mul_expr '*' unary_expr  */
#line 1002 "yacc_sql.y"
                              {
      (yyval.expression) = new ArithmeticExpr(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2918 "yacc_sql.cpp"
    break;

  case 123: /* mul_expr: mul_expr '/' unary_expr  */
#line 1005 "yacc_sql.y"
                              {
      (yyval.expression) = new ArithmeticExpr(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2926 "yacc_sql.cpp"
    break;

  case 124: /* unary_expr: value  */
#line 1012 "yacc_sql.y"
          {     
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
    }
#line 2934 "yacc_sql.cpp"
    break;

  case 125: /* unary_expr: ID  */
#line 1015 "yacc_sql.y"
         {
      (yyval.expression) = new FieldExpr((yyvsp[0].string));
    }
#line 2942 "yacc_sql.cpp"
    break;

  case 126: /* unary_expr: ID DOT ID  */
#line 1018 "yacc_sql.y"
                {
      (yyval.expression) = new FieldExpr((yyvsp[0].string), (yyvsp[-2].string));
    }
#line 2950 "yacc_sql.cpp"
    break;

  case 127: /* unary_expr: LBRACE add_expr RBRACE  */
#line 1021 "yacc_sql.y"
                             {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_with_brace();
    }
#line 2959 "yacc_sql.cpp"
    break;

  case 128: /* unary_expr: func_expr  */
#line 1025 "yacc_sql.y"
                {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2967 "yacc_sql.cpp"
    break;

  case 129: /* unary_expr: aggr_func_expr  */
#line 1028 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2975 "yacc_sql.cpp"
    break;

  case 130: /* unary_expr: sub_select_expr  */
#line 1031 "yacc_sql.y"
                      {
       (yyval.expression) = (yyvsp[0].expression);
    }
#line 2983 "yacc_sql.cpp"
    break;

  case 131: /* unary_expr: sub_select_list  */
#line 1034 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2991 "yacc_sql.cpp"
    break;

  case 132: /* unary_expr: SUB unary_expr  */
#line 1037 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
      (yyval.expression)->set_negtive();
    }
#line 3000 "yacc_sql.cpp"
    break;

  case 133: /* aggr_func_expr: aggr_func_type LBRACE add_expr RBRACE  */
#line 1045 "yacc_sql.y"
  {
    assert(ExprType::FIELD == (yyvsp[-1].expression)->type());
    (yyval.expression) = new AggrFuncExpression((yyvsp[-3].aggr_func_type), static_cast<FieldExpr*>((yyvsp[-1].expression)));
  }
#line 3009 "yacc_sql.cpp"
    break;

  case 134: /* aggr_func_expr: AGGR_COUNT LBRACE add_expr RBRACE  */
#line 1050 "yacc_sql.y"
  {
    assert(ExprType::FIELD == (yyvsp[-1].expression)->type());
    (yyval.expression) = new AggrFuncExpression(AggrFuncType::CNT, static_cast<FieldExpr*>((yyvsp[-1].expression)));
  }
#line 3018 "yacc_sql.cpp"
    break;

  case 135: /* aggr_func_expr: AGGR_COUNT LBRACE '*' RBRACE  */
#line 1055 "yacc_sql.y"
  {
    ValueExpr *temp = new ValueExpr(Value("*"));
    (yyval.expression) = new AggrFuncExpression(AggrFuncType::CNT, temp);
  }
#line 3027 "yacc_sql.cpp"
    break;

  case 136: /* aggr_func_type: AGGR_MAX  */
#line 1062 "yacc_sql.y"
             {
      (yyval.aggr_func_type) = AggrFuncType::MAX;
    }
#line 3035 "yacc_sql.cpp"
    break;

  case 137: /* aggr_func_type: AGGR_MIN  */
#line 1065 "yacc_sql.y"
               {
      (yyval.aggr_func_type) = AggrFuncType::MIN;
    }
#line 3043 "yacc_sql.cpp"
    break;

  case 138: /* aggr_func_type: AGGR_SUM  */
#line 1068 "yacc_sql.y"
               {
      (yyval.aggr_func_type) = AggrFuncType::SUM;
    }
#line 3051 "yacc_sql.cpp"
    break;

  case 139: /* aggr_func_type: AGGR_AVG  */
#line 1071 "yacc_sql.y"
               {
      (yyval.aggr_func_type) = AggrFuncType::AVG;
    }
#line 3059 "yacc_sql.cpp"
    break;

  case 140: /* sub_select_expr: LBRACE select_stmt RBRACE  */
#line 1079 "yacc_sql.y"
  {
    // SubQueryExpression
    (yyval.expression) = new SubQueryExpression((yyvsp[-1].sql_node));
  }
#line 3068 "yacc_sql.cpp"
    break;

  case 141: /* sub_select_list: LBRACE value value_list RBRACE  */
#line 1087 "yacc_sql.y"
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
#line 3084 "yacc_sql.cpp"
    break;

  case 142: /* func_expr: LENGTH LBRACE add_expr RBRACE  */
#line 1101 "yacc_sql.y"
                                {
    (yyval.expression) = new FuncExpression(FUNC_LENGTH, 1, (yyvsp[-1].expression), nullptr, true);
  }
#line 3092 "yacc_sql.cpp"
    break;

  case 143: /* func_expr: ROUND LBRACE add_expr RBRACE  */
#line 1104 "yacc_sql.y"
                                 {
    (yyval.expression) = new FuncExpression(FUNC_ROUND, 1, (yyvsp[-1].expression), nullptr, true);
  }
#line 3100 "yacc_sql.cpp"
    break;

  case 144: /* func_expr: ROUND LBRACE add_expr COMMA add_expr RBRACE  */
#line 1107 "yacc_sql.y"
                                                {
    (yyval.expression) = new FuncExpression(FUNC_ROUND, 2, (yyvsp[-3].expression), (yyvsp[-1].expression), true);
  }
#line 3108 "yacc_sql.cpp"
    break;

  case 145: /* func_expr: DATE_FORMAT LBRACE add_expr COMMA add_expr RBRACE  */
#line 1110 "yacc_sql.y"
                                                      {
    (yyval.expression) = new FuncExpression(FUNC_DATE_FORMAT, 2, (yyvsp[-3].expression), (yyvsp[-1].expression), true);
  }
#line 3116 "yacc_sql.cpp"
    break;

  case 146: /* comp_op: EQ  */
#line 1116 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3122 "yacc_sql.cpp"
    break;

  case 147: /* comp_op: LT  */
#line 1117 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3128 "yacc_sql.cpp"
    break;

  case 148: /* comp_op: GT  */
#line 1118 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3134 "yacc_sql.cpp"
    break;

  case 149: /* comp_op: LE  */
#line 1119 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3140 "yacc_sql.cpp"
    break;

  case 150: /* comp_op: GE  */
#line 1120 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3146 "yacc_sql.cpp"
    break;

  case 151: /* comp_op: NE  */
#line 1121 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3152 "yacc_sql.cpp"
    break;

  case 152: /* comp_op: LIKE_T  */
#line 1122 "yacc_sql.y"
             { (yyval.comp) = LIKE_OP; }
#line 3158 "yacc_sql.cpp"
    break;

  case 153: /* comp_op: NOT_LIKE_T  */
#line 1123 "yacc_sql.y"
                 {(yyval.comp) = NOT_LIKE_OP; }
#line 3164 "yacc_sql.cpp"
    break;

  case 154: /* comp_op: IN  */
#line 1124 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3170 "yacc_sql.cpp"
    break;

  case 155: /* comp_op: EXISTS  */
#line 1125 "yacc_sql.y"
             {(yyval.comp) = EXISTS_OP; }
#line 3176 "yacc_sql.cpp"
    break;

  case 156: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1130 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3190 "yacc_sql.cpp"
    break;

  case 157: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1143 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3199 "yacc_sql.cpp"
    break;

  case 158: /* set_variable_stmt: SET ID EQ value  */
#line 1151 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3211 "yacc_sql.cpp"
    break;


#line 3215 "yacc_sql.cpp"

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

#line 1163 "yacc_sql.y"

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
