%{
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include "SymbolTable.h"
#include "SymbolNode.h"
#include "AST.h"
#include "ASTNode.h"

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
string inputFileName;

void parserOutput(string s);

//Command line Parse
int parseCommandLine(int argc, char** argv);
bool command_l = false;
bool command_s = false;
//

void recursiveOffsetInitDeclList( ASTNode* currentNode );

void handleOffsetType( int inputType );

SymbolTable st;
string nodeIdentifier = "";
int nodeLineNumber = -1;
int nodeStorageClassSpecifier = -1;
int nodeTypeSpecifier = 3;
int nodeTypeQualifier = -1;
bool nodeIsFunction = false;
bool nodeIsSigned = true;
string lastNodeInserted = "";
bool inFunctionParameters = false;
string currentFunctionNode = "";
bool inFunctionPrototype = false;
bool sameArray = false;
list<array<int, 3>> matchedParameters;
int currentOffset = 4;

ASTNode* root;
%}

%union
{
    char sval[255];
    ASTNode *nodePtr;
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

%type <nodePtr> translation_unit external_declaration function_definition declaration declaration_list
%type <nodePtr> declaration_specifiers type_specifier init_declarator_list init_declarator declarator
%type <nodePtr> direct_declarator compound_statement constant initializer assignment_expression
%type <nodePtr> conditional_expression logical_or_expression logical_and_expression inclusive_or_expression
%type <nodePtr> exclusive_or_expression and_expression equality_expression relational_expression
%type <nodePtr> shift_expression additive_expression multiplicative_expression cast_expression unary_expression
%type <nodePtr> postfix_expression primary_expression statement expression_statement unary_operator
%type <nodePtr> statement_list expression constant_expression storage_class_specifier type_qualifier
%type <nodePtr> struct_or_union_specifier enum_specifier string argument_expression_list jump_statement
%type <nodePtr> struct_declaration_list struct_declaration specifier_qualifier_list assignment_operator
%type <nodePtr> iteration_statement selection_statement labeled_statement direct_abstract_declarator
%type <nodePtr> abstract_declarator type_name initializer_list identifier_list parameter_declaration
%type <nodePtr> parameter_list parameter_type_list type_qualifier_list pointer enumerator enumerator_list
%type <nodePtr> struct_declarator struct_declarator_list struct_or_union identifier
//%type <nodePtr>

%%

translation_unit
	: external_declaration {	$1->setOffset( root->getActivationFrameSize() );
								root->addChild($1); parserOutput("translation_unit -> external_declaration"); }
	| translation_unit external_declaration {  $2->setOffset( root->getActivationFrameSize() );
											   root->addChild($2);
	                                           parserOutput("translation_unit -> translation_unit external_declaration");
                                            }
	;

external_declaration
	: function_definition { $$ = $1; parserOutput("external_declaration -> function_definition"); }
	| declaration { $$ = $1; parserOutput("external_declaration -> declaration");}
	;

function_definition
	: declarator compound_statement { ASTFunctionNode* temp = new ASTFunctionNode("function_definition", ( ( ASTTypeNode* )$1 )-> getType() );
                                      temp -> addChild($1);
                                      temp -> addChild($2);
                                      $$ = temp;
                                      if( temp->getActivationFrameSize() % 8 != 0 )
                                        temp->setActivationFrameSize( (temp->getActivationFrameSize() + 4) + 8 - ( (temp->getActivationFrameSize() + 4) % 8) );
                                      currentOffset = 4;
                                      parserOutput("function_definition -> declarator compound_statement");
                                      st.popLevel(); }
	| declarator declaration_list compound_statement { ASTFunctionNode* temp = new ASTFunctionNode("function_definition", ( ( ASTTypeNode* )$1 )-> getType() );
	                                                     $2->setType( $1->getType() );
                                                         //temp -> addChild($1);
                                                         temp -> addChild($2);
                                                         temp -> addChild($3);
                                                         $$ = temp;
                                                         if( temp->getActivationFrameSize() % 8 != 0 )
                                                            temp->setActivationFrameSize( (temp->getActivationFrameSize() + 4) + 8 - ( (temp->getActivationFrameSize() + 4) % 8) );
                                                         currentOffset = 4;
                                                         parserOutput("function_definition -> declarator declaration_list compound_statement");
                                                         st.popLevel(); }
	| declaration_specifiers declarator compound_statement {
	                                                        ASTFunctionNode* temp = new ASTFunctionNode("function_definition", ( ( ASTTypeNode* )$1 )-> getType() );
                                                            //$2->setType( $1->getType() ); //Might not need??
                                                            //temp -> addChild($1);
                                                            temp -> addChild($2);
	                                                        temp->addChild($3);
	                                                        $$ = temp;
                                                            if( temp->getActivationFrameSize() % 8 != 0 )
                                                                temp->setActivationFrameSize( (temp->getActivationFrameSize() + 4) + 8 - ( (temp->getActivationFrameSize() + 4) % 8) );
	                                                        if($2->getLabel() == "direct_declarator")
                                                            {
                                                                auto symbolPair = st.searchAll( ( (ASTIdNode*) $2 -> getChildren().front() )-> getId()  ).second;
                                                                handleOffsetType( ( (ASTIdNode*) $2 -> getChildren().front() )->getType() );
                                                                currentOffset += $2->getActivationFrameSize();
                                                                symbolPair->second.offset = currentOffset;
                                                            } else
                                                            {
                                                                auto symbolPair = st.searchAll( ( (ASTIdNode*) $2 ) -> getId()  ).second;
                                                                handleOffsetType( ( (ASTIdNode*) $2)->getType() );
                                                                currentOffset += $2->getActivationFrameSize();
                                                                symbolPair->second.offset = currentOffset;
                                                            }
                                                            currentOffset = 4;
	                                                        parserOutput("function_definition -> declaration_specifiers declarator compound_statement");
	                                                        st.popLevel(); }
	| declaration_specifiers declarator declaration_list compound_statement {
                                                                             ASTFunctionNode* temp = new ASTFunctionNode("function_definition", ( ( ASTTypeNode* )$1 )-> getType());
                                                                             $2->setType( $1->getType() );
                                                                               //temp -> addChild($1);
                                                                               temp -> addChild($2);
                                                                               temp -> addChild($3);
                                                                               temp -> addChild($4);
                                                                               $$ = temp;
                                                                               if( temp->getActivationFrameSize() % 8 != 0 ) // The activation frame of functions is a multiple of 8
                                                                                   temp->setActivationFrameSize( (temp->getActivationFrameSize() + 8) + 8 - ( (temp->getActivationFrameSize() + 8) % 8) );
                                                                               currentOffset = 4;
                                                                               parserOutput("function_definition -> declaration_specifiers declarator declaration_list compound_statement");
                                                                               st.popLevel(); }
	;

declaration
	: declaration_specifiers SEMICOLON {    $$ = new ASTDeclarationNode( "declaration", $1->getType(), $1);
                                            parserOutput("declaration -> declaration_specifiers SEMICOLON"); }
	| declaration_specifiers init_declarator_list SEMICOLON {
                                                                sameArray = false;
	                                                            ASTDeclarationNode* temp = new ASTDeclarationNode("Declaration", ( ( ASTTypeNode* )$1 )->getType(), $2);

                                                                 // damn you Will for ditching this project for a girl
	                                                            $$ = temp;
	                                                            parserOutput("declaration -> declaration_specifiers init_declarator_list SEMICOLON");
                                                            }
	;

declaration_list
	: declaration { ASTDeclListNode* temp = new ASTDeclListNode("declaration_list", $1);
	                temp->setOffset(currentOffset); // This shouldn't do anything.
                    if ($1->getChildren().front()->getLabel() == "IDENTIFIER")
                    {
                        auto symbolPair = st.searchAll( ( (ASTIdNode*) $1->getChildren().front() )->getId()  ).second;
                        handleOffsetType( ( (ASTIdNode*) $1->getChildren().front() )->getType() );
                        currentOffset += $1->getActivationFrameSize();
                        $1->setOffset( currentOffset );
                        symbolPair->second.offset = ( (ASTIdNode*) $1->getChildren().front() )->getOffset();
                    } else if($1->getChildren().front()->getLabel() == "init_declarator") //Need nested if to handle array nodes
                    {
                        auto symbolPair = st.searchAll( ( (ASTIdNode*) $1->getChildren().front()->getChildren().front() )->getId()  ).second;
                        $1->setOffset( currentOffset ); // Probably don't need?
                        handleOffsetType( ( (ASTIdNode*) $1->getChildren().front()->getChildren().front() )->getType() );
                        currentOffset += $1->getActivationFrameSize();
                        $1->getChildren().front()->setOffset( currentOffset );
                        symbolPair->second.offset = $1->getOffset(); // Need the line two line previous if you do it this way.
                    } else if($1->getChildren().front()->getLabel() == "array_node")//if it is an array node;
                    {
                        auto symbolPair = st.searchAll( ( (ASTArrayNode*) $1->getChildren().front() )->getId()  ).second;
                        handleOffsetType( ( (ASTArrayNode*) $1->getChildren().front() )->getType() );
                        currentOffset += $1->getActivationFrameSize();
                        $1->setOffset( currentOffset );
                        symbolPair->second.offset = ( (ASTArrayNode*) $1->getChildren().front() )->getOffset();
                    } else if ($1->getChildren().front()->getLabel() == "init_declarator_list")
                    {
                        currentOffset -= $1->getActivationFrameSize(); // Subtract for the plus. The recursive function handles it
                        recursiveOffsetInitDeclList( $1 );
                        temp->setActivationFrameSize( currentOffset );
                    } else
                    {
                        cerr << "Something wrong in declaration_list -> declaration. " << endl << "Label is: " << $1->getChildren().front()->getLabel() << endl;
                    }
	                $$ = temp;
	                parserOutput("declaration_list -> declaration"); st.setInsertMode(false); }
	| declaration_list declaration {    ASTDeclListNode* temp = new ASTDeclListNode("declaration_list", $1, $2);
	                                    $$ = temp;
                                        if ($2->getChildren().front()->getLabel() == "IDENTIFIER")
                                        {
                                            auto symbolPair = st.searchAll( ( (ASTIdNode*) $2->getChildren().front() )->getId()  ).second;
                                            handleOffsetType( ( (ASTIdNode*) $2->getChildren().front() )->getType() );
                                            currentOffset += $2->getActivationFrameSize();
                                            $2->getChildren().front()->setOffset( currentOffset );
                                            symbolPair->second.offset = ( (ASTIdNode*) $2->getChildren().front() )->getOffset();
                                        } else if( $2->getChildren().front()->getLabel() == "init_declarator" )
                                        { // Need a nested if for arrayNode initializer
                                            auto symbolPair = st.searchAll( ( (ASTIdNode*) $2->getChildren().front()->getChildren().front() )->getId()  ).second;
                                            $2->getChildren().front()->setOffset( currentOffset ); // Probably don't need?
                                            handleOffsetType( ( (ASTIdNode*) $2->getChildren().front()->getChildren().front() )->getType() );
                                            currentOffset += $2->getActivationFrameSize();
                                            $2->getChildren().front()->getChildren().front()->setOffset( currentOffset );
                                            symbolPair->second.offset = ( (ASTIdNode*) $2->getChildren().front() )->getOffset();
                                        } else if( $2->getChildren().front()->getLabel() == "array_node" )//if it is an array node;
                                        {
                                            auto symbolPair = st.searchAll( ( (ASTArrayNode*) $2->getChildren().front() )->getId()  ).second;
                                            handleOffsetType( ( (ASTArrayNode*) $2->getChildren().front() )->getType() );
                                            currentOffset += $2->getActivationFrameSize();
                                            $2->getChildren().front()->setOffset( currentOffset );
                                            symbolPair->second.offset = ( (ASTArrayNode*) $2->getChildren().front() )->getOffset();
                                        } else
                                        {
                                            cerr << "Something went wrong in declaration_list -> declaration_list declaration" << endl << "Label: " << $2->getChildren().front()->getLabel() << endl;
                                        }
                                       	parserOutput("declaration_list -> declaration_list declaration"); st.setInsertMode(false); }
	;

declaration_specifiers
	: storage_class_specifier { $$ = $1; parserOutput("declaration_specifiers -> storage_class_specifier"); }
	| storage_class_specifier declaration_specifiers {    ASTNode* temp = new ASTNode("declaration_specifiers");
                                                          temp -> addChild($1);
                                                          temp -> addChild($2);
                                                          $$ = temp;
	                                                    parserOutput("declaration_specifiers -> storage_class_specifier declaration_specifiers"); }

	| type_specifier { $$ = $1; parserOutput("declaration_specifiers -> type_specifier"); }
	| type_specifier declaration_specifiers {   errorStream << "ERROR: multiple type specifiers on line " << line << ". " <<  printType( $1->getType() ) << " and " << printType( $2->getType() ) << endl;
	                                            return -1;
                                                /*ASTNode* temp = new ASTNode("declaration_specifiers");
                                                temp -> addChild($1);
                                                temp -> addChild($2);
                                                $$ = temp;*/
                                                parserOutput("declaration_specifiers -> type_specifier declaration_specifiers"); }
	| type_qualifier { $$ = $1; parserOutput("declaration_specifiers -> type_qualifier"); }
	| type_qualifier declaration_specifiers { ASTNode* temp = new ASTNode("declaration_specifiers");
                                                temp -> addChild($1);
                                                temp -> addChild($2);
                                                $$ = temp;
                                                parserOutput("declaration_specifiers -> type_qualifier declaration_specifiers"); }
	;

storage_class_specifier
	: AUTO { $$ = new ASTNode("AUTO"); parserOutput("storage_class_specifier -> AUTO"); st.setInsertMode(true); nodeStorageClassSpecifier = 0; }
	| REGISTER { $$ = new ASTNode("Register"); parserOutput("storage_class_specifier -> REGISTER"); st.setInsertMode(true); nodeStorageClassSpecifier = 1; }
	| STATIC { $$ = new ASTNode("STATIC"); parserOutput("storage_class_specifier -> STATIC"); st.setInsertMode(true); nodeStorageClassSpecifier = 2; }
	| EXTERN { $$ = new ASTNode("EXTERN"); parserOutput("storage_class_specifier -> EXTERN"); st.setInsertMode(true); nodeStorageClassSpecifier = 3; }
	| TYPEDEF { $$ = new ASTNode("TYPDEF"); parserOutput("storage_class_specifier -> TYPEDEF"); st.setInsertMode(true); nodeStorageClassSpecifier = 4; }
	;

type_specifier
	: VOID { $$ = new ASTTypeNode("type_specifier", Void); parserOutput("type_specifier -> VOID"); st.setInsertMode(true); nodeTypeSpecifier = 0; }
	| CHAR { $$ = new ASTTypeNode("type_specifier", Char); parserOutput("type_specifier -> CHAR"); st.setInsertMode(true); nodeTypeSpecifier = 1; }
	| SHORT { $$ = new ASTTypeNode("type_specifier", Short); parserOutput("type_specifier -> SHORT"); st.setInsertMode(true); nodeTypeSpecifier = 2; }
	| INT { $$ = new ASTTypeNode("type_specifier", Int); parserOutput("type_specifier -> INT"); st.setInsertMode(true); nodeTypeSpecifier = 3; }
	| LONG { $$ = new ASTTypeNode("type_specifier", Long); parserOutput("type_specifier -> LONG"); st.setInsertMode(true); nodeTypeSpecifier = 4; }
	| FLOAT { $$ = new ASTTypeNode("type_specifier", Float); parserOutput("type_specifier -> FLOAT"); st.setInsertMode(true); nodeTypeSpecifier = 5; }
	| DOUBLE { $$ = new ASTTypeNode("type_specifier", Double); parserOutput("type_specifier -> DOUBLE"); st.setInsertMode(true); nodeTypeSpecifier = 6; }
	| SIGNED { parserOutput("type_specifier -> SIGNED"); st.setInsertMode(true); nodeIsSigned = true; }
	| UNSIGNED { parserOutput("type_specifier -> UNSIGNED"); st.setInsertMode(true); nodeIsSigned = false; }
	| struct_or_union_specifier { $$ = $1; parserOutput("type_specifier -> struct_or_union_specifier"); }
	| enum_specifier { $$ = $1; parserOutput("type_specifier -> enum_specifier"); /* TODO: Enums... one day... */ }
	| TYPEDEF_NAME { $$ = new ASTNode("TYPEDEF_NAME"); parserOutput("type_specifier -> TYPEDEF_NAME"); /* TODO: typedefs in symbol table */ }
	;

type_qualifier
	: CONST { $$ = new ASTNode("CONST"); parserOutput("type_qualifier -> CONST"); st.setInsertMode(true); nodeTypeQualifier = 0; }
	| VOLATILE { $$ = new ASTNode("VOLATILE"); parserOutput("type_qualifier -> VOLATILE"); st.setInsertMode(true); nodeTypeQualifier = 1; }
	;

struct_or_union_specifier
	: struct_or_union identifier OBRACE struct_declaration_list CBRACE {  ASTNode* temp = new ASTNode("struct_or_union_specifier");
                                                                          temp -> addChild($1);
                                                                          temp -> addChild($2);
                                                                          temp -> addChild($4);
                                                                          $$ = temp;
                                                                          parserOutput("struct_or_union_specifier -> struct_or_union identifier OBRACE struct_declaration_list CBRACE"); }
	| struct_or_union OBRACE struct_declaration_list CBRACE {  ASTNode* temp = new ASTNode("struct_or_union_specifier");
                                                               temp -> addChild($1);
                                                               temp -> addChild($3);
                                                               $$ = temp;
                                                               parserOutput("struct_or_union_specifier -> struct_or_union OBRACE struct_declaration_list CBRACE"); }
	| struct_or_union identifier { 	 ASTVariableNode* temp = new ASTVariableNode("struct_or_union_specifier", Struct, $2->getId() );
                                     $$ = temp;
                                     parserOutput("struct_or_union_specifier -> struct_or_union identifier"); }
	;

struct_or_union
	: STRUCT { $$ = new ASTNode("STRUCT"); parserOutput("struct_or_union -> STRUCT"); nodeTypeSpecifier = 7; }
	| UNION { $$ = new ASTNode("UNION"); parserOutput("struct_or_union -> UNION"); }
	;

struct_declaration_list
	: struct_declaration { $$ = $1; parserOutput("struct_declaration_list -> struct_declaration"); }
	| struct_declaration_list struct_declaration {ASTNode* temp = new ASTNode("struct_declaration_list");
                                                    temp -> addChild($1);
                                                    temp -> addChild($2);
                                                    $$ = temp;
                                                    parserOutput("struct_declaration_list -> struct_declaration_list struct_declaration"); }
	;

init_declarator_list
	: init_declarator {$$ = $1; parserOutput("init_declarator_list -> init_declarator"); }
	| init_declarator_list COMMA init_declarator {ASTNode* temp = new ASTNode("init_declarator_list");
	                                              temp->addChild($1);
	                                              temp->addChild($3);
	                                              $$ = temp;
	                                              parserOutput("init_declarator_list -> init_declarator_list COMMA init_declarator"); }
	;

init_declarator
	: declarator {$$ = $1; parserOutput("init_declarator -> declarator"); }
	| declarator ASSIGN initializer {
                                        if( $1->getLabel() == "IDENTIFIER" )
                                        {
                                            ( (ASTIdNode*) $1)->setType( nodeTypeSpecifier ); // Very fragile.. help.
                                        } else if( $1->getLabel() == "array_node" )
                                        {
                                            ( (ASTArrayNode*) $1)->setType( nodeTypeSpecifier );
                                        }
                                        $3->setType( nodeTypeSpecifier );
                                        $$ = new ASTAssignNode("init_declarator", $1, new ASTNode("ASSIGN"), $3);
                                        parserOutput("init_declarator -> declarator ASSIGN initializer"); }
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list SEMICOLON {ASTNode* temp = new ASTNode("struct_declaration");
                                                                 temp -> addChild($1);
                                                                 temp -> addChild($2);
                                                                 $$ = temp;
                                                                 parserOutput("struct_declaration -> specifier_qualifier_list struct_declarator_list SEMICOLON"); }
	;

specifier_qualifier_list
	: type_specifier { $$ = $1; parserOutput("specifier_qualifier_list -> type_specifier"); }
	| type_specifier specifier_qualifier_list {ASTNode* temp = new ASTNode("specifier_qualifier_list");
                                                temp -> addChild($1);
                                                temp -> addChild($2);
                                                $$ = temp;
                                                parserOutput("specifier_qualifier_list -> type_specifier specifier_qualifier_list"); }
	| type_qualifier { $$ = $1; parserOutput("specifier_qualifier_list -> type_qualifier"); }
	| type_qualifier specifier_qualifier_list { ASTNode* temp = new ASTNode("specifier_qualifier_list");
                                                temp -> addChild($1);
                                                temp -> addChild($2);
                                                $$ = temp;
                                                parserOutput("specifier_qualifier_list -> type_qualifier specifier_qualifier_list"); }
	;

struct_declarator_list
	: struct_declarator { $$ = $1; parserOutput("struct_declarator_list -> struct_declarator"); }
	| struct_declarator_list COMMA struct_declarator {ASTNode* temp = new ASTNode("struct_declarator_list");
                                                      temp -> addChild($1);
                                                      temp -> addChild($3);
                                                      $$ = temp;
                                                      parserOutput("struct_declarator_list -> struct_declarator_list COMMA struct_declarator"); }
	;

struct_declarator
	: declarator { $$ = $1; parserOutput("struct_declarator -> declarator"); }
	| COLON constant_expression { $$ = $2; parserOutput("struct_declarator -> COLON constant_expression"); }
	| declarator COLON constant_expression { ASTNode* temp = new ASTNode("struct_declarator");
                                               temp -> addChild($1);
                                               temp -> addChild($3);
                                               $$ = temp;
                                               parserOutput("struct_declarator -> declarator COLON constant_expression"); }
	;

enum_specifier
	: ENUM OBRACE enumerator_list CBRACE { $$ = $3; parserOutput("enum_specifier -> ENUM OBRACE enumerator_list CBRACE"); }
	| ENUM identifier OBRACE enumerator_list CBRACE {   ASTNode* temp = new ASTNode("enum_specifier");
	                                                    ASTVariableNode* tempId = new ASTVariableNode("IDENTIFIER", Enum, $2->getId());
                                                        temp -> addChild($4);
                                                        $$ = temp;
                                                        parserOutput("enum_specifier -> ENUM identifier OBRACE enumerator_list CBRACE"); }
	| ENUM identifier { ASTVariableNode* tempId = new ASTVariableNode("IDENTIFIER", Enum, $2->getId());
	                    tempId->setType(Enum);
	                    $$ = tempId;
	                    parserOutput("enum_specifier -> ENUM identifier"); }
	;

enumerator_list
	: enumerator { $$ = $1; parserOutput("enumerator_list -> enumerator"); }
	| enumerator_list COMMA enumerator { ASTNode* temp = new ASTNode("enumerator_list");
                                         temp -> addChild($1);
                                         temp -> addChild($3);
                                         $$ = temp;
                                         parserOutput("enumerator_list -> enumerator_list COMMA enumerator"); }
	;

enumerator
	: identifier {  $$ = $1;
                    parserOutput("enumerator -> identifier"); }
	| identifier ASSIGN constant_expression { $$ = new ASTAssignNode("enumerator", $1, new ASTNode("ASSIGN"), $3);
                                              parserOutput("enumerator -> identifier ASSIGN constant_expression"); }
	;

declarator
	: direct_declarator {$$ = $1; parserOutput("declarator -> direct_declarator"); }
	| pointer direct_declarator { ASTNode* temp = new ASTNode("declarator");
                                    temp -> addChild($1);
                                    temp -> addChild($2);
                                    $$ = temp;
                                    parserOutput("declarator -> pointer direct_declarator"); }
	;

direct_declarator
	: identifier    {
                        parserOutput("direct_declarator -> identifier");
                        if (inFunctionParameters)
                        {
                            auto functionPair = st.searchAll(currentFunctionNode);
                            if (!st.isLastSearchValid())
                            {
                                return 1;
                            }
                            
                            if (!functionPair.second->second.isIsFunctionDefined())
                            {
                                functionPair.second->second.pushFunctionParameter();
                                functionPair.second->second.setCurrentFunctionParameterTypeSpecifier(nodeTypeSpecifier);
                                functionPair.second->second.setCurrentFunctionParameterTypeQualifier(nodeTypeQualifier);
                                functionPair.second->second.setCurrentFunctionParameterSign(nodeIsSigned);
                            }
                            else
                            {
                                array<int, 3> currentParameter = {nodeTypeQualifier, nodeIsSigned, nodeTypeSpecifier};
                                if (currentParameter == matchedParameters.front())
                                {
                                    matchedParameters.pop_front();
                                }
                                else
                                {
                                    cerr << "ERROR: REDEFINITION OF FUNCTION" << endl;
                                    yyerror(NULL);
                                    return 1;
                                }
                            }
                        }

                        auto functionPair = st.searchTop(nodeIdentifier);
                        if (st.isLastSearchValid() && functionPair.second->second.getIsFunction())
                        {
                            if (!functionPair.second->second.isIsFunctionDefined())
                            {
                                functionPair.second->second.setIsFunctionDefined(true);
                                matchedParameters = functionPair.second->second.getFunctionParameters();
                                lastNodeInserted = nodeIdentifier;
                            }
                            else
                            {
                                cerr << "ERROR: REDEFINITION OF FUNCTION" << endl;
                                yyerror(NULL);
                                return 1;
                            }
                        }
                        else
                        {   
                            SymbolNode node(nodeIdentifier, line, column, nodeTypeSpecifier);
                            node.setTypeStorageClassIndex(nodeStorageClassSpecifier);
                            node.setTypeQualifierIndex(nodeTypeQualifier);
                            node.setIsFunction(nodeIsFunction);
                            node.setIsSigned(nodeIsSigned);
                            $$ = $1;
                            if (!st.insert(node))
                            {
                                return 1;
                            }
                            lastNodeInserted = nodeIdentifier;
                            nodeIdentifier = "";
                            nodeLineNumber = -1;
                            nodeStorageClassSpecifier = -1;
                            //nodeTypeSpecifier = 3;
                            nodeTypeQualifier = -1;
                            nodeIsFunction = false;
                            nodeIsSigned = true;
                        }
                    }
	| OPAREN declarator CPAREN { $$ = $2; parserOutput("direct_declarator -> OPAREN declarator CPAREN"); }
	| direct_declarator OBRACKET CBRACKET { $$ = $1; parserOutput("direct_declarator -> direct_declarator OBRACKET CBRACKET"); }
	| direct_declarator OBRACKET constant_expression CBRACKET { auto arrayPair = st.searchTop(lastNodeInserted);
                                                                if (arrayPair.first == -1)
                                                                {
                                                                    return -1;
                                                                }
                                                                arrayPair.second->second.setIsArray(true);
                                                                int dimension = ((ASTConstNode*)$3)->getValue().intVal;
                                                                arrayPair.second->second.addArrayDimension(dimension);

                                                                ASTArrayNode* temp = new ASTArrayNode("array_node", arrayPair.second->second.getIdentifier(), $1 -> getType());
                                                                temp -> addDimension(dimension);
                                                                if(sameArray)
                                                                    temp -> addDimensions ( ( (ASTArrayNode*) $1 )->getDimensions() );
                                                                $$ = temp;
                                                                sameArray = true;
                                                                parserOutput("direct_declarator -> direct_declarator OBRACKET constant_expression CBRACKET"); }
	| direct_declarator OPAREN CPAREN { $$ = $1; parserOutput("direct_declarator -> direct_declarator OPAREN CPAREN"); }
	| direct_declarator OPAREN parameter_type_list CPAREN   {
                                                                inFunctionPrototype = true;
                                                                ASTNode* temp = new ASTNode("direct_declarator");
                                                                temp -> addChild($1);
                                                                temp -> addChild($3);
                                                                $$ = temp;
                                                                parserOutput("direct_declarator -> direct_declarator OPAREN parameter_type_list CPAREN");
                                                            }
	| direct_declarator OPAREN identifier_list CPAREN {ASTNode* temp = new ASTNode("direct_declarator");
                                                       temp -> addChild($1);
                                                       temp -> addChild($3);
                                                       $$ = temp;
                                                       parserOutput("direct_declarator -> direct_declarator OPAREN identifier_list CPAREN"); }
	;

pointer
	: STAR { $$ = new ASTNode("STAR"); parserOutput("pointer -> STAR"); }
	| STAR type_qualifier_list { $$ = $2; parserOutput("pointer -> STAR type_qualifier_list"); }
	| STAR pointer { $$ = $2; parserOutput("pointer -> STAR pointer"); }
	| STAR type_qualifier_list pointer {ASTNode* temp = new ASTNode("pointer");
                                        temp -> addChild($2);
                                        temp -> addChild($3);
                                        $$ = temp;
                                        parserOutput("pointer -> STAR type_qualifier_list pointer"); }
	;

type_qualifier_list
	: type_qualifier { $$ = $1; parserOutput("type_qualifier_list -> type_qualifier"); }
	| type_qualifier_list type_qualifier { ASTNode* temp = new ASTNode("type_qualifier_list");
                                           temp -> addChild($1);
                                           temp -> addChild($2);
                                           $$ = temp;
                                           parserOutput("type_qualifier_list -> type_qualifier_list type_qualifier"); }
	;

parameter_type_list
	: parameter_list { $$ = $1; parserOutput("parameter_type_list -> parameter_list"); }
	| parameter_list COMMA ELLIPSIS { $$ = $1; parserOutput("parameter_type_list -> parameter_list COMMA ELLIPSIS"); }
	;

parameter_list
	: parameter_declaration {
                                if ($1->getLabel() == "IDENTIFIER")
                                {
                                    auto symbolPair = st.searchAll( ( (ASTIdNode*) $1 )->getId()  ).second;
                                    handleOffsetType( ( (ASTIdNode*) $1 )->getType() );
                                    currentOffset += $1->getActivationFrameSize();
                                    symbolPair->second.offset = currentOffset;
                                    //currentOffset += ( (ASTIdNode*) $1 )->getActivationFrameSize();
                                } else //if it is an array node;
                                {
                                    auto symbolPair = st.searchAll( ( (ASTArrayNode*) $1 )->getId()  ).second;
                                    handleOffsetType( ( (ASTArrayNode*) $1 )->getType() );
                                    currentOffset += $1->getActivationFrameSize();
                                    symbolPair->second.offset = currentOffset;//( (ASTArrayNode*) $1 )->getOffset();
                                    //currentOffset += ( (ASTArrayNode*) $1 )->getActivationFrameSize();
                                }
                                $1->setOffset( currentOffset );
                                $$ = $1;
	                            parserOutput("parameter_list -> parameter_declaration"); }
	| parameter_list COMMA parameter_declaration { if($1->getLabel() != "parameter_list")
                                                    {
                                                        ASTNode *temp = new ASTNode("parameter_list");
                                                        temp -> addChild($1);
                                                        /*currentOffset += $1->getActivationFrameSize();


                                                        ///Symbol table stuff
                                                        if ($1->getLabel() == "IDENTIFIER")
                                                        {
                                                            auto symbolPair = st.searchAll( ( (ASTIdNode*) $1 )->getId()  ).second;
                                                            symbolPair->second.offset = $1->getOffset();
                                                            //currentOffset += ( (ASTIdNode*) $1 )->getActivationFrameSize();
                                                        } else //if it is an array node;
                                                        {
                                                            auto symbolPair = st.searchAll( ( (ASTArrayNode*) $1 )->getId()  ).second;
                                                            symbolPair->second.offset = $1->getOffset();//( (ASTArrayNode*) $1 )->getOffset();
                                                            //currentOffset += ( (ASTArrayNode*) $1 )->getActivationFrameSize();
                                                        }*/

                                                        temp -> addChild($3);
                                                        $$ = temp;
                                                        sameArray = false;

                                                        if ($3->getLabel() == "IDENTIFIER")
                                                        {
                                                            auto symbolPair = st.searchAll( ( (ASTIdNode*) $3 )->getId()  ).second;
                                                            handleOffsetType( ( (ASTIdNode*) $3 )->getType() );
                                                            currentOffset += $3->getActivationFrameSize();
                                                            symbolPair->second.offset = currentOffset;//( (ASTIdNode*) $3 )->getOffset();
                                                            //currentOffset += ( (ASTIdNode*) $3 )->getActivationFrameSize();
                                                        } else //if it is an array node;
                                                        {
                                                            auto symbolPair = st.searchAll( ( (ASTArrayNode*) $3 )->getId()  ).second;
                                                            handleOffsetType( ( (ASTArrayNode*) $3 )->getType() );
                                                            currentOffset += $3->getActivationFrameSize();
                                                            symbolPair->second.offset = currentOffset;//( (ASTArrayNode*) $3 )->getOffset();
                                                            //currentOffset += ( (ASTArrayNode*) $3 )->getActivationFrameSize();
                                                        }
                                                        $3->setOffset( currentOffset );

                                                        //no more symbol table for now
                                                    } else
                                                    {
	                                                    $1->addChild($3);
	                                                    $$ = $1;
	                                                    //Some more symbol table adding
                                                        if ($3->getLabel() == "IDENTIFIER") // This if could potentially be broken, weird offset fix.
                                                        {
                                                            auto symbolPair = st.searchAll( ( (ASTIdNode*) $3 )->getId()  ).second;
                                                            handleOffsetType( ( (ASTIdNode*) $3 )->getType() );
                                                            currentOffset += $3->getActivationFrameSize();
                                                            //currentOffset += ( (ASTIdNode*) $3 )->getActivationFrameSize();// - typeToByteSize( ( (ASTIdNode*) $3 ) -> getType() );
                                                            symbolPair->second.offset = currentOffset;//( (ASTIdNode*) $3 )->getActivationFrameSize();// - typeToByteSize( ( (ASTIdNode*) $3 ) -> getType() );

                                                        } else //if it is an array node;
                                                        {
                                                            auto symbolPair = st.searchAll( ( (ASTArrayNode*) $3 )->getId()  ).second;
                                                            handleOffsetType( ( (ASTArrayNode*) $3 )->getType() );
                                                            currentOffset += $3->getActivationFrameSize();
                                                            //currentOffset += ( (ASTArrayNode*) $3 )->getActivationFrameSize(); // - typeToByteSize( ( (ASTArrayNode*) $3 ) -> getType() );
                                                            symbolPair->second.offset = currentOffset; //( (ASTArrayNode*) $3 )->getActivationFrameSize();// - typeToByteSize( ( (ASTArrayNode*) $3 ) -> getType() );
                                                         }
                                                        $3->setOffset( currentOffset );
                                                        // no more symbol table adding, thank god.
                                                    }
                                                    parserOutput("parameter_list -> parameter_list COMMA parameter_declaration"); }
	;

parameter_declaration
	: declaration_specifiers declarator {
                                            if( $2->getLabel() == "IDENTIFIER" )
                                            {
                                                ASTIdNode *temp = new ASTIdNode($2->getLabel(), ( (ASTIdNode*) $2 )->getId() );
                                                temp->setType( ( (ASTTypeNode*) $1 )-> getType() );
                                                $$ = temp;
                                            } else //for arrays
                                            {
                                                ASTArrayNode* temp = new ASTArrayNode($2->getLabel(),  ( (ASTArrayNode*) $2 ) ->getId(), ( (ASTTypeNode*) $1 )->getType() );
                                                temp->setDimensions( ( (ASTArrayNode*) $2) ->getDimensions() );
                                                $$ = temp;
                                            }

                                            sameArray = false;
                                            parserOutput("parameter_declaration -> declaration_specifiers declarator"); }
	| declaration_specifiers { $$ = $1; parserOutput("parameter_declaration -> declaration_specifiers"); }
	| declaration_specifiers abstract_declarator {ASTNode* temp = new ASTNode("parameter_declaration");
                                                     temp -> addChild($1);
                                                     temp -> addChild($2);
                                                     $$ = temp;

                                                        sameArray = false;
                                                     parserOutput("parameter_declaration -> declaration_specifiers abstract_declarator"); }
	;

identifier_list
	: identifier { $$ = $1;
				   parserOutput("identifier_list -> identifier"); }
	| identifier_list COMMA identifier {   ASTNode* temp = new ASTNode("identifier_list");
                                           temp -> addChild($1);
                                           temp -> addChild( $3 );
                                           $$ = temp;
                                           parserOutput("identifier_list -> identifier_list COMMA identifier"); }
	;

initializer
	: assignment_expression { $$ = $1; parserOutput("initializer -> assignment_expression"); }
	| OBRACE initializer_list CBRACE { $$ = $2; parserOutput("initializer -> OBRACE initializer_list CBRACE"); }
	| OBRACE initializer_list COMMA CBRACE { $$ = $2; parserOutput("initializer -> OBRACE initializer_list COMMA CBRACE"); }
	;

initializer_list
	: initializer { ASTNode* temp = new ASTNode("initializer_list");
	                temp -> addChild($1);
	                $$ = temp;
	                parserOutput("initializer_list -> initializer"); }
	| initializer_list COMMA initializer {    $$ = new ASTArrayInitializerNode("array_initializer", $1, (ASTConstNode*) $3, $3->getType() );
                                              parserOutput("initializer_list -> initializer_list COMMA initializer"); }
	;

type_name
	: specifier_qualifier_list { $$ = $1; parserOutput("type_name -> specifier_qualifier_list"); st.setInsertMode(false); }
	| specifier_qualifier_list abstract_declarator  { 
                                                        ASTNode* temp = new ASTNode("type_name");
                                                        temp -> addChild($1);
                                                        temp -> addChild($2);
                                                        $$ = temp;
                                                        parserOutput("type_name -> specifier_qualifier_list abstract_declarator");
                                                        st.setInsertMode(false);
                                                    }
	;

abstract_declarator
	: pointer { $$ = $1; parserOutput("abstract_declarator -> pointer"); }
	| direct_abstract_declarator { $$ = $1; parserOutput("abstract_declarator -> direct_abstract_declarator"); }
	| pointer direct_abstract_declarator { ASTNode* temp = new ASTNode("abstract_declarator");
                                            temp -> addChild($1);
                                            temp -> addChild($2);
                                            $$ = temp;
                                            parserOutput("abstract_declarator -> pointer direct_abstract_declarator"); }
	;

direct_abstract_declarator
	: OPAREN abstract_declarator CPAREN { $$ = $2; parserOutput("direct_abstract_declarator -> OPAREN abstract_declarator CPAREN"); }
	| OBRACKET CBRACKET { $$ = new ASTNode("NAN"); parserOutput("direct_abstract_declarator -> OBRACKET CBRACKET"); }
	| OBRACKET constant_expression CBRACKET { $$ = $2; parserOutput("direct_abstract_declarator -> OBRACKET constant_expression CBRACKET"); }
	| direct_abstract_declarator OBRACKET CBRACKET { $$ = $1; parserOutput("direct_abstract_declarator -> direct_abstract_declarator OBRACKET CBRACKET"); }
	| direct_abstract_declarator OBRACKET constant_expression CBRACKET {ASTNode* temp = new ASTNode("direct_abstract_declarator");
                                                                        temp -> addChild($1);
                                                                        temp -> addChild($3);
                                                                        $$ = temp;
                                                                        parserOutput("direct_abstract_declarator -> direct_abstract_declarator OBRACKET constant_expression CBRACKET"); }
	| OPAREN CPAREN { $$ = new ASTNode("NAN"); parserOutput("direct_abstract_declarator -> OPAREN CPAREN"); }
	| OPAREN parameter_type_list CPAREN { $$ = $2; parserOutput("direct_abstract_declarator -> OPAREN parameter_type_list CPAREN"); }
	| direct_abstract_declarator OPAREN CPAREN { $$ = $1; parserOutput("direct_abstract_declarator -> direct_abstract_declarator OPAREN CPAREN"); }
	| direct_abstract_declarator OPAREN parameter_type_list CPAREN { ASTNode* temp = new ASTNode("direct_abstract_declarator");
                                                                     temp -> addChild($1);
                                                                     temp -> addChild($3);
                                                                     $$ = temp;
                                                                     parserOutput("direct_abstract_declarator -> direct_abstract_declarator OPAREN parameter_type_list CPAREN"); }
	;

statement
	: labeled_statement { $$ = $1; parserOutput("statement -> labeled_statement"); }
	| compound_statement { $$ = $1; parserOutput("statement -> compound_statement"); }
	| expression_statement { $$ = $1; parserOutput("statement -> expression_statement"); }
	| selection_statement { $$ = $1; parserOutput("statement -> selection_statement"); }
	| iteration_statement { $$ = $1; parserOutput("statement -> iteration_statement"); }
	| jump_statement { $$ = $1; parserOutput("statement -> jump_statement"); }
	;

labeled_statement
	: identifier COLON statement {ASTNode* temp = new ASTNode("labeled_statement");
                                  temp -> addChild($1);
                                  temp -> addChild($3);
                                  $$ = temp;
                                  parserOutput("labeled_statement -> identifier COLON statement"); }
	| CASE constant_expression COLON statement { ASTNode* temp = new ASTNode("labeled_statement");
                                                   temp -> addChild($2);
                                                   temp -> addChild($4);
                                                   $$ = temp;
                                                   parserOutput("labeled_statement -> CASE constant_expression COLON statement"); }
	| DEFAULT COLON statement { $$ = $3; parserOutput("labeled_statement -> DEFAULT COLON statement"); }
	;

expression_statement
	: SEMICOLON { $$ = new ASTNode("SEMICOLON"); parserOutput("expression_statement -> SEMICOLON"); }
	| expression SEMICOLON { $$ = $1; parserOutput("expression_statement -> expression SEMICOLON"); }
	;

compound_statement
	: OBRACE CBRACE { $$ = new ASTNode("NAN"); parserOutput("compound_statement -> OBRACE CBRACE"); }
	| OBRACE statement_list CBRACE { $$ = $2; parserOutput("compound_statement -> OBRACE statement_list CBRACE"); }
	| OBRACE declaration_list CBRACE { $$ = $2; parserOutput("compound_statement -> OBRACE declaration_list CBRACE"); }
	| OBRACE declaration_list statement_list CBRACE { ASTNode* temp = new ASTNode("compound_statement");
	                                                    temp->addChild($2);
	                                                    temp->addChild($3);
	                                                    $$ = temp;
	                                                    parserOutput("compound_statement -> OBRACE declaration_list statement_list CBRACE"); }
	;

statement_list
	: statement { $$ = $1; parserOutput("statement_list -> statement"); }
	| statement_list statement {ASTNode* temp = new ASTNode("statement_list");
                                  temp -> addChild($1);
                                  temp -> addChild($2);
                                  $$ = temp;
                                  parserOutput("statement_list -> statement_list statement"); }
	;

selection_statement
	: IF OPAREN expression CPAREN statement { ASTNode* temp = new ASTSelectionNode("selection_statement");
	                                            temp -> addChild(new ASTNode("IF"));
                                                temp -> addChild($3);
                                                temp -> addChild($5);
                                                temp -> addChild(new ASTNode("ELSE"));
                                                temp -> addChild(new ASTNode("NAN"));
                                                $$ = temp;
                                                parserOutput("selection_statement -> IF OPAREN expression CPAREN statement"); }
	| IF OPAREN expression CPAREN statement ELSE statement {ASTNode* temp = new ASTSelectionNode("selection_statement");
                                                            temp -> addChild(new ASTNode("IF"));
                                                            temp -> addChild($3);
                                                            temp -> addChild($5);
                                                            temp -> addChild(new ASTNode("ELSE"));
                                                            temp -> addChild($7);
                                                            $$ = temp;
                                                            parserOutput("selection_statement -> IF OPAREN expression CPAREN statement ELSE statement"); }
	| SWITCH OPAREN expression CPAREN statement {ASTNode* temp = new ASTNode("selection_statement"); // TODO: Switch statements? Unlikely but we will see.
                                                     temp -> addChild(new ASTNode("SWITCH"));
                                                     temp -> addChild($3);
                                                     temp -> addChild($5);
                                                     $$ = temp;
                                                     parserOutput("selection_statement -> SWITCH OPAREN expression CPAREN statement"); }
	;

iteration_statement
	: WHILE OPAREN expression CPAREN statement {ASTIterationNode* temp = new ASTIterationNode("iteration_statement");
                                                    temp -> addChild(new ASTNode("WHILE"));
                                                    temp -> addChild(new ASTNode("NAN"));
                                                    temp -> addChild($3);
                                                    temp -> addChild(new ASTNode("NAN"));
                                                    temp -> addChild($5);
                                                    $$ = temp;
                                                    parserOutput("iteration_statement -> WHILE OPAREN expression CPAREN statement"); }
	| DO statement WHILE OPAREN expression CPAREN SEMICOLON { ASTIterationNode* temp = new ASTIterationNode("iteration_statement");
                                                              temp -> addChild(new ASTNode("DO"));
                                                              temp -> addChild(new ASTNode("NAN"));
                                                              temp -> addChild($5);
                                                              temp -> addChild(new ASTNode("WHILE"));
                                                              temp -> addChild($2);
                                                              $$ = temp;
                                                              parserOutput("iteration_statement -> DO statement WHILE OPAREN expression CPAREN SEMICOLON"); }
	| FOR OPAREN SEMICOLON SEMICOLON CPAREN statement { ASTIterationNode* temp = new ASTIterationNode("iteration_statement");
                                                          temp -> addChild(new ASTNode("FOR"));
                                                          temp -> addChild(new ASTNode("NAN"));
                                                          temp -> addChild(new ASTNode("NAN"));
                                                          temp -> addChild(new ASTNode("NAN"));
                                                          temp -> addChild($6);
                                                          $$ = temp;
                                                          parserOutput("iteration_statement -> FOR OPAREN SEMICOLON SEMICOLON CPAREN statement"); }
	| FOR OPAREN SEMICOLON SEMICOLON expression CPAREN statement { ASTIterationNode* temp = new ASTIterationNode("iteration_statement");
                                                                      temp -> addChild(new ASTNode("FOR"));
                                                                      temp -> addChild(new ASTNode("NAN"));
                                                                      temp -> addChild(new ASTNode("NAN"));
                                                                      temp -> addChild($5);
                                                                      temp -> addChild($7);
                                                                      $$ = temp;
                                                                      parserOutput("iteration_statement -> FOR OPAREN SEMICOLON SEMICOLON expression CPAREN statement"); }
	| FOR OPAREN SEMICOLON expression SEMICOLON CPAREN statement {ASTIterationNode* temp = new ASTIterationNode("iteration_statement");
                                                                      temp -> addChild(new ASTNode("FOR"));
                                                                      temp -> addChild(new ASTNode("NAN"));
                                                                      temp -> addChild($4);
                                                                      temp -> addChild(new ASTNode("NAN"));
                                                                      temp -> addChild($7);
                                                                      $$ = temp;
                                                                      parserOutput("iteration_statement -> FOR OPAREN SEMICOLON expression SEMICOLON CPAREN statement"); }
	| FOR OPAREN SEMICOLON expression SEMICOLON expression CPAREN statement { ASTIterationNode* temp = new ASTIterationNode("iteration_statement");
                                                                                  temp -> addChild(new ASTNode("FOR"));
                                                                                  temp -> addChild(new ASTNode("NAN"));
                                                                                  temp -> addChild($4);
                                                                                  temp -> addChild($6);
                                                                                  temp -> addChild($8);
                                                                                  $$ = temp;
                                                                                  parserOutput("iteration_statement -> FOR OPAREN SEMICOLON expression SEMICOLON expression CPAREN statement"); }
	| FOR OPAREN expression SEMICOLON SEMICOLON CPAREN statement { ASTIterationNode* temp = new ASTIterationNode("iteration_statement");
                                                                       temp -> addChild(new ASTNode("FOR"));
                                                                       temp -> addChild($3);
                                                                       temp -> addChild(new ASTNode("NAN"));
                                                                       temp -> addChild(new ASTNode("NAN"));
                                                                       temp -> addChild($7);
                                                                       $$ = temp;
                                                                       parserOutput("iteration_statement -> FOR OPAREN expression SEMICOLON SEMICOLON CPAREN statement"); }
	| FOR OPAREN expression SEMICOLON SEMICOLON expression CPAREN statement {ASTIterationNode* temp = new ASTIterationNode("iteration_statement");
                                                                                 temp -> addChild(new ASTNode("FOR"));
                                                                                 temp -> addChild($3);
                                                                                 temp -> addChild(new ASTNode("NAN"));
                                                                                 temp -> addChild($6);
                                                                                 temp -> addChild($8);
                                                                                 $$ = temp;
                                                                                 parserOutput("iteration_statement -> FOR OPAREN expression SEMICOLON SEMICOLON expression CPAREN statement"); }
	| FOR OPAREN expression SEMICOLON expression SEMICOLON CPAREN statement {ASTIterationNode* temp = new ASTIterationNode("iteration_statement");
                                                                                 temp -> addChild(new ASTNode("FOR"));
                                                                                 temp -> addChild($3);
                                                                                 temp -> addChild($5);
                                                                                 temp -> addChild(new ASTNode("NAN"));
                                                                                 temp -> addChild($8);
                                                                                 $$ = temp;
                                                                                 parserOutput("iteration_statement -> FOR OPAREN expression SEMICOLON expression SEMICOLON CPAREN statement"); }
	| FOR OPAREN expression SEMICOLON expression SEMICOLON expression CPAREN statement { ASTIterationNode* temp = new ASTIterationNode("iteration_statement");
                                                                                         temp -> addChild(new ASTNode("FOR"));
                                                                                         temp -> addChild($3);
                                                                                         temp -> addChild($5);
                                                                                         temp -> addChild($7);
                                                                                         temp -> addChild($9);
                                                                                         $$ = temp;
                                                                                         parserOutput("iteration_statement -> FOR OPAREN expression SEMICOLON expression SEMICOLON expression CPAREN statement"); }
	;

jump_statement
	: GOTO identifier SEMICOLON { ASTNode* temp = new ASTNode("jump_statement");
                                  temp -> addChild(new ASTNode("GOTO"));
                                  temp -> addChild($2);
                                  $$ = temp;
                                  parserOutput("jump_statement -> GOTO identifier SEMICOLON"); }
	| CONTINUE SEMICOLON { $$ = new ASTNode("CONTINUE"); parserOutput("jump_statement -> CONTINUE SEMICOLON"); }
	| BREAK SEMICOLON { $$ = new ASTNode("BREAK"); parserOutput("jump_statement -> BREAK SEMICOLON"); }
	| RETURN SEMICOLON { $$ = new ASTNode("RETURN"); parserOutput("jump_statement -> RETURN SEMICOLON"); }
	| RETURN expression SEMICOLON { ASTNode* temp = new ASTNode("jump_statement");
                                      temp -> addChild(new ASTNode("RETURN"));
                                      temp -> addChild($2);
                                      $$ = temp;
                                      parserOutput("jump_statement -> RETURN expression SEMICOLON"); }
	;

expression
	: assignment_expression { $$ = $1; parserOutput("expression -> assignment_expression"); }
	| expression COMMA assignment_expression { ASTNode* temp = new ASTNode("expression");
                                                 temp -> addChild($1);
                                                 temp -> addChild($3);
                                                 $$ = temp;
                                                 parserOutput("expression -> expression COMMA assignment_expression"); }
	;

assignment_expression
	: conditional_expression { $$ = $1; parserOutput("assignment_expression -> conditional_expression"); }
	| unary_expression assignment_operator assignment_expression { $$ = new ASTAssignNode("enumerator", $1, $2, $3);
                                                                    parserOutput("assignment_expression -> unary_expression assignment_operator assignment_expression"); }
	;

assignment_operator
	: ASSIGN { $$ = new ASTNode("ASSIGN"); parserOutput("assignment_operator -> ASSIGN"); }
	| MUL_ASSIGN { $$ = new ASTNode("MUL_ASSIGN"); parserOutput("assignment_operator -> MUL_ASSIGN"); }
	| DIV_ASSIGN { $$ = new ASTNode("DIV_ASSIGN"); parserOutput("assignment_operator -> DIV_ASSIGN"); }
	| MOD_ASSIGN { $$ = new ASTNode("MOD_ASSIGN"); parserOutput("assignment_operator -> MOD_ASSIGN"); }
	| ADD_ASSIGN { $$ = new ASTNode("ADD_ASSIGN"); parserOutput("assignment_operator -> ADD_ASSIGN"); }
	| SUB_ASSIGN { $$ = new ASTNode("SUB_ASSIGN"); parserOutput("assignment_operator -> SUB_ASSIGN"); }
	| B_SL_ASSIGN { $$ = new ASTNode("B_SL_ASSIGN"); parserOutput("assignment_operator -> B_SL_ASSIGN"); }
	| B_SR_ASSIGN {$$ = new ASTNode("B_SR_ASSIGN"); parserOutput("assignment_operator -> B_SR_ASSIGN"); }
	| B_AND_ASSIGN { $$ = new ASTNode("B_AND_ASSIGN"); parserOutput("assignment_operator -> B_AND_ASSIGN"); }
	| B_XOR_ASSIGN { $$ = new ASTNode("B_XOR_ASSIGN"); parserOutput("assignment_operator -> B_XOR_ASSIGN"); }
	| B_OR_ASSIGN { $$ = new ASTNode("B_OR_ASSIGN"); parserOutput("assignment_operator -> B_OR_ASSIGN"); }
	;

conditional_expression
	: logical_or_expression { $$ = $1; parserOutput("conditional_expression -> logical_or_expression"); }
	| logical_or_expression QUESTION expression COLON conditional_expression { ASTNode* temp = new ASTNode("conditional_expression");
                                                                               temp -> addChild($1);
                                                                               temp -> addChild(new ASTNode("QUESTION"));
                                                                               temp -> addChild($3);
                                                                               temp -> addChild(new ASTNode("COLON"));
                                                                               temp -> addChild($5);
                                                                               $$ = temp;
                                                                               parserOutput("conditional_expression -> logical_or_expression QUESTION expression COLON conditional_expression"); }
	;

constant_expression
	: conditional_expression { $$ = $1; parserOutput("constant_expression -> conditional_expression"); }
	;

logical_or_expression
	: logical_and_expression { $$ = $1;
	                           parserOutput("logical_or_expression -> logical_and_expression"); }
	| logical_or_expression L_OR logical_and_expression { ASTNode* temp = new ASTNode("logical_or_expression");
                                                             temp -> addChild($1);
                                                             temp -> addChild(new ASTNode("L_OR"));
                                                             temp -> addChild($3);
                                                             $$ = temp;
                                                             parserOutput("logical_or_expression -> logical_or_expression L_OR logical_and_expression"); }
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; parserOutput("logical_and_expression -> inclusive_or_expression"); }
	| logical_and_expression L_AND inclusive_or_expression { ASTNode* temp = new ASTNode("logical_and_expression");
                                                              temp -> addChild($1);
                                                              temp -> addChild(new ASTNode("L_AND"));
                                                              temp -> addChild($3);
                                                              $$ = temp;
                                                              parserOutput("logical_and_expression -> logical_and_expression L_AND inclusive_or_expression"); }
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; parserOutput("inclusive_or_expression -> exclusive_or_expression"); }
	| inclusive_or_expression B_OR exclusive_or_expression { ASTNode* temp = new ASTNode("inclusive_or_expression");
                                                               temp -> addChild($1);
                                                               temp -> addChild(new ASTNode("B_OR"));
                                                               temp -> addChild($3);
                                                               $$ = temp;
                                                               parserOutput("inclusive_or_expression -> inclusive_or_expression B_OR exclusive_or_expression"); }
	;

exclusive_or_expression
	: and_expression { $$ = $1; parserOutput("exclusive_or_expression -> and_expression"); }
	| exclusive_or_expression B_XOR and_expression { ASTNode* temp = new ASTNode("exclusive_or_expression");
                                                        temp -> addChild($1);
                                                        temp -> addChild(new ASTNode("B_XOR"));
                                                        temp -> addChild($3);
                                                        $$ = temp;
                                                        parserOutput("exclusive_or_expression -> exclusive_or_expression B_XOR and_expression"); }
	;

and_expression
	: equality_expression { $$ = $1; parserOutput("and_expression -> equality_expression"); }
	| and_expression AMPERSAND equality_expression { ASTNode* temp = new ASTNode("and_expression");
                                                     temp -> addChild($1);
                                                     temp -> addChild(new ASTNode("AMPERSAND"));
                                                     temp -> addChild($3);
                                                     $$ = temp;
                                                     parserOutput("and_expression -> and_expression AMPERSAND equality_expression"); }
	;

equality_expression
	: relational_expression { $$ = $1; parserOutput("equality_expression -> relational_expression"); }
	| equality_expression EQ_OP relational_expression { ASTRelExprNode* temp = new ASTRelExprNode("equality_expression");
                                                         temp -> addChild($1);
                                                         temp -> addChild(new ASTNode("EQ_OP"));
                                                         temp -> addChild($3);
                                                         $$ = temp;
                                                         parserOutput("equality_expression -> equality_expression EQ_OP relational_expression"); }
	| equality_expression NE_OP relational_expression { ASTRelExprNode* temp = new ASTRelExprNode("equality_expression");
                                                         temp -> addChild($1);
                                                         temp -> addChild(new ASTNode("NE_OP"));
                                                         temp -> addChild($3);
                                                         $$ = temp;
                                                         parserOutput("equality_expression -> equality_expression NE_OP relational_expression"); }
	;

relational_expression
	: shift_expression { $$ = $1; parserOutput("relational_expression -> shift_expression"); }
	| relational_expression LT_OP shift_expression { ASTRelExprNode* temp = new ASTRelExprNode("relational_expression");
                                                      temp -> addChild($1);
                                                      temp -> addChild(new ASTNode("LT_OP"));
                                                      temp -> addChild($3);
                                                      $$ = temp;
                                                      parserOutput("relational_expression -> relational_expression LT_OP shift_expression"); }
	| relational_expression GT_OP shift_expression { ASTRelExprNode* temp = new ASTRelExprNode("relational_expression");
                                                       temp -> addChild($1);
                                                       temp -> addChild(new ASTNode("GT_OP"));
                                                       temp -> addChild($3);
                                                       $$ = temp;
                                                       parserOutput("relational_expression -> relational_expression GT_OP shift_expression"); }
	| relational_expression LE_OP shift_expression { ASTRelExprNode* temp = new ASTRelExprNode("relational_expression");
                                                       temp -> addChild($1);
                                                       temp -> addChild(new ASTNode("LE_OP"));
                                                       temp -> addChild($3);
                                                       $$ = temp;
                                                       parserOutput("relational_expression -> relational_expression LE_OP shift_expression"); }
	| relational_expression GE_OP shift_expression { ASTRelExprNode* temp = new ASTRelExprNode("relational_expression");
                                                       temp -> addChild($1);
                                                       temp -> addChild(new ASTNode("GE_OP"));
                                                       temp -> addChild($3);
                                                       $$ = temp;
                                                       parserOutput("relational_expression -> relational_expression GE_OP shift_expression"); }
	;

shift_expression
	: additive_expression { $$ = $1; parserOutput("shift_expression -> additive_expression"); }
	| shift_expression B_SL additive_expression { ASTNode* temp = new ASTNode("shift_expression");
                                                    temp -> addChild($1);
                                                    temp -> addChild(new ASTNode("B_SL"));
                                                    temp -> addChild($3);
                                                    $$ = temp;
                                                    parserOutput("shift_expression -> shift_expression B_SL additive_expression"); }
	| shift_expression B_SR additive_expression { ASTNode* temp = new ASTNode("shift_expression");
                                                      temp -> addChild($1);
                                                      temp -> addChild(new ASTNode("B_SR"));
                                                      temp -> addChild($3);
                                                      $$ = temp;
                                                      parserOutput("shift_expression -> shift_expression B_SR additive_expression"); }
	;

additive_expression
	: multiplicative_expression { $$ = $1; parserOutput("additive_expression -> multiplicative_expression"); }
	| additive_expression ADD multiplicative_expression { $$ = new ASTMathNode("additive_expression", $1, new ASTNode("add"), $3);
	                                                      parserOutput("additive_expression -> additive_expression ADD multiplicative_expression"); }
	| additive_expression SUB multiplicative_expression { $$ = new ASTMathNode("additive_expression", $1, new ASTNode("sub"), $3);
                                                          parserOutput("additive_expression -> additive_expression SUB multiplicative_expression"); }
	;

multiplicative_expression
	: cast_expression { $$ = $1; parserOutput("multiplicative_expression -> cast_expression"); }
	| multiplicative_expression STAR cast_expression { $$ = new ASTMathNode("multiplicative_expression", $1, new ASTNode("mult"), $3);
                                                       parserOutput("multiplicative_expression -> multiplicative_expression STAR cast_expression"); }
	| multiplicative_expression DIV cast_expression { $$ = new ASTMathNode("multiplicative_expression", $1, new ASTNode("div"), $3);
													   parserOutput("multiplicative_expression -> multiplicative_expression DIV cast_expression"); }
	| multiplicative_expression MOD cast_expression {  $$ = new ASTMathNode("multiplicative_expression", $1, new ASTNode("mod"), $3); //TODO check for ints in MOD
                                                       parserOutput("multiplicative_expression -> multiplicative_expression MOD cast_expression"); }
	;

cast_expression
	: unary_expression { $$ = $1;

	                     parserOutput("cast_expression -> unary_expression"); }
	| OPAREN type_name CPAREN cast_expression { ASTCastNode* temp = new ASTCastNode("cast_node");
                                                   temp -> setType($2 -> getType());
                                                   //temp -> addChild($2);
                                                   temp -> addChild($4);
                                                   $$ = temp;
                                                   parserOutput("cast_expression -> OPAREN type_name CPAREN cast_expression"); }
	;

unary_expression
	: postfix_expression { $$ = $1;  parserOutput("unary_expression -> postfix_expression"); }
	| INC_OP unary_expression { ASTNode* temp = new ASTNode("unary_expression");
                                   temp -> addChild(new ASTNode("INC_OP"));
                                   temp -> addChild($2);
                                   $$ = temp;
                                   parserOutput("unary_expression -> INC_OP unary_expression"); }
	| DEC_OP unary_expression { ASTNode* temp = new ASTNode("unary_expression");
                                   temp -> addChild(new ASTNode("DEC_OP"));
                                   temp -> addChild($2);
                                   $$ = temp;
                                   parserOutput("unary_expression -> DEC_OP unary_expression"); }
    | unary_operator cast_expression { ASTNode* temp = new ASTNode("unary_expression");
                                      temp -> addChild($1);
                                      temp -> addChild($2);
                                      $$ = temp;
                                      parserOutput("unary_expression -> unary_operator cast_expression"); }
	| SIZEOF unary_expression { ASTNode* temp = new ASTNode("unary_expression");
                                   temp -> addChild(new ASTNode("SIZEOF"));
                                   temp -> addChild($2);
                                   $$ = temp;
                                   parserOutput("unary_expression -> SIZEOF unary_expression"); }
	| SIZEOF OPAREN type_name CPAREN { ASTNode* temp = new ASTNode("unary_expression");
                                          temp -> addChild(new ASTNode("SIZEOF"));
                                          temp -> addChild($3);
                                          $$ = temp;
                                          parserOutput("unary_expression -> SIZEOF OPAREN type_name CPAREN"); }
	;

unary_operator
	: AMPERSAND { $$ = new ASTNode("AMPERSAND"); parserOutput("unary_operator -> AMPERSAND"); }
	| STAR { $$ = new ASTNode("STAR"); parserOutput("unary_operator -> STAR"); }
	| ADD { $$ = new ASTNode("add"); parserOutput("unary_operator -> ADD"); }
	| SUB { $$ = new ASTNode("sub"); parserOutput("unary_operator -> SUB"); }
	| B_NOT { $$ = new ASTNode("B_NOT"); parserOutput("unary_operator -> B_NOT"); }
	| L_NOT { $$ = new ASTNode("L_NOT"); parserOutput("unary_operator -> L_NOT"); }
	;

postfix_expression
	: primary_expression { $$ = $1; parserOutput("postfix_expression -> primary_expression"); }
    | postfix_expression OBRACKET expression CBRACKET { ASTArrayNode* temp = new ASTArrayNode("array_node", $1);
                                                        string tempId;
                                                        int tempType;
                                                        if( $1->getLabel() == "IDENTIFIER")
                                                        {
                                                            tempId = ( (ASTIdNode*) $1)->getId();
                                                            tempType = ( (ASTIdNode*) $1)->getType();
                                                        } else
                                                        {
                                                            tempId = ( (ASTArrayNode*) $1)->getId();
                                                            tempType = ( (ASTArrayNode*) $1)->getType();
                                                        }
                                                        temp->setId( tempId );
                                                        temp->setType( tempType );
                                                        SymbolNode arrayNode = st.searchAll( tempId ).second->second;
                                                        if( arrayNode.getDimensions().size() < temp->getChildren().size() )
                                                        {
                                                            cerr << "Too many indexes on array " << tempId << endl;
                                                            exit(-1);
                                                        }
                                                        list<int> tempDimensions;
                                                        for(int i = 0 ; i < arrayNode.getDimensions().size() ; ++i)
                                                        {
                                                            tempDimensions.push_front( arrayNode.getDimensions()[i] );
                                                        }
                                                        temp->setDimensions( tempDimensions );
    												 	 temp->addChild( $3 );
                                                        $$ = temp;
                                                        parserOutput("postfix_expression -> postfix_expression OBRACKET expression CBRACKET"); }
	| postfix_expression OPAREN CPAREN { $$ = new ASTFunctionCallNode("function_call", $1); parserOutput("postfix_expression -> postfix_expression OPAREN CPAREN"); }
	| postfix_expression OPAREN argument_expression_list CPAREN {ASTFunctionCallNode* temp = new ASTFunctionCallNode("function_call", $1, $3);
                                                                   $$ = temp;
                                                                   parserOutput("postfix_expression -> postfix_expression OPAREN argument_expression_list CPAREN"); }
	| postfix_expression PERIOD identifier { ASTNode* temp = new ASTNode("postfix_expression");
                                               temp -> addChild($1);
                                               temp -> addChild(new ASTNode("PERIOD"));
                                               temp -> addChild($3);
                                               $$ = temp;
                                               parserOutput("postfix_expression -> postfix_expression PERIOD identifier"); }
	| postfix_expression ARROW identifier { ASTNode* temp = new ASTNode("postfix_expression");
                                              temp -> addChild($1);
                                              temp -> addChild(new ASTNode("ARROW"));
                                              temp -> addChild($3);
                                              $$ = temp;
                                              parserOutput("postfix_expression -> postfix_expression ARROW identifier"); }
	| postfix_expression INC_OP { ASTNode* temp = new ASTNode("postfix_expression");
                                    temp -> addChild($1);
                                    temp -> addChild(new ASTNode("INC_OP"));
                                    $$ = temp;
                                    parserOutput("postfix_expression -> postfix_expression INC_OP"); }
	| postfix_expression DEC_OP { ASTNode* temp = new ASTNode("postfix_expression");
                                    temp -> addChild($1);
                                    temp -> addChild(new ASTNode("DEC_OP"));
                                    $$ = temp;
                                    parserOutput("postfix_expression -> postfix_expression DEC_OP"); }
	;

primary_expression
	: identifier {  $$ = $1;
					parserOutput("primary_expression -> identifier"); }
	| constant { $$ = $1; parserOutput("primary_expression -> constant"); }
	| string { $$ = $1; parserOutput("primary_expression -> string"); }
	| OPAREN expression CPAREN { $$ = $2; parserOutput("primary_expression -> OPAREN expression CPAREN"); }
	;

argument_expression_list
	: assignment_expression { $$ = $1; parserOutput("argument_expression_list -> assignment_expression"); }
	| argument_expression_list COMMA assignment_expression { ASTNode* temp = new ASTNode("argument_expression_list");
                                                               temp -> addChild($1);
                                                               temp -> addChild($3);
                                                               $$ = temp;
                                                               parserOutput("argument_expression_list -> argument_expression_list COMMA assignment_expression"); }
	;

constant
	: INTEGER_CONSTANT {    int value;
                            valueUnion temp;
                            try{
                                value = stoi(yylval.sval);
                                temp.intVal = value;
                            }
                            catch(...)
                            {
                                errorStream << "Error converting string to int in INT_CONSTANT" << endl;
                                return 1;
                            }
                            $$ = new ASTConstNode("INT_CONSTANT", Int, temp);
	                        parserOutput("constant -> INTEGER_CONSTANT"); }
	| CHARACTER_CONSTANT {  char value;
                            valueUnion temp;
                            try{
                                value = yylval.sval[1]; //Gets the character. Does not work for escape characters
                                temp.charVal = value;
                            }
                            catch(...)
                            {
                                errorStream << "Error converting string to char in CHAR_CONSTANT" << endl;
                                return 1;
                            }
                            $$ = new ASTConstNode("CHAR_CONSTANT", Char, temp);
                            parserOutput("constant -> CHARACTER_CONSTANT"); }
	| FLOATING_CONSTANT { float value;
	                      valueUnion temp;
                          try{
                              value = stof(yylval.sval);
                              temp.fVal = value;
	                      }
	                      catch(...)
                          {
                              errorStream << "Error converting string to float in FLOATING_CONSTANT" << endl;
                              return 1;
                          }
                          $$ = new ASTConstNode("FLOAT_CONSTANT", Float, temp);
                          parserOutput("constant -> FLOATING_CONSTANT"); }
	| ENUMERATION_CONSTANT { ASTVariableNode* temp = new ASTVariableNode("ENUMERATION_CONSTANT");
                             						  temp->setType(Enum);
                             						  $$ = temp;
                             						   parserOutput("constant -> ENUMERATION_CONSTANT"); }
	;

string
	: STRING_LITERAL { $$ = new ASTNode("STRING_LITERAL"); parserOutput("string -> STRING_LITERAL"); }
	;

identifier
	: IDENTIFIER {
					ASTIdNode* temp = new ASTIdNode("IDENTIFIER", yylval.sval);
					string outputString = "identifier -> IDENTIFIER (";
					outputString += yylval.sval;
					outputString += ")";
                    parserOutput(outputString);
                    nodeIdentifier = yylval.sval; 
                    nodeLineNumber = line;
                    if (!st.getInsertMode())
                    {
                    	if(st.searchAll(nodeIdentifier).first == -1)
						{
                        	yyerror(NULL);
                        	return 1;
						}
						SymbolNode idNode = st.searchAll(yylval.sval).second->second;
                        temp->setType( idNode.getTypeSpecifierIndex() );
						temp->setOffset( idNode.offset );
                    }
					$$ = temp;
                 }
	;

%%

int main(int argc, char** argv)
{
	int outputIndex = parseCommandLine(argc, argv); //Returns the index of the output file in argv or 0 if there is no -o

    root = new ASTNode(argv[1]);
    AST tree(root);
	yyparse();
	tree.printTree();
	tree.walk();

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
    //cout << s << endl;
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

	if(argc == 0)
    {
	    cerr << "No input file" << endl;
	    exit(-1);
    }
	inputFileName = argv[1];
    inputFile.open(inputFileName); //Assumes the first command line arguement is the input file.
    FILE* inputStream = fopen(inputFileName.c_str(), "r");
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


void recursiveOffsetInitDeclList( ASTNode* currentNode )
{
    if( currentNode->getLabel() == "init_declarator" )
    {
        currentNode = currentNode->getChildren().front();
    }

    if( currentNode->getLabel() == "init_declarator_list" or
        currentNode->getLabel() == "Declaration")
    {
        recursiveOffsetInitDeclList( currentNode->getChildren().front() );
        recursiveOffsetInitDeclList( currentNode->getChildren().back() );
    } else if( currentNode->getLabel() == "array_node")
    {
        auto symbolPair = st.searchAll( ( (ASTArrayNode*) currentNode )->getId()  ).second;
        currentOffset += currentNode -> getActivationFrameSize();
        currentNode->setOffset( currentOffset );
        symbolPair->second.offset = currentOffset;
        symbolPair->second.setTypeSpecifierIndex( currentNode->getType() );
    } else if ( currentNode->getLabel() == "IDENTIFIER" )
    {
        auto symbolPair = st.searchAll( ( (ASTIdNode*) currentNode )->getId()  ).second;
        currentOffset += currentNode -> getActivationFrameSize();
        currentNode->setOffset( currentOffset );
        symbolPair->second.offset = currentOffset;
        symbolPair->second.setTypeSpecifierIndex( currentNode->getType() );
    } else
    {
        cerr << "Something went wrong in recursiveOffsetInitDeclList." << endl;
    }

}


void handleOffsetType( int inputType )
{
    switch (inputType)
    {
        case Char:
            break;
        case Short:
        case Int:
        case Long:
        case Float:
            if( currentOffset % 4 != 0 )
                currentOffset = (currentOffset + 4) - ( currentOffset + 4 ) % 4;
            break;
        case Double:
            if( currentOffset % 8 != 0 )
                currentOffset = (currentOffset + 8) - ( currentOffset + 8 ) % 8;
    }
}