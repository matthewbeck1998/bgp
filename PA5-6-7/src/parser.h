/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_SRC_PARSER_H_INCLUDED
# define YY_YY_SRC_PARSER_H_INCLUDED
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
#line 47 "src/parser.y" /* yacc.c:1909  */

    char sval[255];

#line 147 "src/parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_H_INCLUDED  */
