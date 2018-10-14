%{
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

extern int yylex();
extern int yyparse();
void yyerror(const char* s);
extern FILE* yyin;

extern int line_num;
extern int column_num;
extern int tab_num;

ofstream outputStream;
void output(string s);
%}

%union
{
    char sval[255];
}

%define parse.error verbose

%token <sval> AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE
%token <sval> ELLIPSIS ELSE ENUM EXTERN FLOAT FOR GOTO IF INT LONG
%token <sval> REGISTER RETURN SHORT SIGNED SIZEOF STATIC STRUCT SWITCH
%token <sval> TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE

%token <sval> AMPERSAND ARROW ASSIGN COMMA PERIOD SEMICOLON STAR
%token <sval> OBRACE CBRACE OBRACKET CBRACKET OPAREN CPAREN QUESTION COLON
%token <sval> ADD SUB DIV MOD
%token <sval> INC_OP DEC_OP
%token <sval> ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token <sval> L_AND L_OR L_NOT
%token <sval> EQ_OP NE_OP GT_OP LT_OP GE_OP LE_OP
%token <sval> B_NOT B_OR B_XOR B_SL B_SR
%token <sval> B_AND_ASSIGN B_OR_ASSIGN B_XOR_ASSIGN B_SL_ASSIGN B_SR_ASSIGN

%token <sval> CHARACTER_CONSTANT ENUMERATION_CONSTANT FLOATING_CONSTANT INTEGER_CONSTANT
%token <sval> STRING_LITERAL TYPEDEF_NAME IDENTIFIER
%token <sval> ERROR

%%

translation_unit
	: external_declaration { output("translation_unit -> external_declaration"); }
	| translation_unit external_declaration { output("translation_unit -> translation_unit external_declaration"); }
	;

external_declaration
	: function_definition { output("external_declaration -> function_definition"); }
	| declaration { output("external_declaration -> declaration"); }
	;

function_definition
	: declarator compound_statement { output("function_definition -> declarator compound_statement"); }
	| declarator declaration_list compound_statement { output("function_definition -> declarator declaration_list compound_statement"); }
	| declaration_specifiers declarator compound_statement { output("function_definition -> declaration_specifiers declarator compound_statement"); }
	| declaration_specifiers declarator declaration_list compound_statement { output("function_definition -> declaration_specifiers declarator declaration_list compound_statement"); }
	;

declaration
	: declaration_specifiers SEMICOLON { output("declaration -> declaration_specifiers SEMICOLON"); }
	| declaration_specifiers init_declarator_list SEMICOLON { output("declaration -> declaration_specifiers init_declarator_list SEMICOLON"); }
	;

declaration_list
	: declaration { output("declaration_list -> declaration"); }
	| declaration_list declaration { output("declaration_list -> declaration_list declaration"); }
	;

declaration_specifiers
	: storage_class_specifier { output("declaration_specifiers -> storage_class_specifier"); }
	| storage_class_specifier declaration_specifiers { output("declaration_specifiers -> storage_class_specifier declaration_specifiers"); }
	| type_specifier { output("declaration_specifiers -> type_specifier"); }
	| type_specifier declaration_specifiers { output("declaration_specifiers -> type_specifier declaration_specifiers"); }
	| type_qualifier { output("declaration_specifiers -> type_qualifier"); }
	| type_qualifier declaration_specifiers { output("declaration_specifiers -> type_qualifier declaration_specifiers"); }
	;

storage_class_specifier
	: AUTO { output("storage_class_specifier -> AUTO"); }
	| REGISTER { output("storage_class_specifier -> REGISTER"); }
	| STATIC { output("storage_class_specifier -> STATIC"); }
	| EXTERN { output("storage_class_specifier -> EXTERN"); }
	| TYPEDEF { output("storage_class_specifier -> TYPEDEF"); }
	;

type_specifier
	: VOID { output("type_specifier -> VOID"); }
	| CHAR { output("type_specifier -> CHAR"); }
	| SHORT { output("type_specifier -> SHORT"); }
	| INT { output("type_specifier -> INT"); }
	| LONG { output("type_specifier -> LONG"); }
	| FLOAT { output("type_specifier -> FLOAT"); }
	| DOUBLE { output("type_specifier -> DOUBLE"); }
	| SIGNED { output("type_specifier -> SIGNED"); }
	| UNSIGNED { output("type_specifier -> UNSIGNED"); }
	| struct_or_union_specifier { output("type_specifier -> struct_or_union_specifier"); }
	| enum_specifier { output("type_specifier -> enum_specifier"); }
	| TYPEDEF_NAME { output("type_specifier -> TYPEDEF_NAME"); }
	;

type_qualifier
	: CONST { output("type_qualifier -> CONST"); }
	| VOLATILE { output("type_qualifier -> VOLATILE"); }
	;

struct_or_union_specifier
	: struct_or_union identifier OBRACE struct_declaration_list CBRACE { output("struct_or_union_specifier -> struct_or_union identifier OBRACE struct_declaration_list CBRACE"); }
	| struct_or_union OBRACE struct_declaration_list CBRACE { output("struct_or_union_specifier -> struct_or_union OBRACE struct_declaration_list CBRACE"); }
	| struct_or_union identifier { output("struct_or_union_specifier -> struct_or_union identifier"); }
	;

struct_or_union
	: STRUCT { output("struct_or_union -> STRUCT"); }
	| UNION { output("struct_or_union -> UNION"); }
	;

struct_declaration_list
	: struct_declaration { output("struct_declaration_list -> struct_declaration"); }
	| struct_declaration_list struct_declaration { output("struct_declaration_list -> struct_declaration_list struct_declaration"); }
	;

init_declarator_list
	: init_declarator { output("init_declarator_list -> init_declarator"); }
	| init_declarator_list COMMA init_declarator { output("init_declarator_list -> init_declarator_list COMMA init_declarator"); }
	;

init_declarator
	: declarator { output("init_declarator -> declarator"); }
	| declarator ASSIGN initializer { output("init_declarator -> declarator ASSIGN initializer"); }
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list SEMICOLON { output("struct_declaration -> specifier_qualifier_list struct_declarator_list SEMICOLON"); }
	;

specifier_qualifier_list
	: type_specifier { output("specifier_qualifier_list -> type_specifier"); }
	| type_specifier specifier_qualifier_list { output("specifier_qualifier_list -> type_specifier specifier_qualifier_list"); }
	| type_qualifier { output("specifier_qualifier_list -> type_qualifier"); }
	| type_qualifier specifier_qualifier_list { output("specifier_qualifier_list -> type_qualifier specifier_qualifier_list"); }
	;

struct_declarator_list
	: struct_declarator { output("struct_declarator_list -> struct_declarator"); }
	| struct_declarator_list COMMA struct_declarator { output("struct_declarator_list -> struct_declarator_list COMMA struct_declarator"); }
	;

struct_declarator
	: declarator { output("struct_declarator -> declarator"); }
	| COLON constant_expression { output("struct_declarator -> COLON constant_expression"); }
	| declarator COLON constant_expression { output("struct_declarator -> declarator COLON constant_expression"); }
	;

enum_specifier
	: ENUM OBRACE enumerator_list CBRACE { output("enum_specifier -> ENUM OBRACE enumerator_list CBRACE"); }
	| ENUM identifier OBRACE enumerator_list CBRACE { output("enum_specifier -> ENUM identifier OBRACE enumerator_list CBRACE"); }
	| ENUM identifier { output("enum_specifier -> ENUM identifier"); }
	;

enumerator_list
	: enumerator { output("enumerator_list -> enumerator"); }
	| enumerator_list COMMA enumerator { output("enumerator_list -> enumerator_list COMMA enumerator"); }
	;

enumerator
	: identifier { output("enumerator -> identifier"); }
	| identifier ASSIGN constant_expression { output("enumerator -> identifier ASSIGN constant_expression"); }
	;

declarator
	: direct_declarator { output("declarator -> direct_declarator"); }
	| pointer direct_declarator { output("declarator -> pointer direct_declarator"); }
	;

direct_declarator
	: identifier { output("direct_declarator -> identifier"); }
	| OPAREN declarator CPAREN { output("direct_declarator -> OPAREN declarator CPAREN"); }
	| direct_declarator OBRACKET CBRACKET { output("direct_declarator -> direct_declarator OBRACKET CBRACKET"); }
	| direct_declarator OBRACKET constant_expression CBRACKET { output("direct_declarator -> direct_declarator OBRACKET constant_expression CBRACKET"); }
	| direct_declarator OPAREN CPAREN { output("direct_declarator -> direct_declarator OPAREN CPAREN"); }
	| direct_declarator OPAREN parameter_type_list CPAREN { output("direct_declarator -> direct_declarator OPAREN parameter_type_list CPAREN"); }
	| direct_declarator OPAREN identifier_list CPAREN { output("direct_declarator -> direct_declarator OPAREN identifier_list CPAREN"); }
	;

pointer
	: STAR { output("pointer -> STAR"); }
	| STAR type_qualifier_list { output("pointer -> STAR type_qualifier_list"); }
	| STAR pointer { output("pointer -> STAR pointer"); }
	| STAR type_qualifier_list pointer { output("pointer -> STAR type_qualifier_list pointer"); }
	;

type_qualifier_list
	: type_qualifier { output("type_qualifier_list -> type_qualifier"); }
	| type_qualifier_list type_qualifier { output("type_qualifier_list -> type_qualifier_list type_qualifier"); }
	;

parameter_type_list
	: parameter_list { output("parameter_type_list -> parameter_list"); }
	| parameter_list COMMA ELLIPSIS { output("parameter_type_list -> parameter_list COMMA ELLIPSIS"); }
	;

parameter_list
	: parameter_declaration { output("parameter_list -> parameter_declaration"); }
	| parameter_list COMMA parameter_declaration { output("parameter_list -> parameter_list COMMA parameter_declaration"); }
	;

parameter_declaration
	: declaration_specifiers declarator { output("parameter_declaration -> declaration_specifiers declarator"); }
	| declaration_specifiers { output("parameter_declaration -> declaration_specifiers"); }
	| declaration_specifiers abstract_declarator { output("parameter_declaration -> declaration_specifiers abstract_declarator"); }
	;

identifier_list
	: identifier { output("identifier_list -> identifier"); }
	| identifier_list COMMA identifier { output("identifier_list -> identifier_list COMMA identifier"); }
	;

initializer
	: assignment_expression { output("initializer -> assignment_expression"); }
	| OBRACE initializer_list CBRACE { output("initializer -> OBRACE initializer_list CBRACE"); }
	| OBRACE initializer_list COMMA CBRACE { output("initializer -> OBRACE initializer_list COMMA CBRACE"); }
	;

initializer_list
	: initializer { output("initializer_list -> initializer"); }
	| initializer_list COMMA initializer { output("initializer_list -> initializer_list COMMA initializer"); }
	;

type_name
	: specifier_qualifier_list { output("type_name -> specifier_qualifier_list"); }
	| specifier_qualifier_list abstract_declarator { output("type_name -> specifier_qualifier_list abstract_declarator"); }
	;

abstract_declarator
	: pointer { output("abstract_declarator -> pointer"); }
	| direct_abstract_declarator { output("abstract_declarator -> direct_abstract_declarator"); }
	| pointer direct_abstract_declarator { output("abstract_declarator -> pointer direct_abstract_declarator"); }
	;

direct_abstract_declarator
	: OPAREN abstract_declarator CPAREN { output("direct_abstract_declarator -> OPAREN abstract_declarator CPAREN"); }
	| OBRACKET CBRACKET { output("direct_abstract_declarator -> OBRACKET CBRACKET"); }
	| OBRACKET constant_expression CBRACKET { output("direct_abstract_declarator -> OBRACKET constant_expression CBRACKET"); }
	| direct_abstract_declarator OBRACKET CBRACKET { output("direct_abstract_declarator -> direct_abstract_declarator OBRACKET CBRACKET"); }
	| direct_abstract_declarator OBRACKET constant_expression CBRACKET { output("direct_abstract_declarator -> direct_abstract_declarator OBRACKET constant_expression CBRACKET"); }
	| OPAREN CPAREN { output("direct_abstract_declarator -> OPAREN CPAREN"); }
	| OPAREN parameter_type_list CPAREN { output("direct_abstract_declarator -> OPAREN parameter_type_list CPAREN"); }
	| direct_abstract_declarator OPAREN CPAREN { output("direct_abstract_declarator -> direct_abstract_declarator OPAREN CPAREN"); }
	| direct_abstract_declarator OPAREN parameter_type_list CPAREN { output("direct_abstract_declarator -> direct_abstract_declarator OPAREN parameter_type_list CPAREN"); }
	;

statement
	: labeled_statement { output("statement -> labeled_statement"); }
	| compound_statement { output("statement -> compound_statement"); }
	| expression_statement { output("statement -> expression_statement"); }
	| selection_statement { output("statement -> selection_statement"); }
	| iteration_statement { output("statement -> iteration_statement"); }
	| jump_statement { output("statement -> jump_statement"); }
	;

labeled_statement
	: identifier COLON statement { output("labeled_statement -> identifier COLON statement"); }
	| CASE constant_expression COLON statement { output("labeled_statement -> CASE constant_expression COLON statement"); }
	| DEFAULT COLON statement { output("labeled_statement -> DEFAULT COLON statement"); }
	;

expression_statement
	: SEMICOLON { output("expression_statement -> SEMICOLON"); }
	| expression SEMICOLON { output("expression_statement -> expression SEMICOLON"); }
	;

compound_statement
	: OBRACE CBRACE { output("compound_statement -> OBRACE CBRACE"); }
	| OBRACE statement_list CBRACE { output("compound_statement -> OBRACE statement_list CBRACE"); }
	| OBRACE declaration_list CBRACE { output("compound_statement -> OBRACE declaration_list CBRACE"); }
	| OBRACE declaration_list statement_list CBRACE { output("compound_statement -> OBRACE declaration_list statement_list CBRACE"); }
	;

statement_list
	: statement { output("statement_list -> statement"); }
	| statement_list statement { output("statement_list -> statement_list statement"); }
	;

selection_statement
	: IF OPAREN expression CPAREN statement { output("selection_statement -> IF OPAREN expression CPAREN statement"); }
	| IF OPAREN expression CPAREN statement ELSE statement { output("selection_statement -> IF OPAREN expression CPAREN statement ELSE statement"); }
	| SWITCH OPAREN expression CPAREN statement { output("selection_statement -> SWITCH OPAREN expression CPAREN statement"); }
	;

iteration_statement
	: WHILE OPAREN expression CPAREN statement { output("iteration_statement -> WHILE OPAREN expression CPAREN statement"); }
	| DO statement WHILE OPAREN expression CPAREN SEMICOLON { output("iteration_statement -> DO statement WHILE OPAREN expression CPAREN SEMICOLON"); }
	| FOR OPAREN SEMICOLON SEMICOLON CPAREN statement { output("iteration_statement -> FOR OPAREN SEMICOLON SEMICOLON CPAREN statement"); }
	| FOR OPAREN SEMICOLON SEMICOLON expression CPAREN statement { output("iteration_statement -> FOR OPAREN SEMICOLON SEMICOLON expression CPAREN statement"); }
	| FOR OPAREN SEMICOLON expression SEMICOLON CPAREN statement { output("iteration_statement -> FOR OPAREN SEMICOLON expression SEMICOLON CPAREN statement"); }
	| FOR OPAREN SEMICOLON expression SEMICOLON expression CPAREN statement { output("iteration_statement -> FOR OPAREN SEMICOLON expression SEMICOLON expression CPAREN statement"); }
	| FOR OPAREN expression SEMICOLON SEMICOLON CPAREN statement { output("iteration_statement -> FOR OPAREN expression SEMICOLON SEMICOLON CPAREN statement"); }
	| FOR OPAREN expression SEMICOLON SEMICOLON expression CPAREN statement { output("iteration_statement -> FOR OPAREN expression SEMICOLON SEMICOLON expression CPAREN statement"); }
	| FOR OPAREN expression SEMICOLON expression SEMICOLON CPAREN statement { output("iteration_statement -> FOR OPAREN expression SEMICOLON expression SEMICOLON CPAREN statement"); }
	| FOR OPAREN expression SEMICOLON expression SEMICOLON expression CPAREN statement { output("iteration_statement -> FOR OPAREN expression SEMICOLON expression SEMICOLON expression CPAREN statement"); }
	;

jump_statement
	: GOTO identifier SEMICOLON { output("jump_statement -> GOTO identifier SEMICOLON"); }
	| CONTINUE SEMICOLON { output("jump_statement -> CONTINUE SEMICOLON"); }
	| BREAK SEMICOLON { output("jump_statement -> BREAK SEMICOLON"); }
	| RETURN SEMICOLON { output("jump_statement -> RETURN SEMICOLON"); }
	| RETURN expression SEMICOLON { output("jump_statement -> RETURN expression SEMICOLON"); }
	;

expression
	: assignment_expression { output("expression -> assignment_expression"); }
	| expression COMMA assignment_expression { output("expression -> expression COMMA assignment_expression"); }
	;

assignment_expression
	: conditional_expression { output("assignment_expression -> conditional_expression"); }
	| unary_expression assignment_operator assignment_expression { output("assignment_expression -> unary_expression assignment_operator assignment_expression"); }
	;

assignment_operator
	: ASSIGN { output("assignment_operator -> ASSIGN"); }
	| MUL_ASSIGN { output("assignment_operator -> MUL_ASSIGN"); }
	| DIV_ASSIGN { output("assignment_operator -> DIV_ASSIGN"); }
	| MOD_ASSIGN { output("assignment_operator -> MOD_ASSIGN"); }
	| ADD_ASSIGN { output("assignment_operator -> ADD_ASSIGN"); }
	| SUB_ASSIGN { output("assignment_operator -> SUB_ASSIGN"); }
	| B_SL_ASSIGN { output("assignment_operator -> B_SL_ASSIGN"); }
	| B_SR_ASSIGN { output("assignment_operator -> B_SR_ASSIGN"); }
	| B_AND_ASSIGN { output("assignment_operator -> B_AND_ASSIGN"); }
	| B_XOR_ASSIGN { output("assignment_operator -> B_XOR_ASSIGN"); }
	| B_OR_ASSIGN { output("assignment_operator -> B_OR_ASSIGN"); }
	;

conditional_expression
	: logical_or_expression { output("conditional_expression -> logical_or_expression"); }
	| logical_or_expression QUESTION expression COLON conditional_expression { output("conditional_expression -> logical_or_expression QUESTION expression COLON conditional_expression"); }
	;

constant_expression
	: conditional_expression { output("constant_expression -> conditional_expression"); }
	;

logical_or_expression
	: logical_and_expression { output("logical_or_expression -> logical_and_expression"); }
	| logical_or_expression L_OR logical_and_expression { output("logical_or_expression -> logical_or_expression L_OR logical_and_expression"); }
	;

logical_and_expression
	: inclusive_or_expression { output("logical_and_expression -> inclusive_or_expression"); }
	| logical_and_expression L_AND inclusive_or_expression { output("logical_and_expression -> logical_and_expression L_AND inclusive_or_expression"); }
	;

inclusive_or_expression
	: exclusive_or_expression { output("inclusive_or_expression -> exclusive_or_expression"); }
	| inclusive_or_expression B_OR exclusive_or_expression { output("inclusive_or_expression -> inclusive_or_expression B_OR exclusive_or_expression"); }
	;

exclusive_or_expression
	: and_expression { output("exclusive_or_expression -> and_expression"); }
	| exclusive_or_expression B_XOR and_expression { output("exclusive_or_expression -> exclusive_or_expression B_XOR and_expression"); }
	;

and_expression
	: equality_expression { output("and_expression -> equality_expression"); }
	| and_expression AMPERSAND equality_expression { output("and_expression -> and_expression AMPERSAND equality_expression"); }
	;

equality_expression
	: relational_expression { output("equality_expression -> relational_expression"); }
	| equality_expression EQ_OP relational_expression { output("equality_expression -> equality_expression EQ_OP relational_expression"); }
	| equality_expression NE_OP relational_expression { output("equality_expression -> equality_expression NE_OP relational_expression"); }
	;

relational_expression
	: shift_expression { output("relational_expression -> shift_expression"); }
	| relational_expression LT_OP shift_expression { output("relational_expression -> relational_expression LT_OP shift_expression"); }
	| relational_expression GT_OP shift_expression { output("relational_expression -> relational_expression GT_OP shift_expression"); }
	| relational_expression LE_OP shift_expression { output("relational_expression -> relational_expression LE_OP shift_expression"); }
	| relational_expression GE_OP shift_expression { output("relational_expression -> relational_expression GE_OP shift_expression"); }
	;

shift_expression
	: additive_expression { output("shift_expression -> additive_expression"); }
	| shift_expression B_SL additive_expression { output("shift_expression -> shift_expression B_SL additive_expression"); }
	| shift_expression B_SR additive_expression { output("shift_expression -> shift_expression B_SR additive_expression"); }
	;

additive_expression
	: multiplicative_expression { output("additive_expression -> multiplicative_expression"); }
	| additive_expression ADD multiplicative_expression { output("additive_expression -> additive_expression ADD multiplicative_expression"); }
	| additive_expression SUB multiplicative_expression { output("additive_expression -> additive_expression SUB multiplicative_expression"); }
	;

multiplicative_expression
	: cast_expression { output("multiplicative_expression -> cast_expression"); }
	| multiplicative_expression STAR cast_expression { output("multiplicative_expression -> multiplicative_expression STAR cast_expression"); }
	| multiplicative_expression DIV cast_expression { output("multiplicative_expression -> multiplicative_expression DIV cast_expression"); }
	| multiplicative_expression MOD cast_expression { output("multiplicative_expression -> multiplicative_expression MOD cast_expression"); }
	;

cast_expression
	: unary_expression { output("cast_expression -> unary_expression"); }
	| OPAREN type_name CPAREN cast_expression { output("cast_expression -> OPAREN type_name CPAREN cast_expression"); }
	;

unary_expression
	: postfix_expression { output("unary_expression -> postfix_expression"); }
	| INC_OP unary_expression { output("unary_expression -> INC_OP unary_expression"); }
	| DEC_OP unary_expression { output("unary_expression -> DEC_OP unary_expression"); }
	| unary_operator cast_expression { output("unary_expression -> unary_operator cast_expression"); }
	| SIZEOF unary_expression { output("unary_expression -> SIZEOF unary_expression"); }
	| SIZEOF OPAREN type_name CPAREN { output("unary_expression -> SIZEOF OPAREN type_name CPAREN"); }
	;

unary_operator
	: AMPERSAND { output("unary_operator -> AMPERSAND"); }
	| STAR { output("unary_operator -> STAR"); }
	| ADD { output("unary_operator -> ADD"); }
	| SUB { output("unary_operator -> SUB"); }
	| B_NOT { output("unary_operator -> B_NOT"); }
	| L_NOT { output("unary_operator -> L_NOT"); }
	;

postfix_expression
	: primary_expression { output("postfix_expression -> primary_expression"); }
	| postfix_expression OBRACKET expression CBRACKET { output("postfix_expression -> postfix_expression OBRACKET expression CBRACKET"); }
	| postfix_expression OPAREN CPAREN { output("postfix_expression -> postfix_expression OPAREN CPAREN"); }
	| postfix_expression OPAREN argument_expression_list CPAREN { output("postfix_expression -> postfix_expression OPAREN argument_expression_list CPAREN"); }
	| postfix_expression PERIOD identifier { output("postfix_expression -> postfix_expression PERIOD identifier"); }
	| postfix_expression ARROW identifier { output("postfix_expression -> postfix_expression ARROW identifier"); }
	| postfix_expression INC_OP { output("postfix_expression -> postfix_expression INC_OP"); }
	| postfix_expression DEC_OP { output("postfix_expression -> postfix_expression DEC_OP"); }
	;

primary_expression
	: identifier { output("primary_expression -> identifier"); }
	| constant { output("primary_expression -> constant"); }
	| string { output("primary_expression -> string"); }
	| OPAREN expression CPAREN { output("primary_expression -> OPAREN expression CPAREN"); }
	;

argument_expression_list
	: assignment_expression { output("argument_expression_list -> assignment_expression"); }
	| argument_expression_list COMMA assignment_expression { output("argument_expression_list -> argument_expression_list COMMA assignment_expression"); }
	;

constant
	: INTEGER_CONSTANT { output("constant -> INTEGER_CONSTANT"); }
	| CHARACTER_CONSTANT { output("constant -> CHARACTER_CONSTANT"); }
	| FLOATING_CONSTANT { output("constant -> FLOATING_CONSTANT"); }
	| ENUMERATION_CONSTANT { output("constant -> ENUMERATION_CONSTANT"); }
	;

string
	: STRING_LITERAL { output("string -> STRING_LITERAL"); }
	;

identifier
	: IDENTIFIER { output("identifier -> IDENTIFIER"); }
	;

%%

int main(int argc, char** argv)
{
    FILE* inputStream = fopen(argv[1], "r");
    if (!inputStream)
    {
        cout << "Cannot open input file." << endl;
    }
    else
    {
        yyin = inputStream;
    }
    
    outputStream.open(argv[2]);
    yyparse();
    cout << "line_num: " << line_num << endl;
    cout << "column_num: " << column_num << endl;
    cout << "tab_num: " << tab_num << endl;
}

void yyerror(const char* s)
{
    cout << "Error: " << yylval.sval << endl;
}

void output(string s)
{
    if (outputStream.good())
    {
        outputStream << s << endl;
    }
    else
    {
        cout << s << endl;
    }
}
