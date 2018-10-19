%{
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include "parser.h"
#include "symbolTable.h"
#include "node.h"

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

symbolTable st;
string nodeIdentifier;
int nodeType = 3;
%}

%option noyywrap

letter                  [A-Za-z]
dec                     [0-9]
oct                     [0-7]
hex                     [0-9A-Fa-f]

identifier              {letter}({letter}|{dec})*

integer_constant        {decimal_integer}|{octal_integer}|{hexadecimal_integer}
decimal_integer         {dec}+
octal_integer           [0]{oct}+
hexadecimal_integer     [0][x]{hex}+

character_constant      {escaped_character}|{octal_character}|{hexadecimal_character}|{regular_character}
regular_character       ['].[']
escaped_character       ['][\\].[']
octal_character         ['][\\]{oct}{oct}{oct}[']
hexadecimal_character   {hexadecimal_character_2}|{hexadecimal_character_4}|{hexadecimal_character_8}
hexadecimal_character_2 ['][\\][x]{hex}+[']
hexadecimal_character_4 ['][\\][u]{hex}{hex}{hex}{hex}[']
hexadecimal_character_8 ['][\\][U]{hex}{hex}{hex}{hex}{hex}{hex}{hex}{hex}[']

floating_constant       {dec}+\.{dec}+

string_literal          ["].*["]

comment                 {line_comment}|{block_comment}
line_comment            [/][/].*
block_comment           [/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]

productions_on          [@][p][+]
productions_off         [@][p][-]

%%

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
                            st.setInsertMode(true);
                            cout << "INSERT MODE" << endl;
                            nodeType = 3;
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
                            st.setInsertMode(false);
                            cout << "LOOKUP MODE" << endl;
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
                            st.setInsertMode(false);
                            cout << "LOOKUP MODE" << endl;
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
                            cout << "CURRENT: " << (st.getInsertMode() ? "INSERT" : "LOOKUP") << endl;
                            if (st.getInsertMode())
                            {
                                st.insert(node(nodeIdentifier, line, nodeType));
                                nodeType = 3;
                            }
                            else
                            {
                                st.searchTop(nodeIdentifier);
                            }
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

{productions_on}        {
                            outputProductions = true;
                        }

{productions_off}       {
                            outputProductions = false;
                        }

{comment}               {}

.                       {
                            scannerOutput(yytext);
							incrementColumn(yyleng);
                            strcpy(yylval.sval, yytext);
                            return ERROR;
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
