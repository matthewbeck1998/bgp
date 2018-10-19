%{
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include "parser.h"
#include "symbolTable.h"
using namespace std;

extern bool outputProductions;

int line = 1;
int column = 1;
int tab = 0;

void handleNewline();
void incrementColumn(int n);
void incrementTab(int n);
const char* textToStr(char* text, size_t text_len);

extern ofstream lexDebugOutput;
extern stringstream outputStream;
extern symbolTable symTable;
extern bool command_l;
void scannerOutput(char* text, size_t text_len);
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

symbol_table_dump		[@]

%%

"auto"                  {                            
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return AUTO;
                        }
                    
"break"                 {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return BREAK;
                        }

"case"                  {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return CASE;
                        }

"char"                  {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return CHAR;
                        }

"const"                 {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return CONST;
                        }

"continue"              {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return CONTINUE;
                        }

"default"               {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return DEFAULT;
                        }

"do"                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return DO;
                        }

"double"                {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return DOUBLE;
                        }

"..."                   {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return ELLIPSIS;
                        }

"else"                  {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return ELSE;
                        }

"enum"                  {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return ENUM;
                        }

"extern"                {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return EXTERN;
                        }

"float"                 {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return FLOAT;
                        }

"for"                   {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return FOR;
                        }

"goto"                  {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return GOTO;
                        }

"if"                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return IF;
                        }

"int"                   {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return INT;
                        }

"long"                  {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return LONG;
                        }

"register"              {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return REGISTER;
                        }

"return"                {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return RETURN;
                        }

"short"                 {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return SHORT;
                        }

"signed"                {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return SIGNED;
                        }

"sizeof"                {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return SIZEOF;
                        }

"static"                {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return STATIC;
                        }

"struct"                {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return STRUCT;
                        }

"switch"                {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return SWITCH;
                        }

"typedef"               {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return TYPEDEF;
                        }

"union"                 {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return UNION;
                        }

"unsigned"              {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return UNSIGNED;
                        }

"void"                  {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return VOID;
                        }

"volatile"              {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return VOLATILE;
                        }

"while"                 {
                            scannerOutput(yytext, yyleng);
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
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return ASSIGN;
                        }

"->"                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return ARROW;
                        }

","                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return COMMA;
                        }

";"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return SEMICOLON;
                        }

"."                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return PERIOD;
                        }

"&"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return AMPERSAND;
                        }

"*"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return STAR;
                        }

"{"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return OBRACE;
                        }

"}"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return CBRACE;
                        }

"["                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return OBRACKET;
                        }

"]"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return CBRACKET;
                        }

"("                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return OPAREN;
                        }

")"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return CPAREN;
                        }

"?"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return QUESTION;
                        }

":"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return COLON;
                        }

"+"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return ADD;
                        }

"-"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return SUB;
                        }

"/"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return DIV;
                        }

"%"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return MOD;
                        }

"++"                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return INC_OP;
                        }

"--"                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return DEC_OP;
                        }

"+="                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return ADD_ASSIGN;
                        }

"-="                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return SUB_ASSIGN;
                        }

"*="                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return MUL_ASSIGN;
                        }

"/="                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return DIV_ASSIGN;
                        }

"%="                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return MOD_ASSIGN;
                        }

"!"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return L_NOT;
                        }

"&&"                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return L_AND;
                        }

"||"                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return L_OR;
                        }

">"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return GT_OP;
                        }

"<"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return LT_OP;
                        }

"=="                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return EQ_OP;
                        }

"!="                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return NE_OP;
                        }

">="                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return GE_OP;
                        }

"<="                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return LE_OP;
                        }

"~"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return B_NOT;
                        }

"^"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return B_XOR;
                        }

"|"                     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return B_OR;
                        }

"<<"                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return B_SL;
                        }

">>"                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return B_SR;
                        }

"&="                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return B_AND_ASSIGN;
                        }

"|="                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return B_OR_ASSIGN;
                        }

"^="                    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return B_XOR_ASSIGN;
                        }

"<<="                   {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return B_SL_ASSIGN;
                        }

">>="                   {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            return B_SR_ASSIGN;
                        }

{identifier}            {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            strcpy(yylval.sval, textToStr(yytext, yyleng));
                            return IDENTIFIER;
                        }

{integer_constant}      {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            strcpy(yylval.sval, textToStr(yytext, yyleng));
                            return INTEGER_CONSTANT;
                        }

{character_constant}    {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            strcpy(yylval.sval, textToStr(yytext, yyleng));
                            return CHARACTER_CONSTANT;
                        }

{floating_constant}     {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            strcpy(yylval.sval, textToStr(yytext, yyleng));
                            return FLOATING_CONSTANT;
                        }

{string_literal}        {
                            scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
                            strcpy(yylval.sval, textToStr(yytext, yyleng));
                            return STRING_LITERAL;
                        }

{symbol_table_dump}		{
							scannerOutput(yytext, yyleng);
							incrementColumn(yyleng);
							ofstream symbolTableOut;
							symbolTableOut.open( "SymbolTableDump.txt" );
							if( symbolTableOut.good() )
							{
								symbolTableOut << symTable << endl << endl;
							}
						}

{productions_on}        {
                            outputProductions = true;
                        }

{productions_off}       {
                            outputProductions = false;
                        }

{comment}               {}

.                       {
                            scannerOutput(yytext, yyleng);
							//incrementColumn(yyleng); //Want the error to point to the start of the error.
                            strcpy(yylval.sval, textToStr(yytext, yyleng));
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

void scannerOutput(char* text, size_t text_len)
{
	string outputStr = textToStr(text, text_len);
	if( command_l and lexDebugOutput.good() )
	{
    	lexDebugOutput << "Token: " << outputStr << endl;
	}
}

const char* textToStr(char* text, size_t text_len)
{
	string st(text, text_len);
	return st.c_str();
}