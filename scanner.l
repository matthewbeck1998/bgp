%{
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include "parser.h"

using namespace std;

extern bool outputProductions;

int line = 1;
int column = 1;
int tab = 0;

void handleNewline();
void incrementColumn(int n);
void incrementTab(int n);

extern stringstream outputStream;
void scannerOutput(string s);
%}

%option noyywrap

letter                  [A-Za-z]
digit                   [0-9]
identifier              {letter}({letter}|{digit})*
integer_constant        {digit}+
character_constant      ['].[']
floating_constant       {digit}+\.{digit}+
string_literal          ["].*["]
line_comment            [/][/].*
block_comment           [/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]

productions_on          [@][p][+]
productions_off         [@][p][-]

%%

{productions_on}        {
                            outputProductions = true;
                        }

{productions_off}       {
                            outputProductions = false;
                        }

"auto"                  {                            
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return AUTO;
                        }
                    
"break"                 {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return BREAK;
                        }

"case"                  {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return CASE;
                        }

"char"                  {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return CHAR;
                        }

"const"                 {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return CONST;
                        }

"continue"              {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return CONTINUE;
                        }

"default"               {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return DEFAULT;
                        }

"do"                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return DO;
                        }

"double"                {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return DOUBLE;
                        }

"..."                   {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return ELLIPSIS;
                        }

"else"                  {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return ELSE;
                        }

"enum"                  {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return ENUM;
                        }

"extern"                {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return EXTERN;
                        }

"float"                 {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return FLOAT;
                        }

"for"                   {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return FOR;
                        }

"goto"                  {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return GOTO;
                        }

"if"                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return IF;
                        }

"int"                   {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return INT;
                        }

"long"                  {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return LONG;
                        }

"register"              {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return REGISTER;
                        }

"return"                {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return RETURN;
                        }

"short"                 {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return SHORT;
                        }

"signed"                {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return SIGNED;
                        }

"sizeof"                {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return SIZEOF;
                        }

"static"                {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return STATIC;
                        }

"struct"                {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return STRUCT;
                        }

"switch"                {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return SWITCH;
                        }

"typedef"               {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return TYPEDEF;
                        }

"union"                 {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return UNION;
                        }

"unsigned"              {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return UNSIGNED;
                        }

"void"                  {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return VOID;
                        }

"volatile"              {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return VOLATILE;
                        }

"while"                 {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return WHILE;
                        }

" "                     {
							incrementColumn(yyleng);
                        }

"\t"                    {
                            incrementTab(1);
                        }

"\n"                    {
                            handleNewline();
                        }

"="                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return ASSIGN;
                        }

"->"                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return ARROW;
                        }

","                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return COMMA;
                        }

";"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return SEMICOLON;
                        }

"."                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return PERIOD;
                        }

"&"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return AMPERSAND;
                        }

"*"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return STAR;
                        }

"{"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return OBRACE;
                        }

"}"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return CBRACE;
                        }

"["                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return OBRACKET;
                        }

"]"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return CBRACKET;
                        }

"("                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return OPAREN;
                        }

")"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return CPAREN;
                        }

"?"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return QUESTION;
                        }

":"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return COLON;
                        }

"+"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return ADD;
                        }

"-"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return SUB;
                        }

"/"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return DIV;
                        }

"%"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return MOD;
                        }

"++"                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return INC_OP;
                        }

"--"                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return DEC_OP;
                        }

"+="                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return ADD_ASSIGN;
                        }

"-="                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return SUB_ASSIGN;
                        }

"*="                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return MUL_ASSIGN;
                        }

"/="                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return DIV_ASSIGN;
                        }

"%="                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return MOD_ASSIGN;
                        }

"!"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return L_NOT;
                        }

"&&"                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return L_AND;
                        }

"||"                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return L_OR;
                        }

">"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return GT_OP;
                        }

"<"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return LT_OP;
                        }

"=="                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return EQ_OP;
                        }

"!="                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return NE_OP;
                        }

">="                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return GE_OP;
                        }

"<="                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return LE_OP;
                        }

"~"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return B_NOT;
                        }

"^"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return B_XOR;
                        }

"|"                     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return B_OR;
                        }

"<<"                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return B_SL;
                        }

">>"                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return B_SR;
                        }

"&="                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return B_AND_ASSIGN;
                        }

"|="                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return B_OR_ASSIGN;
                        }

"^="                    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return B_XOR_ASSIGN;
                        }

"<<="                   {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return B_SL_ASSIGN;
                        }

">>="                   {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            return B_SR_ASSIGN;
                        }

{identifier}            {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            strcpy(yylval.sval, yytext);
                            return IDENTIFIER;
                        }

{integer_constant}      {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            strcpy(yylval.sval, yytext);
                            return INTEGER_CONSTANT;
                        }

{character_constant}    {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            strcpy(yylval.sval, yytext);
                            return CHARACTER_CONSTANT;
                        }

{floating_constant}     {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            strcpy(yylval.sval, yytext);
                            return FLOATING_CONSTANT;
                        }

{string_literal}        {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            strcpy(yylval.sval, yytext);
                            return STRING_LITERAL;
                        }

{line_comment}          {}

{block_comment}         {}

.                       {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            strcpy(yylval.sval, yytext);
                        }

%%

inline void handleNewline()
{
    line++;
    column = 1;
    tab = 0;
}

inline void incrementColumn(int n)
{
    column += n;
}

inline void incrementTab(int n)
{
    tab += n;
}

void scannerOutput(string s)
{
    outputStream << "Token: " << s << endl;
}
