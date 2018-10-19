//
// Created by WIll on 10/3/2018.
//

#include "node.h"

const string &node::getIdentifier () const
{
	return identifier;
}

void node::setIdentifier (const string &identifier)
{
	node::identifier = identifier;
}

int node::getTypeStorageClassIndex () const
{
	return typeStorageClassIndex;
}

void node::setTypeStorageClassIndex (int typeStorageClassIndex)
{
	node::typeStorageClassIndex = typeStorageClassIndex;
}

int node::getTypeQualifierIndex () const
{
	return typeQualifierIndex;
}

void node::setTypeQualifierIndex (int typeQualifierIndex)
{
	node::typeQualifierIndex = typeQualifierIndex;
}

int node::getTypeSpecifierIndex () const
{
	return typeSpecifierIndex;
}

void node::setTypeSpecifierIndex (int typeSpecifierIndex)
{
	node::typeSpecifierIndex = typeSpecifierIndex;
}

int node::getVarScopeLevel () const
{
	return varScopeLevel;
}

void node::setVarScopeLevel (int varScopeLevel)
{
	node::varScopeLevel = varScopeLevel;
}

int node::getLineNum () const
{
	return lineNum;
}

void node::setLineNum (int lineNum)
{
	node::lineNum = lineNum;
}

bool node::getIsFunction () const
{
	return isFunction;
}

void node::setIsFunction (bool isFunction)
{
	node::isFunction = isFunction;
}

bool node::getIsSigned () const
{
	return isSigned;
}

void node::setIsSigned (bool isSigned)
{
	node::isSigned = isSigned;
}

ostream &operator<< (ostream &os, const node &node1)
{
	os << "identifier: \"" << node1.identifier << "\"" << endl;
	os << "\tlineNum: " << node1.lineNum << " colNum: " << node1.colNum << " scopeLevel: " << node1.varScopeLevel;
	os << " Function: " << (node1.isFunction ? "True" : "False") << endl;
	os << "\tSignature: \"";

	switch (node1.typeQualifierIndex)
	{
		case Const:
			os << "const ";
			break;
		case Volatile:
			os << "volatile ";
			break;
		case Both:
			os << "const volatile ";
			break;
		default:
			break;
	}

	switch (node1.typeStorageClassIndex)
	{
		case Auto:
			os << "auto ";
			break;
		case Register:
			os << "register ";
			break;
		case Static:
			os << "static ";
			break;
		case Extern:
			os << "extern ";
			break;
		case Typedef:
			os << "typedef ";
			break;
		default:
			break;
	}

	if(node1.isSigned)
		os << "signed ";
	else
		os << "unsigned ";

	switch (node1.typeSpecifierIndex)
	{
		case Void:
			os << "void";
			break;
		case Char:
			os << "char";
			break;
		case Short:
			os << "short";
			break;
		case Int:
			os << "int";
			break;
		case Long:
			os << "long";
			break;
		case Float:
			os << "float";
			break;
		case Double:
			os << "double";
			break;
		case Struct:
			os << "struct";
			break;
		default:
			break;
	}

	os << "\"" << endl;
	return os;
}

node::node (const string &identifier, int lineNum, int colNum, int typeSpecifier)
		: identifier(identifier), lineNum(lineNum), typeSpecifierIndex(typeSpecifier), colNum(colNum)
{
	varScopeLevel = -1;
	isFunction = false;
	isSigned = true;
	typeQualifierIndex = -1;
	typeStorageClassIndex = -1;
}
