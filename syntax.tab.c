
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "syntax.y"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "symtable.h"
#include "hash.h"
#include "list.h"
  
  /* MACROS FOR BISON */
  /* This macro prints verbose error messages when syntax errors happen. */
#define YYERROR_VERBOSE
#define YYDEBUG 1
  
#define MAX_IDEN_LEN 50

  extern int yydebug; /* For parser-trace facilities. */
  extern int yylineno; /* Making the global variable yylineno available to us. */
  extern char yytext[]; /* Making global variable yytext available to us. */
  extern int yyleng; /* Length of the yytext returned. */
  char* file_name; /* The name of the file that we are parsing. */

  int yywrap (void); /* Function that is called when scanner reaches EOF. */
  void yyerror (const char* s);  /* Function that is called when a parsing error occurs. */
  void print_warning (const char* s);
  void AddCode();
  int codeGen(char*);
  
  char* id_arr[50]; 
  int id_arr_size = 0;
  bool inside_paramlist = false; /* Used during variable declarations. */

  typedef struct kiran
  {
    char name[20];
    int offset;
  }ret_off;
  
  ret_off  ret_offset[20];
  int ret_address=0;
 
  //LATEST
  /* Global function/scope table. */
  struct hash func_table;

  /* Current scope. */
  func_entry_t* current_scope; /* The current scope's symbol table is available in this itself. */

  /* Functions for semantic actions. */
  void init_global_scope (char* iden);
  void idarr_assign_types (enum type enumtype, int lower_bound, int upper_bound);
  void idarr_assign_array_types (enum type id_type, int lower_bound, int upper_bound);
  void idarr_assign_simple_types (enum type id_type);
  void switch_to_newscope (char* iden);
  func_entry_t* lookup_func_entry (char* iden);
  func_entry_t* lookup_func_scope (char* iden);
  id_entry_t* lookup_id_entry (char* iden, func_entry_t* scope);
  id_entry_t* lookup_id_scopes (char* iden);
  void make_idarray_entry (char* iden);
  void make_scope_entry (func_entry_t* scope);
  int offset=0;
  int return_offset=1000;

  /* Next line no in intermediate code. */ //ASSGN4
  int next_quad = 1;

  /* Structures for intermediate code generation. */ //ASSGN4
  struct three_addr
  {
    float lineno; //line number ("float" because of need during sorting)
    char* code; //string containing the three address code
    struct list_elem elem;
  };
  
  struct list code_list; //list of three_addr

  typedef struct
  {
    int* lst;
    int length;
  } lst_t;

  bool lineno_less (const struct list_elem* a, const struct list_elem* b, void* aux);
  void backpatch (lst_t* lst, int quad);
  lst_t* merge_list (lst_t* lst1, lst_t* lst2);
  lst_t* make_list (int num);
  char* new_temp (void);


/* Line 189 of yacc.c  */
#line 163 "syntax.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     INTNUM = 259,
     REALNUM = 260,
     ADDOP = 261,
     MULOP = 262,
     RELOP = 263,
     ASSIGNOP = 264,
     ARRAY = 265,
     BEG = 266,
     BOOLEAN = 267,
     CASE = 268,
     CHAR = 269,
     DO = 270,
     ELSE = 271,
     END = 272,
     FUNCTION = 273,
     IF = 274,
     IN = 275,
     INTEGER = 276,
     NOT = 277,
     OF = 278,
     PROCEDURE = 279,
     PROGRAM = 280,
     REAL = 281,
     REPEAT = 282,
     THEN = 283,
     TYPE = 284,
     UNTIL = 285,
     VAR = 286,
     WHILE = 287,
     WITH = 288,
     INPUT = 289,
     OUTPUT = 290,
     PLUS = 291,
     MINUS = 292,
     OR_OP = 293,
     MULTIPLY = 294,
     DIVIDE = 295,
     INT_DIVIDE = 296,
     MOD_OP = 297,
     AND_OP = 298,
     DIGITS = 299,
     EQ = 300,
     NEQ = 301,
     LT = 302,
     LTE = 303,
     GT = 304,
     GTE = 305,
     WRONG_IDENTIFIER = 306,
     INVALID_CHAR = 307
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 92 "syntax.y"

   /* For integer values and all other token values. */
   int value;

   /* For floating point values. */
   float fl;

   /* String that stores the identifier. */
   char* iden;

   /* Stores one of the basic types - use in expressions. */
   enum type type_simple;

   /* Stores also the array type information. */
   struct type_struct
   {
     enum type enumtype;
     int lower_bound;
     int upper_bound;
   } type_detail;

   /* For storing details of actual arguments passed to procs/funcs. */
   struct actualargs_struct
   {
     enum type* arg_types;
     int num_args;
   } argument_detail;

   /* For intermediate code generation. */ //ASSGN4
   struct expr_struct
   {
     enum type type_simple;
     char* place;
     lst_t* truelist;
     lst_t* falselist;
   } expr_detail;

   /* For each statement. */ //ASSGN4
   struct stmt_struct
   {
     lst_t* nextlist;
   } stmt_detail;

   /* For keeping track of line numbers during intermediate code generation. */  //ASSGN4
   struct quad_struct
   {
     int quad;
   } quad_detail;



/* Line 214 of yacc.c  */
#line 303 "syntax.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 315 "syntax.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   451

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNRULES -- Number of states.  */
#define YYNSTATES  203

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      61,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      54,    55,     2,     2,    57,     2,    53,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,    56,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    59,     2,    60,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,    11,    12,    19,    21,    23,    27,    31,
      33,    35,    39,    43,    47,    51,    56,    60,    61,    67,
      71,    77,    83,    88,    92,    96,    98,   100,   110,   112,
     114,   116,   118,   120,   124,   128,   129,   134,   139,   147,
     153,   154,   156,   158,   161,   163,   166,   169,   172,   177,
     179,   183,   184,   188,   190,   193,   203,   210,   214,   215,
     217,   222,   227,   232,   235,   237,   242,   244,   249,   254,
     259,   262,   266,   268,   272,   276,   278,   282,   287,   290,
     292,   296,   298,   303,   307,   309,   311,   316,   321,   326,
     331,   336,   342,   348,   350,   352,   355,   359,   363,   367,
     370,   371
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      63,     0,    -1,    65,    68,    73,    64,    11,    79,    53,
      -1,    -1,    25,    66,    54,    67,    55,    56,    -1,     3,
      -1,    34,    -1,    34,    57,    35,    -1,    35,    57,    34,
      -1,    35,    -1,     1,    -1,     1,    57,    34,    -1,     1,
      57,    35,    -1,    34,    57,     1,    -1,    35,    57,     1,
      -1,    68,    31,    69,    56,    -1,    68,     1,    69,    -1,
      -1,    69,    56,    70,    58,    71,    -1,    70,    58,    71,
      -1,    69,    56,    70,     1,    71,    -1,    69,     1,    70,
      58,    71,    -1,    69,    70,    58,    71,    -1,    70,     1,
      71,    -1,    70,    57,     3,    -1,     3,    -1,    72,    -1,
      10,    59,     4,    53,    53,     4,    60,    23,    72,    -1,
      21,    -1,    26,    -1,    14,    -1,    12,    -1,     1,    -1,
      73,    74,    56,    -1,    73,    74,     1,    -1,    -1,    75,
      68,    11,    79,    -1,    75,    68,     1,    79,    -1,    18,
      76,    54,    78,    58,    72,    56,    -1,    24,    77,    54,
      78,    56,    -1,    -1,     3,    -1,     3,    -1,    69,    55,
      -1,    55,    -1,    69,     1,    -1,    80,    17,    -1,    80,
       1,    -1,    80,    90,    56,    81,    -1,    81,    -1,    80,
       1,    81,    -1,    -1,    83,     9,    86,    -1,    84,    -1,
      11,    79,    -1,    19,    86,    28,    90,    81,    82,    16,
      90,    81,    -1,    32,    90,    86,    15,    90,    81,    -1,
      83,     1,    86,    -1,    -1,     3,    -1,     3,    59,    86,
      60,    -1,     3,    59,    86,     1,    -1,     3,     1,    86,
      60,    -1,     3,    86,    -1,     3,    -1,     3,    54,    85,
      55,    -1,    51,    -1,    51,    54,    85,    55,    -1,     3,
       1,    85,    55,    -1,     3,    54,    85,     1,    -1,     3,
      85,    -1,    85,    57,    86,    -1,    86,    -1,    85,     1,
      86,    -1,    87,     8,    87,    -1,    87,    -1,    87,     1,
      87,    -1,    87,     6,    90,    88,    -1,    91,    88,    -1,
      88,    -1,    87,     1,    88,    -1,    89,    -1,    88,     7,
      90,    89,    -1,    88,     1,    89,    -1,     3,    -1,    51,
      -1,     3,    54,    85,    55,    -1,    51,    54,    85,    55,
      -1,     3,     1,    85,    55,    -1,     3,     1,    85,    56,
      -1,     3,     1,    85,    61,    -1,     3,    54,    85,     1,
      56,    -1,     3,    54,    85,     1,    61,    -1,     4,    -1,
       5,    -1,    22,    89,    -1,    54,    86,    55,    -1,    54,
      86,     1,    -1,     1,    86,    55,    -1,     1,    86,    -1,
      -1,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   215,   215,   228,   252,   257,   262,   269,   277,   285,
     292,   294,   296,   298,   300,   306,   308,   310,   315,   327,
     339,   341,   343,   345,   351,   359,   371,   373,   442,   444,
     446,   448,   450,   455,   470,   472,   477,   479,   485,   506,
     548,   554,   569,   586,   588,   590,   596,   598,   604,   606,
     610,   612,   617,   637,   644,   649,   664,   687,   698,   713,
     735,   779,   781,   783,   789,   824,   875,   877,   879,   881,
     883,   888,   905,   920,   925,   975,   984,   989,  1057,  1065,
    1073,  1079,  1087,  1157,  1163,  1208,  1210,  1272,  1275,  1276,
    1277,  1278,  1279,  1281,  1288,  1295,  1308,  1316,  1318,  1320,
    1330,  1340
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "INTNUM", "REALNUM",
  "ADDOP", "MULOP", "RELOP", "ASSIGNOP", "ARRAY", "BEG", "BOOLEAN", "CASE",
  "CHAR", "DO", "ELSE", "END", "FUNCTION", "IF", "IN", "INTEGER", "NOT",
  "OF", "PROCEDURE", "PROGRAM", "REAL", "REPEAT", "THEN", "TYPE", "UNTIL",
  "VAR", "WHILE", "WITH", "INPUT", "OUTPUT", "PLUS", "MINUS", "OR_OP",
  "MULTIPLY", "DIVIDE", "INT_DIVIDE", "MOD_OP", "AND_OP", "DIGITS", "EQ",
  "NEQ", "LT", "LTE", "GT", "GTE", "WRONG_IDENTIFIER", "INVALID_CHAR",
  "'.'", "'('", "')'", "';'", "','", "':'", "'['", "']'", "'\\n'",
  "$accept", "program", "M2", "program_heading", "program_identifier",
  "program_argument_lst", "declarations", "var_declarations",
  "var_identifier_lst", "type", "standard_type", "subprogram_declarations",
  "subprogram_declaration", "subprogram_head", "function_identifier",
  "procedure_identifier", "arguments", "compound_statement",
  "statement_lst", "statement", "N1", "variable", "procedure_statement",
  "actual_arguments_lst", "expression", "simple_exp", "term", "factor",
  "M1", "sign", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,    46,    40,    41,    59,    44,    58,    91,
      93,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    64,    65,    66,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    68,    68,    68,    69,    69,
      69,    69,    69,    69,    70,    70,    71,    71,    72,    72,
      72,    72,    72,    73,    73,    73,    74,    74,    75,    75,
      75,    76,    77,    78,    78,    78,    79,    79,    80,    80,
      80,    80,    81,    81,    81,    81,    81,    81,    82,    83,
      83,    83,    83,    83,    84,    84,    84,    84,    84,    84,
      84,    85,    85,    85,    86,    86,    86,    87,    87,    87,
      87,    88,    88,    88,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      90,    91
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     7,     0,     6,     1,     1,     3,     3,     1,
       1,     3,     3,     3,     3,     4,     3,     0,     5,     3,
       5,     5,     4,     3,     3,     1,     1,     9,     1,     1,
       1,     1,     1,     3,     3,     0,     4,     4,     7,     5,
       0,     1,     1,     2,     1,     2,     2,     2,     4,     1,
       3,     0,     3,     1,     2,     9,     6,     3,     0,     1,
       4,     4,     4,     2,     1,     4,     1,     4,     4,     4,
       2,     3,     1,     3,     3,     1,     3,     4,     2,     1,
       3,     1,     4,     3,     1,     1,     4,     4,     4,     4,
       4,     5,     5,     1,     1,     2,     3,     3,     3,     2,
       0,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    17,     5,     0,     1,     0,     0,     0,
       0,    40,    10,     6,     9,     0,    25,     0,     0,     0,
       0,     0,     0,     0,    17,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    15,    41,     0,    42,     0,
      51,    34,    33,     0,    11,    12,    13,     7,    14,     8,
       4,     0,     0,     0,    32,     0,    31,    30,    28,    29,
      23,    26,    24,    19,     0,     0,     0,    51,     0,   100,
      66,     0,     0,    49,     0,    53,    51,    51,     0,     0,
       0,    22,     0,    44,     0,     0,     0,     0,     0,    93,
      94,   101,     0,    85,     0,     0,     0,    72,     0,     0,
      81,     0,    54,     0,     0,     0,     0,     0,     2,    47,
      46,     0,     0,     0,     0,    37,    36,    21,    20,    18,
       0,    45,    43,     0,    39,     0,    99,     0,     0,    95,
       0,     0,     0,     0,     0,     0,     0,   100,     0,     0,
     100,     0,    99,     0,   100,     0,     0,    72,    50,     0,
      57,    52,     0,     0,    68,    98,    62,     0,     0,     0,
       0,    65,    97,    96,    61,    60,    73,    71,     0,     0,
       0,     0,    83,     0,     0,   100,    67,    48,     0,    38,
      88,    89,    90,     0,    86,    87,     0,     0,    82,    58,
       0,     0,    91,    92,     0,     0,    56,     0,   100,     0,
       0,    27,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    22,     3,     5,    15,     7,    17,    18,    60,
      61,    11,    23,    24,    37,    39,    85,    71,    72,    73,
     195,    74,    75,    96,   147,    98,    99,   100,   106,   101
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -114
static const yytype_int16 yypact[] =
{
       2,    31,    37,  -114,  -114,    -8,  -114,   235,   230,   110,
     110,   120,   100,   102,   105,    39,  -114,   372,    44,     6,
     164,   169,   177,    22,  -114,    94,    24,    16,   129,   110,
     110,   122,   406,   194,   406,   110,  -114,   150,  -114,   160,
     216,  -114,  -114,    32,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,   184,    54,   406,  -114,   143,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,    33,    33,   355,   216,   335,  -114,
     168,   196,   157,  -114,    51,  -114,   292,   216,   406,   406,
     406,  -114,   233,  -114,   174,   189,   195,   335,    91,  -114,
    -114,  -114,   397,   198,   335,   335,   104,    95,   108,   126,
    -114,   397,  -114,   335,   335,   222,   335,   335,  -114,   216,
    -114,   202,   335,   335,   311,  -114,  -114,  -114,  -114,  -114,
     201,   110,  -114,   373,  -114,    34,    27,   335,   335,  -114,
     335,   121,   138,    19,   335,   335,   335,  -114,   335,   397,
    -114,   183,   207,    25,  -114,   248,   139,  -114,  -114,   216,
    -114,  -114,   215,   213,  -114,  -114,  -114,    20,   148,   155,
     375,  -114,  -114,  -114,  -114,  -114,  -114,  -114,   200,   126,
     397,   217,  -114,   397,   216,  -114,  -114,  -114,   266,  -114,
    -114,  -114,  -114,    10,  -114,  -114,   397,   274,  -114,  -114,
     216,   211,  -114,  -114,   291,   260,  -114,   256,  -114,   373,
     216,  -114,  -114
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -114,  -114,  -114,  -114,  -114,  -114,   261,   156,   -11,   -22,
    -113,  -114,  -114,  -114,  -114,  -114,   219,   -23,  -114,  -107,
    -114,  -114,  -114,    43,   -65,    17,   -96,   -88,   -72,  -114
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -101
static const yytype_int16 yytable[] =
{
     111,    97,   148,   105,   129,   141,    31,    29,    31,    16,
     153,   103,    63,    88,    89,    90,    91,    48,    51,    52,
     164,   134,   126,    41,    52,    46,   162,     1,   -72,   132,
     133,    81,    92,    76,     4,   134,    16,     6,   142,   143,
     169,   145,   177,    77,   102,    32,     8,   150,   151,    97,
      49,   172,   112,   115,   116,    79,   117,   118,   119,    47,
     113,    93,    35,    10,   104,   170,   192,   189,   173,   166,
     167,   193,   174,    31,   187,   180,   181,   135,    42,   165,
     163,   182,   155,   196,   -72,   188,   201,   156,    83,   154,
     194,   135,   127,   202,    28,   166,   -63,   -84,   -84,   -84,
     -84,    33,    34,   190,   -63,   134,   -84,   -84,   -84,   136,
      51,    33,    80,    16,   137,   -75,   138,   -75,   166,   -84,
     -70,   -70,   160,   -75,   -75,   -75,   200,   139,    44,    45,
     125,    -3,   -79,   140,   -79,   -79,   -75,   131,    20,   162,
     134,   -79,   -79,   -79,    21,   128,   -84,   -84,   -84,   183,
     146,   -84,   -84,   168,   -79,   171,   134,    25,   109,    26,
     -70,   135,    27,   -75,   -75,   -75,    19,    36,   -75,   -75,
     157,   158,    38,   159,   110,   121,   161,    16,   135,    33,
      53,   -79,   -79,   -79,   139,    50,   -79,   -79,    40,   -78,
     140,   -78,   -78,   163,   176,   -72,   135,    62,   -78,   -78,
     -78,   186,    82,   184,    64,   135,   137,   -76,   -76,   -76,
     185,   -78,   135,  -100,    65,   -76,   -76,   -76,   186,    66,
      84,    84,   107,   137,   -74,   -74,   -74,    67,   -76,   122,
      30,    12,   -74,   -74,   -74,    68,     9,   120,   -78,   -78,
     -78,    33,    78,   -78,   -78,   -74,   -35,   123,    69,   108,
     144,   124,   130,   -35,   152,   -76,   -76,   -76,   149,   -35,
     -76,   -76,   155,   175,    13,    14,    10,    70,   178,   179,
     191,   197,   -74,   -74,   -74,   139,   198,   -74,   -74,   199,
     -77,   140,   -77,   -77,    86,    43,     0,     0,     0,   -77,
     -77,   -77,   139,     0,     0,   114,     0,   -80,   140,   -80,
     -80,     0,   -77,    67,     0,     0,   -80,   -80,   -80,     0,
       0,    68,    87,     0,    88,    89,    90,    91,     0,   -80,
     -59,     0,     0,     0,    69,     0,     0,     0,   -64,   -77,
     -77,   -77,     0,    92,   -77,   -77,   103,     0,    88,    89,
      90,    91,     0,    70,     0,     0,   -80,   -80,   -80,     0,
       0,   -80,   -80,     0,     0,     0,    87,    92,    88,    89,
      90,    91,    93,     0,   -59,    94,     0,   -64,   -25,   -25,
      95,   -64,   -64,    29,    54,    16,   103,    92,    88,    89,
      90,    91,     0,   -16,     0,    56,    93,    57,     0,   104,
     -16,   -69,   -69,     0,    58,     0,   -16,    92,   103,    59,
      88,    89,    90,   -16,     0,     0,    93,    54,     0,    94,
       0,   -64,     0,     0,    95,     0,    55,     0,    56,    92,
      57,     0,     0,     0,     0,     0,    93,    58,    30,   104,
       0,   -69,    59,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,     0,
       0,   104
};

static const yytype_int16 yycheck[] =
{
      72,    66,   109,    68,    92,   101,    17,     1,    19,     3,
     123,     1,    34,     3,     4,     5,     6,     1,    29,    30,
       1,     1,    87,     1,    35,     1,     1,    25,     1,    94,
      95,    53,    22,     1,     3,     1,     3,     0,   103,   104,
     136,   106,   149,    11,    67,     1,    54,   112,   113,   114,
      34,   139,     1,    76,    77,     1,    78,    79,    80,    35,
       9,    51,    56,    31,    54,   137,    56,   174,   140,   134,
     135,    61,   144,    84,   170,    55,    56,    57,    56,    60,
      55,    61,    55,   190,    57,   173,   199,    60,    55,    55,
     186,    57,     1,   200,    55,   160,     1,     6,     7,     8,
       9,    57,    58,   175,     9,     1,    15,    16,    17,     1,
     121,    57,    58,     3,     6,     7,     8,     9,   183,    28,
      16,    17,     1,    15,    16,    17,   198,     1,    34,    35,
      87,    11,     6,     7,     8,     9,    28,    94,    18,     1,
       1,    15,    16,    17,    24,    54,    55,    56,    57,     1,
     107,    60,    61,   136,    28,   138,     1,    57,     1,    57,
      56,    57,    57,    55,    56,    57,    10,     3,    60,    61,
     127,   128,     3,   130,    17,     1,    55,     3,    57,    57,
      58,    55,    56,    57,     1,    56,    60,    61,    11,     6,
       7,     8,     9,    55,    55,    57,    57,     3,    15,    16,
      17,     1,    59,    55,    54,    57,     6,     7,     8,     9,
      55,    28,    57,    56,    54,    15,    16,    17,     1,     3,
      64,    65,    54,     6,     7,     8,     9,    11,    28,    55,
      56,     1,    15,    16,    17,    19,     1,     4,    55,    56,
      57,    57,    58,    60,    61,    28,    11,    58,    32,    53,
      28,    56,    54,    18,    53,    55,    56,    57,    56,    24,
      60,    61,    55,    15,    34,    35,    31,    51,    53,    56,
       4,    60,    55,    56,    57,     1,    16,    60,    61,    23,
       6,     7,     8,     9,    65,    24,    -1,    -1,    -1,    15,
      16,    17,     1,    -1,    -1,     3,    -1,     6,     7,     8,
       9,    -1,    28,    11,    -1,    -1,    15,    16,    17,    -1,
      -1,    19,     1,    -1,     3,     4,     5,     6,    -1,    28,
       9,    -1,    -1,    -1,    32,    -1,    -1,    -1,    17,    55,
      56,    57,    -1,    22,    60,    61,     1,    -1,     3,     4,
       5,     6,    -1,    51,    -1,    -1,    55,    56,    57,    -1,
      -1,    60,    61,    -1,    -1,    -1,     1,    22,     3,     4,
       5,     6,    51,    -1,     9,    54,    -1,    56,    57,    58,
      59,    16,    17,     1,     1,     3,     1,    22,     3,     4,
       5,     6,    -1,    11,    -1,    12,    51,    14,    -1,    54,
      18,    16,    17,    -1,    21,    -1,    24,    22,     1,    26,
       3,     4,     5,    31,    -1,    -1,    51,     1,    -1,    54,
      -1,    56,    -1,    -1,    59,    -1,    10,    -1,    12,    22,
      14,    -1,    -1,    -1,    -1,    -1,    51,    21,    56,    54,
      -1,    56,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    54
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    25,    63,    65,     3,    66,     0,    68,    54,     1,
      31,    73,     1,    34,    35,    67,     3,    69,    70,    69,
      18,    24,    64,    74,    75,    57,    57,    57,    55,     1,
      56,    70,     1,    57,    58,    56,     3,    76,     3,    77,
      11,     1,    56,    68,    34,    35,     1,    35,     1,    34,
      56,    70,    70,    58,     1,    10,    12,    14,    21,    26,
      71,    72,     3,    71,    54,    54,     3,    11,    19,    32,
      51,    79,    80,    81,    83,    84,     1,    11,    58,     1,
      58,    71,    59,    55,    69,    78,    78,     1,     3,     4,
       5,     6,    22,    51,    54,    59,    85,    86,    87,    88,
      89,    91,    79,     1,    54,    86,    90,    54,    53,     1,
      17,    90,     1,     9,     3,    79,    79,    71,    71,    71,
       4,     1,    55,    58,    56,    85,    86,     1,    54,    89,
      54,    85,    86,    86,     1,    57,     1,     6,     8,     1,
       7,    88,    86,    86,    28,    86,    85,    86,    81,    56,
      86,    86,    53,    72,    55,    55,    60,    85,    85,    85,
       1,    55,     1,    55,     1,    60,    86,    86,    87,    88,
      90,    87,    89,    90,    90,    15,    55,    81,    53,    56,
      55,    56,    61,     1,    55,    55,     1,    88,    89,    81,
      90,     4,    56,    61,    88,    82,    81,    60,    16,    23,
      90,    72,    81
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 216 "syntax.y"
    {
  /* Generating the final line of the code. */
  backpatch((yyvsp[(6) - (7)].stmt_detail).nextlist,next_quad);
  struct three_addr* addr = malloc (sizeof (struct three_addr)); 
  addr->lineno = next_quad;
  addr->code = malloc (11);
  sprintf(addr->code, "%d:\t halt", (int)next_quad);
  list_push_back(&code_list, &addr->elem);
  next_quad++;
;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 228 "syntax.y"
    {
  struct three_addr* addr = malloc (sizeof (struct three_addr));
  addr->lineno = next_quad - 0.5;
  addr->code = malloc (strlen (current_scope->name));
  sprintf(addr->code, "%s:",current_scope->name);
  list_push_back(&code_list, &addr->elem);
;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 252 "syntax.y"
    { make_scope_entry (current_scope); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 257 "syntax.y"
    {init_global_scope ((yyvsp[(1) - (1)].iden));;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 263 "syntax.y"
    {
  current_scope->num_args = 1;
  current_scope->arg_types = malloc (sizeof (enum type));
  *current_scope->arg_types = INPUT_TYPE;
;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 270 "syntax.y"
    {
  current_scope->num_args = 2;
  current_scope->arg_types = malloc (2 * sizeof (enum type));
  *current_scope->arg_types = INPUT_TYPE;
  *(current_scope->arg_types + 1) = OUTPUT_TYPE;
;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 278 "syntax.y"
    {
  current_scope->num_args = 2;
  current_scope->arg_types = malloc (2 * sizeof (enum type));
  *current_scope->arg_types = OUTPUT_TYPE;
  *(current_scope->arg_types + 1) = INPUT_TYPE;
;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 286 "syntax.y"
    {
  current_scope->num_args = 1;
  current_scope->arg_types = malloc (sizeof (enum type));
  *current_scope->arg_types = OUTPUT_TYPE;
;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 292 "syntax.y"
    {yyerror ("expected 'input' or 'output' in program heading"); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 294 "syntax.y"
    {yyerror ("expected 'output' in program header");;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 296 "syntax.y"
    {yyerror ("expected 'input' in program header");;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 298 "syntax.y"
    {yyerror ("expected 'output' in program header");;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 300 "syntax.y"
    {yyerror ("expected 'input' in program header");;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 308 "syntax.y"
    {yyerror("Expected keyword var in the declarations statement");;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 316 "syntax.y"
    {
  if (inside_paramlist)
    {
      current_scope->arg_types = realloc (current_scope->arg_types, current_scope->num_args * sizeof (enum type));
      int i;
      for (i = current_scope->num_args - id_arr_size; i < current_scope->num_args; i++)
	current_scope->arg_types[i] = (yyvsp[(5) - (5)].type_detail).enumtype;
    }
  idarr_assign_types ((yyvsp[(5) - (5)].type_detail).enumtype, (yyvsp[(5) - (5)].type_detail).lower_bound, (yyvsp[(5) - (5)].type_detail).upper_bound);
;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 328 "syntax.y"
    {
  if (inside_paramlist)
    {
      current_scope->arg_types = malloc (current_scope->num_args * sizeof (enum type));
      int i;
      for (i = 0; i < id_arr_size; i++)
	current_scope->arg_types[i] = (yyvsp[(3) - (3)].type_detail).enumtype;
    }
  idarr_assign_types ((yyvsp[(3) - (3)].type_detail).enumtype, (yyvsp[(3) - (3)].type_detail).lower_bound, (yyvsp[(3) - (3)].type_detail).upper_bound);
;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 339 "syntax.y"
    {yyerror("expected : before specifying the type for the list of identifiers");;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 341 "syntax.y"
    {yyerror("expected ; after specifying the type for the list of identifiers");;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 343 "syntax.y"
    {yyerror ("Missing ; between variable declarations"); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 345 "syntax.y"
    {yyerror("Expected : before specifying the type for the list of identifiers");;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 352 "syntax.y"
    {
  make_idarray_entry ((yyvsp[(3) - (3)].iden));

  if (inside_paramlist)
    current_scope->num_args++;
;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 360 "syntax.y"
    {
  make_idarray_entry ((yyvsp[(1) - (1)].iden));

  if (inside_paramlist)
    current_scope->num_args++;
;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 371 "syntax.y"
    {(yyval.type_detail).enumtype = (yyvsp[(1) - (1)].type_simple);;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 374 "syntax.y"
    {
  switch ((yyvsp[(9) - (9)].type_simple))
    {
    case INT_TYPE:
      (yyval.type_detail).enumtype = ARRAY_INT_TYPE;
      (yyval.type_detail).lower_bound = (yyvsp[(3) - (9)].value);
      (yyval.type_detail).upper_bound = (yyvsp[(6) - (9)].value);
      break;
    case REAL_TYPE:
      (yyval.type_detail).enumtype = ARRAY_REAL_TYPE;
      (yyval.type_detail).lower_bound = (yyvsp[(3) - (9)].value);
      (yyval.type_detail).upper_bound = (yyvsp[(6) - (9)].value);
      break;
    case CHAR_TYPE:
      (yyval.type_detail).enumtype = ARRAY_CHAR_TYPE;
      (yyval.type_detail).lower_bound = (yyvsp[(3) - (9)].value);
      (yyval.type_detail).upper_bound = (yyvsp[(6) - (9)].value);
      break;
    case BOOL_TYPE:
      (yyval.type_detail).enumtype = ARRAY_BOOL_TYPE;
      (yyval.type_detail).lower_bound = (yyvsp[(3) - (9)].value);
      (yyval.type_detail).upper_bound = (yyvsp[(6) - (9)].value);
      break;
    default:
      break;
    }

  if ((yyvsp[(3) - (9)].value) > (yyvsp[(6) - (9)].value))
    yyerror ("invalid index range for the array type");
;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 442 "syntax.y"
    {(yyval.type_simple) = INT_TYPE;;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 444 "syntax.y"
    {(yyval.type_simple) = REAL_TYPE;;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 446 "syntax.y"
    {(yyval.type_simple) = CHAR_TYPE;;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 448 "syntax.y"
    {(yyval.type_simple) = BOOL_TYPE;;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 450 "syntax.y"
    {(yyval.type_simple) = NO_TYPE; yyerror ("expected a valid type");;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 456 "syntax.y"
    {
  /* Thats the end of a function/procedure definition. 
     So now we switch back to the parent scope. */
  current_scope = current_scope->parent_scope;

  /* Generating 3addr code. */
  struct three_addr* addr = malloc (sizeof (struct three_addr)); 
  addr->lineno = next_quad;
  addr->code = malloc (13);
  sprintf(addr->code, "%d:\t return\n", (int)next_quad);
  list_push_front(&code_list, &addr->elem);
  next_quad++;
;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 470 "syntax.y"
    {yyerror("Expected ; at the end of the declarations");;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 479 "syntax.y"
    { yyerror("Expected keyword begin after all the declarations ");;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 486 "syntax.y"
    {
  /* Parameters have already been entered into symbol table now. One more entry left in sym table. 
     That is the name of the function itself, with the return type as the type. */
  inside_paramlist = false;
  id_arr[0] = (yyvsp[(2) - (7)].iden);
  id_arr_size = 1;
  current_scope->return_type = (yyvsp[(6) - (7)].type_simple);
  idarr_assign_types ((yyvsp[(6) - (7)].type_simple), 0, 0);
  id_arr_size = 0;
  make_scope_entry (current_scope);
  
  struct three_addr* addr = malloc (sizeof (struct three_addr)); 
  addr->lineno = next_quad - 0.5; //to make it appear before the first statement of the procedure/function
  addr->code = malloc (strlen((yyvsp[(2) - (7)].iden))+2);
  sprintf(addr->code, "%s:",(yyvsp[(2) - (7)].iden));
  list_push_front(&code_list, &addr->elem);
  //next_quad++;
  
;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 507 "syntax.y"
    {
  inside_paramlist = false;
  current_scope->return_type = NO_TYPE;
  make_scope_entry (current_scope);
  
  struct three_addr* addr = malloc (sizeof (struct three_addr)); 
  addr->lineno = next_quad - 0.5; //to make it appear before the first statement of the procedure/function
  addr->code = malloc (strlen((yyvsp[(2) - (5)].iden))+2);
  sprintf(addr->code, "%s:",(yyvsp[(2) - (5)].iden));
  list_push_front(&code_list, &addr->elem);
  //next_quad++;
;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 555 "syntax.y"
    {
  (yyval.iden) = (yyvsp[(1) - (1)].iden);
  /* If not already present. */
  if (!lookup_func_entry ((yyvsp[(1) - (1)].iden)))
    {
      switch_to_newscope ((yyvsp[(1) - (1)].iden)); /* Create a new scope (which is the 'child') and assign it to current scope. */
      inside_paramlist = true; /* We are now entering the formal parameter list. */
    }
  else
    yyerror ("redeclaration of function: two functions cannot have same name");
;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 570 "syntax.y"
    {
  (yyval.iden) = (yyvsp[(1) - (1)].iden);
  /* If not already present. */
  if (!lookup_func_entry ((yyvsp[(1) - (1)].iden)))
    {
      switch_to_newscope ((yyvsp[(1) - (1)].iden)); /* Create a new scope (which is the 'child') and assign it to current scope. */
      inside_paramlist = true;
    }
  else
    yyerror ("redeclaration of procedure: two procedure cannot have same name");
;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 590 "syntax.y"
    {yyerror("Expected ) after list of parameters");;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 596 "syntax.y"
    { (yyval.stmt_detail).nextlist = (yyvsp[(1) - (2)].stmt_detail).nextlist;;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 598 "syntax.y"
    {yyerror("Expected keyword end at the end of the list of statements");;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 604 "syntax.y"
    { backpatch((yyvsp[(1) - (4)].stmt_detail).nextlist,(yyvsp[(2) - (4)].quad_detail).quad); (yyval.stmt_detail).nextlist = (yyvsp[(4) - (4)].stmt_detail).nextlist;;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 606 "syntax.y"
    {(yyval.stmt_detail).nextlist = (yyvsp[(1) - (1)].stmt_detail).nextlist;;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 610 "syntax.y"
    {yyerror("Expected ; between two statements");;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 612 "syntax.y"
    {(yyval.stmt_detail).nextlist = (lst_t*) malloc(sizeof(lst_t)); (yyval.stmt_detail).nextlist->lst = (int*) malloc(20*sizeof(int)); (yyval.stmt_detail).nextlist->length =0;;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 618 "syntax.y"
    {
  if (! ((yyvsp[(1) - (3)].expr_detail).type_simple == REAL_TYPE && (yyvsp[(3) - (3)].expr_detail).type_simple == INT_TYPE)
      && (yyvsp[(1) - (3)].expr_detail).type_simple != (yyvsp[(3) - (3)].expr_detail).type_simple)
    yyerror ("incompatible types in assignment");
  else if ((yyvsp[(1) - (3)].expr_detail).type_simple == ARRAY_INT_TYPE || (yyvsp[(1) - (3)].expr_detail).type_simple == ARRAY_REAL_TYPE
	   || (yyvsp[(1) - (3)].expr_detail).type_simple == ARRAY_CHAR_TYPE || (yyvsp[(1) - (3)].expr_detail).type_simple == ARRAY_BOOL_TYPE)
    yyerror ("assignment operation cannot be done on arrays");
  else
    {
      /* Generate the three address code. */
      struct three_addr* addr_n = malloc (sizeof (struct three_addr));
      addr_n->code = malloc (11 + strlen ((yyvsp[(1) - (3)].expr_detail).place) + strlen ((yyvsp[(3) - (3)].expr_detail).place));
      addr_n->lineno = next_quad;
      sprintf(addr_n->code,"%d:\t %s := %s",(int)next_quad,(yyvsp[(1) - (3)].expr_detail).place,(yyvsp[(3) - (3)].expr_detail).place);
      list_push_front(&code_list, &addr_n->elem);
      next_quad++;
    }
;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 638 "syntax.y"
    {
  (yyval.stmt_detail).nextlist = (lst_t*)malloc(sizeof(lst_t));
  (yyval.stmt_detail).nextlist->lst = (int*)malloc(sizeof(int)*20);
  (yyval.stmt_detail).nextlist->length = 0;
;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 645 "syntax.y"
    {
  (yyval.stmt_detail).nextlist = (yyvsp[(2) - (2)].stmt_detail).nextlist
;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 650 "syntax.y"
    {
  if ((yyvsp[(2) - (9)].expr_detail).type_simple != BOOL_TYPE)
    yyerror ("boolean type expected for 'if' condition");
  else
    {
      (yyval.stmt_detail).nextlist = (lst_t*)malloc(sizeof(lst_t)*20);
      backpatch ((yyvsp[(2) - (9)].expr_detail).truelist,(yyvsp[(4) - (9)].quad_detail).quad);
      backpatch ((yyvsp[(2) - (9)].expr_detail).falselist,(yyvsp[(8) - (9)].quad_detail).quad);
      //$$.nextlist = merge_list ($2.falselist,$9.nextlist);
      (yyval.stmt_detail).nextlist = merge_list ((yyvsp[(9) - (9)].stmt_detail).nextlist,(yyvsp[(6) - (9)].stmt_detail).nextlist);
      (yyval.stmt_detail).nextlist = merge_list ((yyval.stmt_detail).nextlist,(yyvsp[(5) - (9)].stmt_detail).nextlist);
    }
;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 665 "syntax.y"
    {
  if ((yyvsp[(3) - (6)].expr_detail).type_simple != BOOL_TYPE)
    yyerror ("boolean type expected for 'while' condition");
  else
    {
      //printf ("I am here 1 for backpatch in the list %x \n",$6.nextlist);
      backpatch ((yyvsp[(6) - (6)].stmt_detail).nextlist, (yyvsp[(2) - (6)].quad_detail).quad);
      //printf ("I am here 2 \n");
      backpatch ((yyvsp[(3) - (6)].expr_detail).truelist, (yyvsp[(5) - (6)].quad_detail).quad);
      //printf ("I am here 3 \n");
      (yyval.stmt_detail).nextlist = (yyvsp[(3) - (6)].expr_detail).falselist;
    }

  /* Goto statement for looping back. */
  struct three_addr* addr_n = malloc (sizeof (struct three_addr));
  addr_n->code = malloc (17);
  addr_n->lineno = next_quad;
  sprintf(addr_n->code,"%d:\t goto %d",(int)next_quad,(yyvsp[(2) - (6)].quad_detail).quad);
  list_push_front(&code_list, &addr_n->elem);
  next_quad++;
;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 687 "syntax.y"
    {yyerror("Expected := between LHS and expression ");;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 698 "syntax.y"
    {
  //printf ("Reducing N\n");
  (yyval.stmt_detail).nextlist = make_list(next_quad);
 
  struct three_addr* addr = malloc (sizeof (struct three_addr));
  addr->code = malloc (13);
  addr->lineno = next_quad;
  sprintf(addr->code,"%d:\t goto ",(int)next_quad);      
  list_push_front(&code_list, &addr->elem);

  next_quad++;
;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 714 "syntax.y"
    {
  //printf ("Variable is %s\n", $1);

  //printf ("Current scope is %s\n", current_scope->name);
  /* We will check current scope. If not, then we shall iteratively check all
     visible scopes. If it is declared in some other visible scope, then we will make
     an entry in our scope too. */
  id_entry_t* t;
  if (t = lookup_id_scopes ((yyvsp[(1) - (1)].iden)))
    {
      (yyval.expr_detail).type_simple = t->id_type; /* BEWARE: this could be any of the ARRAY types too. But that is checked elsewhere, not here. */
      if (t->scope_name != current_scope->name)
	hash_insert (current_scope->symbol_table, &t->sym_table_elem);

      /* For 3addr code. */
      (yyval.expr_detail).place = malloc (strlen ((yyvsp[(1) - (1)].iden)) + 1);
      strcpy ((yyval.expr_detail).place, (yyvsp[(1) - (1)].iden));
    }
  else
    yyerror ("undeclared identifier");
;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 736 "syntax.y"
    {
  id_entry_t* t;
  if ((t = lookup_id_scopes ((yyvsp[(1) - (4)].iden))) && (yyvsp[(3) - (4)].expr_detail).type_simple == INT_TYPE)
    {
      switch (t->id_type)
	{
	case ARRAY_INT_TYPE:
	  (yyval.expr_detail).type_simple = INT_TYPE;
	  break;
	case ARRAY_REAL_TYPE:
	  (yyval.expr_detail).type_simple = REAL_TYPE;
	  break;
	case ARRAY_CHAR_TYPE:
	  (yyval.expr_detail).type_simple = CHAR_TYPE;
	  break;
	case ARRAY_BOOL_TYPE:
	  (yyval.expr_detail).type_simple = BOOL_TYPE;
	  break;

	default:
	  yyerror ("identifier is not an array variable: dereference on non-array types invalid");
	  break;
	}
      
      if (t->scope_name != current_scope->name)
	hash_insert (current_scope->symbol_table, &t->sym_table_elem);

      /* Generating 3addr code. */
      (yyval.expr_detail).place = (char*) malloc (strlen ((yyvsp[(1) - (4)].iden)) + 1 + 2 + strlen ((yyvsp[(3) - (4)].expr_detail).place) + 1);
      strcpy ((yyval.expr_detail).place, (yyvsp[(1) - (4)].iden));
      strcat ((yyval.expr_detail).place, "[");
      strcat ((yyval.expr_detail).place, (yyvsp[(3) - (4)].expr_detail).place);
      strcat ((yyval.expr_detail).place, "]");
    }
  else 
    {
      if (t == NULL)
	yyerror ("undeclared array identifier");
      if ((yyvsp[(3) - (4)].expr_detail).type_simple != INT_TYPE)
	yyerror ("array index should be an integer");
    }
;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 779 "syntax.y"
    {yyerror("Expected ] after expression");;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 781 "syntax.y"
    {yyerror("Expected [ before expression");;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 783 "syntax.y"
    {yyerror("Expected [ and ] before and after the expression"); yynerrs++; YYERROR;;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 790 "syntax.y"
    {
  //printf ("This is %s\n", $1);

  /* This represents a procedure/function call. The procedure/function must be declared within the current scope. */
  bool flag = true;
  func_entry_t* f;
  if (f = lookup_func_scope ((yyvsp[(1) - (1)].iden)))
    {
      /* Now we need to do validity checks. */

      /*(1) checking number of arguments */
      if (f->num_args != 0)
	{
	  flag = false;
	  yyerror ("procedure/function call expects arguments");
	}
    }
  else
    {
      flag = false;
      yyerror ("undeclared procedure/function name");
    }

  if (flag)
    {
      struct three_addr* addr = malloc (sizeof (struct three_addr)); 
      addr->lineno = next_quad;
      addr->code = malloc (13 + strlen ((yyvsp[(1) - (1)].iden)));
      sprintf(addr->code,"%d:\t call %s,0",(int)next_quad,(yyvsp[(1) - (1)].iden));
      list_push_front(&code_list, &addr->elem);
      next_quad++;
    }
;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 825 "syntax.y"
    {
  //printf ("I am here");
  bool flag = true;
  func_entry_t* f;
  if (f = lookup_func_scope ((yyvsp[(1) - (4)].iden)))
    {
      /* Now we need to do validity checks. */
      
      /*(1) checking number of arguments */
      if (f->num_args != (yyvsp[(3) - (4)].argument_detail).num_args)
	{
	  flag = false;
	  yyerror ("number of arguments mismatch in call to procedure/function");
	  printf ("expected %d arguments for function but received %d\n", f->num_args, (yyvsp[(3) - (4)].argument_detail).num_args);
	}
      
      /*(2) checking types of arguments */
      else
	{
	  int i;
	  for (i = 0; i < (yyvsp[(3) - (4)].argument_detail).num_args; i++)
	    {
	      if ((yyvsp[(3) - (4)].argument_detail).arg_types[i] != f->arg_types[i])
		{
		  flag = false;
		  yyerror ("conflicting types for actual argument(s) of procedure/function call");
		  break;
		}
	    }
	  free ((yyvsp[(3) - (4)].argument_detail).arg_types);
	}
    }
  else
    {
      yyerror ("undeclared procedure/function name");
      flag = false;
    }

  if (flag)
    {
      struct three_addr* addr = malloc (sizeof (struct three_addr)); 
      addr->lineno = next_quad;
      addr->code = malloc (16 + strlen ((yyvsp[(1) - (4)].iden)));
//      printf (" I am here ");
      sprintf(addr->code,"%d:\t call %s,%d",(int) next_quad, (yyvsp[(1) - (4)].iden), f->num_args);
      list_push_front(&code_list, &addr->elem);
      next_quad++;
    }
;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 875 "syntax.y"
    {yyerror("Expected valid identifier for procedure/function name ");yynerrs++;YYERROR;;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 877 "syntax.y"
    {yyerror("Expected valid identifier for procedure/function name ");yynerrs++;YYERROR;;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 879 "syntax.y"
    {yyerror("Expected ( before the expression list");;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 881 "syntax.y"
    {yyerror("Expected ) after the expression list");;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 883 "syntax.y"
    {yyerror("Expected ( and ) paranthesis before and after the list of expressions");yynerrs++;YYERROR;;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 889 "syntax.y"
    {
  (yyval.argument_detail).num_args = (yyvsp[(1) - (3)].argument_detail).num_args + 1;
  (yyval.argument_detail).arg_types = realloc ((yyvsp[(1) - (3)].argument_detail).arg_types, (yyval.argument_detail).num_args * sizeof (enum type));
  if ((yyval.argument_detail).arg_types != (yyvsp[(1) - (3)].argument_detail).arg_types)
    free ((yyvsp[(1) - (3)].argument_detail).arg_types); /* If block of memory was moved, then free the old block. */
  (yyval.argument_detail).arg_types[(yyvsp[(1) - (3)].argument_detail).num_args] = (yyvsp[(3) - (3)].expr_detail).type_simple;  

  /* Generating the 3addr code. */
  struct three_addr* addr = malloc (sizeof (struct three_addr)); 
  addr->lineno = next_quad;
  addr->code = malloc (13 + strlen ((yyvsp[(3) - (3)].expr_detail).place));
  sprintf(addr->code,"%d:\t param %s",(int)next_quad, (yyvsp[(3) - (3)].expr_detail).place);
  list_push_front (&code_list, &addr->elem);
  next_quad++;
;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 906 "syntax.y"
    {
  (yyval.argument_detail).num_args  = 1;
  (yyval.argument_detail).arg_types = realloc ((yyval.argument_detail).arg_types, 1 * sizeof (enum type));
  (yyval.argument_detail).arg_types[0] = (yyvsp[(1) - (1)].expr_detail).type_simple;

  /* Generating the 3addr code. */
  struct three_addr* addr = malloc (sizeof (struct three_addr)); 
  addr->lineno = next_quad;
  addr->code = malloc (13 + strlen ((yyvsp[(1) - (1)].expr_detail).place));  
  sprintf(addr->code,"%d:\t param %s",(int)next_quad,(yyvsp[(1) - (1)].expr_detail).place);
  list_push_front(&code_list, &addr->elem);
  next_quad++;
;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 920 "syntax.y"
    {yyerror("Expected , between two expressions");;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 926 "syntax.y"
    {
  enum type t = (yyvsp[(1) - (3)].expr_detail).type_simple;
  if (t == INT_TYPE && (yyvsp[(3) - (3)].expr_detail).type_simple == REAL_TYPE 
      || t == REAL_TYPE && (yyvsp[(3) - (3)].expr_detail).type_simple == INT_TYPE)
    {
      print_warning ("no typecasting provided for integer operand");
    }
  else if (t != (yyvsp[(3) - (3)].expr_detail).type_simple)
    yyerror ("incompatible types in comparison");
  else if (t >= ARRAY_INT_TYPE && t <= ARRAY_BOOL_TYPE)
    yyerror ("array types cannot be compared");
  else if (t == CHAR_TYPE)
    yyerror ("characters cannot be compared");
  else if (t == BOOL_TYPE)
    yyerror ("booleans cannot be compared ");
  else
    {
      /* Generating 3addr code. */
      (yyval.expr_detail).place = new_temp();
      (yyval.expr_detail).truelist = make_list (next_quad);
      (yyval.expr_detail).falselist = make_list (next_quad + 1);

      struct three_addr* addr = malloc (sizeof (struct three_addr)); //struct three_addr will have "char* addr and struct list_elem elems"
      addr->lineno = next_quad;
      addr->code = malloc (20 + strlen ((yyvsp[(1) - (3)].expr_detail).place) + strlen ((yyvsp[(3) - (3)].expr_detail).place));
      switch((yyvsp[(2) - (3)].value))
	{ 
        case EQ:  sprintf(addr->code,"%d:\t if %s = %s goto " , (int)next_quad, (yyvsp[(1) - (3)].expr_detail).place,(yyvsp[(3) - (3)].expr_detail).place);break;
	case NEQ: sprintf(addr->code,"%d:\t if %s <> %s goto ", (int)next_quad, (yyvsp[(1) - (3)].expr_detail).place,(yyvsp[(3) - (3)].expr_detail).place);break;
	case GT:  sprintf(addr->code,"%d:\t if %s > %s goto " , (int)next_quad, (yyvsp[(1) - (3)].expr_detail).place,(yyvsp[(3) - (3)].expr_detail).place);break;
	case GTE: sprintf(addr->code,"%d:\t if %s >= %s goto ", (int)next_quad, (yyvsp[(1) - (3)].expr_detail).place,(yyvsp[(3) - (3)].expr_detail).place);break;
	case LT:  sprintf(addr->code,"%d:\t if %s < %s goto " , (int)next_quad, (yyvsp[(1) - (3)].expr_detail).place,(yyvsp[(3) - (3)].expr_detail).place);break;
	case LTE: sprintf(addr->code,"%d:\t if %s <= %s goto ", (int)next_quad, (yyvsp[(1) - (3)].expr_detail).place,(yyvsp[(3) - (3)].expr_detail).place);break;
	}
      
      list_push_front (&code_list, &addr->elem);
      next_quad++;
      struct three_addr* addr_next = malloc (sizeof (struct three_addr)); //struct three_addr will have "char* addr and struct list_elem elems"
      addr_next->lineno = next_quad;
      addr_next->code = malloc (12); 
      sprintf(addr_next->code,"%d:\t goto ",(int)next_quad);
      list_push_front (&code_list, &addr_next->elem);
      next_quad++;
    }
  
  (yyval.expr_detail).type_simple = BOOL_TYPE; /* Whatever happens, finally the type of expression will be BOOLEAN. */
  id_entry_t* ent = lookup_id_entry ((yyval.expr_detail).place, current_scope);
  ent->id_type = BOOL_TYPE;
;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 976 "syntax.y"
    {
  (yyval.expr_detail).type_simple = (yyvsp[(1) - (1)].expr_detail).type_simple;
  (yyval.expr_detail).truelist = make_list (next_quad);
  (yyval.expr_detail).falselist = make_list (next_quad + 1);
  (yyval.expr_detail).place = (yyvsp[(1) - (1)].expr_detail).place;
  //printf ("$1.place here in expression->simple_exp is %s\n", $1.place);
;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 984 "syntax.y"
    {yyerror("Expected either * =,<,>,<=,>=,<> or a ,");;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 990 "syntax.y"
    {
  bool flag = true;
  enum type t = (yyvsp[(1) - (4)].expr_detail).type_simple;
  if ((yyvsp[(2) - (4)].value) == OR_OP)
    {
      if ((yyvsp[(1) - (4)].expr_detail).type_simple != BOOL_TYPE || (yyvsp[(4) - (4)].expr_detail).type_simple != BOOL_TYPE)
	{
	  yyerror ("invalid operands: logical OR operation requires boolean operands");
	  flag = false;
	}
      (yyval.expr_detail).type_simple = BOOL_TYPE;
    }
  else if (t == INT_TYPE && (yyvsp[(4) - (4)].expr_detail).type_simple == REAL_TYPE 
      || t == REAL_TYPE && (yyvsp[(4) - (4)].expr_detail).type_simple == INT_TYPE)
    {
      print_warning ("no typecasting provided for integer operand");
      (yyval.expr_detail).type_simple = REAL_TYPE;
    }
  else 
    {
      (yyval.expr_detail).type_simple = NO_TYPE;
      flag = false;
      if (t != (yyvsp[(4) - (4)].expr_detail).type_simple)
	yyerror ("incompatible types for add op");
      else if (t >= ARRAY_INT_TYPE && t <= ARRAY_BOOL_TYPE)
	yyerror ("add ops cannot be used on array type");
      else if (t == CHAR_TYPE)
	yyerror ("add ops cannot be used on character type");
      else if (t == BOOL_TYPE)
	yyerror ("add ops cannot be used on boolean type");
      else
	{
	  (yyval.expr_detail).type_simple = t;
	  flag = true;
	}
    }

  /* Generating the 3addr code. */
  if (flag)
    {
      if((yyvsp[(2) - (4)].value) == OR_OP)
	{
	  backpatch ((yyvsp[(1) - (4)].expr_detail).falselist,(yyvsp[(3) - (4)].quad_detail).quad);
	  (yyval.expr_detail).truelist = merge_list ((yyvsp[(1) - (4)].expr_detail).truelist,(yyvsp[(4) - (4)].expr_detail).truelist);
	  (yyval.expr_detail).falselist = (yyvsp[(4) - (4)].expr_detail).falselist;
	}
      else
	{
	  strcpy((yyval.expr_detail).place, new_temp());
	  struct three_addr* addr = malloc (sizeof (struct three_addr)); //struct three_addr will have "char* addr and struct list_elem elems"
	  addr->lineno = next_quad;
	  addr->code = malloc (14 + strlen ((yyval.expr_detail).place) + strlen ((yyvsp[(1) - (4)].expr_detail).place) + strlen ((yyvsp[(4) - (4)].expr_detail).place));
	  if((yyvsp[(2) - (4)].value) == PLUS)
	    sprintf(addr->code,"%d:\t %s := %s + %s",(int)next_quad,(yyval.expr_detail).place,(yyvsp[(1) - (4)].expr_detail).place,(yyvsp[(4) - (4)].expr_detail).place);
	  else
	    sprintf(addr->code,"%d:\t %s := %s - %s",(int)next_quad,(yyval.expr_detail).place,(yyvsp[(1) - (4)].expr_detail).place,(yyvsp[(4) - (4)].expr_detail).place);
	  
	  list_push_front(&code_list, &addr->elem);
	  next_quad++;

	  id_entry_t* ent = lookup_id_entry ((yyval.expr_detail).place, current_scope);
	  //printf ("value of ent = %p\n", (void*)ent);
   	  ent->id_type = (yyval.expr_detail).type_simple;
	}
    }
;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1058 "syntax.y"
    {
  (yyval.expr_detail).type_simple = (yyvsp[(2) - (2)].expr_detail).type_simple;
  (yyval.expr_detail).place = malloc (strlen ((yyvsp[(2) - (2)].expr_detail).place) + 2);
  strcpy ((yyval.expr_detail).place,(yyvsp[(1) - (2)].iden));
  strcat ((yyval.expr_detail).place,(yyvsp[(2) - (2)].expr_detail).place);
;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 1066 "syntax.y"
    {
  (yyval.expr_detail).type_simple = (yyvsp[(1) - (1)].expr_detail).type_simple;
  //$$.place = malloc (strlen ($1.place) + 1);
  //strcpy ($$.place, $1.place);
  (yyval.expr_detail).place = (yyvsp[(1) - (1)].expr_detail).place;
;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 1073 "syntax.y"
    {yyerror("Expected either +,-,or between two terms");;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 1080 "syntax.y"
    {
  (yyval.expr_detail).type_simple = (yyvsp[(1) - (1)].expr_detail).type_simple;
  //$$.place = malloc (strlen ($1.place) + 1);
  //strcpy ($$.place, $1.place);
  (yyval.expr_detail).place = (yyvsp[(1) - (1)].expr_detail).place
;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1088 "syntax.y"
    {
  bool flag = true;
  enum type t = (yyvsp[(1) - (4)].expr_detail).type_simple;
  if ((yyvsp[(2) - (4)].value) == AND_OP)
    {
      if ((yyvsp[(1) - (4)].expr_detail).type_simple != BOOL_TYPE || (yyvsp[(4) - (4)].expr_detail).type_simple != BOOL_TYPE)
	{
	  yyerror ("invalid operands: logical AND operation requires boolean operands");
	  flag = false;
	}
      (yyval.expr_detail).type_simple = BOOL_TYPE;
    }
  else if (t == INT_TYPE && (yyvsp[(4) - (4)].expr_detail).type_simple == REAL_TYPE 
      || t == REAL_TYPE && (yyvsp[(4) - (4)].expr_detail).type_simple == INT_TYPE)
    {
      print_warning ("no typecasting provided for integer operand");
      (yyval.expr_detail).type_simple = REAL_TYPE;
    }
  else 
    {
      (yyval.expr_detail).type_simple = NO_TYPE;
      flag = false;
      if (t != (yyvsp[(4) - (4)].expr_detail).type_simple)
	yyerror ("incompatible types for mul op");
      else if (t >= ARRAY_INT_TYPE && t <= ARRAY_BOOL_TYPE)
	yyerror ("mul ops cannot be used on array type");
      else if (t == CHAR_TYPE)
	yyerror ("mul ops cannot be used on character type");
      else if (t == BOOL_TYPE)
	yyerror ("mul ops cannot be used on boolean type");
      else
	{
	  (yyval.expr_detail).type_simple = t;
	  flag = true;
	}
    }

  /* Generating the 3addr code. */
  if (flag)
    {
      if((yyvsp[(2) - (4)].value) == AND_OP)
	{
	  backpatch ((yyvsp[(1) - (4)].expr_detail).truelist,(yyvsp[(3) - (4)].quad_detail).quad);
	  (yyval.expr_detail).truelist = (yyvsp[(4) - (4)].expr_detail).truelist;
	  (yyval.expr_detail).falselist = merge_list ((yyvsp[(1) - (4)].expr_detail).falselist,(yyvsp[(4) - (4)].expr_detail).falselist);
	}
      else
	{
	  (yyval.expr_detail).place = new_temp();
	  struct three_addr* addr = malloc (sizeof (struct three_addr)); //struct three_addr will have "char* addr and struct list_elem elems"
	  addr->lineno = next_quad;
	  addr->code = malloc (14 + strlen ((yyval.expr_detail).place) + strlen ((yyvsp[(1) - (4)].expr_detail).place) + strlen ((yyvsp[(4) - (4)].expr_detail).place));
	  switch((yyvsp[(2) - (4)].value))
	    {
	    case MOD_OP:   sprintf(addr->code,"%d:\t %s := %s %% %s",(int)next_quad,(yyval.expr_detail).place,(yyvsp[(1) - (4)].expr_detail).place,(yyvsp[(4) - (4)].expr_detail).place); break;
	    case INT_DIVIDE: 
	    case DIVIDE:   sprintf(addr->code,"%d:\t %s := %s / %s",(int)next_quad,(yyval.expr_detail).place,(yyvsp[(1) - (4)].expr_detail).place,(yyvsp[(4) - (4)].expr_detail).place); break;
	    case MULTIPLY: sprintf(addr->code,"%d:\t %s := %s * %s",(int)next_quad,(yyval.expr_detail).place,(yyvsp[(1) - (4)].expr_detail).place,(yyvsp[(4) - (4)].expr_detail).place); break;
	    default: break;
	    }
	  list_push_front (&code_list, &addr->elem);
	  next_quad++;

	  id_entry_t* ent = lookup_id_entry ((yyval.expr_detail).place, current_scope);
	  ent->id_type = (yyval.expr_detail).type_simple;
	}
    }
;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 1157 "syntax.y"
    {yyerror("Expected either * ,/,div,mod,and or a relational operator or a ,");;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1164 "syntax.y"
    {
  //printf ("Variable use is %s\n", $1);

  //printf ("Current scope is %s\n", current_scope->name);
  /* We will check current scope. If not, then we shall iteratively check all
     visible scopes. If it is declared in some other visible scope, then we will make
     an entry in our scope too. */
  id_entry_t* t;
  if (t = lookup_id_scopes ((yyvsp[(1) - (1)].iden)))
    {
      (yyval.expr_detail).type_simple = t->id_type; /* BEWARE: this could be any of the ARRAY types too. But that is checked elsewhere, not here. */
      if (t->scope_name != current_scope->name)
	hash_insert (current_scope->symbol_table, &t->sym_table_elem);

      /* Generating 3 addr code */
      (yyval.expr_detail).place = malloc (strlen ((yyvsp[(1) - (1)].iden)) + 1);
      strcpy((yyval.expr_detail).place, (yyvsp[(1) - (1)].iden)); 
    }
  else
    {
      yyerror ("undeclared identifier");
      (yyval.expr_detail).type_simple = NO_TYPE;
    }
  
  /* /\* This represents a function call. The function must be declared within the current scope. *\/ */
  /* func_entry_t* f; */
  /* if (f = lookup_func_scope ($1)) */
  /*   { */
  /*     /\* Now we need to do validity checks. *\/ */

  /*     /\*(1) checking number of arguments *\/ */
  /*     if (f->num_args != 0) */
  /* 	yyerror ("function call expects no arguments"); */

  /*     /\*(2) checking return type *\/ */
  /*     if (f->return_type == NO_TYPE)  */
  /* 	yyerror ("function doesn't return any value: illegal use of a procedure call"); */
  /*     else */
  /* 	$$ = f->return_type; /\* Return type is only one of the standard_type values. *\/ */
  /*   } */
  /* else */
  /*   yyerror ("undeclared function name"); */
;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 1208 "syntax.y"
    { yyerror ("expected an identifier: valid identifier cannot begin with a numeral"); yynerrs++; YYERROR; ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 1211 "syntax.y"
    {
  /* This represents a function call. */
  bool flag = true;
  func_entry_t* f;
  if (f = lookup_func_scope ((yyvsp[(1) - (4)].iden)))
    {
      /* Now we need to do validity checks. */
      
      /*(1) checking number of arguments */
      if (f->num_args != (yyvsp[(3) - (4)].argument_detail).num_args)
	{
	  flag = false;
	  yyerror ("number of arguments mismatch in call to function");
	  printf ("expected %d arguments for function but received %d\n", f->num_args, (yyvsp[(3) - (4)].argument_detail).num_args);
	}
      /*(2) checking types of arguments */
      else
	{
	  int i;
	  for (i = 0; i < (yyvsp[(3) - (4)].argument_detail).num_args; i++)
	    {
	      if ((yyvsp[(3) - (4)].argument_detail).arg_types[i] != f->arg_types[i])
		{
		  yyerror ("conflicting types for actual argument(s) of function call");
		  flag = false;
		  break;
		}
	    }
	  free ((yyvsp[(3) - (4)].argument_detail).arg_types);
	}
      
      /*(3) checking return type */
      if (f->return_type == NO_TYPE) 
	{
	  yyerror ("function doesn't return any value: illegal use of a procedure call");
	  flag = false;
	}
    }
  else
    {
      flag = false;
      yyerror ("undeclared procedure/function name");
      (yyval.expr_detail).type_simple = NO_TYPE;
    }

  if (flag == true)
    {
      (yyval.expr_detail).type_simple = f->return_type;
      
      /* Generating 3addr code. */
      struct three_addr* addr = malloc (sizeof (struct three_addr)); 
      addr->lineno = next_quad;
      addr->code = malloc (17 + strlen ((yyvsp[(1) - (4)].iden)));
      sprintf(addr->code,"%d:\t call %s,%d",(int)next_quad, (yyvsp[(1) - (4)].iden), f->num_args);
      list_push_front(&code_list, &addr->elem);
      next_quad++;
      (yyval.expr_detail).place = malloc (strlen ((yyvsp[(1) - (4)].iden)) + 1);
      strcpy((yyval.expr_detail).place,(yyvsp[(1) - (4)].iden));
    }
;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 1272 "syntax.y"
    { yyerror ("expected an identifier: valid identifier cannot begin with a numeral"); yynerrs++; YYERROR; ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 1275 "syntax.y"
    { yyerror ("expected ( before function invokation"); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 1276 "syntax.y"
    { yyerror ("expected (, ) between arguments to function"); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 1277 "syntax.y"
    { yyerror ("expected (, ) between arguments to function"); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1278 "syntax.y"
    { yyerror ("expected ) after function invokation"); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1279 "syntax.y"
    { yyerror ("expected ) after function invokation"); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1282 "syntax.y"
    {
  (yyval.expr_detail).type_simple = INT_TYPE;
  (yyval.expr_detail).place = malloc (10);
  sprintf ((yyval.expr_detail).place, "%d", (yyvsp[(1) - (1)].value));
;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1289 "syntax.y"
    {
  (yyval.expr_detail).type_simple = REAL_TYPE;
  (yyval.expr_detail).place = malloc (10);
  sprintf ((yyval.expr_detail).place, "%f", (yyvsp[(1) - (1)].fl));
;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1296 "syntax.y"
    { /* Bitwise NOT operation. */
  if ((yyvsp[(2) - (2)].expr_detail).type_simple != INT_TYPE)
    {
      yyerror ("wrong type of argument to bitwise NOT operator");
      (yyval.expr_detail).type_simple = INT_TYPE;
      (yyval.expr_detail).truelist = (yyvsp[(2) - (2)].expr_detail).falselist;
      (yyval.expr_detail).falselist = (yyvsp[(2) - (2)].expr_detail).truelist;
    }
  else
    (yyval.expr_detail).type_simple = INT_TYPE;
;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1309 "syntax.y"
    {
  (yyval.expr_detail).type_simple = (yyvsp[(2) - (3)].expr_detail).type_simple;
  (yyval.expr_detail).truelist = (yyvsp[(2) - (3)].expr_detail).truelist;
  (yyval.expr_detail).falselist = (yyvsp[(2) - (3)].expr_detail).falselist;
;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1316 "syntax.y"
    {yyerror("Expected ) after the expression");;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 1318 "syntax.y"
    {yyerror("Expected ( before the expression");;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1320 "syntax.y"
    {yyerror("Unexpected token before the expression");;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1330 "syntax.y"
    {
  //printf ("Reducing M\n");
  (yyval.quad_detail).quad = next_quad;
;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1341 "syntax.y"
    { 
  if ((yyvsp[(1) - (1)].value) == OR_OP) 
    {
      yyerror ("Expected either unary + or - before term"); yynerrs++;YYERROR; 
      (yyval.iden) = malloc (1);
      *(yyval.iden) = '\0';
    }
  else
    {
      (yyval.iden) = malloc (2);
      if ((yyvsp[(1) - (1)].value) == PLUS)
	strcpy ((yyval.iden), "+");
      else
	strcpy ((yyval.iden), "-");
    }
;}
    break;



/* Line 1455 of yacc.c  */
#line 3125 "syntax.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



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
		      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1359 "syntax.y"


#include "lex.yy.c"

void yyerror (const char* s)
{
  fprintf (stderr, "%s:%d: error:", file_name == NULL? "stdin" : file_name, yylineno, yytext);
  fprintf (stderr, "%s\n", s);
}

void print_warning (const char* s)
{
  fprintf (stderr, "%s:%d: warning:", file_name == NULL? "stdin" : file_name, yylineno, yytext);
  fprintf (stderr, "%s\n", s);
}


int yywrap (void)
{
  return 1;
}



/********* FUNCTIONS FOR SEMANTIC ACTIONS **********/

/* Initializes the global scope. */
void init_global_scope (char* iden)
{
  current_scope = malloc (sizeof (func_entry_t));
  current_scope->name = malloc (strlen (iden) + 1);
  strcpy (current_scope->name, iden);
  current_scope->return_type = NO_TYPE;
  current_scope->scope = 0;
  current_scope->symbol_table = malloc (sizeof (struct hash));
  hash_init (current_scope->symbol_table, symtable_hashpjw, symtable_less, (void*) NULL);
  current_scope->parent_scope = NULL;
  current_scope->num_childscopes = 0;
  current_scope->child_scopes = NULL;
}

/* Makes a entry of the current scope in the function table. */
void make_scope_entry (func_entry_t* scope)
{
  hash_insert (&func_table, &scope->func_table_elem);
}


/* Called whenever a variable declaration is seen. So if the variable is not already in the 
   current scope's symbol table, then it is added to the "id_arr" list of identifiers 
   (waiting to be assigned types). */
void make_idarray_entry (char* iden)
{
  if (!lookup_id_entry (iden, current_scope))
    {
      char* temp = malloc (strlen (iden) + 1);
      strcpy (temp, iden);
      id_arr[id_arr_size++] = temp;
    } //make_idarray_entry ($3.iden);
  else
    yyerror ("redeclaration of variable: same identifier cannot be used twice in the same scope");
}

/* Returns TRUE if iden is declared in any of the previous visible scopes. This is NOT called
   during variable declaration, but during the access of a variable. */
id_entry_t* lookup_id_scopes (char* iden)
{
  func_entry_t* f = current_scope;
  id_entry_t* t;
  
  do
    {
      t = lookup_id_entry (iden, f);
      if (t == NULL)
	f = f->parent_scope;
      else
	break;
    } while (f != NULL);

  return t;
}

/* Returns TRUE if iden is already declared as a variable in the CURRENT scope, else FALSE. */
id_entry_t* lookup_id_entry (char* iden, func_entry_t* scope)
{
  id_entry_t id;
  id.id_name = iden;
  struct hash_elem* e;
  
  e = hash_find (scope->symbol_table, &id.sym_table_elem);

  return e == NULL? NULL : hash_entry (e, id_entry_t, sym_table_elem);
}


/* Returns TRUE if iden represents a function that IS WITHIN the scope of current 
   scope (THAT IS VISIBLE FROM THE CURRENT SCOPE). */
func_entry_t* lookup_func_scope (char* iden)
{
  func_entry_t* func = lookup_func_entry (iden);
  func_entry_t* temp = current_scope; /* We start looking from current scope. */
  
  if (func == NULL)
    temp = NULL;
  else
    {
      /* FOR NOW WE SAY THAT ONLY SUCCESSIVE PARENTS AND CHILDREN ARE VISIBLE (NO AUNTS OR UNCLES). */
      if (func->scope < current_scope->scope)
	{
	  do
	    {
	      if (func == temp)
		break;
	      temp = temp->parent_scope;
	    } while (temp != NULL);
	}
      else if (func->scope == current_scope->scope)
	{
	  if (func->parent_scope != current_scope->parent_scope)
	    temp = NULL;
	}
      else
	{
	  int num = temp->num_childscopes;
	  int i;
	  for (i = 0; i < num; i++)
	    {
	      if ((temp->child_scopes)[i] == func)
		{
		  temp = (temp->child_scopes)[i];
		  break;
		}
	    }
	  if (i == num)
	    temp = NULL;
	}
    }
  return temp;
}

/* Returns TRUE if iden is already declared as a function, else FALSE. 
   This is used whenever a function/procedure declaration is seen. 
   NO TWO FUNCTION/PROCEDURE NAMES ARE ALLOWED TO CLASH ANYWHERE IN THE PROGRAM. */
func_entry_t* lookup_func_entry (char* iden)
{
  func_entry_t func;
  func.name = iden;
  struct hash_elem* e;
  
  e = hash_find (&func_table, &func.func_table_elem);

  return e == NULL? NULL : hash_entry (e, func_entry_t, func_table_elem);
}


/* This one creates a child scope and assigns it to current scope. */
void switch_to_newscope (char* iden)
{
  func_entry_t* func = malloc (sizeof (func_entry_t));
  func->name = malloc (strlen (iden) + 1);
  strcpy (func->name, iden);
  func->scope = current_scope->scope + 1;
  func->symbol_table = malloc (sizeof (struct hash));
  hash_init (func->symbol_table, symtable_hashpjw, symtable_less, (void*) NULL);
  func->parent_scope = current_scope;
  current_scope->num_childscopes += 1;
  current_scope->child_scopes = realloc (current_scope->child_scopes, (current_scope->num_childscopes) * sizeof (func_entry_t*));
  (current_scope->child_scopes)[current_scope->num_childscopes - 1] = func;
  func->num_args = 0;
  func->arg_types = NULL;
  func->return_type = NO_TYPE;
  current_scope = func;
}


/* Called when type of a list of variables becomes known. So it assigns the types and updates symbol table. */
void idarr_assign_simple_types (enum type id_type)
{
  id_entry_t* temp;
  int i;
  for (i = 0; i < id_arr_size; i++)
    {
      temp = malloc (sizeof (id_entry_t));
      temp->id_name = id_arr[i];
      temp->scope_name = current_scope->name;
      temp->offset = offset++; //incrementing offset (global var)
      temp->id_type = id_type;

      /* If it is global scope, then allocate space for variables. */
      if (current_scope->scope == 0)
	{
	  switch (id_type)
	    {
	    case INT_TYPE:
	      temp->mem_loc.i = malloc (sizeof (int));
	      break;
	    case REAL_TYPE:
	      temp->mem_loc.f = malloc (sizeof (float));
	      break;
	    case CHAR_TYPE:
	      temp->mem_loc.c = malloc (sizeof (char));
	      break;
	    case BOOL_TYPE:
	      temp->mem_loc.b = malloc (sizeof (bool));
	      break;
	    }
	}
      
      /* Now that an id entry is initialized, make the entry in the symbol table. */
      hash_insert (current_scope->symbol_table, &temp->sym_table_elem);
    }
}

void idarr_assign_array_types (enum type id_type, int lower_bound, int upper_bound)
{
  id_entry_t* temp;
  int i;
  for (i = 0; i < id_arr_size; i++)
    {
      temp = malloc (sizeof (id_entry_t));
      temp->id_name = id_arr[i];
      temp->scope_name = current_scope->name;
      temp->id_type = id_type;
      temp->offset = offset++; //incrementing offset (global var)
      temp->mem_loc.arr.lower_bound = lower_bound;
      temp->mem_loc.arr.upper_bound = upper_bound;
      
      /* If it is global scope, then allocate space for variables. */
      int* int_ptr;
      float* fl_ptr;
      char* ch_ptr;
      bool*  bl_ptr;
      if (current_scope->scope == 0)
	{
	  switch (id_type)
	    {
	    case ARRAY_INT_TYPE:
	      int_ptr = ((int*)malloc ((temp->mem_loc.arr.upper_bound - temp->mem_loc.arr.lower_bound) * sizeof (int)));
	      temp->mem_loc.arr.ptr_val.iptr = &(int_ptr);
              break;
	    case ARRAY_REAL_TYPE:
	      fl_ptr = ((float*)malloc ((temp->mem_loc.arr.upper_bound - temp->mem_loc.arr.lower_bound) * sizeof (int)));
	      temp->mem_loc.arr.ptr_val.fptr = &(fl_ptr);
              break;
	    case ARRAY_CHAR_TYPE:
	      ch_ptr = ((char*)malloc ((temp->mem_loc.arr.upper_bound - temp->mem_loc.arr.lower_bound) * sizeof (int)));
	      temp->mem_loc.arr.ptr_val.cptr = &(ch_ptr);
              break;
	    case ARRAY_BOOL_TYPE:
	      bl_ptr = ((bool*)malloc ((temp->mem_loc.arr.upper_bound - temp->mem_loc.arr.lower_bound) * sizeof (int)));
	      temp->mem_loc.arr.ptr_val.bptr = &(bl_ptr);
              break;
	    }
	}
      
      /* Now that an id entry is initialized, make the entry in the symbol table. */
      hash_insert (current_scope->symbol_table, &temp->sym_table_elem);
    }
}

/* Function that assigns the type to the list of identifiers that have been seen so far. */
void idarr_assign_types (enum type enumtype, int lower_bound, int upper_bound)
{
  switch (enumtype)
    {
    case INT_TYPE:
    case REAL_TYPE:
    case CHAR_TYPE:
    case BOOL_TYPE:
      idarr_assign_simple_types (enumtype);
      id_arr_size = 0;
      break;
      
    case ARRAY_INT_TYPE:
    case ARRAY_REAL_TYPE:
    case ARRAY_CHAR_TYPE:
    case ARRAY_BOOL_TYPE:
      idarr_assign_array_types (enumtype, lower_bound, upper_bound);
      id_arr_size = 0;
      break;

    default:
      break;
    }
}


char* new_temp (void)
{
  static int count = 1;
  char* t = malloc (10);
  sprintf (t, "t_%d", count++);
  t = realloc (t, strlen (t));

  /* Installing new temp in symbol table. */
  id_entry_t* ent = malloc (sizeof (id_entry_t));
  ent->id_name = t;
  ent->scope_name = current_scope->name;
  ent->id_type = NO_TYPE;
  ent->offset = offset++;
  printf ("This scope = %s, symbol = %s\n", current_scope->name, t);
  hash_insert (current_scope->symbol_table, &ent->sym_table_elem);  
  return t;
}

lst_t* make_list(int num)
{
  lst_t* l = malloc (sizeof (lst_t));
  l->length = 1;
  l->lst = malloc (sizeof (int));
  l->lst[0] = num;
  return l;
}

lst_t* merge_list(lst_t* t1,lst_t* t2)
{
  int len1 = (t1 == NULL? 0 : t1->length);
  int len2 = (t2 == NULL? 0 : t2->length);
  int new_len = len1 + len2;
  int* new_arr = (int*)malloc(new_len*(sizeof(int)));
  int i,j;

  for(i=0;i<len1;i++)
    new_arr[i]= t1->lst[i];

  for(j=0;j<len2;j++)
    new_arr[i+j] = t2->lst[j];

  lst_t* new_lst = (lst_t*) malloc(sizeof(lst_t));
  new_lst->lst = new_arr;
  new_lst->length = new_len;

  if (t1 != NULL)
    free(t1->lst);
  if (t2 != NULL)
    free(t2->lst);
  free(t1);
  free(t2);

  return new_lst;
}


void backpatch(lst_t* l, int num)
{
  int i;
  //printf("the number is %d\n",num);
  //printf("this is %x",(int*)l);
  int len = (l == NULL)? 0 : l->length;
  for(i = 0; i < len; i++)
    {
      int ln_no = l->lst[i];
      //printf ("the line number is %d\n",ln_no);
      struct list_elem* e;
      struct three_addr* t;

      //printf("i came into backpatch\n");

      for (e = list_begin (&code_list); e != list_end (&code_list); e = list_next (e))
	{
	  t = list_entry (e, struct three_addr, elem);
	  if (t->lineno == ln_no)
	    {
	      char temp[10];
              sprintf(temp,"%d",num);
	      int len = strlen (t->code);
	      t->code = realloc (t->code, len + strlen (temp) + 1);
              strcat(t->code,temp);
	    }
	}
    }
}


bool lineno_less (const struct list_elem* a, const struct list_elem* b, void* aux)
{
  struct three_addr* s1 = list_entry (a, struct three_addr, elem);
  struct three_addr* s2 = list_entry (b, struct three_addr, elem);

  return (s1->lineno < s2->lineno);    
}


/***************************************************/

int main(int argc,char* argv[])
{
  int token;
  
  if(argc == 1)
    {
      yyin = stdin;
      file_name = NULL;
    }

  else
    {
      yyin=fopen(argv[1],"r");

      if (yyin == NULL)
	return -1;
      
      file_name = argv[1];
    }
  //yydebug = 1;

  /* Initializing tables. */
  hash_init (&func_table, functable_hashpjw, functable_less, (void*) NULL);

  /* Initializing global code list. */
  list_init (&code_list);
  
  if(yyparse() == 0)
{
    printf ("Parsing done.\n");
    printf("#include<stdio.h>\n#include<stdlib.h>\n#include<string.h>\n");
    printf("struct data_stack\n");
    printf("{\nint val;\nfloat fl;\n};\n");
    printf("typedef struct data_stack data_st;\n");
    printf("int main()\n");							 
    printf("{\ndata_st arr[1001];\n"); 
    AddCode();
}
  else
    printf ("Unrecoverable syntax error in line no %d.\n", yylineno);
  //printf ("No of syntax errors = %d.\n", yynerrs);
  /* while(token = yylex()) */
  /*   { */
  /*     printf("Token Read %d - %s\n", token, yytext); */
  /*   } */
  
  fclose (yyin);

  list_sort((&code_list),lineno_less,NULL);

  FILE* fout = fopen ("imcode.tmp","w");
  
  struct list_elem* e;
  struct three_addr* t;
  
  for (e = list_begin (&code_list); e != list_end (&code_list); e = list_next (e))
    {
      t = list_entry (e, struct three_addr, elem);
      fprintf (fout, "%s\n", t->code);
    }
  return 0;
}

int lookup(char str[])
{
  int i;
  for(i=0;i<20;i++)
    {
      if(strcmp(ret_offset[i].name,str)==0)
	{
	  return ret_offset[i].offset;
	}
    }
}

void add_return(char ret[])
{
  int temp=1000-return_offset;
  strcpy(ret_offset[temp].name,ret);
  ret_offset[temp].offset=return_offset;
  return_offset--;
}

char* getLabel(char * str,int b)
{
  char *ret;
  int len=strlen(str);
  ret=(char*)malloc(len);
  int i;
  for(i=0;i<len-1;i++)
    ret[i]=str[i];
  ret[i-1]='\0'; //ignoring the ':' character
  if(b==1)
    add_return(ret);
  return ret;
}

int codeGen(char* str)
{
  int i=0;
  int j=0;
  int z;
  char tac[50][50];
  char *pch;
  pch=(char*)malloc(50);
  pch = strtok (str," ");
  while (pch != NULL)
    {
      strcpy(tac[i++],pch);
      pch = strtok (NULL, " ,\n");
    }
  //  for(j;j<i;j++)
  //    printf("%s\n",tac[j]);
  if(i==1 && strcmp(tac[0],"\n")!=0)
    {
      //switch_to_newscope(getLabel(tac[0]));
      char* temp;
      temp=getLabel(tac[0],1);
      current_scope = lookup_func_entry (temp); //switch to existing scope
      printf("%s:\n",temp);
      return 0;
      //      printf ("Now current scope name is %s\n", temp);
    }
  else
    {
      if(strcmp(tac[0],"\n")!=0 && strcmp(tac[1],"param")!=0)
	printf("_%s  ",tac[0]);
    }
  if(strcmp(tac[0],"\n")==0)
    {
      return 0;
    }
  else if(strcmp(tac[1],"if")==0)
    {
      id_entry_t* t=lookup_id_scopes(tac[2]);
      if(isdigit(tac[4][0]))
	{
	  printf("if(arr[%d]%s%s) goto _%s;\n",t->offset,tac[3],tac[4],tac[6]);
	}
      id_entry_t* t2=lookup_id_scopes(tac[4]);
      if(t2!=NULL)
	printf("if(arr[%d]%sarr[%d]) goto _%s;\n",t->offset,tac[3],t2->offset,tac[6]);
      if(t2==NULL)
	printf("if(arr[%d]%sarr[%d]) goto _%s;\n",t->offset,tac[3],lookup(tac[3]),tac[6]);      
    }
  else if(strcmp(tac[1],"return")==0)
    {
      //      printf("%d",get_return_address(current_scope->name));
      printf("goto _%d;\n",ret_address+1);
    }
  else if(strcmp(tac[1],"halt")==0)
    {
      printf("return 0;\n}\n");
    }
  else if(strcmp(tac[2],":=")==0 && i==4)
    {
      //      printf("Current Scope is %s\n",current_scope->name);
      //printf("Search for ID %s ",tac[1]);
      //printf("Assignmnet Op\n");
      id_entry_t* t=lookup_id_scopes(tac[1]);
      if(t==NULL)
	printf("arr[%d]=%s;\n",lookup(tac[1]),tac[3]);
      //printf("Id Offset is %d\n",t->offset);
      if(isdigit(tac[3][0]))
	{
	  //printf("right is a num\n");
	  printf("arr[%d]=%s;\n",t->offset,tac[3]);
	}
      else if(t!=NULL)
	{
	  id_entry_t* t2=lookup_id_scopes(tac[3]);
	  if(t2!=NULL)
	    printf("arr[%d]=arr[%d];\n",t->offset,t2->offset);
	  if(t2==NULL)
	    printf("arr[%d]=arr[%d];\n",t->offset,lookup(tac[3]));
	}
    }
  else if(strcmp(tac[2],":=")==0 && i==6)
    {
      //      printf("Current Scope is %s\n",current_scope->name);
      //      printf("Search for ID %s ",tac[1]);
      //      printf("Assignmnet Op\n");
      id_entry_t* t1=lookup_id_scopes(tac[1]);
      if(isdigit(tac[3][0]) & isdigit(tac[5][0]))
	printf("arr[%d]=%s%s%s;\n",t1->offset,tac[3],tac[4],tac[5]);
      if(isdigit(tac[3][0]) & !isdigit(tac[5][0]))
	{
	  id_entry_t* t2=lookup_id_scopes(tac[5]);
	  printf("arr[%d]=%s%sarr[%d];\n",t1->offset,tac[3],tac[4],t2->offset);
	}
      if(!isdigit(tac[3][0]) & isdigit(tac[5][0]))
	{
	  id_entry_t* t2=lookup_id_scopes(tac[3]);
	  printf("arr[%d]=arr[%d]%s%s;\n",t1->offset,t2->offset,tac[4],tac[5]);
	}
      if(!isdigit(tac[3][0]) & !isdigit(tac[5][0]))
	{
	  id_entry_t* t2=lookup_id_scopes(tac[3]);
	  id_entry_t* t3=lookup_id_scopes(tac[5]);
	  printf("arr[%d]=arr[%d]%sarr[%d];\n",t1->offset,t2->offset,tac[4],t3->offset);
	}
      //      printf("Id Offset is %d\n",t->offset);
      //      printf("Assignment with binary ops\n");
    }
  else if(strcmp(tac[1],"call")==0)
    {
      printf("goto %s;\n",tac[2]);
      char* temp;
      temp=getLabel(tac[0],0);
      ret_address=atoi(temp);
      //      printf("Return address modified here\n");
    }
  else if(strcmp(tac[1],"param")==0)
    {
      //Include parameters to be added
    }
  else if(strcmp(tac[1],"goto")==0)
    {
      printf("goto _%s;\n",tac[2]);
    }
  return 0;
}
void AddCode()
{
  FILE *infile;
  infile=fopen("imcode.tmp","r");
  char* str;
  int i=0;
  str=(char*) malloc(50);
  char tac[50];
  while( fgets(str, 50, infile) != NULL ) 
    {
      codeGen(str);
    }
}


