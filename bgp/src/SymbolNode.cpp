//
// Created by WIll on 10/3/2018.
//

#include "SymbolNode.h"

///A stringstream to output error/warnings
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
 * @brief An insertion operator to help print the Node
 * @param os The ostream object
 * @param table The Node to be printed
 * @return The ostream with everything to print
 * @note Uses the enums: storage_class_specifier, type_specifier, type_qualifier, parameterSign, and parameterIndices
 * 			from SymbolNode.h
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
		if(!node.functionParameters.empty())
		{
			for (auto functionParameter : node.functionParameters)
			{
				os << "\t\t";
				switch (functionParameter.begin()[parameterQualifierIndex])
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

				switch (functionParameter.begin()[parameterSignIndex])
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

				switch (functionParameter.begin()[parameterSpecifierIndex])
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
	if(node.getIsArray())
	{
		os << "\tArray Dimensions: " << node.getIdentifier();
		for(int arrayDimensions : node.arrayDimensions)
			os << '[' << arrayDimensions << ']';
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
	isFunctionDefined = false;
}

bool SymbolNode::getIsArray() const
{
	return isArray;
}

void SymbolNode::setIsArray (bool isArray)
{
	SymbolNode::isArray = isArray;
}

/**
 * @brief A function to push parameters onto a function node in the Symbol Table
 * @note Uses the enum parameterIndices from SymbolNode.h
 * @note the default values are:
 * 			index parameterQualifierIndex (Zero): The qualifier
 * 															default: -2 (for no qualifier)
 * 			index parameterSignIndex (One): The sign of parameter
 * 															default: Signed (Zero)
* 			index parameterSpecifierIndex (Two): The parameter specifier
 * 															default: Int (Three)
 * @return True if the function flag is set to true
 * 			false if the function flag is set to false
 * 				Will output an error message to errorStream if the function flag is not set
 */
bool SymbolNode::pushFunctionParameter ()
{
	if(isFunction)
	{
		array<int, 3> ar = {-2, Signed, Int};
		functionParameters.push_back(ar);
		return true;
	} else
	{
		errorStream << "ERROR: Node: \"" << identifier << "\" is not a function. Cannot add parameter" << endl;
		return false;
	}

}

/**
 * @brief A function to set the parameter's type using the enum parameterIndices in SymbolNode.h
 * @return True if the function flag is set to true
 * 			false if the function flag is set to false
 * 				Will output an error message to errorStream if the function flag is not set
 */
bool SymbolNode::setCurrentFunctionParameterTypeSpecifier (int typeSpecifier)
{
	if(isFunction)
	{
		functionParameters.back()[parameterSpecifierIndex] = typeSpecifier;
		return true;
	}
	else
	{
		errorStream << "ERROR: Node: \"" << identifier << "\" is not a function. Cannot set type specifier" << endl;
		return false;
	}
}

/**
 * @brief A function to set the parameter's sign using the enum parameterIndices in SymbolNode.h
 * @return True if the function flag is set to true
 * 			false if the function flag is set to false
 * 				Will output an error message to errorStream if the function flag is not set
 */
bool SymbolNode::setCurrentFunctionParameterSign (int sign)
{
	if(isFunction)
	{
		functionParameters.back()[parameterSignIndex] = sign;
		return true;
	}
	else
	{
		errorStream << "ERROR: Node: \"" << identifier << "\" is not a function. Cannot set parameter parameterSign" << endl;
		return false;
	}
}

/**
 * @brief A function to set the parameter's qualifier using the enum parameterIndices in SymbolNode.h
 * @return True if the function flag is set to true
 * 			false if the function flag is set to false
 * 				Will output an error message to errorStream if the function flag is not set
 */
bool SymbolNode::setCurrentFunctionParameterTypeQualifier (int typeQualifier)
{
	if(isFunction)
	{
		functionParameters.back()[parameterQualifierIndex] = typeQualifier;
		return true;
	}
	else
	{
		errorStream << "ERROR: Node: \"" << identifier << "\" is not a function. Cannot type qualifier" << endl;
		return false;
	}
}

/**
 * @brief A function to get the parameter's type using the enum parameterIndices in SymbolNode.h
 * @return The integer mapped to the type using the enum in SymbolNode.h
 * 			-1 if the function flag is set to false
 * 				Will output an error message to errorStream if the function flag is not set
 */
int SymbolNode::getCurrentFunctionParameterTypeSpecifier ()
{
	if(isFunction)
		return functionParameters.back()[parameterSpecifierIndex];
	else
	{
		errorStream << "ERROR: Node: \"" << identifier << "\" is not a function. Cannot get type specifier" << endl;
		return -1;
	}
}

/**
 * @brief A function to get the parameter's sign using the enum parameterIndices in SymbolNode.h
 * @return The integer mapped to the type using the enum in SymbolNode.h
 * 			-1 if the function flag is set to false
 * 				Will output an error message to errorStream if the function flag is not set
 */
int SymbolNode::getCurrentFunctionParameterSign ()
{
	if(isFunction)
		return functionParameters.back()[parameterSignIndex];
	else
	{
		errorStream << "ERROR: Node: \"" << identifier << "\" is not a function. Cannot get parameter parameterSign" << endl;
		return -1;
	}
}

/**
 * @brief A function to get the parameter's qualifier using the enum parameterIndices in SymbolNode.h
 * @return The integer mapped to the type using the enum in SymbolNode.h
 * 			-1 if the function flag is set to false
 * 				Will output an error message to errorStream if the function flag is not set
 */
int SymbolNode::getCurrentFunctionParameterTypeQualifier ()
{
	if(isFunction)
		return functionParameters.back()[parameterQualifierIndex];
	else
	{
		errorStream << "ERROR: Node: \"" << identifier << "\" is not a function. Cannot get parameter qualifier" << endl;
		return -1;
	}
}

bool SymbolNode::addArrayDimension (int dimension)
{
	if(isArray)
	{
		arrayDimensions.push_back(dimension);
		return true;
	}
	else
	{
		errorStream << "ERROR: Node: \"" << identifier << "\" is not an array. Cannot add array dimension" << endl;
		return false;
	}
}

bool SymbolNode::isIsFunctionDefined() const
{
	return isFunctionDefined;
}

void SymbolNode::setIsFunctionDefined(bool isFunctionDefined)
{
	SymbolNode::isFunctionDefined = isFunctionDefined;
}

const list<array<int, 3>> &SymbolNode::getFunctionParameters() const
{
	return functionParameters;
}



vector<int> SymbolNode::getDimensions () const
{
	return arrayDimensions;
}
