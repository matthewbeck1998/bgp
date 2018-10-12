dvorak = " declaration 	: declaration_specifiers SEMICOLON 	| declaration_specifiers init_declarator_list SEMICOLON 	;  declaration_list 	: declaration 	| declaration_list declaration 	;  declaration_specifiers 	: storage_class_specifier 	| storage_class_specifier declaration_specifiers 	| type_specifier 	| type_specifier declaration_specifiers 	| type_qualifier  	| type_qualifier declaration_specifiers 	;  storage_class_specifier 	: AUTO 	| REGISTER 	| STATIC 	| EXTERN 	| TYPEDEF 	;  type_specifier 	: VOID 	| CHAR 	| SHORT 	| INT 	| LONG 	| FLOAT  	| DOUBLE 	| SIGNED 	| UNSIGNED 	| struct_or_union_specifier 	| enum_specifier 	| TYPEDEF_NAME 	;  type_qualifier 	: CONST 	| VOLATILE 	;  struct_or_union_specifier 	: struct_or_union identifier OBRACE struct_declaration_list CBRACE 	| struct_or_union OBRACE struct_declaration_list CBRACE 	| struct_or_union identifier 	;  struct_or_union 	: STRUCT 	| UNION 	;  struct_declaration_list 	: struct_declaration 	| struct_declaration_list struct_declaration 	;  init_declarator_list 	: init_declarator 	| init_declarator_list COMMA init_declarator 	;  init_declarator 	: declarator 	| declarator ASSIGN initializer 	;  struct_declaration 	: specifier_qualifier_list struct_declarator_list SEMICOLON 	;  specifier_qualifier_list 	: type_specifier 	| type_specifier specifier_qualifier_list 	| type_qualifier 	| type_qualifier specifier_qualifier_list 	;  struct_declarator_list 	: struct_declarator 	| struct_declarator_list COMMA struct_declarator 	;  struct_declarator 	: declarator 	| COLON constant_expression 	| declarator COLON constant_expression 	;  enum_specifier 	: ENUM OBRACE enumerator_list CBRACE 	| ENUM identifier OBRACE enumerator_list CBRACE 	| ENUM identifier 	;  enumerator_list 	: enumerator 	| enumerator_list COMMA enumerator 	;  enumerator 	: identifier 	| identifier ASSIGN constant_expression 	;  declarator 	: direct_declarator 	| pointer direct_declarator 	;  direct_declarator 	: identifier 	| OPAREN declarator CPAREN 	| direct_declarator OBRACKET CBRACKET 	| direct_declarator OBRACKET constant_expression CBRACKET 	| direct_declarator OPAREN CPAREN 	| direct_declarator OPAREN parameter_type_list CPAREN 	| direct_declarator OPAREN identifier_list CPAREN 	;  pointer 	: STAR 	| STAR type_qualifier_list 	| STAR pointer 	| STAR type_qualifier_list pointer 	;  type_qualifier_list 	: type_qualifier 	| type_qualifier_list type_qualifier 	;  parameter_type_list 	: parameter_list 	| parameter_list COMMA ELLIPSIS 	;  parameter_list 	: parameter_declaration 	| parameter_list COMMA parameter_declaration 	;  parameter_declaration 	: declaration_specifiers declarator 	| declaration_specifiers 	| declaration_specifiers abstract_declarator 	;  identifier_list 	: identifier 	| identifier_list COMMA identifier 	;  initializer 	: assignment_expression 	| OBRACE initializer_list CBRACE 	| OBRACE initializer_list COMMA CBRACE 	;  initializer_list 	: initializer 	| initializer_list COMMA initializer 	;  type_name 	: specifier_qualifier_list 	| specifier_qualifier_list abstract_declarator 	;  abstract_declarator 	: pointer 	| direct_abstract_declarator 	| pointer direct_abstract_declarator 	;  direct_abstract_declarator 	: OPAREN abstract_declarator CPAREN 	| OBRACKET CBRACKET 	| OBRACKET constant_expression CBRACKET 	| direct_abstract_declarator OBRACKET CBRACKET 	| direct_abstract_declarator OBRACKET constant_expression CBRACKET 	| OPAREN CPAREN 	| OPAREN parameter_type_list CPAREN 	| direct_abstract_declarator OPAREN CPAREN 	| direct_abstract_declarator OPAREN parameter_type_list CPAREN 	;  statement 	: labeled_statement 	| compound_statement 	| expression_statement 	| selection_statement 	| iteration_statement 	| jump_statement 	;  labeled_statement 	: identifier COLON statement 	| CASE constant_expression COLON statement 	| DEFAULT COLON statement 	;  expression_statement 	: SEMICOLON 	| expression SEMICOLON 	;  compound_statement 	: OBRACE CBRACE 	| OBRACE statement_list CBRACE 	| OBRACE declaration_list CBRACE 	| OBRACE declaration_list statement_list CBRACE 	;  statement_list 	: statement 	| statement_list statement 	;  selection_statement 	: IF OPAREN expression CPAREN statement 	| IF OPAREN expression CPAREN statement ELSE statement 	| SWITCH OPAREN expression CPAREN statement 	;  iteration_statement 	: WHILE OPAREN expression CPAREN statement 	| DO statement WHILE OPAREN expression CPAREN SEMICOLON 	| FOR OPAREN SEMICOLON SEMICOLON CPAREN statement 	| FOR OPAREN SEMICOLON SEMICOLON expression CPAREN statement 	| FOR OPAREN SEMICOLON expression SEMICOLON CPAREN statement 	| FOR OPAREN SEMICOLON expression SEMICOLON expression CPAREN statement 	| FOR OPAREN expression SEMICOLON SEMICOLON CPAREN statement 	| FOR OPAREN expression SEMICOLON SEMICOLON expression CPAREN statement 	| FOR OPAREN expression SEMICOLON expression SEMICOLON CPAREN statement 	| FOR OPAREN expression SEMICOLON expression SEMICOLON expression CPAREN statement 	;  jump_statement 	: GOTO identifier SEMICOLON 	| CONTINUE SEMICOLON 	| BREAK SEMICOLON 	| RETURN SEMICOLON 	| RETURN expression SEMICOLON 	;  expression 	: assignment_expression 	| expression COMMA assignment_expression 	;  assignment_expression 	: conditional_expression 	| unary_expression assignment_operator assignment_expression 	;  assignment_operator 	: ASSIGN 	| MUL_ASSIGN 	| DIV_ASSIGN 	| MOD_ASSIGN 	| ADD_ASSIGN 	| SUB_ASSIGN 	| B_SL_ASSIGN 	| B_SR_ASSIGN 	| B_AND_ASSIGN 	| B_XOR_ASSIGN 	| B_OR_ASSIGN 	;  conditional_expression 	: logical_or_expression 	| logical_or_expression QUESTION expression COLON conditional_expression 	;  constant_expression 	: conditional_expression 	;  logical_or_expression 	: logical_and_expression 	| logical_or_expression L_OR logical_and_expression 	;  logical_and_expression 	: inclusive_or_expression 	| logical_and_expression L_AND inclusive_or_expression 	;  inclusive_or_expression 	: exclusive_or_expression 	| inclusive_or_expression B_OR exclusive_or_expression 	;  exclusive_or_expression 	: and_expression 	| exclusive_or_expression B_XOR and_expression 	;  and_expression 	: equality_expression 	| and_expression AMPERSAND equality_expression 	;  equality_expression 	: relational_expression 	| equality_expression EQ_OP relational_expression 	| equality_expression NE_OP relational_expression 	;  relational_expression 	: shift_expression 	| relational_expression LT_OP shift_expression 	| relational_expression GT_OP shift_expression 	| relational_expression LE_OP shift_expression 	| relational_expression GE_OP shift_expression 	;  shift_expression 	: additive_expression 	| shift_expression B_SL additive_expression 	| shift_expression B_SR additive_expression 	;  additive_expression 	: multiplicative_expression 	| additive_expression ADD multiplicative_expression 	| additive_expression SUB multiplicative_expression 	;  multiplicative_expression 	: cast_expression 	| multiplicative_expression STAR cast_expression 	| multiplicative_expression DIV cast_expression 	| multiplicative_expression MOD cast_expression 	;  cast_expression 	: unary_expression 	| OPAREN type_name CPAREN cast_expression 	;  unary_expression 	: postfix_expression 	| INC_OP unary_expression 	| DEC_OP unary_expression 	| unary_operator cast_expression 	| SIZEOF unary_expression 	| SIZEOF OPAREN type_name CPAREN 	;  unary_operator 	: AMPERSAND 	| STAR 	| ADD 	| SUB 	| B_NOT 	| L_NOT 	;  postfix_expression 	: primary_expression 	| postfix_expression OBRACKET expression CBRACKET 	| postfix_expression OPAREN CPAREN 	| postfix_expression OPAREN argument_expression_list CPAREN 	| postfix_expression PERIOD identifier 	| postfix_expression ARROW identifier 	| postfix_expression INC_OP 	| postfix_expression DEC_OP 	;  primary_expression 	: identifier 	| constant 	| string 	| OPAREN expression CPAREN 	;  argument_expression_list 	: assignment_expression 	| argument_expression_list COMMA assignment_expression 	;  constant 	: INTEGER_CONSTANT 	| CHARACTER_CONSTANT 	| FLOATING_CONSTANT 	| ENUMERATION_CONSTANT 	;  string 	: STRING_LITERAL 	;  identifier 	: IDENTIFIER 	;"

dvorak_split = dvorak.split()

productions_list = []
production = []
rhs_list = []
rhs = []
in_lhs = True

for x in dvorak_split:
  if x == ":":
    in_lhs = False
  elif x == "|":
    rhs_list.append(rhs)
    rhs = []
  elif x == ";":
    in_lhs = True
    rhs_list.append(rhs)
    rhs = []
    production.append(rhs_list)
    rhs_list = []
    productions_list.append(production)
    production = []
  elif in_lhs:
    production.append(x)
  else:
    rhs.append(x)

outputStrList = []

for production in productions_list:
  lhs = production[0]
  for rhs in production[1]:
    rhs_str = " ".join(rhs)
    outputStrList.append("{ output(\"" + lhs + " -> " + rhs_str + "\"); }")

for outputStr in outputStrList:
  print(outputStr)
