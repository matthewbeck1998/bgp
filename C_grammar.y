%token IDENTIFIER 
%token INTEGER_CONSTANT FLOATING_CONSTANT CHARACTER_CONSTANT ENUMERATION_CONSTANT 
%token STRING_LITERAL 
%token SIZEOF
%token PTR_OP 
%token INC_OP DEC_OP 
%token LEFT_OP RIGHT_OP 
%token LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP 
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN 
%token LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN 
%token TYPEDEF_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELIPSIS RANGE

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%start translation_unit
%% /* GRAMMAR AND ACTIONS */

translation_unit
	: external_declaration { std::cout << "translation_unit -> external declaration" << std::endl }
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declarator compound_statement
	| declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	| declaration_specifiers declarator declaration_list compound_statement
	;

declaration
	: declaration_specifiers SEMICOLON /* declaration_specifiers ';' */
	| declaration_specifiers init_declarator_list SEMICOLON /* declaration_specifiers init_declarator_list ';' */
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier 
	| type_qualifier declaration_specifiers
	;

storage_class_specifier
	: AUTO
	| REGISTER
	| STATIC
	| EXTERN
	| TYPEDEF
	;

type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT 
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| struct_or_union_specifier
	| enum_specifier
	| TYPEDEF_NAME
	;

type_qualifier
	: CONST
	| VOLATILE
	;

struct_or_union_specifier
	: struct_or_union identifier LEFT_BRACE struct_declaration_list RIGHT_BRACE /* struct_or_union identifier '{' struct_declaration_list '}'*/
	| struct_or_union LEFT_BRACE struct_declaration_list RIGHT_BRACE /* struct_or_union '{' struct_declaration_list '}' */
	| struct_or_union identifier
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

init_declarator_list
	: init_declarator
	| init_declarator_list COMMA init_declarator /* init_declarator_list ',' init_declarator */
	;

init_declarator
	: declarator
	| declarator ASSIGN initializer /* declarator '=' initializer */
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list SEMICOLON /* specifier_qualifier_list struct_declarator_list ';' */
	;

specifier_qualifier_list
	: type_specifier
	| type_specifier specifier_qualifier_list
	| type_qualifier
	| type_qualifier specifier_qualifier_list
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list COMMA struct_declarator /* struct_declarator_list ',' struct_declarator */
	;

struct_declarator
	: declarator
	| COLON constant_expression /* ':' constant_expression */
	| declarator COLON constant_expression /* declarator ':' constant_expression */
	;

enum_specifier
	: ENUM LEFT_BRACE enumerator_list RIGHT_BRACE /* ENUM '{' enumerator_list '}' */
	| ENUM identifier LEFT_BRACE enumerator_list RIGHT_BRACE /* ENUM identifier '{' enumerator_list '}' */
	| ENUM identifier
	;

enumerator_list
	: enumerator
	| enumerator_list COMMA enumerator /* enumerator_list ',' enumerator */
	;

enumerator
	: identifier
	| identifier ASSIGN constant_expression /* identifier '=' constant_expression */
	;

declarator
	: direct_declarator
	| pointer direct_declarator
	;

direct_declarator
	: identifier
	| LEFT_PARENTHESE declarator RIGHT_PARENTHESE /* '(' declarator ')' */
	| direct_declarator LEFT_BRACKET RIGHT_BRACKET /* direct_declarator '[' ']' */
	| direct_declarator LEFT_BRACKET constant_expression RIGHT_BRACKET /* direct_declarator '[' constant_expression ']' */
	| direct_declarator LEFT_PARENTHESE RIGHT_PARENTHESE  /* direct_declarator '(' ')' */
	| direct_declarator LEFT_PARENTHESE parameter_type_list RIGHT_PARENTHESE /* direct_declarator '(' parameter_type_list ')' */
	| direct_declarator LEFT_PARENTHESE identifier_list RIGHT_PARENTHESE /* direct_declarator '(' identifier_list ')' */
	;

pointer /* Must separate pointer * from multiplication *... */
	: '*'
	| '*' type_qualifier_list
	| '*' pointer
	| '*' type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;

parameter_type_list
	: parameter_list
	| parameter_list COMMA ELIPSIS /* parameter_list ',' ELIPSIS */
	;

parameter_list
	: parameter_declaration
	| parameter_list COMMA parameter_declaration /* parameter_list ',' parameter_declaration */
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers
	| declaration_specifiers abstract_declarator
	;

identifier_list
	: identifier
	| identifier_list COMMA identifier /* identifier_list ',' identifier */
	;

initializer
	: assignment_expression
	| LEFT_BRACE initializer_list RIGHT_BRACE /* '{' initializer_list '}' */
	| LEFT_BRACE initializer_list COMMA RIGHT_BRACE /* '{' initializer_list ',' '}' */
	;

initializer_list
	: initializer
	| initializer_list COMMA initializer /* initializer_list ',' initializer */
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: LEFT_PARENTHESE abstract_declarator RIGHT_PARENTHESE /* '(' abstract_declarator ')' */
	| LEFT_BRACKET RIGHT_BRACKET /* '[' ']' */
	| LEFT_BRACKET constant_expression RIGHT_BRACKET /* '[' constant_expression ']'*/
	| direct_abstract_declarator LEFT_BRACKET RIGHT_BRACKET /* direct_abstract_declarator '[' ']' */
	| direct_abstract_declarator LEFT_BRACKET constant_expression RIGHT_BRACKET /* direct_abstract_declarator '[' constant_expression ']' */
	| LEFT_PARENTHESE RIGHT_PARENTHESE /* '(' ')' */
	| LEFT_PARENTHESE parameter_type_list RIGHT_PARENTHESE /* '(' parameter_type_list ')' */
	| direct_abstract_declarator LEFT_PARENTHESE RIGHT_PARENTHESE /* direct_abstract_declarator '(' ')' */
	| direct_abstract_declarator LEFT_PARENTHESE parameter_type_list RIGHT_PARENTHESE /* direct_abstract_declarator '(' parameter_type_list ')' */
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: identifier COLON statement /* identifier ':' statement */
	| CASE constant_expression COLON statement /* CASE constant_expression ':' statement */
	| DEFAULT COLON statement /* DEFAULT ':' statement */
	;

expression_statement
	: SEMICOLON /* ';' */
	| expression SEMICOLON /* expression ';' */
	;

compound_statement
	: LEFT_BRACE RIGHT_BRACE /* '{' '}' */
	| LEFT_BRACE statement_list RIGHT_BRACE /* '{' statement_list '}' */
	| LEFT_BRACE declaration_list RIGHT_BRACE /* '{' declaration_list '}' */
	| LEFT_BRACE declaration_list statement_list RIGHT_BRACE /* '{' declaration_list statement_list '}' */
	;

statement_list
	: statement
	| statement_list statement
	;

selection_statement
	: IF LEFT_PARENTHESE expression RIGHT_PARENTHESE statement /* IF '(' expression ')' statement */
	| IF LEFT_PARENTHESE expression RIGHT_PARENTHESE statement ELSE statement /* IF '(' expression ')' statement ELSE statement */
	| SWITCH LEFT_PARENTHESE expression RIGHT_PARENTHESE statement /* SWITCH '(' expression ')' statement */
	;

iteration_statement
	: WHILE LEFT_PARENTHESE expression RIGHT_PARENTHESE statement /* WHILE '(' expression ')' statement */
	| DO statement WHILE LEFT_PARENTHESE expression RIGHT_PARENTHESE SEMICOLON /* DO statement WHILE '(' expression ')' ';' */
	| FOR LEFT_PARENTHESE SEMICOLON SEMICOLON RIGHT_PARENTHESE statement /* FOR '(' ';' ';' ')' statement */
	| FOR LEFT_PARENTHESE SEMICOLON SEMICOLON expression RIGHT_PARENTHESE statement /* FOR '(' ';' ';' expression ')' statement */
	| FOR LEFT_PARENTHESE SEMICOLON expression SEMICOLON RIGHT_PARENTHESE statement /* FOR '(' ';' expression ';' ')' statement */
	| FOR LEFT_PARENTHESE SEMICOLON expression SEMICOLON expression RIGHT_PARENTHESE statement /* FOR '(' ';' expression ';' expression ')' statement */
	| FOR LEFT_PARENTHESE expression SEMICOLON SEMICOLON RIGHT_PARENTHESE statement /* FOR '(' expression ';' ';' ')' statement */
	| FOR LEFT_PARENTHESE expression SEMICOLON SEMICOLON expression RIGHT_PARENTHESE statement /* FOR '(' expression ';' ';' expression ')' statement */
	| FOR LEFT_PARENTHESE expression SEMICOLON expression SEMICOLON RIGHT_PARENTHESE statement /* FOR '(' expression ';' expression ';' ')' statement */
	| FOR LEFT_PARENTHESE expression SEMICOLON expression SEMICOLON expression RIGHT_PARENTHESE statement /* FOR '(' expression ';' expression ';' expression ')' statement */
	;

jump_statement
	: GOTO identifier SEMICOLON /* GOTO identifier ';' */
	| CONTINUE SEMICOLON /* CONTINUE ';' */
	| BREAK SEMICOLON /* BREAK ';' */
	| RETURN SEMICOLON /* RETURN ';' */
	| RETURN expression SEMICOLON /* RETURN expression ';' */
	;

expression
	: assignment_expression
	| expression COMMA assignment_expression /* expression ',' assignment_expression */
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
	: ASSIGN /* '=' */
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression TERNARY expression COLON conditional_expression /* logical_or_expression '?' expression ':' conditional_expression */
	;

constant_expression
	: conditional_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression BITWISE_INCLUSIVE_OR exclusive_or_expression /* inclusive_or_expression '|' exclusive_or_expression */
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression BITWISE_EXCLUSIVE_OR and_expression /* exclusive_or_expression '^' and_expression */
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression /* and_expression '&' equality_expression */
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

relational_expression
	: shift_expression
	| relational_expression LESS_THAN shift_expression /* relational_expression '<' shift_expression */
	| relational_expression GREATER_THAN shift_expression /* relational_expression '>' shift_expression */
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression ADD multiplicative_expression /* additive_expression '+' multiplicative_expression */
	| additive_expression SUBTRACT multiplicative_expression /* additive_expression '-' multiplicative_expression */
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression MULTIPLY cast_expression /* multiplicative_expression '*' cast_expression */
	| multiplicative_expression DIVIDE cast_expression /* multiplicative_expression '/' cast_expression */
	| multiplicative_expression MODULO cast_expression /* multiplicative_expression '%' cast_expression */
	;

cast_expression
	: unary_expression
	| LEFT_PARENTHESE type_name RIGHT_PARENTHESE cast_expression /* '(' type_name ')' cast_expression */
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| unary_operator cast_expression
	| SIZEOF unary_expression
	| SIZEOF LEFT_PARENTHESE type_name RIGHT_PARENTHESE /* SIZEOF '(' type_name ')' */
	;

unary_operator
	: '&'
	| '*'
	| ADD /* '+' */
	| SUBTRACT /* '-' */
	| BITWISE_NOT /* '~' */
	| LOGICAL_NOT /* '!' */
	;

postfix_expression
	: primary_expression
	| postfix_expression LEFT_BRACKET expression RIGHT_BRACKET /* postfix_expression '[' expression ']' */
	| postfix_expression LEFT_PARENTHESE RIGHT_PARENTHESE /* postfix_expression '(' ')' */
	| postfix_expression LEFT_PARENTHESE argument_expression_list RIGHT_PARENTHESE /* postfix_expression '(' argument_expression_list ')' */
	| postfix_expression MEMBER_OF identifier /* postfix_expression '.' identifier */
	| postfix_expression PTR_OP identifier
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	;

primary_expression
	: identifier
	| constant
	| string
	| LEFT_PARENTHESE expression RIGHT_PARENTHESE /* '(' expression ')' */
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list COMMA assignment_expression /* argument_expression_list ',' assignment_expression */
	;

constant
	: INTEGER_CONSTANT
	| CHARACTER_CONSTANT
	| FLOATING_CONSTANT
	| ENUMERATION_CONSTANT
	;

string
	: STRING_LITERAL
	;

identifier
	: IDENTIFIER
	;
%% /* USER-DEFINED CODE */

#include <stdio.h>

extern char yytext[];
extern int column;

yyerror(s)
char *s;
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}

