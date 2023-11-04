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
  YYSYMBOL_NUMBER = 68,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 69,                     /* FLOAT  */
  YYSYMBOL_ID = 70,                        /* ID  */
  YYSYMBOL_DATE = 71,                      /* DATE  */
  YYSYMBOL_SSS = 72,                       /* SSS  */
  YYSYMBOL_73_ = 73,                       /* '+'  */
  YYSYMBOL_74_ = 74,                       /* '-'  */
  YYSYMBOL_75_ = 75,                       /* '*'  */
  YYSYMBOL_76_ = 76,                       /* '/'  */
  YYSYMBOL_UMINUS = 77,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 78,                  /* $accept  */
  YYSYMBOL_commands = 79,                  /* commands  */
  YYSYMBOL_command_wrapper = 80,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 81,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 82,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 83,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 84,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 85,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 86,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 87,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 88,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 89,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 90,         /* create_index_stmt  */
  YYSYMBOL_create_unique_index_stmt = 91,  /* create_unique_index_stmt  */
  YYSYMBOL_drop_index_stmt = 92,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 93,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 94,             /* attr_def_list  */
  YYSYMBOL_attr_def = 95,                  /* attr_def  */
  YYSYMBOL_number = 96,                    /* number  */
  YYSYMBOL_type = 97,                      /* type  */
  YYSYMBOL_insert_stmt = 98,               /* insert_stmt  */
  YYSYMBOL_value_list = 99,                /* value_list  */
  YYSYMBOL_value = 100,                    /* value  */
  YYSYMBOL_delete_stmt = 101,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 102,              /* update_stmt  */
  YYSYMBOL_set_attr_list = 103,            /* set_attr_list  */
  YYSYMBOL_select_stmt = 104,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 105,                /* calc_stmt  */
  YYSYMBOL_expression_list = 106,          /* expression_list  */
  YYSYMBOL_arithmetic_expr = 107,          /* arithmetic_expr  */
  YYSYMBOL_rel_attr = 108,                 /* rel_attr  */
  YYSYMBOL_attr_list_index = 109,          /* attr_list_index  */
  YYSYMBOL_select_attr = 110,              /* select_attr  */
  YYSYMBOL_rel_attr_item = 111,            /* rel_attr_item  */
  YYSYMBOL_attr_list = 112,                /* attr_list  */
  YYSYMBOL_from = 113,                     /* from  */
  YYSYMBOL_rel_list = 114,                 /* rel_list  */
  YYSYMBOL_rel_item = 115,                 /* rel_item  */
  YYSYMBOL_inner_join_list = 116,          /* inner_join_list  */
  YYSYMBOL_join_clause = 117,              /* join_clause  */
  YYSYMBOL_join_conditions = 118,          /* join_conditions  */
  YYSYMBOL_order_direction = 119,          /* order_direction  */
  YYSYMBOL_order_by_item = 120,            /* order_by_item  */
  YYSYMBOL_order_by_list = 121,            /* order_by_list  */
  YYSYMBOL_order_by = 122,                 /* order_by  */
  YYSYMBOL_where = 123,                    /* where  */
  YYSYMBOL_condition_list = 124,           /* condition_list  */
  YYSYMBOL_condition = 125,                /* condition  */
  YYSYMBOL_add_expr = 126,                 /* add_expr  */
  YYSYMBOL_mul_expr = 127,                 /* mul_expr  */
  YYSYMBOL_unary_expr = 128,               /* unary_expr  */
  YYSYMBOL_aggr_func_expr = 129,           /* aggr_func_expr  */
  YYSYMBOL_aggr_func_type = 130,           /* aggr_func_type  */
  YYSYMBOL_sub_select_expr = 131,          /* sub_select_expr  */
  YYSYMBOL_sub_select_list = 132,          /* sub_select_list  */
  YYSYMBOL_comp_op = 133,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 134,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 135,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 136,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 137             /* opt_semicolon  */
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
#define YYFINAL  83
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   302

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  154
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  279

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   328


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
       2,     2,    75,    73,     2,    74,     2,    76,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    77
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   241,   241,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   273,   279,   284,   290,   296,   302,
     308,   315,   321,   329,   350,   370,   380,   399,   402,   415,
     423,   431,   440,   448,   456,   468,   472,   473,   474,   475,
     478,   493,   496,   508,   512,   524,   529,   537,   548,   573,
     576,   593,   628,   638,   643,   655,   658,   661,   664,   667,
     671,   674,   682,   687,   696,   699,   712,   717,   730,   735,
     740,   744,   749,   758,   761,   772,   778,   787,   790,   800,
     804,   809,   824,   827,   838,   848,   851,   856,   866,   869,
     873,   879,   892,   896,   905,   908,   919,   922,   928,   933,
     939,   949,   952,   955,   958,   961,   966,   975,   978,   981,
     988,   991,   994,  1001,  1004,  1007,  1010,  1017,  1020,  1023,
    1026,  1033,  1038,  1043,  1051,  1054,  1057,  1060,  1067,  1075,
    1090,  1091,  1092,  1093,  1094,  1095,  1096,  1097,  1098,  1099,
    1103,  1116,  1124,  1134,  1135
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
  "UNIQUE", "NUMBER", "FLOAT", "ID", "DATE", "SSS", "'+'", "'-'", "'*'",
  "'/'", "UMINUS", "$accept", "commands", "command_wrapper", "exit_stmt",
  "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "create_unique_index_stmt", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "number", "type",
  "insert_stmt", "value_list", "value", "delete_stmt", "update_stmt",
  "set_attr_list", "select_stmt", "calc_stmt", "expression_list",
  "arithmetic_expr", "rel_attr", "attr_list_index", "select_attr",
  "rel_attr_item", "attr_list", "from", "rel_list", "rel_item",
  "inner_join_list", "join_clause", "join_conditions", "order_direction",
  "order_by_item", "order_by_list", "order_by", "where", "condition_list",
  "condition", "add_expr", "mul_expr", "unary_expr", "aggr_func_expr",
  "aggr_func_type", "sub_select_expr", "sub_select_list", "comp_op",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-197)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-52)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     193,     2,   163,    37,    14,   -57,    10,  -197,     6,    67,
     -40,  -197,  -197,  -197,  -197,  -197,     0,    75,   193,   127,
     135,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,   125,   131,   160,   147,   148,    37,  -197,  -197,
    -197,  -197,    37,  -197,  -197,    61,    -4,    95,  -197,  -197,
    -197,  -197,   161,   175,  -197,  -197,   186,   200,   -30,    98,
    -197,  -197,   205,  -197,  -197,  -197,  -197,   154,   155,   190,
     185,   188,  -197,  -197,  -197,  -197,   212,   196,   165,  -197,
     199,    22,  -197,    37,    37,    37,    37,    37,   207,   172,
     219,     1,  -197,    54,   -59,   169,    14,  -197,    95,   170,
    -197,    95,    95,    95,    95,   209,   208,   173,   109,   174,
     177,   178,   213,   179,  -197,  -197,   118,   118,  -197,  -197,
     181,   109,   225,  -197,  -197,   226,   102,  -197,  -197,   -19,
     204,   233,   200,    98,  -197,    98,  -197,  -197,   113,   236,
      84,  -197,   214,  -197,   224,   158,   237,   240,   189,  -197,
     242,  -197,  -197,  -197,   194,  -197,   210,   208,   204,   169,
    -197,  -197,  -197,   109,    95,   211,  -197,   -26,   -21,   109,
     257,  -197,  -197,  -197,  -197,   -11,   177,   246,   197,   250,
    -197,  -197,   169,   218,  -197,   233,   242,   -44,    95,    84,
      84,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,    -1,
     216,  -197,  -197,    95,   251,   202,   206,   215,  -197,   237,
    -197,   245,   256,   197,   241,   227,  -197,  -197,   258,   -44,
    -197,  -197,   222,  -197,    95,   -44,   217,   208,  -197,  -197,
     262,  -197,  -197,   220,   197,   263,   256,    84,  -197,   197,
    -197,  -197,   -44,   243,  -197,   142,  -197,   256,  -197,   264,
     249,   201,   266,  -197,   109,   230,  -197,  -197,  -197,    84,
    -197,  -197,  -197,   197,   251,  -197,  -197,  -197,  -197
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     153,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    13,    14,     8,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,    53,    54,
      55,    56,     0,    71,    62,    63,     0,     0,   134,   135,
     136,   137,     0,   124,    78,   123,     0,    76,    80,   117,
     120,   127,     0,   128,   129,    32,    31,     0,     0,     0,
       0,     0,   151,     1,   154,     2,     0,     0,     0,    30,
       0,     0,    70,     0,     0,     0,     0,     0,   124,   123,
       0,     0,   130,     0,     0,     0,     0,    77,     0,     0,
      82,     0,     0,     0,     0,     0,   106,     0,     0,     0,
       0,     0,     0,     0,    69,    64,    65,    66,    67,    68,
       0,     0,     0,   138,   126,     0,     0,   125,    79,    89,
      92,    85,    83,   119,    81,   118,   121,   122,     0,     0,
       0,    57,     0,   152,     0,     0,    37,     0,     0,    35,
      51,   139,   133,   132,     0,    90,     0,   106,    92,     0,
      86,    84,   131,     0,     0,     0,   107,   108,     0,     0,
       0,    46,    48,    49,    47,    42,     0,     0,     0,     0,
      52,    91,     0,   104,    93,    87,    51,   115,     0,     0,
       0,   140,   141,   142,   143,   144,   145,   148,   149,     0,
       0,   146,   147,     0,    59,     0,     0,     0,    44,    37,
      36,    72,    74,     0,    95,     0,    61,    88,     0,   116,
     109,   110,     0,   112,     0,   111,     0,   106,   150,    45,
       0,    43,    38,     0,     0,     0,    74,     0,    94,     0,
      50,   113,   114,     0,    58,    39,    73,    74,    33,     0,
      96,   100,   102,   105,     0,     0,    41,    75,    34,     0,
      98,    99,   101,     0,    59,    40,    97,   103,    60
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -197,  -197,   271,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,    72,   106,  -197,  -197,
    -197,  -148,    -3,  -197,  -197,    19,   238,  -197,   203,    93,
    -113,  -158,  -197,   191,   153,  -197,   103,   -62,   132,  -197,
    -197,  -197,  -197,    26,  -197,  -166,  -196,    55,    -2,   -93,
      30,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,   187,   156,   240,   185,
      34,   132,    65,    35,    36,   237,    37,    38,    54,    55,
     261,   245,    66,    67,   107,   140,   170,   141,   167,   168,
     248,   272,   262,   263,   226,   151,   176,   177,   178,    69,
      70,    71,    72,    73,    74,   213,    39,    40,    41,    85
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,   193,    68,   230,   231,   108,     4,   216,    42,   199,
      43,   137,   190,    75,    56,   143,   138,    76,   145,   108,
     134,   201,   202,   203,   204,   205,   206,   200,   108,   111,
      79,   109,    56,   207,   208,   209,   210,    77,   211,   212,
     110,   124,   164,   111,    53,    57,   217,   218,   228,    53,
     108,   165,   111,    99,   101,    47,   232,   233,    58,    59,
      60,    61,    62,    57,    48,    49,    98,    50,    51,    44,
      80,   254,    56,   276,   111,   222,    58,    59,    60,    61,
      62,    93,    48,    49,    63,    50,    51,   102,   259,    64,
      53,    53,    53,    53,    53,    94,    95,    96,    97,   267,
      78,   136,    56,    57,    68,    48,    49,   195,    50,    51,
     246,    52,   148,    56,    81,   153,    58,    59,    60,    61,
      62,   163,    48,    49,    98,    50,    51,    83,   160,   135,
     224,   257,   172,    57,    94,    95,    96,    97,    84,   174,
      91,   175,   146,   147,    57,    92,    58,    59,    60,    61,
      62,   108,    48,    49,    98,    50,    51,    58,    59,    60,
      61,    62,   108,    48,    49,    98,    50,    51,    88,    45,
     196,    46,   197,   112,   113,   111,   214,    48,    49,   103,
      50,    51,   181,   182,   183,   184,   111,   126,   127,   128,
     129,   -51,   131,    96,    97,    86,   229,     1,     2,   265,
     266,    87,     3,     4,     5,   104,     6,     7,     8,     9,
      10,   235,   270,   271,    11,    12,    13,    89,    90,   105,
     106,    14,    15,   114,   115,   116,   117,   118,   119,    16,
     120,    17,   252,   121,    18,   122,   123,   130,   133,   139,
     144,   149,   150,   152,   161,   162,   154,   155,   157,   159,
     158,   137,   166,   169,   173,   180,   179,   186,   188,   189,
     192,   274,   131,   215,   191,   220,   198,   221,   223,   225,
     234,   236,   238,   241,   239,   243,   244,   250,   247,   249,
     251,   255,   258,   268,   269,   264,   273,   253,   275,    82,
     256,   242,   219,   278,   100,   171,   125,   142,   227,   277,
     194,     0,   260
};

static const yytype_int16 yycheck[] =
{
       3,   167,     4,   199,   200,    49,    10,    18,     6,    35,
       8,    70,   160,    70,    18,   108,    75,     7,   111,    49,
      19,    42,    43,    44,    45,    46,    47,    53,    49,    73,
      70,    61,    18,    54,    55,    56,    57,    31,    59,    60,
      70,    19,    61,    73,    47,    49,    57,    58,   196,    52,
      49,    70,    73,    56,    56,    18,    57,    58,    62,    63,
      64,    65,    66,    49,    68,    69,    70,    71,    72,    67,
      70,   237,    18,   269,    73,   188,    62,    63,    64,    65,
      66,    20,    68,    69,    70,    71,    72,    57,   246,    75,
      93,    94,    95,    96,    97,    73,    74,    75,    76,   257,
      33,   103,    18,    49,   106,    68,    69,   169,    71,    72,
     223,    74,   114,    18,    39,   118,    62,    63,    64,    65,
      66,    19,    68,    69,    70,    71,    72,     0,   131,    75,
     192,   244,    19,    49,    73,    74,    75,    76,     3,    55,
      47,    57,   112,   113,    49,    52,    62,    63,    64,    65,
      66,    49,    68,    69,    70,    71,    72,    62,    63,    64,
      65,    66,    49,    68,    69,    70,    71,    72,     8,     6,
     173,     8,   174,    75,    76,    73,   179,    68,    69,    18,
      71,    72,    24,    25,    26,    27,    73,    94,    95,    96,
      97,    19,    20,    75,    76,    70,   198,     4,     5,    57,
      58,    70,     9,    10,    11,    30,    13,    14,    15,    16,
      17,   213,    11,    12,    21,    22,    23,    70,    70,    33,
      20,    28,    29,    18,    70,    70,    36,    42,    40,    36,
      18,    38,   234,    37,    41,    70,    37,    30,    19,    70,
      70,    32,    34,    70,    19,    19,    72,    70,    70,    70,
      37,    70,    48,    20,    18,    31,    42,    20,    18,    70,
      50,   264,    20,     6,    70,    19,    55,    70,    18,    51,
      54,    20,    70,    58,    68,    30,    20,    19,    37,    52,
      58,    19,    19,    19,    35,    42,    20,    70,    58,    18,
      70,   219,   186,   274,    56,   142,    93,   106,   195,   273,
     168,    -1,   247
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    13,    14,    15,    16,
      17,    21,    22,    23,    28,    29,    36,    38,    41,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    98,   101,   102,   104,   105,   134,
     135,   136,     6,     8,    67,     6,     8,    18,    68,    69,
      71,    72,    74,   100,   106,   107,    18,    49,    62,    63,
      64,    65,    66,    70,    75,   100,   110,   111,   126,   127,
     128,   129,   130,   131,   132,    70,     7,    31,    33,    70,
      70,    39,    80,     0,     3,   137,    70,    70,     8,    70,
      70,   107,   107,    20,    73,    74,    75,    76,    70,   100,
     104,   126,   128,    18,    30,    33,    20,   112,    49,    61,
      70,    73,    75,    76,    18,    70,    70,    36,    42,    40,
      18,    37,    70,    37,    19,   106,   107,   107,   107,   107,
      30,    20,    99,    19,    19,    75,   126,    70,    75,    70,
     113,   115,   111,   127,    70,   127,   128,   128,   126,    32,
      34,   123,    70,   100,    72,    70,    95,    70,    37,    70,
     100,    19,    19,    19,    61,    70,    48,   116,   117,    20,
     114,   112,    19,    18,    55,    57,   124,   125,   126,    42,
      31,    24,    25,    26,    27,    97,    20,    94,    18,    70,
      99,    70,    50,   123,   116,   115,   100,   126,    55,    35,
      53,    42,    43,    44,    45,    46,    47,    54,    55,    56,
      57,    59,    60,   133,   100,     6,    18,    57,    58,    95,
      19,    70,   108,    18,   115,    51,   122,   114,    99,   126,
     124,   124,    57,    58,    54,   126,    20,   103,    70,    68,
      96,    58,    94,    30,    20,   109,   108,    37,   118,    52,
      19,    58,   126,    70,   123,    19,    70,   108,    19,   109,
     125,   108,   120,   121,    42,    57,    58,   109,    19,    35,
      11,    12,   119,    20,   100,    58,   124,   121,   103
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    78,    79,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    94,    95,
      95,    95,    95,    95,    95,    96,    97,    97,    97,    97,
      98,    99,    99,   100,   100,   100,   100,   101,   102,   103,
     103,   104,   105,   106,   106,   107,   107,   107,   107,   107,
     107,   107,   108,   108,   109,   109,   110,   110,   111,   111,
     111,   111,   111,   112,   112,   113,   113,   114,   114,   115,
     115,   115,   116,   116,   117,   118,   118,   118,   119,   119,
     119,   120,   121,   121,   122,   122,   123,   123,   124,   124,
     124,   125,   125,   125,   125,   125,   125,   126,   126,   126,
     127,   127,   127,   128,   128,   128,   128,   128,   128,   128,
     128,   129,   129,   129,   130,   130,   130,   130,   131,   132,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     134,   135,   136,   137,   137
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
       5,     7,     2,     1,     3,     3,     3,     3,     3,     3,
       2,     1,     1,     3,     0,     3,     1,     2,     1,     3,
       1,     3,     2,     0,     3,     1,     2,     0,     3,     1,
       2,     3,     0,     2,     4,     0,     2,     4,     1,     1,
       0,     2,     1,     3,     0,     3,     0,     2,     1,     3,
       3,     3,     3,     4,     4,     2,     3,     1,     3,     3,
       1,     3,     3,     1,     1,     3,     3,     1,     1,     1,
       2,     4,     4,     4,     1,     1,     1,     1,     3,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       7,     2,     4,     0,     1
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
#line 242 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1855 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 273 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1864 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 279 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1872 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 284 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1880 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 290 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1888 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 296 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1896 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 302 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1904 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 308 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1914 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 315 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1922 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 321 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1932 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE rel_attr attr_list_index RBRACE  */
#line 330 "yacc_sql.y"
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
#line 1954 "yacc_sql.cpp"
    break;

  case 34: /* create_unique_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE rel_attr attr_list_index RBRACE  */
#line 351 "yacc_sql.y"
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
#line 1976 "yacc_sql.cpp"
    break;

  case 35: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 371 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1988 "yacc_sql.cpp"
    break;

  case 36: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 381 "yacc_sql.y"
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
#line 2008 "yacc_sql.cpp"
    break;

  case 37: /* attr_def_list: %empty  */
#line 399 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2016 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 403 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));  // 按照语法树递归执行，最后一个attr将会放到vector的第一个位置，所以在调用attr_def_list的部分需要reverse
      delete (yyvsp[-1].attr_info);
    }
#line 2030 "yacc_sql.cpp"
    break;

  case 39: /* attr_def: ID type LBRACE number RBRACE  */
#line 416 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      free((yyvsp[-4].string));
    }
#line 2042 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE NOT NULL_VALUE  */
#line 424 "yacc_sql.y"
                {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      free((yyvsp[-6].string));
		}
#line 2054 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type LBRACE number RBRACE NULL_VALUE  */
#line 432 "yacc_sql.y"
                {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-5].string));
		}
#line 2067 "yacc_sql.cpp"
    break;

  case 42: /* attr_def: ID type  */
#line 441 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      free((yyvsp[-1].string));
    }
#line 2079 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type NOT NULL_VALUE  */
#line 449 "yacc_sql.y"
                {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      free((yyvsp[-3].string));
		}
#line 2091 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type NULL_VALUE  */
#line 457 "yacc_sql.y"
                {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-2].string));
		}
#line 2104 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 468 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2110 "yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 472 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2116 "yacc_sql.cpp"
    break;

  case 47: /* type: DATE_T  */
#line 473 "yacc_sql.y"
                {(yyval.number)=DATES;}
#line 2122 "yacc_sql.cpp"
    break;

  case 48: /* type: STRING_T  */
#line 474 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2128 "yacc_sql.cpp"
    break;

  case 49: /* type: FLOAT_T  */
#line 475 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2134 "yacc_sql.cpp"
    break;

  case 50: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 479 "yacc_sql.y"
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
#line 2149 "yacc_sql.cpp"
    break;

  case 51: /* value_list: %empty  */
#line 493 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2157 "yacc_sql.cpp"
    break;

  case 52: /* value_list: COMMA value value_list  */
#line 496 "yacc_sql.y"
                              {   
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2171 "yacc_sql.cpp"
    break;

  case 53: /* value: NUMBER  */
#line 508 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2180 "yacc_sql.cpp"
    break;

  case 54: /* value: FLOAT  */
#line 512 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2189 "yacc_sql.cpp"
    break;

  case 55: /* value: DATE  */
#line 524 "yacc_sql.y"
           {    // T1修改点
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp, 0, true);    // 构建Date类型的Value
      free(tmp);
    }
#line 2199 "yacc_sql.cpp"
    break;

  case 56: /* value: SSS  */
#line 529 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2209 "yacc_sql.cpp"
    break;

  case 57: /* delete_stmt: DELETE FROM ID where  */
#line 538 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2222 "yacc_sql.cpp"
    break;

  case 58: /* update_stmt: UPDATE ID SET ID EQ value set_attr_list where  */
#line 549 "yacc_sql.y"
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
#line 2247 "yacc_sql.cpp"
    break;

  case 59: /* set_attr_list: %empty  */
#line 573 "yacc_sql.y"
    {
      (yyval.set_attrs) = nullptr;
    }
#line 2255 "yacc_sql.cpp"
    break;

  case 60: /* set_attr_list: COMMA ID EQ value set_attr_list  */
#line 577 "yacc_sql.y"
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
#line 2273 "yacc_sql.cpp"
    break;

  case 61: /* select_stmt: SELECT select_attr FROM from inner_join_list where order_by  */
#line 594 "yacc_sql.y"
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
#line 2309 "yacc_sql.cpp"
    break;

  case 62: /* calc_stmt: CALC expression_list  */
#line 629 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2320 "yacc_sql.cpp"
    break;

  case 63: /* expression_list: arithmetic_expr  */
#line 639 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2329 "yacc_sql.cpp"
    break;

  case 64: /* expression_list: arithmetic_expr COMMA expression_list  */
#line 644 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2342 "yacc_sql.cpp"
    break;

  case 65: /* arithmetic_expr: arithmetic_expr '+' arithmetic_expr  */
#line 655 "yacc_sql.y"
                                        {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2350 "yacc_sql.cpp"
    break;

  case 66: /* arithmetic_expr: arithmetic_expr '-' arithmetic_expr  */
#line 658 "yacc_sql.y"
                                          {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2358 "yacc_sql.cpp"
    break;

  case 67: /* arithmetic_expr: arithmetic_expr '*' arithmetic_expr  */
#line 661 "yacc_sql.y"
                                          {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2366 "yacc_sql.cpp"
    break;

  case 68: /* arithmetic_expr: arithmetic_expr '/' arithmetic_expr  */
#line 664 "yacc_sql.y"
                                          {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2374 "yacc_sql.cpp"
    break;

  case 69: /* arithmetic_expr: LBRACE arithmetic_expr RBRACE  */
#line 667 "yacc_sql.y"
                                    {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2383 "yacc_sql.cpp"
    break;

  case 70: /* arithmetic_expr: '-' arithmetic_expr  */
#line 671 "yacc_sql.y"
                                       {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2391 "yacc_sql.cpp"
    break;

  case 71: /* arithmetic_expr: value  */
#line 674 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2401 "yacc_sql.cpp"
    break;

  case 72: /* rel_attr: ID  */
#line 682 "yacc_sql.y"
       {
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2411 "yacc_sql.cpp"
    break;

  case 73: /* rel_attr: ID DOT ID  */
#line 687 "yacc_sql.y"
                {
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr_item)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2423 "yacc_sql.cpp"
    break;

  case 74: /* attr_list_index: %empty  */
#line 696 "yacc_sql.y"
  {
    (yyval.attr_list) = nullptr;
  }
#line 2431 "yacc_sql.cpp"
    break;

  case 75: /* attr_list_index: COMMA rel_attr attr_list_index  */
#line 699 "yacc_sql.y"
                                   {
    std:vector<RelAttrSqlNode> *temp = (yyvsp[0].attr_list);
    if (temp == nullptr) {
      temp = new std::vector<RelAttrSqlNode>;
    }
    temp->emplace_back(*(yyvsp[-1].rel_attr_item));
    (yyval.attr_list) = temp;
    free (yyvsp[-1].rel_attr_item);
  }
#line 2445 "yacc_sql.cpp"
    break;

  case 76: /* select_attr: rel_attr_item  */
#line 712 "yacc_sql.y"
                {
    (yyval.attr_list) = new std::vector<RelAttrSqlNode>;
    (yyval.attr_list)->emplace_back(*(yyvsp[0].rel_attr_item));
    delete (yyvsp[0].rel_attr_item);
  }
#line 2455 "yacc_sql.cpp"
    break;

  case 77: /* select_attr: rel_attr_item attr_list  */
#line 717 "yacc_sql.y"
                            {
    std::vector<RelAttrSqlNode> *temp = (yyvsp[0].attr_list);
    if (temp == nullptr) {
      temp = new std::vector<RelAttrSqlNode>;
    } 
    temp->emplace_back(*(yyvsp[-1].rel_attr_item));
    (yyval.attr_list) = temp;
    delete (yyvsp[-1].rel_attr_item);
  }
#line 2469 "yacc_sql.cpp"
    break;

  case 78: /* rel_attr_item: '*'  */
#line 730 "yacc_sql.y"
        {  
      (yyval.rel_attr_item) = new RelAttrSqlNode ;
      (yyval.rel_attr_item)->relation_name  = "";
      (yyval.rel_attr_item)->attribute_name = "*";
		}
#line 2479 "yacc_sql.cpp"
    break;

  case 79: /* rel_attr_item: ID DOT '*'  */
#line 735 "yacc_sql.y"
                 {
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->relation_name = (yyvsp[-2].string);
      (yyval.rel_attr_item)->attribute_name = "*";
    }
#line 2489 "yacc_sql.cpp"
    break;

  case 80: /* rel_attr_item: add_expr  */
#line 740 "yacc_sql.y"
               {       
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->expr = (yyvsp[0].expression);
    }
#line 2498 "yacc_sql.cpp"
    break;

  case 81: /* rel_attr_item: add_expr AS ID  */
#line 744 "yacc_sql.y"
                     {   // 只有单列和聚集函数才能取别名
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->expr = (yyvsp[-2].expression);
      (yyval.rel_attr_item)->alias = (yyvsp[0].string);
    }
#line 2508 "yacc_sql.cpp"
    break;

  case 82: /* rel_attr_item: add_expr ID  */
#line 749 "yacc_sql.y"
                  {
      (yyval.rel_attr_item) = new RelAttrSqlNode;
      (yyval.rel_attr_item)->expr = (yyvsp[-1].expression);
      (yyval.rel_attr_item)->alias = (yyvsp[0].string);
    }
#line 2518 "yacc_sql.cpp"
    break;

  case 83: /* attr_list: %empty  */
#line 758 "yacc_sql.y"
    {
      (yyval.attr_list) = nullptr;
    }
#line 2526 "yacc_sql.cpp"
    break;

  case 84: /* attr_list: COMMA rel_attr_item attr_list  */
#line 761 "yacc_sql.y"
                                    {
      std::vector<RelAttrSqlNode> *temp = (yyvsp[0].attr_list);
      if (temp == nullptr) {
        temp = new std::vector<RelAttrSqlNode>;
      } 
      temp->emplace_back(*(yyvsp[-1].rel_attr_item));
      (yyval.attr_list) = temp;
    }
#line 2539 "yacc_sql.cpp"
    break;

  case 85: /* from: rel_item  */
#line 773 "yacc_sql.y"
  {
    (yyval.relation_list) = new std::vector<Relation>;
    (yyval.relation_list)->emplace_back(*(yyvsp[0].relation_item));
    delete (yyvsp[0].relation_item);
  }
#line 2549 "yacc_sql.cpp"
    break;

  case 86: /* from: rel_item rel_list  */
#line 779 "yacc_sql.y"
  {
    (yyval.relation_list) = (yyvsp[0].relation_list);
    (yyval.relation_list)->emplace_back(*(yyvsp[-1].relation_item));
    delete (yyvsp[-1].relation_item);
  }
#line 2559 "yacc_sql.cpp"
    break;

  case 87: /* rel_list: %empty  */
#line 787 "yacc_sql.y"
  {
    (yyval.relation_list) = nullptr;
  }
#line 2567 "yacc_sql.cpp"
    break;

  case 88: /* rel_list: COMMA rel_item rel_list  */
#line 790 "yacc_sql.y"
                            {	
    std::vector<Relation> * temp = (yyvsp[0].relation_list);
    if (temp == nullptr) {
      temp = new std::vector<Relation>;
      temp->emplace_back(*(yyvsp[-1].relation_item));
    }
    (yyval.relation_list) = temp;
  }
#line 2580 "yacc_sql.cpp"
    break;

  case 89: /* rel_item: ID  */
#line 800 "yacc_sql.y"
     {
    (yyval.relation_item) = new Relation;
    (yyval.relation_item)->relation_name = (yyvsp[0].string);
  }
#line 2589 "yacc_sql.cpp"
    break;

  case 90: /* rel_item: ID ID  */
#line 804 "yacc_sql.y"
         {       
    (yyval.relation_item) = new Relation;
    (yyval.relation_item)->relation_name = (yyvsp[-1].string);
    (yyval.relation_item)->alias = (yyvsp[0].string);
  }
#line 2599 "yacc_sql.cpp"
    break;

  case 91: /* rel_item: ID AS ID  */
#line 809 "yacc_sql.y"
            {
    (yyval.relation_item) = new Relation;
    (yyval.relation_item)->relation_name = (yyvsp[-2].string);
    (yyval.relation_item)->alias = (yyvsp[0].string);
  }
#line 2609 "yacc_sql.cpp"
    break;

  case 92: /* inner_join_list: %empty  */
#line 824 "yacc_sql.y"
    {
        (yyval.inner_join_list) = nullptr;
    }
#line 2617 "yacc_sql.cpp"
    break;

  case 93: /* inner_join_list: join_clause inner_join_list  */
#line 827 "yacc_sql.y"
                                  {
        if((yyvsp[0].inner_join_list) != nullptr) {
            (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
        } else {
            (yyval.inner_join_list) = new std::vector<InnerJoinNode>;
        }
        (yyval.inner_join_list)->push_back(*(yyvsp[-1].join_clause));
    }
#line 2630 "yacc_sql.cpp"
    break;

  case 94: /* join_clause: INNER JOIN rel_item join_conditions  */
#line 838 "yacc_sql.y"
                                        {
        (yyval.join_clause) = new InnerJoinNode;
        (yyval.join_clause)->relation_name = *(yyvsp[-1].relation_item);
        (yyval.join_clause)->conditions = (yyvsp[0].join_conditions);
        delete (yyvsp[-1].relation_item);
    }
#line 2641 "yacc_sql.cpp"
    break;

  case 95: /* join_conditions: %empty  */
#line 848 "yacc_sql.y"
    {
      (yyval.join_conditions) = nullptr;
    }
#line 2649 "yacc_sql.cpp"
    break;

  case 96: /* join_conditions: ON condition  */
#line 851 "yacc_sql.y"
                   {    // 如果有on关键字，则至少必须有一个condition
      ConjunctionExpr *temp = new ConjunctionExpr();
      temp->add_condition((yyvsp[0].expression));
      (yyval.join_conditions) = temp;
    }
#line 2659 "yacc_sql.cpp"
    break;

  case 97: /* join_conditions: ON condition AND condition_list  */
#line 856 "yacc_sql.y"
                                      {     
      ConjunctionExpr *base = static_cast<ConjunctionExpr *>((yyvsp[0].expression));
      assert(base != nullptr);
      base->add_condition((yyvsp[-2].expression));
      (yyval.join_conditions) = base;
    }
#line 2670 "yacc_sql.cpp"
    break;

  case 98: /* order_direction: DESC  */
#line 866 "yacc_sql.y"
         {
        (yyval.order_direction) = OrderDirection::DESC_;
    }
#line 2678 "yacc_sql.cpp"
    break;

  case 99: /* order_direction: ASC  */
#line 869 "yacc_sql.y"
          {
        (yyval.order_direction) = OrderDirection::ASC_;
    }
#line 2686 "yacc_sql.cpp"
    break;

  case 100: /* order_direction: %empty  */
#line 873 "yacc_sql.y"
    {
        (yyval.order_direction) = OrderDirection::ASC_;
    }
#line 2694 "yacc_sql.cpp"
    break;

  case 101: /* order_by_item: rel_attr order_direction  */
#line 879 "yacc_sql.y"
                             {
        (yyval.order_by_item) = new OrderByNode;
        (yyval.order_by_item)->attribute = *(yyvsp[-1].rel_attr_item);
        (yyval.order_by_item)->direction = (yyvsp[0].order_direction);
        delete (yyvsp[-1].rel_attr_item);
    }
#line 2705 "yacc_sql.cpp"
    break;

  case 102: /* order_by_list: order_by_item  */
#line 892 "yacc_sql.y"
                  {
        (yyval.order_by_list) = new std::vector<OrderByNode>;
        (yyval.order_by_list)->push_back(*(yyvsp[0].order_by_item));
    }
#line 2714 "yacc_sql.cpp"
    break;

  case 103: /* order_by_list: order_by_item COMMA order_by_list  */
#line 896 "yacc_sql.y"
                                        {
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
        (yyval.order_by_list)->emplace_back(*(yyvsp[-2].order_by_item));
        delete (yyvsp[-2].order_by_item);
    }
#line 2724 "yacc_sql.cpp"
    break;

  case 104: /* order_by: %empty  */
#line 905 "yacc_sql.y"
    {
        (yyval.order_by_list) = nullptr;
    }
#line 2732 "yacc_sql.cpp"
    break;

  case 105: /* order_by: ORDER BY order_by_list  */
#line 908 "yacc_sql.y"
                             {
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 2740 "yacc_sql.cpp"
    break;

  case 106: /* where: %empty  */
#line 919 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
  }
#line 2748 "yacc_sql.cpp"
    break;

  case 107: /* where: WHERE condition_list  */
#line 922 "yacc_sql.y"
                         {      
    (yyval.expression) = (yyvsp[0].expression);
  }
#line 2756 "yacc_sql.cpp"
    break;

  case 108: /* condition_list: condition  */
#line 928 "yacc_sql.y"
              {
      ConjunctionExpr *temp = new ConjunctionExpr();
      temp->add_condition((yyvsp[0].expression));
      (yyval.expression) = temp;
    }
#line 2766 "yacc_sql.cpp"
    break;

  case 109: /* condition_list: condition AND condition_list  */
#line 933 "yacc_sql.y"
                                   {        
      ConjunctionExpr *base = static_cast<ConjunctionExpr *>((yyvsp[0].expression));
      assert(base != nullptr);
      base->add_condition((yyvsp[-2].expression));
      (yyval.expression) = base;
    }
#line 2777 "yacc_sql.cpp"
    break;

  case 110: /* condition_list: condition OR condition_list  */
#line 939 "yacc_sql.y"
                                  {        
      ConjunctionExpr *base = static_cast<ConjunctionExpr *>((yyvsp[0].expression));
      assert(base != nullptr);
      base->add_condition((yyvsp[-2].expression));
      base->set_conjunction_type(ConjunctionExpr::Type::OR);
      (yyval.expression) = base;
    }
#line 2789 "yacc_sql.cpp"
    break;

  case 111: /* condition: add_expr comp_op add_expr  */
#line 949 "yacc_sql.y"
                             {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2797 "yacc_sql.cpp"
    break;

  case 112: /* condition: add_expr IS NULL_VALUE  */
#line 952 "yacc_sql.y"
                             {
      // TODO
    }
#line 2805 "yacc_sql.cpp"
    break;

  case 113: /* condition: add_expr IS NOT NULL_VALUE  */
#line 955 "yacc_sql.y"
                                 {
      // TODO:
    }
#line 2813 "yacc_sql.cpp"
    break;

  case 114: /* condition: add_expr NOT IN add_expr  */
#line 958 "yacc_sql.y"
                               {
      (yyval.expression) = new ComparisonExpr(CompOp::NOT_IN, (yyvsp[-3].expression), (yyvsp[0].expression));
    }
#line 2821 "yacc_sql.cpp"
    break;

  case 115: /* condition: EXISTS add_expr  */
#line 961 "yacc_sql.y"
                      {
      Value temp_value = Value(1);      // 创建一个临时对象当做表达式
      ValueExpr *value_expr = new ValueExpr(temp_value);
      (yyval.expression) = new ComparisonExpr(CompOp::EXISTS_OP, value_expr, (yyvsp[0].expression));
    }
#line 2831 "yacc_sql.cpp"
    break;

  case 116: /* condition: NOT EXISTS add_expr  */
#line 966 "yacc_sql.y"
                          {
      Value temp_value = Value(1);      // 创建一个临时对象当做表达式
      ValueExpr *value_expr = new ValueExpr(temp_value);
      (yyval.expression) = new ComparisonExpr(CompOp::NOT_EXISTS, value_expr, (yyvsp[0].expression));
    }
#line 2841 "yacc_sql.cpp"
    break;

  case 117: /* add_expr: mul_expr  */
#line 975 "yacc_sql.y"
             {
      (yyval.expression) = (yyvsp[0].expression); 
    }
#line 2849 "yacc_sql.cpp"
    break;

  case 118: /* add_expr: add_expr '+' mul_expr  */
#line 978 "yacc_sql.y"
                            {
      (yyval.expression) = new ArithmeticExpr(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2857 "yacc_sql.cpp"
    break;

  case 119: /* add_expr: add_expr SUB mul_expr  */
#line 981 "yacc_sql.y"
                            {
      (yyval.expression) = new ArithmeticExpr(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2865 "yacc_sql.cpp"
    break;

  case 120: /* mul_expr: unary_expr  */
#line 988 "yacc_sql.y"
               {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2873 "yacc_sql.cpp"
    break;

  case 121: /* mul_expr: mul_expr '*' unary_expr  */
#line 991 "yacc_sql.y"
                              {
      (yyval.expression) = new ArithmeticExpr(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2881 "yacc_sql.cpp"
    break;

  case 122: /* mul_expr: mul_expr '/' unary_expr  */
#line 994 "yacc_sql.y"
                              {
      (yyval.expression) = new ArithmeticExpr(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2889 "yacc_sql.cpp"
    break;

  case 123: /* unary_expr: value  */
#line 1001 "yacc_sql.y"
          {     
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
    }
#line 2897 "yacc_sql.cpp"
    break;

  case 124: /* unary_expr: ID  */
#line 1004 "yacc_sql.y"
         {
      (yyval.expression) = new FieldExpr((yyvsp[0].string));
    }
#line 2905 "yacc_sql.cpp"
    break;

  case 125: /* unary_expr: ID DOT ID  */
#line 1007 "yacc_sql.y"
                {
      (yyval.expression) = new FieldExpr((yyvsp[0].string), (yyvsp[-2].string));
    }
#line 2913 "yacc_sql.cpp"
    break;

  case 126: /* unary_expr: LBRACE add_expr RBRACE  */
#line 1010 "yacc_sql.y"
                             {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_with_brace();
    }
#line 2922 "yacc_sql.cpp"
    break;

  case 127: /* unary_expr: aggr_func_expr  */
#line 1017 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2930 "yacc_sql.cpp"
    break;

  case 128: /* unary_expr: sub_select_expr  */
#line 1020 "yacc_sql.y"
                      {
       (yyval.expression) = (yyvsp[0].expression);
    }
#line 2938 "yacc_sql.cpp"
    break;

  case 129: /* unary_expr: sub_select_list  */
#line 1023 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2946 "yacc_sql.cpp"
    break;

  case 130: /* unary_expr: SUB unary_expr  */
#line 1026 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
      (yyval.expression)->set_negtive();
    }
#line 2955 "yacc_sql.cpp"
    break;

  case 131: /* aggr_func_expr: aggr_func_type LBRACE add_expr RBRACE  */
#line 1034 "yacc_sql.y"
  {
    assert(ExprType::FIELD == (yyvsp[-1].expression)->type());
    (yyval.expression) = new AggrFuncExpression((yyvsp[-3].aggr_func_type), static_cast<FieldExpr*>((yyvsp[-1].expression)));
  }
#line 2964 "yacc_sql.cpp"
    break;

  case 132: /* aggr_func_expr: AGGR_COUNT LBRACE add_expr RBRACE  */
#line 1039 "yacc_sql.y"
  {
    assert(ExprType::FIELD == (yyvsp[-1].expression)->type());
    (yyval.expression) = new AggrFuncExpression(AggrFuncType::CNT, static_cast<FieldExpr*>((yyvsp[-1].expression)));
  }
#line 2973 "yacc_sql.cpp"
    break;

  case 133: /* aggr_func_expr: AGGR_COUNT LBRACE '*' RBRACE  */
#line 1044 "yacc_sql.y"
  {
    ValueExpr *temp = new ValueExpr(Value("*"));
    (yyval.expression) = new AggrFuncExpression(AggrFuncType::CNT, temp);
  }
#line 2982 "yacc_sql.cpp"
    break;

  case 134: /* aggr_func_type: AGGR_MAX  */
#line 1051 "yacc_sql.y"
             {
      (yyval.aggr_func_type) = AggrFuncType::MAX;
    }
#line 2990 "yacc_sql.cpp"
    break;

  case 135: /* aggr_func_type: AGGR_MIN  */
#line 1054 "yacc_sql.y"
               {
      (yyval.aggr_func_type) = AggrFuncType::MIN;
    }
#line 2998 "yacc_sql.cpp"
    break;

  case 136: /* aggr_func_type: AGGR_SUM  */
#line 1057 "yacc_sql.y"
               {
      (yyval.aggr_func_type) = AggrFuncType::SUM;
    }
#line 3006 "yacc_sql.cpp"
    break;

  case 137: /* aggr_func_type: AGGR_AVG  */
#line 1060 "yacc_sql.y"
               {
      (yyval.aggr_func_type) = AggrFuncType::AVG;
    }
#line 3014 "yacc_sql.cpp"
    break;

  case 138: /* sub_select_expr: LBRACE select_stmt RBRACE  */
#line 1068 "yacc_sql.y"
  {
    // SubQueryExpression
    (yyval.expression) = new SubQueryExpression((yyvsp[-1].sql_node));
  }
#line 3023 "yacc_sql.cpp"
    break;

  case 139: /* sub_select_list: LBRACE value value_list RBRACE  */
#line 1076 "yacc_sql.y"
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
#line 3039 "yacc_sql.cpp"
    break;

  case 140: /* comp_op: EQ  */
#line 1090 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3045 "yacc_sql.cpp"
    break;

  case 141: /* comp_op: LT  */
#line 1091 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3051 "yacc_sql.cpp"
    break;

  case 142: /* comp_op: GT  */
#line 1092 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3057 "yacc_sql.cpp"
    break;

  case 143: /* comp_op: LE  */
#line 1093 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3063 "yacc_sql.cpp"
    break;

  case 144: /* comp_op: GE  */
#line 1094 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3069 "yacc_sql.cpp"
    break;

  case 145: /* comp_op: NE  */
#line 1095 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3075 "yacc_sql.cpp"
    break;

  case 146: /* comp_op: LIKE_T  */
#line 1096 "yacc_sql.y"
             { (yyval.comp) = LIKE_OP; }
#line 3081 "yacc_sql.cpp"
    break;

  case 147: /* comp_op: NOT_LIKE_T  */
#line 1097 "yacc_sql.y"
                 {(yyval.comp) = NOT_LIKE_OP; }
#line 3087 "yacc_sql.cpp"
    break;

  case 148: /* comp_op: IN  */
#line 1098 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3093 "yacc_sql.cpp"
    break;

  case 149: /* comp_op: EXISTS  */
#line 1099 "yacc_sql.y"
             {(yyval.comp) = EXISTS_OP; }
#line 3099 "yacc_sql.cpp"
    break;

  case 150: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1104 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3113 "yacc_sql.cpp"
    break;

  case 151: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1117 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3122 "yacc_sql.cpp"
    break;

  case 152: /* set_variable_stmt: SET ID EQ value  */
#line 1125 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3134 "yacc_sql.cpp"
    break;


#line 3138 "yacc_sql.cpp"

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

#line 1137 "yacc_sql.y"

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
