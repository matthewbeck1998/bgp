%{
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include "ASTNode.h"

#include "parser.h"
#include "SymbolTable.h"
#include "SymbolNode.h"


using namespace std;

//Global for the @p++ and @p-- toggle.
extern bool outputProductions;

//Globals to hold line, columns, and tab.
int line = 1;
int column = 1;
int tab = 0;
//External bools to hook in with the command line arguments parsed in the yacc file.
extern bool command_l;
extern bool command_s;

//External streams for the final output and error
extern stringstream outputStream;
extern stringstream errorStream;

//External variable for the symbol table
extern SymbolTable st;
extern string lastNodeInserted;
extern bool inFunctionParameters;
extern string currentFunctionNode;
extern bool inFunctionPrototype;


extern bool sameArray;

extern int currentOffset;
bool globals = true;
//Functions to handle incrementing of globals.
/*
 *@name handleNewLine
 *@brief Keeps track of line, column, and tabs when a new line character is found
*/
void handleNewline();

/*
 *@name incrementColum
 *@brief increments the global column based on the int input
 *@param an integer n representing how many columns to increment
*/
void incrementColumn(int n);

/*
 *@name incrementTab
 *@brief increments the global tab based on the int input
 *@param an integer n representing how many tabs to increment
*/
void incrementTab(int n);

/*
 *@name scannerOutput
 *@brief Outputs the token name and source code to the lexDebugOutput output stream
 *@param a string outputStr that holds the source code to output
 *@param a string token_name that holds the token name to output
*/
void scannerOutput(string s, string token_name);

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

symbol_table_dump		[@][s]
productions_on          [@][p][+]
productions_off         [@][p][-]
%%

"auto"                  {                            
                            scannerOutput(yytext, "AUTO");
							incrementColumn(yyleng);
                            return AUTO;
                        }
                    
"break"                 {
                            scannerOutput(yytext, "BREAK");
							incrementColumn(yyleng);
                            return BREAK;
                        }

"case"                  {
                            scannerOutput(yytext, "CASE");
							incrementColumn(yyleng);
                            return CASE;
                        }

"char"                  {
                            scannerOutput(yytext, "CHAR");
							incrementColumn(yyleng);
                            return CHAR;
                        }

"const"                 {
                            scannerOutput(yytext, "CONST");
							incrementColumn(yyleng);
                            return CONST;
                        }

"continue"              {
                            scannerOutput(yytext, "CONTINUE");
							incrementColumn(yyleng);
                            return CONTINUE;
                        }

"default"               {
                            scannerOutput(yytext, "DEFAULT");
							incrementColumn(yyleng);
                            return DEFAULT;
                        }

"do"                    {
                            scannerOutput(yytext, "DO");
							incrementColumn(yyleng);
                            return DO;
                        }

"double"                {
                            scannerOutput(yytext, "DOUBLE");
							incrementColumn(yyleng);
                            return DOUBLE;
                        }

"..."                   {
                            scannerOutput(yytext, "...");
							incrementColumn(yyleng);
                            return ELLIPSIS;
                        }

"else"                  {
                            scannerOutput(yytext, "ELSE");
							incrementColumn(yyleng);
                            return ELSE;
                        }

"enum"                  {
                            scannerOutput(yytext, "ENUM");
							incrementColumn(yyleng);
                            return ENUM;
                        }

"extern"                {
                            scannerOutput(yytext, "EXTERN");
							incrementColumn(yyleng);
                            return EXTERN;
                        }

"float"                 {
                            scannerOutput(yytext, "FLOAT");
							incrementColumn(yyleng);
                            return FLOAT;
                        }

"for"                   {
                            scannerOutput(yytext, "FOR");
							incrementColumn(yyleng);
                            return FOR;
                        }

"goto"                  {
                            scannerOutput(yytext, "GOTO");
							incrementColumn(yyleng);
                            return GOTO;
                        }

"if"                    {
                            scannerOutput(yytext, "IF");
							incrementColumn(yyleng);
                            return IF;
                        }

"int"                   {
                            scannerOutput(yytext, "INT");
							incrementColumn(yyleng);
                            return INT;
                        }

"long"                  {
                            scannerOutput(yytext, "LONG");
							incrementColumn(yyleng);
                            return LONG;
                        }

"register"              {
                            scannerOutput(yytext, "REGISTER");
							incrementColumn(yyleng);
                            return REGISTER;
                        }

"return"                {
                            scannerOutput(yytext, "RETURN");
							incrementColumn(yyleng);
                            return RETURN;
                        }

"short"                 {
                            scannerOutput(yytext, "SHORT");
							incrementColumn(yyleng);
                            return SHORT;
                        }

"signed"                {
                            scannerOutput(yytext, "SIGNED");
							incrementColumn(yyleng);
                            return SIGNED;
                        }

"sizeof"                {
                            scannerOutput(yytext, "SIZEOF");
							incrementColumn(yyleng);
                            return SIZEOF;
                        }

"static"                {
                            scannerOutput(yytext, "STATIC");
							incrementColumn(yyleng);
                            return STATIC;
                        }

"struct"                {
                            scannerOutput(yytext, "STRUCT");
							incrementColumn(yyleng);
                            return STRUCT;
                        }

"switch"                {
                            scannerOutput(yytext, "SWITCH");
							incrementColumn(yyleng);
                            return SWITCH;
                        }

"typedef"               {
                            scannerOutput(yytext, "TYPEDEF");
							incrementColumn(yyleng);
                            return TYPEDEF;
                        }

"union"                 {
                            scannerOutput(yytext, "UNION");
							incrementColumn(yyleng);
                            return UNION;
                        }

"unsigned"              {
                            scannerOutput(yytext, "UNSIGNED");
							incrementColumn(yyleng);
                            return UNSIGNED;
                        }

"void"                  {
                            scannerOutput(yytext, "VOID");
							incrementColumn(yyleng);
                            return VOID;
                        }

"volatile"              {
                            scannerOutput(yytext, "VOLATILE");
							incrementColumn(yyleng);
                            return VOLATILE;
                        }

"while"                 {
                            scannerOutput(yytext, "WHILE");
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

"\r"                    {
                        }

"="                     {
                            scannerOutput(yytext, "ASSIGN");
							incrementColumn(yyleng);
                            return ASSIGN;
                        }

"->"                    {
                            scannerOutput(yytext, "ARROW");
							incrementColumn(yyleng);
                            return ARROW;
                        }

","                     {
                            sameArray = false;
                            scannerOutput(yytext, "COMMA");
							incrementColumn(yyleng);
                            return COMMA;
                        }

";"                     {
                            if (inFunctionPrototype)
                            {
                                st.popLevel();
                            }
                            scannerOutput(yytext, "SEMICOLON");
							incrementColumn(yyleng);
                            return SEMICOLON;
                        }

"."                     {
                            scannerOutput(yytext, "PERIOD");
							incrementColumn(yyleng);
                            return PERIOD;
                        }

"&"                     {
                            scannerOutput(yytext, "AMPERSAND");
							incrementColumn(yyleng);
                            return AMPERSAND;
                        }

"*"                     {
                            scannerOutput(yytext, "STAR");
							incrementColumn(yyleng);
                            return STAR;
                        }

"{"                     {
							if (inFunctionPrototype)
                            {
                                inFunctionPrototype = false;
                            }

							if( command_s )
							{
								outputStream << st;
							}
                            scannerOutput(yytext, "OBRACE");
							incrementColumn(yyleng);
                            st.pushLevel();
							st.setInsertMode(false);
                            return OBRACE;
                        }

"}"                     {
							if( command_s )
							{
								outputStream << st;
							}
                            scannerOutput(yytext, "CBRACE");
							incrementColumn(yyleng);
                            st.popLevel();
							st.setInsertMode(false);
                            return CBRACE;
                        }

"["                     {
                            scannerOutput(yytext, "OBRACKET");
							incrementColumn(yyleng);
                            return OBRACKET;
                        }

"]"                     {
                            scannerOutput(yytext, "CBRACKET");
							incrementColumn(yyleng);
                            return CBRACKET;
                        }

"("                     {
                            scannerOutput(yytext, "OPAREN");
							incrementColumn(yyleng);
							if(globals)
                            {
                                currentOffset = 4;
                                globals = false;
                            }
                            if (st.getInsertMode())
                            {
                                inFunctionParameters = true;
                                auto functionPair = st.searchTop(lastNodeInserted);

                                if (functionPair.first == -1)
                                {
                                    return ERROR;
                                }

                                functionPair.second->second.setIsFunction(true);
                                currentFunctionNode = lastNodeInserted;
                                st.pushLevel();
                            }
                            return OPAREN;
                        }

")"                     {
                            if (inFunctionParameters)
                            {
                                inFunctionParameters = false;
                                currentFunctionNode = "";
                            }

                            scannerOutput(yytext, "CPAREN");
							incrementColumn(yyleng);
                            return CPAREN;
                        }

"?"                     {
                            scannerOutput(yytext, "QUESTION");
							incrementColumn(yyleng);
                            return QUESTION;
                        }

":"                     {
                            scannerOutput(yytext, "COLON");
							incrementColumn(yyleng);
                            return COLON;
                        }

"+"                     {
                            scannerOutput(yytext, "ADD");
							incrementColumn(yyleng);
                            return ADD;
                        }

"-"                     {
                            scannerOutput(yytext, "SUB");
							incrementColumn(yyleng);
                            return SUB;
                        }

"/"                     {
                            scannerOutput(yytext, "DIV");
							incrementColumn(yyleng);
                            return DIV;
                        }

"%"                     {
                            scannerOutput(yytext, "MOD");
							incrementColumn(yyleng);
                            return MOD;
                        }

"++"                    {
                            scannerOutput(yytext, "INC_OP");
							incrementColumn(yyleng);
                            return INC_OP;
                        }

"--"                    {
                            scannerOutput(yytext, "DEC_OP");
							incrementColumn(yyleng);
                            return DEC_OP;
                        }

"+="                    {
                            scannerOutput(yytext, "ADD_ASSIGN");
							incrementColumn(yyleng);
                            return ADD_ASSIGN;
                        }

"-="                    {
                            scannerOutput(yytext, "SUB_ASSIGN");
							incrementColumn(yyleng);
                            return SUB_ASSIGN;
                        }

"*="                    {
                            scannerOutput(yytext, "MUL_ASSIGN");
							incrementColumn(yyleng);
                            return MUL_ASSIGN;
                        }

"/="                    {
                            scannerOutput(yytext, "DIV_ASSIGN");
							incrementColumn(yyleng);
                            return DIV_ASSIGN;
                        }

"%="                    {
                            scannerOutput(yytext, "MOD_ASSIGN");
							incrementColumn(yyleng);
                            return MOD_ASSIGN;
                        }

"!"                     {
                            scannerOutput(yytext, "L_NOT");
							incrementColumn(yyleng);
                            return L_NOT;
                        }

"&&"                    {
                            scannerOutput(yytext, "L_AND");
							incrementColumn(yyleng);
                            return L_AND;
                        }

"||"                    {
                            scannerOutput(yytext, "L_OR");
							incrementColumn(yyleng);
                            return L_OR;
                        }

">"                     {
                            scannerOutput(yytext, "GT_OP");
							incrementColumn(yyleng);
                            return GT_OP;
                        }

"<"                     {
                            scannerOutput(yytext, "LT_OP");
							incrementColumn(yyleng);
                            return LT_OP;
                        }

"=="                    {
                            scannerOutput(yytext, "EQ_OP");
							incrementColumn(yyleng);
                            return EQ_OP;
                        }

"!="                    {
                            scannerOutput(yytext, "NE_OP");
							incrementColumn(yyleng);
                            return NE_OP;
                        }

">="                    {
                            scannerOutput(yytext, "GE_OP");
							incrementColumn(yyleng);
                            return GE_OP;
                        }

"<="                    {
                            scannerOutput(yytext, "LE_OP");
							incrementColumn(yyleng);
                            return LE_OP;
                        }

"~"                     {
                            scannerOutput(yytext, "B_NOT");
							incrementColumn(yyleng);
                            return B_NOT;
                        }

"^"                     {
                            scannerOutput(yytext, "B_XOR");
							incrementColumn(yyleng);
                            return B_XOR;
                        }

"|"                     {
                            scannerOutput(yytext, "B_OR");
							incrementColumn(yyleng);
                            return B_OR;
                        }

"<<"                    {
                            scannerOutput(yytext, "B_SL");
							incrementColumn(yyleng);
                            return B_SL;
                        }

">>"                    {
                            scannerOutput(yytext, "B_SR");
							incrementColumn(yyleng);
                            return B_SR;
                        }

"&="                    {
                            scannerOutput(yytext, "B_AND_ASSIGN");
							incrementColumn(yyleng);
                            return B_AND_ASSIGN;
                        }

"|="                    {
                            scannerOutput(yytext, "B_OR_ASSIGN");
							incrementColumn(yyleng);
                            return B_OR_ASSIGN;
                        }

"^="                    {
                            scannerOutput(yytext, "B_XOR_ASSIGN");
							incrementColumn(yyleng);
                            return B_XOR_ASSIGN;
                        }

"<<="                   {
                            scannerOutput(yytext, "B_SL_ASSIGN");
							incrementColumn(yyleng);
                            return B_SL_ASSIGN;
                        }

">>="                   {
                            scannerOutput(yytext, "B_SR_ASSIGN");
							incrementColumn(yyleng);
                            return B_SR_ASSIGN;
                        }

{identifier}            {
							if( yyleng > 253 )
							{
								return ERROR;//ID too long
							}
                            scannerOutput(yytext, "IDENTIFIER");
							incrementColumn(yyleng);
                            strcpy(yylval.sval, yytext);
                            return IDENTIFIER;
                        }

{integer_constant}      {
                            scannerOutput(yytext, "INTEGER_CONSTANT");
							if( yyleng > 10 or (yyleng == 10 and strcmp(yytext, "2147483647") > 0) )
							{
								
								errorStream << "WARNING: Integer " << yytext << " too big to be held in an int" << endl;
							}
							incrementColumn(yyleng);
                            strcpy(yylval.sval, yytext);
                            return INTEGER_CONSTANT;
                        }

{character_constant}    {
                            scannerOutput(yytext, "CHARACTER_CONSTANT");
							incrementColumn(yyleng);
                            strcpy(yylval.sval, yytext);
                            return CHARACTER_CONSTANT;
                        }

{floating_constant}     {
							try//Test to check if yytext is a valid float.
							{
								stof(yytext);
							}
							catch(...)
							{
								errorStream << "WARNING: float " << yytext << " too big to be held in an float" << endl;
							}
							
                            scannerOutput(yytext, "FLOATING_CONSTANT");
							incrementColumn(yyleng);
                            strcpy(yylval.sval, yytext);
                            return FLOATING_CONSTANT;
                        }

{string_literal}        {
                            scannerOutput(yytext, "STRING_LITERAL");
							incrementColumn(yyleng);
                            strcpy(yylval.sval, yytext);
                            return STRING_LITERAL;
                        }

{symbol_table_dump}		{
							scannerOutput(yytext, "SYMBOL_TABLE_DUMP");
							incrementColumn(yyleng);
                            outputStream << st;
						}
						
{productions_on}        {
                            outputProductions = true;
                        }

{productions_off}       {
                            outputProductions = false;
                        }

{comment}               {
							scannerOutput(yytext, "COMMENT");
						}

.                       {
                            scannerOutput(yytext, "ERROR");
							//incrementColumn(yyleng); //Want the error to point to the start of the error.
                            strcpy(yylval.sval, yytext);
                            return ERROR;
                        }

%%


/*
 *@name handleNewLine
 *@brief Keeps track of line, column, and tabs when a new line character is found
*/
inline void handleNewline()
{
    line++;
    column = 1;
    tab = 0;
}

/*
 *@name incrementColum
 *@brief increments the global column based on the int input
 *@param an integer n representing how many columns to increment
*/
inline void incrementColumn(int n)
{
    column += n;
}

/*
 *@name incrementTab
 *@brief increments the global tab based on the int input
 *@param an integer n representing how many tabs to increment
*/
inline void incrementTab(int n)
{
    tab += n;
}

/*
 *@name scannerOutput
 *@brief Outputs the token name and source code to the lexDebugOutput output stream
 *@param a string outputStr that holds the source code to output
 *@param a string token_name that holds the token name to output
*/
void scannerOutput(string outputStr, string token_name)
{
	if( command_l )
	{
    	outputStream << "Token: " << token_name << endl << "\tSource: " << outputStr << endl;
	}
}
