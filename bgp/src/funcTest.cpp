//
// Created by WIll on 10/30/2018.
//

#include "SymbolTable.h"
#include "SymbolNode.h"
#include "sstream"

stringstream errorStream;

int main()
{
	SymbolTable symTable;
	SymbolNode node("foo", 1, 1, Char);
	//node.setIsFunction(true);
	node.pushFunctionParameter();
	node.setCurrentFunctionParameterSign(Unsigned);
	node.setCurrentFunctionParameterTypeQualifier(Volatile);
	node.setCurrentFunctionParameterTypeSpecifier(Char);

	node.pushFunctionParameter();
	node.setCurrentFunctionParameterSign(Unsigned);
	node.setCurrentFunctionParameterTypeQualifier(Const);

	symTable.insert(node);

	cout << symTable;

	cout << errorStream.str();

}

