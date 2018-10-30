//
// Created by WIll on 10/3/2018.
//

#include "SymbolNode.h"

const string &Node::getIdentifier () const
{
	return identifier;
}

void Node::setIdentifier (const string &identifier)
{
	Node::identifier = identifier;
}

int Node::getTypeStorageClassIndex () const
{
	return typeStorageClassIndex;
}

void Node::setTypeStorageClassIndex (int typeStorageClassIndex)
{
	Node::typeStorageClassIndex = typeStorageClassIndex;
}

int Node::getTypeQualifierIndex () const
{
	return typeQualifierIndex;
}

void Node::setTypeQualifierIndex (int typeQualifierIndex)
{
	Node::typeQualifierIndex = typeQualifierIndex;
}

int Node::getTypeSpecifierIndex () const
{
	return typeSpecifierIndex;
}

void Node::setTypeSpecifierIndex (int typeSpecifierIndex)
{
	Node::typeSpecifierIndex = typeSpecifierIndex;
}

int Node::getVarScopeLevel () const
{
	return varScopeLevel;
}

void Node::setVarScopeLevel (int varScopeLevel)
{
	Node::varScopeLevel = varScopeLevel;
}

int Node::getLineNum () const
{
	return lineNum;
}

void Node::setLineNum (int lineNum)
{
	Node::lineNum = lineNum;
}

bool Node::getIsFunction () const
{
	return isFunction;
}

void Node::setIsFunction (bool isFunction)
{
	Node::isFunction = isFunction;
}

bool Node::getIsSigned () const
{
	return isSigned;
}

void Node::setIsSigned (bool isSigned)
{
	Node::isSigned = isSigned;
}

/**
 * @brief An inseration operator to help print the Node
 * @param os The ostream object
 * @param table The Node to be printed
 * @return The ostream with everything to print
 */
ostream &operator<< (ostream &os, const Node &node)
{
	os << "identifier: \"" << node.identifier << "\"" << endl;
	os << "\tlineNum: " << node.lineNum << " colNum: " << node.colNum << " scopeLevel: " << node.varScopeLevel;
	os << " Function: " << (node.isFunction ? "True" : "False") << endl;
	os << "\tSignature: \"";

	switch (node.typeQualifierIndex)
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

	switch (node.typeStorageClassIndex)
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

	if(node.isSigned)
		os << "signed ";
	else
		os << "unsigned ";

	switch (node.typeSpecifierIndex)
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

Node::Node (const string &identifier, int lineNum, int colNum, int typeSpecifier)
		: identifier(identifier), lineNum(lineNum), typeSpecifierIndex(typeSpecifier), colNum(colNum)
{
	varScopeLevel = -1;
	isFunction = false;
	isSigned = true;
	typeQualifierIndex = -1;
	typeStorageClassIndex = -1;
	isArray = false;
}

bool Node::isIsArray () const
{
	return isArray;
}

void Node::setIsArray (bool isArray)
{
	Node::isArray = isArray;
}
