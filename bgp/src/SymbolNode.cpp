//
// Created by WIll on 10/3/2018.
//

#include "SymbolNode.h"

extern stringstream errorStream;

const string &SymbolNode::getIdentifier () const
{
	return identifier;
}

void SymbolNode::setIdentifier (const string &identifier)
{
	SymbolNode::identifier = identifier;
}

int SymbolNode::getTypeStorageClassIndex () const
{
	return typeStorageClassIndex;
}

void SymbolNode::setTypeStorageClassIndex (int typeStorageClassIndex)
{
	SymbolNode::typeStorageClassIndex = typeStorageClassIndex;
}

int SymbolNode::getTypeQualifierIndex () const
{
	return typeQualifierIndex;
}

void SymbolNode::setTypeQualifierIndex (int typeQualifierIndex)
{
	SymbolNode::typeQualifierIndex = typeQualifierIndex;
}

int SymbolNode::getTypeSpecifierIndex () const
{
	return typeSpecifierIndex;
}

void SymbolNode::setTypeSpecifierIndex (int typeSpecifierIndex)
{
	SymbolNode::typeSpecifierIndex = typeSpecifierIndex;
}

int SymbolNode::getVarScopeLevel () const
{
	return varScopeLevel;
}

void SymbolNode::setVarScopeLevel (int varScopeLevel)
{
	SymbolNode::varScopeLevel = varScopeLevel;
}

int SymbolNode::getLineNum () const
{
	return lineNum;
}

void SymbolNode::setLineNum (int lineNum)
{
	SymbolNode::lineNum = lineNum;
}

bool SymbolNode::getIsFunction () const
{
	return isFunction;
}

void SymbolNode::setIsFunction (bool isFunction)
{
	SymbolNode::isFunction = isFunction;
}

bool SymbolNode::getIsSigned () const
{
	return isSigned;
}

void SymbolNode::setIsSigned (bool isSigned)
{
	SymbolNode::isSigned = isSigned;
}

/**
 * @brief An inseration operator to help print the Node
 * @param os The ostream object
 * @param table The Node to be printed
 * @return The ostream with everything to print
 */
ostream &operator<< (ostream &os, const SymbolNode &node)
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

	if(node.getIsFunction())
	{
		os << "\tFunction Parameters: " << endl;
		if(node.functionParameters.size())
		{
			for (auto i = node.functionParameters.begin(); i != node.functionParameters.end(); i++)
			{
				os << "\t\t";
				switch (i->begin()[parameterQualifierIndex])
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

				switch (i->begin()[parameterSignIndex])
				{
					case Signed:
						os << "signed ";
						break;
					case Unsigned:
						os << "unsigned ";
						break;
					default:
						break;
				}

				switch (i->begin()[parameterSpecifierIndex])
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
				os << endl;
			}
		} else{
			os << "\t\tNone" << endl;
		}
	}
	return os;
}

SymbolNode::SymbolNode (const string &identifier, int lineNum, int colNum, int typeSpecifier)
		: identifier(identifier), lineNum(lineNum), typeSpecifierIndex(typeSpecifier), colNum(colNum)
{
	varScopeLevel = -1;
	isFunction = false;
	isSigned = true;
	typeQualifierIndex = -1;
	typeStorageClassIndex = -1;
	isArray = false;
}

bool SymbolNode::isIsArray () const
{
	return isArray;
}

void SymbolNode::setIsArray (bool isArray)
{
	SymbolNode::isArray = isArray;
}

void SymbolNode::pushFunctionParameter ()
{
	if(isFunction)
	{
		array<int, 3> ar = {-1, Signed, Int};
		functionParameters.push_back(ar);
	} else
		errorStream << "ERROR: Node: \"" << identifier << "\" is not a function. Cannot add parameter" << endl;

}

void SymbolNode::setCurrentFunctionParameterTypeSpecifier (int typeSpecifier)
{
	if(isFunction)
		functionParameters.back()[parameterSpecifierIndex] = typeSpecifier;
	else
		errorStream << "ERROR: Node: \"" << identifier << "\" is not a function. Cannot set type specifier" << endl;
}

void SymbolNode::setCurrentFunctionParameterSign (int sign)
{
	if(isFunction)
		functionParameters.back()[parameterSignIndex] = sign;
	else
		errorStream << "ERROR: Node: \"" << identifier << "\" is not a function. Cannot set parameter sign" << endl;
}

void SymbolNode::setCurrentFunctionParameterTypeQualifier (int typeQualifier)
{
	if(isFunction)
		functionParameters.back()[parameterQualifierIndex] = typeQualifier;
	else
		errorStream << "ERROR: Node: \"" << identifier << "\" is not a function. Cannot type qualifier" << endl;
}

int SymbolNode::getCurrentFunctionParameterTypeSpecifier ()
{
	if(isFunction)
		return functionParameters.back()[parameterSpecifierIndex];
	else
		errorStream << "ERROR: Node: \"" << identifier << "\" is not a function. Cannot get type specifier" << endl;
}

int SymbolNode::getCurrentFunctionParameterSign ()
{
	if(isFunction)
		return functionParameters.back()[parameterSignIndex];
	else
		errorStream << "ERROR: Node: \"" << identifier << "\" is not a function. Cannot get parameter sign" << endl;
}

int SymbolNode::getCurrentFunctionParameterTypeQualifier ()
{
	if(isFunction)
		return functionParameters.back()[parameterQualifierIndex];
	else
		errorStream << "ERROR: Node: \"" << identifier << "\" is not a function. Cannot get parameter qualifier" << endl;
}
