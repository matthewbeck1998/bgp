%{
#include <iostream>
#include <cstdio>
#include <cstring>
#include "parser.h"

using namespace std;
%}

%option noyywrap

letter	            [A-Za-z]
digit	            [0-9]
identifier          {letter}({letter}|{digit})*
integer_constant    {digit}+
floating_constant   {digit}+\.{digit}+
string_literal      \".*\"

%%

[ \t\n]     {}

auto 		{ return AUTO; }
break 		{ return BREAK; }
case 		{ return CASE; }
char 		{ return CHAR; }
const 		{ return CONST; }
continue 	{ return CONTINUE; }
default 	{ return DEFAULT; }
do 			{ return DO; }
double 		{ return DOUBLE; }
"..."		{ return ELLIPSIS; }
else 		{ return ELSE; }
enum 		{ return ENUM; }
extern 		{ return EXTERN; }
float 		{ return FLOAT; }
for 		{ return FOR; }
goto 		{ return GOTO; }
if 			{ return IF; }
int 		{ return INT; }
long 		{ return LONG; }
register 	{ return REGISTER; }
return 		{ return RETURN; }
short 		{ return SHORT; }
signed 		{ return SIGNED; }
sizeof 		{ return SIZEOF; }
static 		{ return STATIC; }
struct 		{ return STRUCT; }
switch 		{ return SWITCH; }
typedef 	{ return TYPEDEF; }
union 		{ return UNION; }
unsigned	{ return UNSIGNED; }
void 		{ return VOID; }
volatile 	{ return VOLATILE; }
while 		{ return WHILE; }

"="			{ return ASSIGN; }
"->"        { return ARROW; }
","         { return COMMA; }
";"			{ return SEMICOLON; }
"."			{ return PERIOD; }
"&"			{ return AMPERSAND; }
"*"			{ return STAR; }

"{"		{ return OBRACE; }
"}"		{ return CBRACE; }
"["     { return OBRACKET; }
"]"     { return CBRACKET; }
"("		{ return OPAREN; }
")"		{ return CPAREN; }
"?"		{ return QUESTION; }
":"		{ return COLON; }

"+"			{ return ADD; }
"-"			{ return SUB; }
"/"			{ return DIV; }
"%"			{ return MOD; }

"++"		{ return INC_OP; }
"--"		{ return DEC_OP; }

"+="		{ return ADD_ASSIGN; }
"-="		{ return SUB_ASSIGN; }
"*="		{ return MUL_ASSIGN; }
"/="		{ return DIV_ASSIGN; }
"%="		{ return MOD_ASSIGN; }

"!"			{ return L_NOT; }
"&&"		{ return L_AND; }
"||"		{ return L_OR; }

">"			{ return GT_OP; }
"<"			{ return LT_OP; }
"=="		{ return EQ_OP; }
"!="		{ return NE_OP; }
"<="		{ return LE_OP; }
">="		{ return GE_OP; }

"~"			{ return B_NOT; }
"^"			{ return B_XOR; }
"|"			{ return B_OR; }
"<<"		{ return B_SL; }
">>"		{ return B_SR; }

"&="		{ return B_AND_ASSIGN; }
"|="		{ return B_OR_ASSIGN; }
"^="		{ return B_XOR_ASSIGN; }
"<<="		{ return B_SL_ASSIGN; }
">>="		{ return B_SR_ASSIGN; }

{identifier}		{ strcpy(yylval.sval, yytext); return IDENTIFIER; }
{integer_constant}	{ strcpy(yylval.sval, yytext); return INTEGER_CONSTANT; }
{floating_constant}	{ strcpy(yylval.sval, yytext); return FLOATING_CONSTANT; }
{string_literal}    { strcpy(yylval.sval, yytext); return STRING_LITERAL; }

.			{ strcpy(yylval.sval, yytext); return ERROR; }

%%
