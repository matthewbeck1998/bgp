/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include "SymbolTable.h"
#include "SymbolNode.h"

using namespace std;

extern int yylex();
extern int yyparse();
void yyerror(const char* s);
extern FILE* yyin;

extern int line;
extern int column;
extern int tab;

bool outputProductions = false;
ifstream inputFile;
ofstream outputFile;
stringstream outputStream;
stringstream errorStream;
void parserOutput(string s);

//Command line Parse
int parseCommandLine(int argc, char** argv);
bool command_l = false;
bool command_s = false;

SymbolTable st;
string nodeIdentifier = "";
int nodeLineNumber = -1;
int nodeStorageClassSpecifier = -1;
int nodeTypeSpecifier = 3;
int nodeTypeQualifier = -1;
bool nodeIsFunction = false;
bool nodeIsSigned = true;
string lastNodeInserted = "";

#line 109 "parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    AUTO = 258,
    BREAK = 259,
    CASE = 260,
    CHAR = 261,
    CONST = 262,
    CONTINUE = 263,
    DEFAULT = 264,
    DO = 265,
    DOUBLE = 266,
    ELLIPSIS = 267,
    ELSE = 268,
    ENUM = 269,
    EXTERN = 270,
    FLOAT = 271,
    FOR = 272,
    GOTO = 273,
    IF = 274,
    INT = 275,
    LONG = 276,
    REGISTER = 277,
    RETURN = 278,
    SHORT = 279,
    SIGNED = 280,
    SIZEOF = 281,
    STATIC = 282,
    STRUCT = 283,
    SWITCH = 284,
    TYPEDEF = 285,
    UNION = 286,
    UNSIGNED = 287,
    VOID = 288,
    VOLATILE = 289,
    WHILE = 290,
    AMPERSAND = 291,
    ARROW = 292,
    ASSIGN = 293,
    COMMA = 294,
    PERIOD = 295,
    SEMICOLON = 296,
    STAR = 297,
    OBRACE = 298,
    CBRACE = 299,
    OBRACKET = 300,
    CBRACKET = 301,
    OPAREN = 302,
    CPAREN = 303,
    QUESTION = 304,
    COLON = 305,
    ADD = 306,
    SUB = 307,
    DIV = 308,
    MOD = 309,
    INC_OP = 310,
    DEC_OP = 311,
    ADD_ASSIGN = 312,
    SUB_ASSIGN = 313,
    MUL_ASSIGN = 314,
    DIV_ASSIGN = 315,
    MOD_ASSIGN = 316,
    L_AND = 317,
    L_OR = 318,
    L_NOT = 319,
    EQ_OP = 320,
    NE_OP = 321,
    GT_OP = 322,
    LT_OP = 323,
    GE_OP = 324,
    LE_OP = 325,
    B_NOT = 326,
    B_OR = 327,
    B_XOR = 328,
    B_SL = 329,
    B_SR = 330,
    B_AND_ASSIGN = 331,
    B_OR_ASSIGN = 332,
    B_XOR_ASSIGN = 333,
    B_SL_ASSIGN = 334,
    B_SR_ASSIGN = 335,
    CHARACTER_CONSTANT = 336,
    ENUMERATION_CONSTANT = 337,
    FLOATING_CONSTANT = 338,
    INTEGER_CONSTANT = 339,
    STRING_LITERAL = 340,
    TYPEDEF_NAME = 341,
    IDENTIFIER = 342,
    ERROR = 343
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 45 "parser.y" /* yacc.c:355  */

    char sval[255];

#line 242 "parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 259 "parser.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2161

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  89
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  224
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  378

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   343

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    73,    73,    74,    78,    79,    83,    84,    85,    86,
      90,    91,    95,    96,   100,   101,   102,   103,   104,   105,
     109,   110,   111,   112,   113,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   132,   133,   137,
     138,   139,   143,   144,   148,   149,   153,   154,   158,   159,
     163,   167,   168,   169,   170,   174,   175,   179,   180,   181,
     185,   186,   187,   191,   192,   196,   197,   201,   202,   206,
     228,   229,   230,   231,   232,   233,   237,   238,   239,   240,
     244,   245,   249,   250,   254,   255,   259,   260,   261,   265,
     266,   270,   271,   272,   276,   277,   281,   282,   286,   287,
     288,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     304,   305,   306,   307,   308,   309,   313,   314,   315,   319,
     320,   324,   325,   326,   327,   331,   332,   336,   337,   338,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     355,   356,   357,   358,   359,   363,   364,   368,   369,   373,
     374,   375,   376,   377,   378,   379,   380,   381,   382,   383,
     387,   388,   392,   396,   397,   401,   402,   406,   407,   411,
     412,   416,   417,   421,   422,   423,   427,   428,   429,   430,
     431,   435,   436,   437,   441,   442,   443,   447,   448,   449,
     450,   454,   455,   459,   460,   461,   462,   463,   464,   468,
     469,   470,   471,   472,   473,   477,   478,   479,   480,   481,
     482,   483,   484,   488,   489,   490,   491,   495,   496,   500,
     501,   502,   503,   507,   511
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AUTO", "BREAK", "CASE", "CHAR", "CONST",
  "CONTINUE", "DEFAULT", "DO", "DOUBLE", "ELLIPSIS", "ELSE", "ENUM",
  "EXTERN", "FLOAT", "FOR", "GOTO", "IF", "INT", "LONG", "REGISTER",
  "RETURN", "SHORT", "SIGNED", "SIZEOF", "STATIC", "STRUCT", "SWITCH",
  "TYPEDEF", "UNION", "UNSIGNED", "VOID", "VOLATILE", "WHILE", "AMPERSAND",
  "ARROW", "ASSIGN", "COMMA", "PERIOD", "SEMICOLON", "STAR", "OBRACE",
  "CBRACE", "OBRACKET", "CBRACKET", "OPAREN", "CPAREN", "QUESTION",
  "COLON", "ADD", "SUB", "DIV", "MOD", "INC_OP", "DEC_OP", "ADD_ASSIGN",
  "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "L_AND", "L_OR",
  "L_NOT", "EQ_OP", "NE_OP", "GT_OP", "LT_OP", "GE_OP", "LE_OP", "B_NOT",
  "B_OR", "B_XOR", "B_SL", "B_SR", "B_AND_ASSIGN", "B_OR_ASSIGN",
  "B_XOR_ASSIGN", "B_SL_ASSIGN", "B_SR_ASSIGN", "CHARACTER_CONSTANT",
  "ENUMERATION_CONSTANT", "FLOATING_CONSTANT", "INTEGER_CONSTANT",
  "STRING_LITERAL", "TYPEDEF_NAME", "IDENTIFIER", "ERROR", "$accept",
  "translation_unit", "external_declaration", "function_definition",
  "declaration", "declaration_list", "declaration_specifiers",
  "storage_class_specifier", "type_specifier", "type_qualifier",
  "struct_or_union_specifier", "struct_or_union",
  "struct_declaration_list", "init_declarator_list", "init_declarator",
  "struct_declaration", "specifier_qualifier_list",
  "struct_declarator_list", "struct_declarator", "enum_specifier",
  "enumerator_list", "enumerator", "declarator", "direct_declarator",
  "pointer", "type_qualifier_list", "parameter_type_list",
  "parameter_list", "parameter_declaration", "identifier_list",
  "initializer", "initializer_list", "type_name", "abstract_declarator",
  "direct_abstract_declarator", "statement", "labeled_statement",
  "expression_statement", "compound_statement", "statement_list",
  "selection_statement", "iteration_statement", "jump_statement",
  "expression", "assignment_expression", "assignment_operator",
  "conditional_expression", "constant_expression", "logical_or_expression",
  "logical_and_expression", "inclusive_or_expression",
  "exclusive_or_expression", "and_expression", "equality_expression",
  "relational_expression", "shift_expression", "additive_expression",
  "multiplicative_expression", "cast_expression", "unary_expression",
  "unary_operator", "postfix_expression", "primary_expression",
  "argument_expression_list", "constant", "string", "identifier", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343
};
# endif

#define YYPACT_NINF -197

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-197)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     668,  -197,  -197,  -197,  -197,   -13,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
     100,   -29,  -197,  -197,   402,  -197,  -197,  -197,   -22,  1176,
    1176,  1176,  -197,   -11,  -197,  1074,    32,   -24,  -197,   -34,
     -16,  -197,  -197,   100,    13,  -197,  -197,  -197,   179,  -197,
    1036,  -197,  -197,  -197,  1347,    42,   498,  -197,  1074,   -22,
    -197,  1384,   702,    32,    77,  -197,    55,   -34,  -197,  -197,
    -197,   -29,  -197,  1434,  1074,  -197,  1347,  1347,  1287,  -197,
      22,  1347,   111,  1986,   125,    90,   907,   127,   -34,   130,
    1484,  2030,   138,   151,  -197,  -197,  -197,  -197,  1205,  -197,
    -197,  2074,  2074,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
     583,  -197,  -197,  -197,  -197,   739,  -197,  -197,  -197,   180,
    -197,  -197,   -20,   150,    98,   157,   186,   173,   135,   174,
     223,    60,  -197,   275,  1986,   113,  -197,  -197,  -197,   206,
    -197,  -197,   196,  -197,  -197,   218,  -197,  -197,  -197,    99,
     230,   232,  -197,    43,  -197,   -34,  -197,  1986,    94,  -197,
    1434,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  1986,   184,
    -197,   237,  1316,  -197,   240,  -197,   907,   245,  1534,   241,
    1986,  -197,   188,  1205,  -197,  1986,  1986,   164,   247,   108,
    1986,  -197,  -197,  -197,   823,  -197,  -197,  1986,  -197,  1986,
    1986,  1986,  1986,  1986,  1986,  1986,  1986,  1986,  1986,  1986,
    1986,  1986,  1986,  1986,  1986,  1986,  1986,  1986,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  1986,
    -197,   -34,   -34,  1986,  1578,  -197,  -197,   907,  -197,  1622,
     451,  -197,     5,  -197,    54,  -197,  1109,   -34,  -197,  -197,
    -197,  -197,  -197,   152,  -197,    22,  -197,  1986,  -197,   907,
    -197,   250,  1672,   194,  -197,   109,  -197,   252,   123,   124,
     990,   199,  -197,  1986,  -197,  -197,  -197,    39,   150,    98,
     157,   186,   173,   135,   135,   174,   174,   174,   174,   223,
     223,    60,    60,  -197,  -197,  -197,  -197,  -197,  -197,     9,
    -197,  -197,   139,  -197,  -197,   255,  -197,   254,   256,    54,
    1716,  1141,  -197,  -197,  -197,  1340,  -197,  -197,  -197,  -197,
    1986,  1760,   213,  1810,   907,  -197,   907,   907,  -197,  1986,
    -197,  1986,  -197,  -197,  -197,  -197,  -197,   261,  -197,   262,
    -197,  -197,   141,   907,   142,  1854,  1898,   229,   285,  -197,
    -197,  -197,  -197,  -197,  -197,   268,  -197,   907,   907,   145,
     907,   149,  1942,   907,  -197,  -197,  -197,   907,  -197,   907,
     907,   153,  -197,  -197,  -197,  -197,   907,  -197
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    20,    26,    37,    31,     0,    23,    30,    28,    29,
      21,    27,    32,    22,    42,    24,    43,    33,    25,    38,
      76,     0,    36,   224,     0,     2,     4,     5,     0,    14,
      16,    18,    34,     0,    35,     0,    67,     0,    69,     0,
      62,    80,    78,    77,     0,     1,     3,    10,     0,    46,
      48,    15,    17,    19,     0,    41,     0,    12,     0,     0,
       6,     0,     0,    68,     0,    63,    65,     0,    81,    79,
      70,     0,    11,     0,     0,     8,    51,    53,     0,    44,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   199,   119,   200,   121,     0,   201,
     202,     0,     0,   204,   203,   220,   222,   221,   219,   223,
       0,   125,   110,   112,   111,     0,   113,   114,   115,     0,
     145,   147,   160,   163,   165,   167,   169,   171,   173,   176,
     181,   184,   187,   191,     0,   193,   205,   214,   215,   213,
      13,     7,    48,    71,   162,     0,   191,   213,    73,    87,
       0,    82,    84,     0,    89,     0,    60,     0,     0,    47,
       0,    49,    91,     9,    52,    54,    40,    45,     0,     0,
      55,    57,     0,   142,     0,   141,     0,     0,     0,     0,
       0,   143,     0,     0,   197,     0,     0,    96,     0,     0,
       0,   194,   195,   123,     0,   122,   126,     0,   120,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   149,   153,
     154,   150,   151,   152,   157,   159,   158,   155,   156,     0,
     196,     0,     0,     0,     0,   211,   212,     0,    72,     0,
       0,    86,    98,    88,    99,    74,     0,     0,    75,    64,
      66,    61,    94,     0,    58,     0,    50,     0,    39,     0,
     118,     0,     0,     0,   140,     0,   144,     0,     0,     0,
       0,    98,    97,     0,   216,   124,   146,     0,   164,   166,
     168,   170,   172,   174,   175,   178,   177,   180,   179,   182,
     183,   185,   186,   188,   189,   190,   148,   210,   209,     0,
     207,   217,     0,   116,   102,     0,   106,     0,     0,   100,
       0,     0,    83,    85,    90,     0,    92,    56,    59,   117,
       0,     0,     0,     0,     0,   198,     0,     0,   192,     0,
     206,     0,   208,   103,   107,   101,   104,     0,   108,     0,
      93,    95,     0,     0,     0,     0,     0,     0,   127,   129,
     130,   161,   218,   105,   109,     0,   132,     0,     0,     0,
       0,     0,     0,     0,   131,   133,   134,     0,   136,     0,
       0,     0,   128,   135,   137,   138,     0,   139
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -197,  -197,   287,  -197,    10,     4,    11,  -197,    41,    27,
    -197,  -197,   233,  -197,   244,   -66,   -60,  -197,    62,  -197,
     251,   165,   -14,   -35,   -12,  -197,   -61,  -197,    73,  -197,
    -154,  -197,   140,  -100,  -196,   -64,  -197,  -197,    93,   211,
    -197,  -197,  -197,   -54,   -70,  -197,   -57,   -74,  -197,   128,
     129,   136,   122,   133,    71,     7,    74,    75,  -119,   182,
    -197,  -197,  -197,  -197,  -197,  -197,     0
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    24,    25,    26,    57,    58,    59,    29,    30,    31,
      32,    33,    78,    48,    49,    79,    80,   169,   170,    34,
      64,    65,    35,    36,    37,    43,   307,   151,   152,   153,
     161,   253,   188,   308,   244,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   229,   121,   145,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   302,   137,   138,   147
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      38,   150,    63,   162,   144,    40,   252,    44,    42,   174,
      27,    28,   167,    20,    50,   230,   164,   165,    21,    47,
      20,    38,   177,    21,    38,    21,   144,    67,    38,   199,
      39,    69,    54,    55,    27,    28,   182,    38,   187,    66,
      51,    52,    53,   200,   189,   142,   309,    41,   197,   243,
     239,   196,   240,    23,    74,   330,   139,   142,    23,    38,
     110,    70,   154,    23,    20,    23,   171,    66,   140,    21,
      68,    38,   168,   149,    23,   309,    23,    61,   197,    62,
      38,    77,   247,   250,   140,    81,   139,   272,   179,   329,
     162,   248,    23,   157,   254,    76,   293,   294,   295,   310,
     144,   311,   215,    77,    77,    77,   167,     3,    77,    23,
     139,   144,   260,   216,   217,   139,   155,    76,    76,    76,
     140,   156,    76,   187,   263,    77,   265,   276,    60,   189,
     196,   268,   269,   155,    19,   241,   189,   242,   251,    76,
     176,    20,    20,    75,   239,   277,   240,   197,   197,    38,
     231,   141,   173,   232,   328,    66,   274,   324,   233,   296,
     234,   341,   197,   197,   301,   305,   175,   163,   235,   236,
     202,   326,   327,   303,   178,   271,   139,   180,   331,   299,
     197,   197,   144,   318,   197,   185,    23,   332,   197,   355,
     357,   315,   197,   367,   139,   319,   316,   369,   186,    77,
     144,   376,   207,   208,   209,   210,    20,    63,   322,   239,
      77,   270,   201,    76,   285,   286,   287,   288,    71,   197,
      72,   198,   204,   255,    76,   256,    44,   197,   242,   266,
     203,   297,   298,   197,    73,   323,   337,   139,   205,   206,
      38,   171,    38,   146,   239,   162,   270,   314,   211,   212,
     339,   149,   197,   144,   345,    38,   237,   149,   271,   139,
     348,   352,   349,   350,   238,   146,   342,   344,   197,   347,
     362,   246,   351,   184,   213,   214,   283,   284,   245,   356,
     261,   149,   264,   191,   192,   289,   290,   257,   291,   292,
     259,   359,   361,   365,   366,   273,   368,   320,   363,   372,
     325,   333,   334,   373,   335,   374,   375,   353,   371,   364,
     354,    46,   377,   218,   172,   159,   146,   317,   158,   313,
     249,   194,   149,   267,   139,   281,   139,   139,   278,     0,
     279,     0,   219,   220,   221,   222,   223,   282,   280,   146,
       0,     0,     0,   139,     0,     0,     0,     0,     0,     0,
     146,   224,   225,   226,   227,   228,     0,   139,   139,     0,
     139,     0,     0,   139,     0,     0,     0,   139,     0,   139,
     139,     0,     0,     0,     0,     0,   139,     0,     0,     0,
       0,     0,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
       0,     0,    45,     0,     0,     1,     0,     0,     2,     3,
       0,     0,     0,     4,     0,     0,     5,     6,     7,     0,
       0,   146,     8,     9,    10,     0,    11,    12,     0,    13,
      14,     0,    15,    16,    17,    18,    19,     0,     0,   146,
       0,     0,     0,     0,    20,     0,     0,     0,     0,    21,
       0,     0,     0,     0,     1,   146,     0,     2,     3,     0,
       0,     0,     4,     0,     0,     5,     6,     7,     0,     0,
       0,     8,     9,    10,     0,    11,    12,     0,    13,    14,
       0,    15,    16,    17,    18,    19,     0,     0,    22,    23,
       0,     0,   146,    20,     0,     0,   239,     0,   240,   306,
       0,     1,    82,    83,     2,     3,    84,    85,    86,     4,
       0,   146,     5,     6,     7,    87,    88,    89,     8,     9,
      10,    90,    11,    12,    91,    13,    14,    92,    15,    16,
      17,    18,    19,    93,    94,     0,     0,    22,    23,    95,
      96,    56,    97,     0,     0,    98,     0,     0,     0,    99,
     100,     0,     0,   101,   102,     0,     0,     0,     0,     0,
       0,     0,   103,     0,     0,     0,     0,     0,     0,   104,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   105,
     106,   107,   108,   109,    22,    23,     1,    82,    83,     2,
       3,    84,    85,    86,     4,     0,     0,     5,     6,     7,
      87,    88,    89,     8,     9,    10,    90,    11,    12,    91,
      13,    14,    92,    15,    16,    17,    18,    19,    93,    94,
       0,     0,     0,     0,    95,    96,    56,   193,     0,     0,
      98,     0,     0,     0,    99,   100,     0,     0,   101,   102,
       0,     0,     0,     0,     0,     0,     0,   103,     0,     0,
       0,     0,     0,     0,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   105,   106,   107,   108,   109,    22,
      23,     1,     0,     0,     2,     3,     0,     0,     0,     4,
       0,     0,     5,     6,     7,     0,     0,     0,     8,     9,
      10,     0,    11,    12,     0,    13,    14,     0,    15,    16,
      17,    18,    19,     0,     0,     1,     0,     0,     2,     3,
      20,     0,     0,     4,     0,    21,     5,     6,     7,     0,
       0,     0,     8,     9,    10,     0,    11,    12,     0,    13,
      14,     0,    15,    16,    17,    18,    19,     0,     0,     0,
       0,     0,     0,    82,    83,     0,     0,    84,    85,    86,
     148,     0,     0,     0,    22,    23,    87,    88,    89,     0,
       0,     0,    90,     0,     0,    91,     0,     0,    92,     0,
       0,     0,     0,     0,    93,    94,     0,     0,     0,     0,
      95,    96,    56,   195,     0,     0,    98,     0,    22,    23,
      99,   100,     0,     0,   101,   102,     0,     0,     0,     0,
       0,     0,     0,   103,     0,     0,     0,     0,     0,     0,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,   106,   107,   108,   109,     0,    23,    82,    83,     0,
       0,    84,    85,    86,     0,     0,     0,     0,     0,     0,
      87,    88,    89,     0,     0,     0,    90,     0,     0,    91,
       0,     0,    92,     0,     0,     0,     0,     0,    93,    94,
       0,     0,     0,     0,    95,    96,    56,   275,     0,     0,
      98,     0,     0,     0,    99,   100,     0,     0,   101,   102,
       0,     0,     0,     0,     0,     0,     0,   103,     0,     0,
       0,     0,     0,     0,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   105,   106,   107,   108,   109,     0,
      23,    82,    83,     0,     0,    84,    85,    86,     0,     0,
       0,     0,     0,     0,    87,    88,    89,     0,     0,     0,
      90,     0,     0,    91,     0,     0,    92,     0,     0,     0,
       0,     0,    93,    94,     0,     0,     0,     0,    95,    96,
      56,     0,     0,     0,    98,     0,     0,     0,    99,   100,
       0,     0,   101,   102,     0,     0,     0,     0,     0,     0,
       0,   103,     0,     0,     0,     0,     0,     0,   104,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   105,   106,
     107,   108,   109,     1,    23,     0,     2,     3,     0,     0,
       0,     4,     0,     0,     5,     6,     7,     0,     0,     0,
       8,     9,    10,     0,    11,    12,     0,    13,    14,     0,
      15,    16,    17,    18,    19,     0,     0,     0,     0,     0,
       0,     0,    20,     0,     0,   239,     0,   270,   306,     1,
       0,     0,     2,     3,     0,     0,     0,     4,     0,     0,
       5,     6,     7,     0,     0,     0,     8,     9,    10,     0,
      11,    12,     0,    13,    14,     0,    15,    16,    17,    18,
      19,     0,     0,     0,    73,     0,    22,     1,     0,    56,
       2,     3,     0,     0,     0,     4,     0,     0,     5,     6,
       7,     0,     0,     0,     8,     9,    10,     0,    11,    12,
       0,    13,    14,     0,    15,    16,    17,    18,    19,     0,
       0,     0,     1,     0,     0,     2,     3,    56,     0,     0,
       4,   312,    22,     5,     6,     7,     0,     0,     0,     8,
       9,    10,     0,    11,    12,     0,    13,    14,     0,    15,
      16,    17,    18,    19,     1,     0,     0,     2,     3,     0,
       0,     0,     4,     0,     0,     5,     6,     7,     0,     0,
      22,     8,     9,    10,     0,    11,    12,     0,    13,    14,
       0,    15,    16,    17,    18,    19,     0,     0,     0,     1,
       0,     0,     2,     3,     0,     0,     0,     4,     0,   338,
       5,     6,     7,     0,     0,    22,     8,     9,    10,     0,
      11,    12,     0,    13,    14,     0,    15,    16,    17,    18,
      19,     2,     3,     0,     0,     0,     4,     0,     0,     5,
       0,     7,     0,     0,     0,     8,     9,    22,     0,    11,
      12,    91,     0,    14,     0,     0,    16,    17,    18,    19,
       0,    94,     0,     0,     0,     0,     0,    96,     0,     0,
       0,     0,    98,     0,     0,     0,    99,   100,     0,     0,
     101,   102,    22,     0,     0,     0,     0,     0,     0,   103,
       0,     0,     0,     0,     0,     0,   104,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,   106,   107,   108,
     109,    22,    23,     2,     3,     0,     0,     0,     4,     0,
       0,     5,     0,     7,     0,     0,     0,     8,     9,     0,
       0,    11,    12,     0,     0,    14,     0,     0,    16,    17,
      18,    19,     2,     3,     0,     0,     0,     4,     0,     0,
       5,   166,     7,     0,     0,     0,     8,     9,     0,     0,
      11,    12,     0,     0,    14,     0,     0,    16,    17,    18,
      19,     0,     0,     2,     3,     0,     0,     0,     4,     0,
     258,     5,     0,     7,     0,     0,    91,     8,     9,     0,
       0,    11,    12,    22,     0,    14,    94,     0,    16,    17,
      18,    19,    96,   160,   340,     0,     0,    98,     0,     0,
       0,    99,   100,     0,     0,   101,   102,     0,     0,     0,
       0,     0,    22,     0,   103,     0,     0,     0,     0,     0,
      91,   104,     0,     0,     0,     0,     0,     0,     0,     0,
      94,   105,   106,   107,   108,   109,    96,    23,     0,     0,
     143,    98,     0,    22,     0,    99,   100,     0,     0,   101,
     102,     0,     0,     0,     0,     0,     0,     0,   103,     0,
       0,     0,     0,     0,     0,   104,     0,     0,     0,     0,
      91,     0,     0,     0,     0,   105,   106,   107,   108,   109,
      94,    23,     0,     0,     0,     0,    96,   160,     0,     0,
       0,    98,     0,     0,     0,    99,   100,     0,     0,   101,
     102,     0,     0,     0,     0,     0,     0,     0,   103,     0,
       0,     0,     0,     0,     0,   104,     0,     0,     0,     0,
      91,     0,     0,     0,     0,   105,   106,   107,   108,   109,
      94,    23,     0,     0,     0,   181,    96,     0,     0,     0,
       0,    98,     0,     0,     0,    99,   100,     0,     0,   101,
     102,     0,     0,     0,     0,     0,     0,     0,   103,     0,
       0,     0,     0,     0,     0,   104,     0,     0,     0,     0,
      91,     0,     0,     0,     0,   105,   106,   107,   108,   109,
      94,    23,     0,     0,     0,   262,    96,     0,     0,     0,
       0,    98,     0,     0,     0,    99,   100,     0,     0,   101,
     102,     0,     0,     0,     0,     0,     0,     0,   103,     0,
       0,     0,     0,     0,    91,   104,     0,     0,     0,     0,
       0,     0,     0,     0,    94,   105,   106,   107,   108,   109,
      96,    23,     0,     0,     0,    98,   300,     0,     0,    99,
     100,     0,     0,   101,   102,     0,     0,     0,     0,     0,
       0,     0,   103,     0,     0,     0,     0,     0,    91,   104,
       0,     0,     0,     0,     0,     0,     0,     0,    94,   105,
     106,   107,   108,   109,    96,    23,     0,     0,   304,    98,
       0,     0,     0,    99,   100,     0,     0,   101,   102,     0,
       0,     0,     0,     0,     0,     0,   103,     0,     0,     0,
       0,     0,     0,   104,     0,     0,     0,     0,    91,     0,
       0,     0,     0,   105,   106,   107,   108,   109,    94,    23,
       0,     0,     0,   321,    96,     0,     0,     0,     0,    98,
       0,     0,     0,    99,   100,     0,     0,   101,   102,     0,
       0,     0,     0,     0,     0,     0,   103,     0,     0,     0,
       0,     0,    91,   104,     0,     0,     0,     0,     0,     0,
       0,     0,    94,   105,   106,   107,   108,   109,    96,    23,
       0,     0,   336,    98,     0,     0,     0,    99,   100,     0,
       0,   101,   102,     0,     0,     0,     0,     0,     0,     0,
     103,     0,     0,     0,     0,     0,    91,   104,     0,     0,
       0,     0,     0,     0,     0,     0,    94,   105,   106,   107,
     108,   109,    96,    23,     0,     0,     0,    98,   343,     0,
       0,    99,   100,     0,     0,   101,   102,     0,     0,     0,
       0,     0,     0,     0,   103,     0,     0,     0,     0,     0,
       0,   104,     0,     0,     0,     0,    91,     0,     0,     0,
       0,   105,   106,   107,   108,   109,    94,    23,     0,     0,
       0,   346,    96,     0,     0,     0,     0,    98,     0,     0,
       0,    99,   100,     0,     0,   101,   102,     0,     0,     0,
       0,     0,     0,     0,   103,     0,     0,     0,     0,     0,
      91,   104,     0,     0,     0,     0,     0,     0,     0,     0,
      94,   105,   106,   107,   108,   109,    96,    23,     0,     0,
       0,    98,   358,     0,     0,    99,   100,     0,     0,   101,
     102,     0,     0,     0,     0,     0,     0,     0,   103,     0,
       0,     0,     0,     0,    91,   104,     0,     0,     0,     0,
       0,     0,     0,     0,    94,   105,   106,   107,   108,   109,
      96,    23,     0,     0,     0,    98,   360,     0,     0,    99,
     100,     0,     0,   101,   102,     0,     0,     0,     0,     0,
       0,     0,   103,     0,     0,     0,     0,     0,    91,   104,
       0,     0,     0,     0,     0,     0,     0,     0,    94,   105,
     106,   107,   108,   109,    96,    23,     0,     0,     0,    98,
     370,     0,     0,    99,   100,     0,     0,   101,   102,     0,
       0,     0,     0,     0,     0,     0,   103,     0,     0,     0,
       0,     0,    91,   104,     0,     0,     0,     0,     0,     0,
       0,     0,    94,   105,   106,   107,   108,   109,    96,    23,
       0,     0,     0,    98,     0,     0,     0,    99,   100,     0,
       0,   101,   102,     0,     0,     0,     0,     0,     0,     0,
     103,     0,     0,     0,     0,     0,    91,   104,     0,     0,
       0,     0,     0,     0,     0,     0,    94,   105,   106,   107,
     108,   109,    96,    23,     0,     0,     0,   183,     0,     0,
       0,    99,   100,     0,     0,   101,   102,     0,     0,     0,
       0,     0,     0,     0,   103,     0,     0,     0,     0,     0,
      91,   104,     0,     0,     0,     0,     0,     0,     0,     0,
      94,   105,   106,   107,   108,   109,    96,    23,     0,     0,
       0,   190,     0,     0,     0,    99,   100,     0,     0,   101,
     102,     0,     0,     0,     0,     0,     0,     0,   103,     0,
       0,     0,     0,     0,     0,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,   106,   107,   108,   109,
       0,    23
};

static const yytype_int16 yycheck[] =
{
       0,    62,    37,    73,    61,     5,   160,    21,    20,    83,
       0,     0,    78,    42,    28,   134,    76,    77,    47,    41,
      42,    21,    86,    47,    24,    47,    83,    43,    28,    49,
      43,    43,    43,    33,    24,    24,    90,    37,    98,    39,
      29,    30,    31,    63,    98,    59,   242,    20,    39,   149,
      45,   115,    47,    87,    50,    46,    56,    71,    87,    59,
      56,    48,    62,    87,    42,    87,    80,    67,    58,    47,
      43,    71,    50,    62,    87,   271,    87,    45,    39,    47,
      80,    54,    39,   157,    74,    43,    86,   187,    88,    50,
     160,    48,    87,    38,   168,    54,   215,   216,   217,    45,
     157,    47,    42,    76,    77,    78,   172,     7,    81,    87,
     110,   168,   176,    53,    54,   115,    39,    76,    77,    78,
     110,    44,    81,   183,   178,    98,   180,   197,    35,   183,
     194,   185,   186,    39,    34,   149,   190,   149,    44,    98,
      50,    42,    42,    50,    45,   199,    47,    39,    39,   149,
      37,    58,    41,    40,   273,   155,    48,    48,    45,   229,
      47,   315,    39,    39,   234,   239,    41,    74,    55,    56,
      72,    48,    48,   237,    47,   187,   176,    47,    39,   233,
      39,    39,   239,   257,    39,    47,    87,    48,    39,    48,
      48,    39,    39,    48,   194,   259,    44,    48,    47,   172,
     257,    48,    67,    68,    69,    70,    42,   242,   262,    45,
     183,    47,    62,   172,   207,   208,   209,   210,    39,    39,
      41,    41,    36,    39,   183,    41,   240,    39,   240,    41,
      73,   231,   232,    39,    38,    41,   310,   237,    65,    66,
     240,   255,   242,    61,    45,   315,    47,   247,    74,    75,
     311,   240,    39,   310,    41,   255,    50,   246,   270,   259,
     324,   331,   326,   327,    46,    83,   320,   321,    39,   323,
      41,    39,   329,    91,    51,    52,   205,   206,    48,   343,
      35,   270,    41,   101,   102,   211,   212,    50,   213,   214,
      50,   345,   346,   357,   358,    48,   360,    47,    13,   363,
      48,    46,    48,   367,    48,   369,   370,    46,   362,    41,
      48,    24,   376,    38,    81,    71,   134,   255,    67,   246,
     155,   110,   311,   183,   324,   203,   326,   327,   200,    -1,
     201,    -1,    57,    58,    59,    60,    61,   204,   202,   157,
      -1,    -1,    -1,   343,    -1,    -1,    -1,    -1,    -1,    -1,
     168,    76,    77,    78,    79,    80,    -1,   357,   358,    -1,
     360,    -1,    -1,   363,    -1,    -1,    -1,   367,    -1,   369,
     370,    -1,    -1,    -1,    -1,    -1,   376,    -1,    -1,    -1,
      -1,    -1,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
      -1,    -1,     0,    -1,    -1,     3,    -1,    -1,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    14,    15,    16,    -1,
      -1,   239,    20,    21,    22,    -1,    24,    25,    -1,    27,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,   257,
      -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,     3,   273,    -1,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    14,    15,    16,    -1,    -1,
      -1,    20,    21,    22,    -1,    24,    25,    -1,    27,    28,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    86,    87,
      -1,    -1,   310,    42,    -1,    -1,    45,    -1,    47,    48,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,   329,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    86,    87,    41,
      42,    43,    44,    -1,    -1,    47,    -1,    -1,    -1,    51,
      52,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    41,    42,    43,    44,    -1,    -1,
      47,    -1,    -1,    -1,    51,    52,    -1,    -1,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,    86,
      87,     3,    -1,    -1,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    14,    15,    16,    -1,    -1,    -1,    20,    21,
      22,    -1,    24,    25,    -1,    27,    28,    -1,    30,    31,
      32,    33,    34,    -1,    -1,     3,    -1,    -1,     6,     7,
      42,    -1,    -1,    11,    -1,    47,    14,    15,    16,    -1,
      -1,    -1,    20,    21,    22,    -1,    24,    25,    -1,    27,
      28,    -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,     4,     5,    -1,    -1,     8,     9,    10,
      48,    -1,    -1,    -1,    86,    87,    17,    18,    19,    -1,
      -1,    -1,    23,    -1,    -1,    26,    -1,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    35,    36,    -1,    -1,    -1,    -1,
      41,    42,    43,    44,    -1,    -1,    47,    -1,    86,    87,
      51,    52,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    -1,    87,     4,     5,    -1,
      -1,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    -1,    -1,    -1,    23,    -1,    -1,    26,
      -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    35,    36,
      -1,    -1,    -1,    -1,    41,    42,    43,    44,    -1,    -1,
      47,    -1,    -1,    -1,    51,    52,    -1,    -1,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,
      87,     4,     5,    -1,    -1,     8,     9,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    -1,    -1,    -1,
      23,    -1,    -1,    26,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    35,    36,    -1,    -1,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    51,    52,
      -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,     3,    87,    -1,     6,     7,    -1,    -1,
      -1,    11,    -1,    -1,    14,    15,    16,    -1,    -1,    -1,
      20,    21,    22,    -1,    24,    25,    -1,    27,    28,    -1,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    -1,    -1,    45,    -1,    47,    48,     3,
      -1,    -1,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      14,    15,    16,    -1,    -1,    -1,    20,    21,    22,    -1,
      24,    25,    -1,    27,    28,    -1,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    38,    -1,    86,     3,    -1,    43,
       6,     7,    -1,    -1,    -1,    11,    -1,    -1,    14,    15,
      16,    -1,    -1,    -1,    20,    21,    22,    -1,    24,    25,
      -1,    27,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,    -1,     3,    -1,    -1,     6,     7,    43,    -1,    -1,
      11,    12,    86,    14,    15,    16,    -1,    -1,    -1,    20,
      21,    22,    -1,    24,    25,    -1,    27,    28,    -1,    30,
      31,    32,    33,    34,     3,    -1,    -1,     6,     7,    -1,
      -1,    -1,    11,    -1,    -1,    14,    15,    16,    -1,    -1,
      86,    20,    21,    22,    -1,    24,    25,    -1,    27,    28,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,     3,
      -1,    -1,     6,     7,    -1,    -1,    -1,    11,    -1,    48,
      14,    15,    16,    -1,    -1,    86,    20,    21,    22,    -1,
      24,    25,    -1,    27,    28,    -1,    30,    31,    32,    33,
      34,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,    14,
      -1,    16,    -1,    -1,    -1,    20,    21,    86,    -1,    24,
      25,    26,    -1,    28,    -1,    -1,    31,    32,    33,    34,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    51,    52,    -1,    -1,
      55,    56,    86,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    86,    87,     6,     7,    -1,    -1,    -1,    11,    -1,
      -1,    14,    -1,    16,    -1,    -1,    -1,    20,    21,    -1,
      -1,    24,    25,    -1,    -1,    28,    -1,    -1,    31,    32,
      33,    34,     6,     7,    -1,    -1,    -1,    11,    -1,    -1,
      14,    44,    16,    -1,    -1,    -1,    20,    21,    -1,    -1,
      24,    25,    -1,    -1,    28,    -1,    -1,    31,    32,    33,
      34,    -1,    -1,     6,     7,    -1,    -1,    -1,    11,    -1,
      44,    14,    -1,    16,    -1,    -1,    26,    20,    21,    -1,
      -1,    24,    25,    86,    -1,    28,    36,    -1,    31,    32,
      33,    34,    42,    43,    44,    -1,    -1,    47,    -1,    -1,
      -1,    51,    52,    -1,    -1,    55,    56,    -1,    -1,    -1,
      -1,    -1,    86,    -1,    64,    -1,    -1,    -1,    -1,    -1,
      26,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    81,    82,    83,    84,    85,    42,    87,    -1,    -1,
      46,    47,    -1,    86,    -1,    51,    52,    -1,    -1,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      36,    87,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    51,    52,    -1,    -1,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      36,    87,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    51,    52,    -1,    -1,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      36,    87,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    51,    52,    -1,    -1,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      -1,    -1,    -1,    -1,    26,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    81,    82,    83,    84,    85,
      42,    87,    -1,    -1,    -1,    47,    48,    -1,    -1,    51,
      52,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    26,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    81,
      82,    83,    84,    85,    42,    87,    -1,    -1,    46,    47,
      -1,    -1,    -1,    51,    52,    -1,    -1,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    36,    87,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    51,    52,    -1,    -1,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    26,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    81,    82,    83,    84,    85,    42,    87,
      -1,    -1,    46,    47,    -1,    -1,    -1,    51,    52,    -1,
      -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    -1,    -1,    -1,    -1,    26,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    81,    82,    83,
      84,    85,    42,    87,    -1,    -1,    -1,    47,    48,    -1,
      -1,    51,    52,    -1,    -1,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    36,    87,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    51,    52,    -1,    -1,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,
      26,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    81,    82,    83,    84,    85,    42,    87,    -1,    -1,
      -1,    47,    48,    -1,    -1,    51,    52,    -1,    -1,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      -1,    -1,    -1,    -1,    26,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    81,    82,    83,    84,    85,
      42,    87,    -1,    -1,    -1,    47,    48,    -1,    -1,    51,
      52,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    26,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    81,
      82,    83,    84,    85,    42,    87,    -1,    -1,    -1,    47,
      48,    -1,    -1,    51,    52,    -1,    -1,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    26,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    81,    82,    83,    84,    85,    42,    87,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    51,    52,    -1,
      -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    -1,    -1,    -1,    -1,    26,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    81,    82,    83,
      84,    85,    42,    87,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    51,    52,    -1,    -1,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,
      26,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    81,    82,    83,    84,    85,    42,    87,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    51,    52,    -1,    -1,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      -1,    87
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,     7,    11,    14,    15,    16,    20,    21,
      22,    24,    25,    27,    28,    30,    31,    32,    33,    34,
      42,    47,    86,    87,    90,    91,    92,    93,    95,    96,
      97,    98,    99,   100,   108,   111,   112,   113,   155,    43,
     155,    98,   113,   114,   111,     0,    91,    41,   102,   103,
     111,    95,    95,    95,    43,   155,    43,    93,    94,    95,
     127,    45,    47,   112,   109,   110,   155,    43,    98,   113,
      48,    39,    41,    38,    94,   127,    97,    98,   101,   104,
     105,    43,     4,     5,     8,     9,    10,    17,    18,    19,
      23,    26,    29,    35,    36,    41,    42,    44,    47,    51,
      52,    55,    56,    64,    71,    81,    82,    83,    84,    85,
      94,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   135,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   153,   154,   155,
      93,   127,   111,    46,   135,   136,   148,   155,    48,    95,
     115,   116,   117,   118,   155,    39,    44,    38,   109,   103,
      43,   119,   133,   127,   105,   105,    44,   104,    50,   106,
     107,   111,   101,    41,   136,    41,    50,   124,    47,   155,
      47,    41,   132,    47,   148,    47,    47,   105,   121,   132,
      47,   148,   148,    44,   128,    44,   124,    39,    41,    49,
      63,    62,    72,    73,    36,    65,    66,    67,    68,    69,
      70,    74,    75,    51,    52,    42,    53,    54,    38,    57,
      58,    59,    60,    61,    76,    77,    78,    79,    80,   134,
     147,    37,    40,    45,    47,    55,    56,    50,    46,    45,
      47,   111,   113,   122,   123,    48,    39,    39,    48,   110,
     136,    44,   119,   120,   136,    39,    41,    50,    44,    50,
     124,    35,    41,   132,    41,   132,    41,   121,   132,   132,
      47,   113,   122,    48,    48,    44,   133,   132,   138,   139,
     140,   141,   142,   143,   143,   144,   144,   144,   144,   145,
     145,   146,   146,   147,   147,   147,   133,   155,   155,   132,
      48,   133,   152,   124,    46,   136,    48,   115,   122,   123,
      45,    47,    12,   117,   155,    39,    44,   107,   136,   124,
      47,    41,   132,    41,    48,    48,    48,    48,   147,    50,
      46,    39,    48,    46,    48,    48,    46,   136,    48,   115,
      44,   119,   132,    48,   132,    41,    41,   132,   124,   124,
     124,   135,   133,    46,    48,    48,   124,    48,    48,   132,
      48,   132,    41,    13,    41,   124,   124,    48,   124,    48,
      48,   132,   124,   124,   124,   124,    48,   124
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    89,    90,    90,    91,    91,    92,    92,    92,    92,
      93,    93,    94,    94,    95,    95,    95,    95,    95,    95,
      96,    96,    96,    96,    96,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    98,    98,    99,
      99,    99,   100,   100,   101,   101,   102,   102,   103,   103,
     104,   105,   105,   105,   105,   106,   106,   107,   107,   107,
     108,   108,   108,   109,   109,   110,   110,   111,   111,   112,
     112,   112,   112,   112,   112,   112,   113,   113,   113,   113,
     114,   114,   115,   115,   116,   116,   117,   117,   117,   118,
     118,   119,   119,   119,   120,   120,   121,   121,   122,   122,
     122,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     124,   124,   124,   124,   124,   124,   125,   125,   125,   126,
     126,   127,   127,   127,   127,   128,   128,   129,   129,   129,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     131,   131,   131,   131,   131,   132,   132,   133,   133,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     135,   135,   136,   137,   137,   138,   138,   139,   139,   140,
     140,   141,   141,   142,   142,   142,   143,   143,   143,   143,
     143,   144,   144,   144,   145,   145,   145,   146,   146,   146,
     146,   147,   147,   148,   148,   148,   148,   148,   148,   149,
     149,   149,   149,   149,   149,   150,   150,   150,   150,   150,
     150,   150,   150,   151,   151,   151,   151,   152,   152,   153,
     153,   153,   153,   154,   155
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     3,     3,     4,
       2,     3,     1,     2,     1,     2,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       4,     2,     1,     1,     1,     2,     1,     3,     1,     3,
       3,     1,     2,     1,     2,     1,     3,     1,     2,     3,
       4,     5,     2,     1,     3,     1,     3,     1,     2,     1,
       3,     3,     4,     3,     4,     4,     1,     2,     2,     3,
       1,     2,     1,     3,     1,     3,     2,     1,     2,     1,
       3,     1,     3,     4,     1,     3,     1,     2,     1,     1,
       2,     3,     2,     3,     3,     4,     2,     3,     3,     4,
       1,     1,     1,     1,     1,     1,     3,     4,     3,     1,
       2,     2,     3,     3,     4,     1,     2,     5,     7,     5,
       5,     7,     6,     7,     7,     8,     7,     8,     8,     9,
       3,     2,     2,     2,     3,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     1,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     1,     4,     1,     2,     2,     2,     2,     4,     1,
       1,     1,     1,     1,     1,     1,     4,     3,     4,     3,
       3,     2,     2,     1,     1,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 73 "parser.y" /* yacc.c:1646  */
    { parserOutput("translation_unit -> external_declaration"); }
#line 1996 "parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 74 "parser.y" /* yacc.c:1646  */
    { parserOutput("translation_unit -> translation_unit external_declaration"); }
#line 2002 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 78 "parser.y" /* yacc.c:1646  */
    { parserOutput("external_declaration -> function_definition"); }
#line 2008 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 79 "parser.y" /* yacc.c:1646  */
    { parserOutput("external_declaration -> declaration"); }
#line 2014 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 83 "parser.y" /* yacc.c:1646  */
    { parserOutput("function_definition -> declarator compound_statement"); st.popLevel(); }
#line 2020 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 84 "parser.y" /* yacc.c:1646  */
    { parserOutput("function_definition -> declarator declaration_list compound_statement"); st.popLevel(); }
#line 2026 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 85 "parser.y" /* yacc.c:1646  */
    { parserOutput("function_definition -> declaration_specifiers declarator compound_statement"); st.popLevel(); }
#line 2032 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 86 "parser.y" /* yacc.c:1646  */
    { parserOutput("function_definition -> declaration_specifiers declarator declaration_list compound_statement"); st.popLevel(); }
#line 2038 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 90 "parser.y" /* yacc.c:1646  */
    { parserOutput("declaration -> declaration_specifiers SEMICOLON"); }
#line 2044 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 91 "parser.y" /* yacc.c:1646  */
    { parserOutput("declaration -> declaration_specifiers init_declarator_list SEMICOLON"); }
#line 2050 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 95 "parser.y" /* yacc.c:1646  */
    { parserOutput("declaration_list -> declaration"); st.setInsertMode(false); }
#line 2056 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 96 "parser.y" /* yacc.c:1646  */
    { parserOutput("declaration_list -> declaration_list declaration"); st.setInsertMode(false); }
#line 2062 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 100 "parser.y" /* yacc.c:1646  */
    { parserOutput("declaration_specifiers -> storage_class_specifier"); }
#line 2068 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 101 "parser.y" /* yacc.c:1646  */
    { parserOutput("declaration_specifiers -> storage_class_specifier declaration_specifiers"); }
#line 2074 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 102 "parser.y" /* yacc.c:1646  */
    { parserOutput("declaration_specifiers -> type_specifier"); }
#line 2080 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 103 "parser.y" /* yacc.c:1646  */
    { parserOutput("declaration_specifiers -> type_specifier declaration_specifiers"); }
#line 2086 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 104 "parser.y" /* yacc.c:1646  */
    { parserOutput("declaration_specifiers -> type_qualifier"); }
#line 2092 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 105 "parser.y" /* yacc.c:1646  */
    { parserOutput("declaration_specifiers -> type_qualifier declaration_specifiers"); }
#line 2098 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 109 "parser.y" /* yacc.c:1646  */
    { parserOutput("storage_class_specifier -> AUTO"); st.setInsertMode(true); nodeStorageClassSpecifier = 0; }
#line 2104 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 110 "parser.y" /* yacc.c:1646  */
    { parserOutput("storage_class_specifier -> REGISTER"); st.setInsertMode(true); nodeStorageClassSpecifier = 1; }
#line 2110 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 111 "parser.y" /* yacc.c:1646  */
    { parserOutput("storage_class_specifier -> STATIC"); st.setInsertMode(true); nodeStorageClassSpecifier = 2; }
#line 2116 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 112 "parser.y" /* yacc.c:1646  */
    { parserOutput("storage_class_specifier -> EXTERN"); st.setInsertMode(true); nodeStorageClassSpecifier = 3; }
#line 2122 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 113 "parser.y" /* yacc.c:1646  */
    { parserOutput("storage_class_specifier -> TYPEDEF"); st.setInsertMode(true); nodeStorageClassSpecifier = 4; }
#line 2128 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 117 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_specifier -> VOID"); st.setInsertMode(true); nodeTypeSpecifier = 0; }
#line 2134 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 118 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_specifier -> CHAR"); st.setInsertMode(true); nodeTypeSpecifier = 1; }
#line 2140 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 119 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_specifier -> SHORT"); st.setInsertMode(true); nodeTypeSpecifier = 2; }
#line 2146 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 120 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_specifier -> INT"); st.setInsertMode(true); nodeTypeSpecifier = 3; }
#line 2152 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 121 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_specifier -> LONG"); st.setInsertMode(true); nodeTypeSpecifier = 4; }
#line 2158 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 122 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_specifier -> FLOAT"); st.setInsertMode(true); nodeTypeSpecifier = 5; }
#line 2164 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 123 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_specifier -> DOUBLE"); st.setInsertMode(true); nodeTypeSpecifier = 6; }
#line 2170 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 124 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_specifier -> SIGNED"); st.setInsertMode(true); nodeIsSigned = true; }
#line 2176 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 125 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_specifier -> UNSIGNED"); st.setInsertMode(true); nodeIsSigned = false; }
#line 2182 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 126 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_specifier -> struct_or_union_specifier"); }
#line 2188 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 127 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_specifier -> enum_specifier"); /* TODO: Enums... one day... */ }
#line 2194 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 128 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_specifier -> TYPEDEF_NAME"); /* TODO: typedefs in symbol table */ }
#line 2200 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 132 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_qualifier -> CONST"); st.setInsertMode(true); nodeTypeQualifier = 0; }
#line 2206 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 133 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_qualifier -> VOLATILE"); st.setInsertMode(true); nodeTypeQualifier = 1; }
#line 2212 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 137 "parser.y" /* yacc.c:1646  */
    { parserOutput("struct_or_union_specifier -> struct_or_union identifier OBRACE struct_declaration_list CBRACE"); }
#line 2218 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 138 "parser.y" /* yacc.c:1646  */
    { parserOutput("struct_or_union_specifier -> struct_or_union OBRACE struct_declaration_list CBRACE"); }
#line 2224 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 139 "parser.y" /* yacc.c:1646  */
    { parserOutput("struct_or_union_specifier -> struct_or_union identifier"); }
#line 2230 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 143 "parser.y" /* yacc.c:1646  */
    { parserOutput("struct_or_union -> STRUCT"); nodeTypeSpecifier = 7; }
#line 2236 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 144 "parser.y" /* yacc.c:1646  */
    { parserOutput("struct_or_union -> UNION"); }
#line 2242 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 148 "parser.y" /* yacc.c:1646  */
    { parserOutput("struct_declaration_list -> struct_declaration"); }
#line 2248 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 149 "parser.y" /* yacc.c:1646  */
    { parserOutput("struct_declaration_list -> struct_declaration_list struct_declaration"); }
#line 2254 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 153 "parser.y" /* yacc.c:1646  */
    { parserOutput("init_declarator_list -> init_declarator"); }
#line 2260 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 154 "parser.y" /* yacc.c:1646  */
    { parserOutput("init_declarator_list -> init_declarator_list COMMA init_declarator"); }
#line 2266 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 158 "parser.y" /* yacc.c:1646  */
    { parserOutput("init_declarator -> declarator"); }
#line 2272 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 159 "parser.y" /* yacc.c:1646  */
    { parserOutput("init_declarator -> declarator ASSIGN initializer"); }
#line 2278 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 163 "parser.y" /* yacc.c:1646  */
    { parserOutput("struct_declaration -> specifier_qualifier_list struct_declarator_list SEMICOLON"); }
#line 2284 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 167 "parser.y" /* yacc.c:1646  */
    { parserOutput("specifier_qualifier_list -> type_specifier"); }
#line 2290 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 168 "parser.y" /* yacc.c:1646  */
    { parserOutput("specifier_qualifier_list -> type_specifier specifier_qualifier_list"); }
#line 2296 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 169 "parser.y" /* yacc.c:1646  */
    { parserOutput("specifier_qualifier_list -> type_qualifier"); }
#line 2302 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 170 "parser.y" /* yacc.c:1646  */
    { parserOutput("specifier_qualifier_list -> type_qualifier specifier_qualifier_list"); }
#line 2308 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 174 "parser.y" /* yacc.c:1646  */
    { parserOutput("struct_declarator_list -> struct_declarator"); }
#line 2314 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 175 "parser.y" /* yacc.c:1646  */
    { parserOutput("struct_declarator_list -> struct_declarator_list COMMA struct_declarator"); }
#line 2320 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 179 "parser.y" /* yacc.c:1646  */
    { parserOutput("struct_declarator -> declarator"); }
#line 2326 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 180 "parser.y" /* yacc.c:1646  */
    { parserOutput("struct_declarator -> COLON constant_expression"); }
#line 2332 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 181 "parser.y" /* yacc.c:1646  */
    { parserOutput("struct_declarator -> declarator COLON constant_expression"); }
#line 2338 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 185 "parser.y" /* yacc.c:1646  */
    { parserOutput("enum_specifier -> ENUM OBRACE enumerator_list CBRACE"); }
#line 2344 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 186 "parser.y" /* yacc.c:1646  */
    { parserOutput("enum_specifier -> ENUM identifier OBRACE enumerator_list CBRACE"); }
#line 2350 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 187 "parser.y" /* yacc.c:1646  */
    { parserOutput("enum_specifier -> ENUM identifier"); }
#line 2356 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 191 "parser.y" /* yacc.c:1646  */
    { parserOutput("enumerator_list -> enumerator"); }
#line 2362 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 192 "parser.y" /* yacc.c:1646  */
    { parserOutput("enumerator_list -> enumerator_list COMMA enumerator"); }
#line 2368 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 196 "parser.y" /* yacc.c:1646  */
    { parserOutput("enumerator -> identifier"); }
#line 2374 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 197 "parser.y" /* yacc.c:1646  */
    { parserOutput("enumerator -> identifier ASSIGN constant_expression"); }
#line 2380 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 201 "parser.y" /* yacc.c:1646  */
    { parserOutput("declarator -> direct_declarator"); }
#line 2386 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 202 "parser.y" /* yacc.c:1646  */
    { parserOutput("declarator -> pointer direct_declarator"); }
#line 2392 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 206 "parser.y" /* yacc.c:1646  */
    { 
                        parserOutput("direct_declarator -> identifier");
                        SymbolNode node(nodeIdentifier, line, column, nodeTypeSpecifier);
                        node.setTypeStorageClassIndex(nodeStorageClassSpecifier);
                        node.setTypeQualifierIndex(nodeTypeQualifier);
                        node.setIsFunction(nodeIsFunction);
                        node.setIsSigned(nodeIsSigned);
                        
                        if (!st.insert(node))
                        {
                            return 1;
                        }

                        lastNodeInserted = nodeIdentifier;
                        nodeIdentifier = "";
                        nodeLineNumber = -1;
                        nodeStorageClassSpecifier = -1;
                        nodeTypeSpecifier = 3;
                        nodeTypeQualifier = -1;
                        nodeIsFunction = false;
                        nodeIsSigned = true;
                    }
#line 2419 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 228 "parser.y" /* yacc.c:1646  */
    { parserOutput("direct_declarator -> OPAREN declarator CPAREN"); }
#line 2425 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 229 "parser.y" /* yacc.c:1646  */
    { parserOutput("direct_declarator -> direct_declarator OBRACKET CBRACKET"); }
#line 2431 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 230 "parser.y" /* yacc.c:1646  */
    { parserOutput("direct_declarator -> direct_declarator OBRACKET constant_expression CBRACKET"); }
#line 2437 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 231 "parser.y" /* yacc.c:1646  */
    { parserOutput("direct_declarator -> direct_declarator OPAREN CPAREN"); }
#line 2443 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 232 "parser.y" /* yacc.c:1646  */
    { parserOutput("direct_declarator -> direct_declarator OPAREN parameter_type_list CPAREN"); }
#line 2449 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 233 "parser.y" /* yacc.c:1646  */
    { parserOutput("direct_declarator -> direct_declarator OPAREN identifier_list CPAREN"); }
#line 2455 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 237 "parser.y" /* yacc.c:1646  */
    { parserOutput("pointer -> STAR"); }
#line 2461 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 238 "parser.y" /* yacc.c:1646  */
    { parserOutput("pointer -> STAR type_qualifier_list"); }
#line 2467 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 239 "parser.y" /* yacc.c:1646  */
    { parserOutput("pointer -> STAR pointer"); }
#line 2473 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 240 "parser.y" /* yacc.c:1646  */
    { parserOutput("pointer -> STAR type_qualifier_list pointer"); }
#line 2479 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 244 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_qualifier_list -> type_qualifier"); }
#line 2485 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 245 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_qualifier_list -> type_qualifier_list type_qualifier"); }
#line 2491 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 249 "parser.y" /* yacc.c:1646  */
    { parserOutput("parameter_type_list -> parameter_list"); }
#line 2497 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 250 "parser.y" /* yacc.c:1646  */
    { parserOutput("parameter_type_list -> parameter_list COMMA ELLIPSIS"); }
#line 2503 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 254 "parser.y" /* yacc.c:1646  */
    { parserOutput("parameter_list -> parameter_declaration"); }
#line 2509 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 255 "parser.y" /* yacc.c:1646  */
    { parserOutput("parameter_list -> parameter_list COMMA parameter_declaration"); }
#line 2515 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 259 "parser.y" /* yacc.c:1646  */
    { parserOutput("parameter_declaration -> declaration_specifiers declarator"); }
#line 2521 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 260 "parser.y" /* yacc.c:1646  */
    { parserOutput("parameter_declaration -> declaration_specifiers"); }
#line 2527 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 261 "parser.y" /* yacc.c:1646  */
    { parserOutput("parameter_declaration -> declaration_specifiers abstract_declarator"); }
#line 2533 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 265 "parser.y" /* yacc.c:1646  */
    { parserOutput("identifier_list -> identifier"); }
#line 2539 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 266 "parser.y" /* yacc.c:1646  */
    { parserOutput("identifier_list -> identifier_list COMMA identifier"); }
#line 2545 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 270 "parser.y" /* yacc.c:1646  */
    { parserOutput("initializer -> assignment_expression"); }
#line 2551 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 271 "parser.y" /* yacc.c:1646  */
    { parserOutput("initializer -> OBRACE initializer_list CBRACE"); }
#line 2557 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 272 "parser.y" /* yacc.c:1646  */
    { parserOutput("initializer -> OBRACE initializer_list COMMA CBRACE"); }
#line 2563 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 276 "parser.y" /* yacc.c:1646  */
    { parserOutput("initializer_list -> initializer"); }
#line 2569 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 277 "parser.y" /* yacc.c:1646  */
    { parserOutput("initializer_list -> initializer_list COMMA initializer"); }
#line 2575 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 281 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_name -> specifier_qualifier_list"); }
#line 2581 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 282 "parser.y" /* yacc.c:1646  */
    { parserOutput("type_name -> specifier_qualifier_list abstract_declarator"); }
#line 2587 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 286 "parser.y" /* yacc.c:1646  */
    { parserOutput("abstract_declarator -> pointer"); }
#line 2593 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 287 "parser.y" /* yacc.c:1646  */
    { parserOutput("abstract_declarator -> direct_abstract_declarator"); }
#line 2599 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 288 "parser.y" /* yacc.c:1646  */
    { parserOutput("abstract_declarator -> pointer direct_abstract_declarator"); }
#line 2605 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 292 "parser.y" /* yacc.c:1646  */
    { parserOutput("direct_abstract_declarator -> OPAREN abstract_declarator CPAREN"); }
#line 2611 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 293 "parser.y" /* yacc.c:1646  */
    { parserOutput("direct_abstract_declarator -> OBRACKET CBRACKET"); }
#line 2617 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 294 "parser.y" /* yacc.c:1646  */
    { parserOutput("direct_abstract_declarator -> OBRACKET constant_expression CBRACKET"); }
#line 2623 "parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 295 "parser.y" /* yacc.c:1646  */
    { parserOutput("direct_abstract_declarator -> direct_abstract_declarator OBRACKET CBRACKET"); }
#line 2629 "parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 296 "parser.y" /* yacc.c:1646  */
    { parserOutput("direct_abstract_declarator -> direct_abstract_declarator OBRACKET constant_expression CBRACKET"); }
#line 2635 "parser.c" /* yacc.c:1646  */
    break;

  case 106:
#line 297 "parser.y" /* yacc.c:1646  */
    { parserOutput("direct_abstract_declarator -> OPAREN CPAREN"); }
#line 2641 "parser.c" /* yacc.c:1646  */
    break;

  case 107:
#line 298 "parser.y" /* yacc.c:1646  */
    { parserOutput("direct_abstract_declarator -> OPAREN parameter_type_list CPAREN"); }
#line 2647 "parser.c" /* yacc.c:1646  */
    break;

  case 108:
#line 299 "parser.y" /* yacc.c:1646  */
    { parserOutput("direct_abstract_declarator -> direct_abstract_declarator OPAREN CPAREN"); }
#line 2653 "parser.c" /* yacc.c:1646  */
    break;

  case 109:
#line 300 "parser.y" /* yacc.c:1646  */
    { parserOutput("direct_abstract_declarator -> direct_abstract_declarator OPAREN parameter_type_list CPAREN"); }
#line 2659 "parser.c" /* yacc.c:1646  */
    break;

  case 110:
#line 304 "parser.y" /* yacc.c:1646  */
    { parserOutput("statement -> labeled_statement"); }
#line 2665 "parser.c" /* yacc.c:1646  */
    break;

  case 111:
#line 305 "parser.y" /* yacc.c:1646  */
    { parserOutput("statement -> compound_statement"); }
#line 2671 "parser.c" /* yacc.c:1646  */
    break;

  case 112:
#line 306 "parser.y" /* yacc.c:1646  */
    { parserOutput("statement -> expression_statement"); }
#line 2677 "parser.c" /* yacc.c:1646  */
    break;

  case 113:
#line 307 "parser.y" /* yacc.c:1646  */
    { parserOutput("statement -> selection_statement"); }
#line 2683 "parser.c" /* yacc.c:1646  */
    break;

  case 114:
#line 308 "parser.y" /* yacc.c:1646  */
    { parserOutput("statement -> iteration_statement"); }
#line 2689 "parser.c" /* yacc.c:1646  */
    break;

  case 115:
#line 309 "parser.y" /* yacc.c:1646  */
    { parserOutput("statement -> jump_statement"); }
#line 2695 "parser.c" /* yacc.c:1646  */
    break;

  case 116:
#line 313 "parser.y" /* yacc.c:1646  */
    { parserOutput("labeled_statement -> identifier COLON statement"); }
#line 2701 "parser.c" /* yacc.c:1646  */
    break;

  case 117:
#line 314 "parser.y" /* yacc.c:1646  */
    { parserOutput("labeled_statement -> CASE constant_expression COLON statement"); }
#line 2707 "parser.c" /* yacc.c:1646  */
    break;

  case 118:
#line 315 "parser.y" /* yacc.c:1646  */
    { parserOutput("labeled_statement -> DEFAULT COLON statement"); }
#line 2713 "parser.c" /* yacc.c:1646  */
    break;

  case 119:
#line 319 "parser.y" /* yacc.c:1646  */
    { parserOutput("expression_statement -> SEMICOLON"); }
#line 2719 "parser.c" /* yacc.c:1646  */
    break;

  case 120:
#line 320 "parser.y" /* yacc.c:1646  */
    { parserOutput("expression_statement -> expression SEMICOLON"); }
#line 2725 "parser.c" /* yacc.c:1646  */
    break;

  case 121:
#line 324 "parser.y" /* yacc.c:1646  */
    { parserOutput("compound_statement -> OBRACE CBRACE"); }
#line 2731 "parser.c" /* yacc.c:1646  */
    break;

  case 122:
#line 325 "parser.y" /* yacc.c:1646  */
    { parserOutput("compound_statement -> OBRACE statement_list CBRACE"); }
#line 2737 "parser.c" /* yacc.c:1646  */
    break;

  case 123:
#line 326 "parser.y" /* yacc.c:1646  */
    { parserOutput("compound_statement -> OBRACE declaration_list CBRACE"); }
#line 2743 "parser.c" /* yacc.c:1646  */
    break;

  case 124:
#line 327 "parser.y" /* yacc.c:1646  */
    { parserOutput("compound_statement -> OBRACE declaration_list statement_list CBRACE"); }
#line 2749 "parser.c" /* yacc.c:1646  */
    break;

  case 125:
#line 331 "parser.y" /* yacc.c:1646  */
    { parserOutput("statement_list -> statement"); }
#line 2755 "parser.c" /* yacc.c:1646  */
    break;

  case 126:
#line 332 "parser.y" /* yacc.c:1646  */
    { parserOutput("statement_list -> statement_list statement"); }
#line 2761 "parser.c" /* yacc.c:1646  */
    break;

  case 127:
#line 336 "parser.y" /* yacc.c:1646  */
    { parserOutput("selection_statement -> IF OPAREN expression CPAREN statement"); }
#line 2767 "parser.c" /* yacc.c:1646  */
    break;

  case 128:
#line 337 "parser.y" /* yacc.c:1646  */
    { parserOutput("selection_statement -> IF OPAREN expression CPAREN statement ELSE statement"); }
#line 2773 "parser.c" /* yacc.c:1646  */
    break;

  case 129:
#line 338 "parser.y" /* yacc.c:1646  */
    { parserOutput("selection_statement -> SWITCH OPAREN expression CPAREN statement"); }
#line 2779 "parser.c" /* yacc.c:1646  */
    break;

  case 130:
#line 342 "parser.y" /* yacc.c:1646  */
    { parserOutput("iteration_statement -> WHILE OPAREN expression CPAREN statement"); }
#line 2785 "parser.c" /* yacc.c:1646  */
    break;

  case 131:
#line 343 "parser.y" /* yacc.c:1646  */
    { parserOutput("iteration_statement -> DO statement WHILE OPAREN expression CPAREN SEMICOLON"); }
#line 2791 "parser.c" /* yacc.c:1646  */
    break;

  case 132:
#line 344 "parser.y" /* yacc.c:1646  */
    { parserOutput("iteration_statement -> FOR OPAREN SEMICOLON SEMICOLON CPAREN statement"); }
#line 2797 "parser.c" /* yacc.c:1646  */
    break;

  case 133:
#line 345 "parser.y" /* yacc.c:1646  */
    { parserOutput("iteration_statement -> FOR OPAREN SEMICOLON SEMICOLON expression CPAREN statement"); }
#line 2803 "parser.c" /* yacc.c:1646  */
    break;

  case 134:
#line 346 "parser.y" /* yacc.c:1646  */
    { parserOutput("iteration_statement -> FOR OPAREN SEMICOLON expression SEMICOLON CPAREN statement"); }
#line 2809 "parser.c" /* yacc.c:1646  */
    break;

  case 135:
#line 347 "parser.y" /* yacc.c:1646  */
    { parserOutput("iteration_statement -> FOR OPAREN SEMICOLON expression SEMICOLON expression CPAREN statement"); }
#line 2815 "parser.c" /* yacc.c:1646  */
    break;

  case 136:
#line 348 "parser.y" /* yacc.c:1646  */
    { parserOutput("iteration_statement -> FOR OPAREN expression SEMICOLON SEMICOLON CPAREN statement"); }
#line 2821 "parser.c" /* yacc.c:1646  */
    break;

  case 137:
#line 349 "parser.y" /* yacc.c:1646  */
    { parserOutput("iteration_statement -> FOR OPAREN expression SEMICOLON SEMICOLON expression CPAREN statement"); }
#line 2827 "parser.c" /* yacc.c:1646  */
    break;

  case 138:
#line 350 "parser.y" /* yacc.c:1646  */
    { parserOutput("iteration_statement -> FOR OPAREN expression SEMICOLON expression SEMICOLON CPAREN statement"); }
#line 2833 "parser.c" /* yacc.c:1646  */
    break;

  case 139:
#line 351 "parser.y" /* yacc.c:1646  */
    { parserOutput("iteration_statement -> FOR OPAREN expression SEMICOLON expression SEMICOLON expression CPAREN statement"); }
#line 2839 "parser.c" /* yacc.c:1646  */
    break;

  case 140:
#line 355 "parser.y" /* yacc.c:1646  */
    { parserOutput("jump_statement -> GOTO identifier SEMICOLON"); }
#line 2845 "parser.c" /* yacc.c:1646  */
    break;

  case 141:
#line 356 "parser.y" /* yacc.c:1646  */
    { parserOutput("jump_statement -> CONTINUE SEMICOLON"); }
#line 2851 "parser.c" /* yacc.c:1646  */
    break;

  case 142:
#line 357 "parser.y" /* yacc.c:1646  */
    { parserOutput("jump_statement -> BREAK SEMICOLON"); }
#line 2857 "parser.c" /* yacc.c:1646  */
    break;

  case 143:
#line 358 "parser.y" /* yacc.c:1646  */
    { parserOutput("jump_statement -> RETURN SEMICOLON"); }
#line 2863 "parser.c" /* yacc.c:1646  */
    break;

  case 144:
#line 359 "parser.y" /* yacc.c:1646  */
    { parserOutput("jump_statement -> RETURN expression SEMICOLON"); }
#line 2869 "parser.c" /* yacc.c:1646  */
    break;

  case 145:
#line 363 "parser.y" /* yacc.c:1646  */
    { parserOutput("expression -> assignment_expression"); }
#line 2875 "parser.c" /* yacc.c:1646  */
    break;

  case 146:
#line 364 "parser.y" /* yacc.c:1646  */
    { parserOutput("expression -> expression COMMA assignment_expression"); }
#line 2881 "parser.c" /* yacc.c:1646  */
    break;

  case 147:
#line 368 "parser.y" /* yacc.c:1646  */
    { parserOutput("assignment_expression -> conditional_expression"); }
#line 2887 "parser.c" /* yacc.c:1646  */
    break;

  case 148:
#line 369 "parser.y" /* yacc.c:1646  */
    { parserOutput("assignment_expression -> unary_expression assignment_operator assignment_expression"); }
#line 2893 "parser.c" /* yacc.c:1646  */
    break;

  case 149:
#line 373 "parser.y" /* yacc.c:1646  */
    { parserOutput("assignment_operator -> ASSIGN"); }
#line 2899 "parser.c" /* yacc.c:1646  */
    break;

  case 150:
#line 374 "parser.y" /* yacc.c:1646  */
    { parserOutput("assignment_operator -> MUL_ASSIGN"); }
#line 2905 "parser.c" /* yacc.c:1646  */
    break;

  case 151:
#line 375 "parser.y" /* yacc.c:1646  */
    { parserOutput("assignment_operator -> DIV_ASSIGN"); }
#line 2911 "parser.c" /* yacc.c:1646  */
    break;

  case 152:
#line 376 "parser.y" /* yacc.c:1646  */
    { parserOutput("assignment_operator -> MOD_ASSIGN"); }
#line 2917 "parser.c" /* yacc.c:1646  */
    break;

  case 153:
#line 377 "parser.y" /* yacc.c:1646  */
    { parserOutput("assignment_operator -> ADD_ASSIGN"); }
#line 2923 "parser.c" /* yacc.c:1646  */
    break;

  case 154:
#line 378 "parser.y" /* yacc.c:1646  */
    { parserOutput("assignment_operator -> SUB_ASSIGN"); }
#line 2929 "parser.c" /* yacc.c:1646  */
    break;

  case 155:
#line 379 "parser.y" /* yacc.c:1646  */
    { parserOutput("assignment_operator -> B_SL_ASSIGN"); }
#line 2935 "parser.c" /* yacc.c:1646  */
    break;

  case 156:
#line 380 "parser.y" /* yacc.c:1646  */
    { parserOutput("assignment_operator -> B_SR_ASSIGN"); }
#line 2941 "parser.c" /* yacc.c:1646  */
    break;

  case 157:
#line 381 "parser.y" /* yacc.c:1646  */
    { parserOutput("assignment_operator -> B_AND_ASSIGN"); }
#line 2947 "parser.c" /* yacc.c:1646  */
    break;

  case 158:
#line 382 "parser.y" /* yacc.c:1646  */
    { parserOutput("assignment_operator -> B_XOR_ASSIGN"); }
#line 2953 "parser.c" /* yacc.c:1646  */
    break;

  case 159:
#line 383 "parser.y" /* yacc.c:1646  */
    { parserOutput("assignment_operator -> B_OR_ASSIGN"); }
#line 2959 "parser.c" /* yacc.c:1646  */
    break;

  case 160:
#line 387 "parser.y" /* yacc.c:1646  */
    { parserOutput("conditional_expression -> logical_or_expression"); }
#line 2965 "parser.c" /* yacc.c:1646  */
    break;

  case 161:
#line 388 "parser.y" /* yacc.c:1646  */
    { parserOutput("conditional_expression -> logical_or_expression QUESTION expression COLON conditional_expression"); }
#line 2971 "parser.c" /* yacc.c:1646  */
    break;

  case 162:
#line 392 "parser.y" /* yacc.c:1646  */
    { parserOutput("constant_expression -> conditional_expression"); }
#line 2977 "parser.c" /* yacc.c:1646  */
    break;

  case 163:
#line 396 "parser.y" /* yacc.c:1646  */
    { parserOutput("logical_or_expression -> logical_and_expression"); }
#line 2983 "parser.c" /* yacc.c:1646  */
    break;

  case 164:
#line 397 "parser.y" /* yacc.c:1646  */
    { parserOutput("logical_or_expression -> logical_or_expression L_OR logical_and_expression"); }
#line 2989 "parser.c" /* yacc.c:1646  */
    break;

  case 165:
#line 401 "parser.y" /* yacc.c:1646  */
    { parserOutput("logical_and_expression -> inclusive_or_expression"); }
#line 2995 "parser.c" /* yacc.c:1646  */
    break;

  case 166:
#line 402 "parser.y" /* yacc.c:1646  */
    { parserOutput("logical_and_expression -> logical_and_expression L_AND inclusive_or_expression"); }
#line 3001 "parser.c" /* yacc.c:1646  */
    break;

  case 167:
#line 406 "parser.y" /* yacc.c:1646  */
    { parserOutput("inclusive_or_expression -> exclusive_or_expression"); }
#line 3007 "parser.c" /* yacc.c:1646  */
    break;

  case 168:
#line 407 "parser.y" /* yacc.c:1646  */
    { parserOutput("inclusive_or_expression -> inclusive_or_expression B_OR exclusive_or_expression"); }
#line 3013 "parser.c" /* yacc.c:1646  */
    break;

  case 169:
#line 411 "parser.y" /* yacc.c:1646  */
    { parserOutput("exclusive_or_expression -> and_expression"); }
#line 3019 "parser.c" /* yacc.c:1646  */
    break;

  case 170:
#line 412 "parser.y" /* yacc.c:1646  */
    { parserOutput("exclusive_or_expression -> exclusive_or_expression B_XOR and_expression"); }
#line 3025 "parser.c" /* yacc.c:1646  */
    break;

  case 171:
#line 416 "parser.y" /* yacc.c:1646  */
    { parserOutput("and_expression -> equality_expression"); }
#line 3031 "parser.c" /* yacc.c:1646  */
    break;

  case 172:
#line 417 "parser.y" /* yacc.c:1646  */
    { parserOutput("and_expression -> and_expression AMPERSAND equality_expression"); }
#line 3037 "parser.c" /* yacc.c:1646  */
    break;

  case 173:
#line 421 "parser.y" /* yacc.c:1646  */
    { parserOutput("equality_expression -> relational_expression"); }
#line 3043 "parser.c" /* yacc.c:1646  */
    break;

  case 174:
#line 422 "parser.y" /* yacc.c:1646  */
    { parserOutput("equality_expression -> equality_expression EQ_OP relational_expression"); }
#line 3049 "parser.c" /* yacc.c:1646  */
    break;

  case 175:
#line 423 "parser.y" /* yacc.c:1646  */
    { parserOutput("equality_expression -> equality_expression NE_OP relational_expression"); }
#line 3055 "parser.c" /* yacc.c:1646  */
    break;

  case 176:
#line 427 "parser.y" /* yacc.c:1646  */
    { parserOutput("relational_expression -> shift_expression"); }
#line 3061 "parser.c" /* yacc.c:1646  */
    break;

  case 177:
#line 428 "parser.y" /* yacc.c:1646  */
    { parserOutput("relational_expression -> relational_expression LT_OP shift_expression"); }
#line 3067 "parser.c" /* yacc.c:1646  */
    break;

  case 178:
#line 429 "parser.y" /* yacc.c:1646  */
    { parserOutput("relational_expression -> relational_expression GT_OP shift_expression"); }
#line 3073 "parser.c" /* yacc.c:1646  */
    break;

  case 179:
#line 430 "parser.y" /* yacc.c:1646  */
    { parserOutput("relational_expression -> relational_expression LE_OP shift_expression"); }
#line 3079 "parser.c" /* yacc.c:1646  */
    break;

  case 180:
#line 431 "parser.y" /* yacc.c:1646  */
    { parserOutput("relational_expression -> relational_expression GE_OP shift_expression"); }
#line 3085 "parser.c" /* yacc.c:1646  */
    break;

  case 181:
#line 435 "parser.y" /* yacc.c:1646  */
    { parserOutput("shift_expression -> additive_expression"); }
#line 3091 "parser.c" /* yacc.c:1646  */
    break;

  case 182:
#line 436 "parser.y" /* yacc.c:1646  */
    { parserOutput("shift_expression -> shift_expression B_SL additive_expression"); }
#line 3097 "parser.c" /* yacc.c:1646  */
    break;

  case 183:
#line 437 "parser.y" /* yacc.c:1646  */
    { parserOutput("shift_expression -> shift_expression B_SR additive_expression"); }
#line 3103 "parser.c" /* yacc.c:1646  */
    break;

  case 184:
#line 441 "parser.y" /* yacc.c:1646  */
    { parserOutput("additive_expression -> multiplicative_expression"); }
#line 3109 "parser.c" /* yacc.c:1646  */
    break;

  case 185:
#line 442 "parser.y" /* yacc.c:1646  */
    { parserOutput("additive_expression -> additive_expression ADD multiplicative_expression"); }
#line 3115 "parser.c" /* yacc.c:1646  */
    break;

  case 186:
#line 443 "parser.y" /* yacc.c:1646  */
    { parserOutput("additive_expression -> additive_expression SUB multiplicative_expression"); }
#line 3121 "parser.c" /* yacc.c:1646  */
    break;

  case 187:
#line 447 "parser.y" /* yacc.c:1646  */
    { parserOutput("multiplicative_expression -> cast_expression"); }
#line 3127 "parser.c" /* yacc.c:1646  */
    break;

  case 188:
#line 448 "parser.y" /* yacc.c:1646  */
    { parserOutput("multiplicative_expression -> multiplicative_expression STAR cast_expression"); }
#line 3133 "parser.c" /* yacc.c:1646  */
    break;

  case 189:
#line 449 "parser.y" /* yacc.c:1646  */
    { parserOutput("multiplicative_expression -> multiplicative_expression DIV cast_expression"); }
#line 3139 "parser.c" /* yacc.c:1646  */
    break;

  case 190:
#line 450 "parser.y" /* yacc.c:1646  */
    { parserOutput("multiplicative_expression -> multiplicative_expression MOD cast_expression"); }
#line 3145 "parser.c" /* yacc.c:1646  */
    break;

  case 191:
#line 454 "parser.y" /* yacc.c:1646  */
    { parserOutput("cast_expression -> unary_expression"); }
#line 3151 "parser.c" /* yacc.c:1646  */
    break;

  case 192:
#line 455 "parser.y" /* yacc.c:1646  */
    { parserOutput("cast_expression -> OPAREN type_name CPAREN cast_expression"); }
#line 3157 "parser.c" /* yacc.c:1646  */
    break;

  case 193:
#line 459 "parser.y" /* yacc.c:1646  */
    { parserOutput("unary_expression -> postfix_expression"); }
#line 3163 "parser.c" /* yacc.c:1646  */
    break;

  case 194:
#line 460 "parser.y" /* yacc.c:1646  */
    { parserOutput("unary_expression -> INC_OP unary_expression"); }
#line 3169 "parser.c" /* yacc.c:1646  */
    break;

  case 195:
#line 461 "parser.y" /* yacc.c:1646  */
    { parserOutput("unary_expression -> DEC_OP unary_expression"); }
#line 3175 "parser.c" /* yacc.c:1646  */
    break;

  case 196:
#line 462 "parser.y" /* yacc.c:1646  */
    { parserOutput("unary_expression -> unary_operator cast_expression"); }
#line 3181 "parser.c" /* yacc.c:1646  */
    break;

  case 197:
#line 463 "parser.y" /* yacc.c:1646  */
    { parserOutput("unary_expression -> SIZEOF unary_expression"); }
#line 3187 "parser.c" /* yacc.c:1646  */
    break;

  case 198:
#line 464 "parser.y" /* yacc.c:1646  */
    { parserOutput("unary_expression -> SIZEOF OPAREN type_name CPAREN"); }
#line 3193 "parser.c" /* yacc.c:1646  */
    break;

  case 199:
#line 468 "parser.y" /* yacc.c:1646  */
    { parserOutput("unary_operator -> AMPERSAND"); }
#line 3199 "parser.c" /* yacc.c:1646  */
    break;

  case 200:
#line 469 "parser.y" /* yacc.c:1646  */
    { parserOutput("unary_operator -> STAR"); }
#line 3205 "parser.c" /* yacc.c:1646  */
    break;

  case 201:
#line 470 "parser.y" /* yacc.c:1646  */
    { parserOutput("unary_operator -> ADD"); }
#line 3211 "parser.c" /* yacc.c:1646  */
    break;

  case 202:
#line 471 "parser.y" /* yacc.c:1646  */
    { parserOutput("unary_operator -> SUB"); }
#line 3217 "parser.c" /* yacc.c:1646  */
    break;

  case 203:
#line 472 "parser.y" /* yacc.c:1646  */
    { parserOutput("unary_operator -> B_NOT"); }
#line 3223 "parser.c" /* yacc.c:1646  */
    break;

  case 204:
#line 473 "parser.y" /* yacc.c:1646  */
    { parserOutput("unary_operator -> L_NOT"); }
#line 3229 "parser.c" /* yacc.c:1646  */
    break;

  case 205:
#line 477 "parser.y" /* yacc.c:1646  */
    { parserOutput("postfix_expression -> primary_expression"); }
#line 3235 "parser.c" /* yacc.c:1646  */
    break;

  case 206:
#line 478 "parser.y" /* yacc.c:1646  */
    { parserOutput("postfix_expression -> postfix_expression OBRACKET expression CBRACKET"); }
#line 3241 "parser.c" /* yacc.c:1646  */
    break;

  case 207:
#line 479 "parser.y" /* yacc.c:1646  */
    { parserOutput("postfix_expression -> postfix_expression OPAREN CPAREN"); }
#line 3247 "parser.c" /* yacc.c:1646  */
    break;

  case 208:
#line 480 "parser.y" /* yacc.c:1646  */
    { parserOutput("postfix_expression -> postfix_expression OPAREN argument_expression_list CPAREN"); }
#line 3253 "parser.c" /* yacc.c:1646  */
    break;

  case 209:
#line 481 "parser.y" /* yacc.c:1646  */
    { parserOutput("postfix_expression -> postfix_expression PERIOD identifier"); }
#line 3259 "parser.c" /* yacc.c:1646  */
    break;

  case 210:
#line 482 "parser.y" /* yacc.c:1646  */
    { parserOutput("postfix_expression -> postfix_expression ARROW identifier"); }
#line 3265 "parser.c" /* yacc.c:1646  */
    break;

  case 211:
#line 483 "parser.y" /* yacc.c:1646  */
    { parserOutput("postfix_expression -> postfix_expression INC_OP"); }
#line 3271 "parser.c" /* yacc.c:1646  */
    break;

  case 212:
#line 484 "parser.y" /* yacc.c:1646  */
    { parserOutput("postfix_expression -> postfix_expression DEC_OP"); }
#line 3277 "parser.c" /* yacc.c:1646  */
    break;

  case 213:
#line 488 "parser.y" /* yacc.c:1646  */
    { parserOutput("primary_expression -> identifier"); }
#line 3283 "parser.c" /* yacc.c:1646  */
    break;

  case 214:
#line 489 "parser.y" /* yacc.c:1646  */
    { parserOutput("primary_expression -> constant"); }
#line 3289 "parser.c" /* yacc.c:1646  */
    break;

  case 215:
#line 490 "parser.y" /* yacc.c:1646  */
    { parserOutput("primary_expression -> string"); }
#line 3295 "parser.c" /* yacc.c:1646  */
    break;

  case 216:
#line 491 "parser.y" /* yacc.c:1646  */
    { parserOutput("primary_expression -> OPAREN expression CPAREN"); }
#line 3301 "parser.c" /* yacc.c:1646  */
    break;

  case 217:
#line 495 "parser.y" /* yacc.c:1646  */
    { parserOutput("argument_expression_list -> assignment_expression"); }
#line 3307 "parser.c" /* yacc.c:1646  */
    break;

  case 218:
#line 496 "parser.y" /* yacc.c:1646  */
    { parserOutput("argument_expression_list -> argument_expression_list COMMA assignment_expression"); }
#line 3313 "parser.c" /* yacc.c:1646  */
    break;

  case 219:
#line 500 "parser.y" /* yacc.c:1646  */
    { parserOutput("constant -> INTEGER_CONSTANT"); }
#line 3319 "parser.c" /* yacc.c:1646  */
    break;

  case 220:
#line 501 "parser.y" /* yacc.c:1646  */
    { parserOutput("constant -> CHARACTER_CONSTANT"); }
#line 3325 "parser.c" /* yacc.c:1646  */
    break;

  case 221:
#line 502 "parser.y" /* yacc.c:1646  */
    { parserOutput("constant -> FLOATING_CONSTANT"); }
#line 3331 "parser.c" /* yacc.c:1646  */
    break;

  case 222:
#line 503 "parser.y" /* yacc.c:1646  */
    { parserOutput("constant -> ENUMERATION_CONSTANT"); }
#line 3337 "parser.c" /* yacc.c:1646  */
    break;

  case 223:
#line 507 "parser.y" /* yacc.c:1646  */
    { parserOutput("string -> STRING_LITERAL"); }
#line 3343 "parser.c" /* yacc.c:1646  */
    break;

  case 224:
#line 511 "parser.y" /* yacc.c:1646  */
    {
                    parserOutput("identifier -> IDENTIFIER"); 
                    nodeIdentifier = yylval.sval; 
                    nodeLineNumber = line;
                    if (!st.getInsertMode() && st.searchAll(nodeIdentifier).first == -1)
                    {
                        yyerror(NULL);
                        return 1;
                    }
                 }
#line 3358 "parser.c" /* yacc.c:1646  */
    break;


#line 3362 "parser.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 523 "parser.y" /* yacc.c:1906  */


int main(int argc, char** argv)
{
	int outputIndex = parseCommandLine(argc, argv); //Returns the index of the output file in argv or 0 if there is no -o

	yyparse();

    outputFile.open( outputIndex ? argv[outputIndex] : "output/defaultOutput.txt");
    if (outputFile.good())
    {
        outputFile << outputStream.str();
        outputFile << errorStream.str();
        cout << outputStream.str();
        cerr << errorStream.str();
    }
    else
    {
		cerr << "Output file fail." << endl;
        exit(-1);
    }

	  return 0;
}

/// @name yyerror
/// @brief This is the general syntax error function for the parser.
///        It will output the line and column number the error occurred on.
///        The output will first go to an error stream (a stringstream).
///        The error stream is then flushed to the output file and cerr.

void yyerror(const char* s)
{
    if (inputFile.good())
    {
        string currentLine;
        for (int i = 0; i < line; i++)
        {
            getline(inputFile, currentLine);
        }
        errorStream << currentLine << endl;
    }

    for (int i = 0; i < tab; i++)
    {
        errorStream << "\t";
    }

    for (int i = 0; i < column; i++)
    {
        errorStream << " ";
    }

    errorStream << "^ Error on line " << line << ", column " << column << "." << endl;
}

/// @name parserOutput
/// @brief This function simply adds the rule used to the output file, if the option
///        to have debugging productions is on.

void parserOutput(string s)
{
    if (outputProductions)
    {
        outputStream << "Rule: " << s << endl;
    }
}

/// @name parseCommandLine
/// @brief Handles and command line arguments.
///        Returns the argv index of the output file, if it exists, else returns 0.
int parseCommandLine(int argc, char** argv)
{
	int outputIndex = 0;
	const int num_options = 5;
	const char* valid_options[] {
		"-d",
		"-l",
		"-o",
		"-p",
		"-s"
	};

    inputFile.open(argv[1]); //Assumes the first command line arguement is the input file.
    FILE* inputStream = fopen(argv[1], "r");
    if (!inputStream)
    {
        cerr << "Cannot open input file." << endl;
		exit(-1);
    }
    else
    {
        yyin = inputStream;
    }


	for(int i = 2 ; i < argc ; ++i) //Skips the input file name
	{
		for(int j = 0 ; j < num_options ; ++j)
		{
			if( strcmp(valid_options[j], argv[i]) == 0 )
			{
				switch( argv[i][1] ) //Get the single character of the command line arguement
				{
					case 'd': command_s = command_l = true; //Both debug to true.
						break;
					case 'l': command_l = true;
						break;
					case 'o': outputIndex = ++i;
						if(i >= argc)
						{
							cerr << "ERROR: Please provide an output file with -o" << endl;
							exit(-1);
						}
						break;
					case 'p': outputProductions = true;
						break;
					case 's': command_s = true;
						break;
					default:
						cerr << "Invalid command line argument" << endl;
						exit(-1);
						break;
				}
			}
        }
	}

	return outputIndex; 
}
