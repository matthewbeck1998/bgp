#include "ASTNode.h"
#include <fstream>

int ASTNode::totalNodeCount = 0;

ASTNode::ASTNode (string node_label) : label(move(node_label))
{
	nodeNum = totalNodeCount++;
}

void ASTNode::addChild (ASTNode *addNode)
{
    if(addNode)
    {
        children.push_back(addNode);
    }
}

bool ASTNode::walk() const
{
    for(auto it = children.begin() ; it != children.end() ; ++it)
    {
        if(not (*it)->walk())
        {
            return false;
        }
    }
    return true;
}

string ASTNode::getLabel () const
{
    return label;
}

list<ASTNode *> &ASTNode::getChildren ()
{
    return children;
}

int ASTNode::getNodeNum () const
{
	return nodeNum;
}

int ASTNode::getColNum () const
{
	return colNum;
}

void ASTNode::setColNum (int colNum)
{
	ASTNode::colNum = colNum;
}

int ASTNode::getLineNum () const
{
	return lineNum;
}

void ASTNode::setLineNum (int lineNum)
{
	ASTNode::lineNum = lineNum;
}

void ASTNode::printNode (ASTNode* nodePtr, ofstream& treeOutFile)
{
	//cout << "BASE NODE" << endl;
	if(nodePtr)
	{
		treeOutFile << nodePtr->getNodeNum() << "[label = \"" << nodePtr->getLabel() << "\"];" << endl;
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			treeOutFile << nodeNum << " -> " << (*it)->getNodeNum() << endl;
			(*it)->printNode(*it, treeOutFile);
		}
	}
}


ASTMathNode::ASTMathNode (string node_label) : ASTNode::ASTNode(move(node_label))
{
}

ASTMathNode::ASTMathNode(string node_label, ASTNode* LHS, ASTNode* mathOp, ASTNode* RHS) : ASTNode::ASTNode(move(node_label))
{
	setType( getHigherType(LHS, RHS) );
	if( LHS->getType() != RHS->getType() )
    {
        if(LHS->getType() == Float)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", RHS, Float );
            addChild(LHS);
            addChild(mathOp);
            addChild(temp);
            outputStream << "WARNING: implicit conversion from " << printType(RHS) << " to " << printType(LHS) << endl;
        }
        else if(RHS->getType() == Float)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", LHS, Float );
            addChild(temp);
            addChild(mathOp);
            addChild(RHS);
            outputStream << "WARNING: implicit conversion from " << printType(LHS) << " to " << printType(RHS) << endl;
        }
        else if(LHS->getType() == Int)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", RHS, Int );
            addChild(LHS);
            addChild(mathOp);
            addChild(temp);
            outputStream << "WARNING: implicit conversion from " << printType(RHS) << " to " << printType(LHS) << endl;
        }
        else if(RHS->getType() == Int)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", LHS, Int );
            addChild(temp);
            addChild(mathOp);
            addChild(RHS);
            outputStream << "WARNING: implicit conversion from " << printType(LHS) << " to " << printType(RHS) << endl;
        }
        else if(LHS->getType() == Char)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", RHS, Char );
            addChild(LHS);
            addChild(mathOp);
            addChild(temp);
            outputStream << "WARNING: implicit conversion from " << printType(RHS) << " to " << printType(LHS) << endl;
        }
        else if(RHS->getType() == Char)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", LHS, Char );
            addChild(temp);
            addChild(mathOp);
            addChild(RHS);
            outputStream << "WARNING: implicit conversion from " << printType(LHS) << " to " << printType(RHS) << endl;
        }
        //outputStream << "Unsupported types: " << printType( LHS ) << ", " << printType( RHS ) << endl;
    } else
    {
	    addChild(LHS);
	    addChild(mathOp);
	    addChild(RHS);
    }
}

int ASTMathNode::getHigherType(ASTNode* LHS, ASTNode* RHS) const
{
	if(LHS->getType() == Float || RHS->getType() == Float)
	{
		return Float;
	}
	if(LHS->getType() == Int || RHS->getType() == Int)
	{
		return Int;
	}
	if(LHS->getType() == Char || RHS->getType() == Char)
	{
		return Char;
	}
	outputStream << "Unsupported types: " << LHS->getType() << ", " << RHS->getType() << endl;
}

bool ASTMathNode::walk() const
{
    if( ( (ASTVariableNode*) children.front() )->getType() != ( (ASTVariableNode*) children.back() )->getType())
    {
        return false;
    }
    return true;
}

void ASTMathNode::printNode (ASTNode *nodePtr, ofstream &treeOutFile)
{
	//cout << "MATH NODE" << endl;
	if(nodePtr)
	{
		treeOutFile << nodePtr->getNodeNum() << "[label = \"" << nodePtr->getLabel() << endl << "MATH NODE" <<"\"];" << endl;
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			treeOutFile << nodeNum << " -> " << (*it)->getNodeNum() << endl;
			(*it)->printNode(*it, treeOutFile);
		}
	}
}


string ASTMathNode::printType(ASTNode*& node) const
{
    switch (node->getType())
    {
        case Void:
            return "void";
        case Char:
            return "char";
        case Short:
            return "short";
        case Int:
            return "int";
        case Long:
            return "long";
        case Float:
            return "float";
        case Double:
            return "double";
        case Struct:
            return "struct";
        case Enum:
            return "enum";
        default:
            return "type not found";
    }
}


void ASTMathNode::setType(int newType)
{
    type = newType;
}
int ASTMathNode::getType() const
{
    return type;
}

string ASTMathNode::printType() const
{
	switch (type)
	{
		case Void:
			return "void";
		case Char:
			return "char";
		case Short:
			return "short";
		case Int:
			return "int";
		case Long:
			return "long";
		case Float:
			return "float";
		case Double:
			return "double";
		case Struct:
			return "struct";
		case Enum:
			return "enum";
		default:
			return "type not found";
	}
}



ASTAssignNode::ASTAssignNode (string node_label) : ASTNode::ASTNode(move(node_label))
{
}

ASTAssignNode::ASTAssignNode(string node_label, ASTNode* LHS, ASTNode* mathOp, ASTNode* RHS) : ASTNode::ASTNode(move(node_label))
{
    setType( getHigherType(LHS, RHS) );
    if( LHS->getType() != RHS->getType() )
    {
        if(LHS->getType() == Float)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", RHS, Float );
            addChild(LHS);
            addChild(mathOp);
            addChild(temp);
            outputStream << "WARNING: implicit conversion from " << printType(RHS) << " to " << printType(LHS) << endl;
        }
        else if(LHS->getType() == Int)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", RHS, Int );
            addChild(LHS);
            addChild(mathOp);
            addChild(temp);
            outputStream << "WARNING: implicit conversion from " << printType(RHS) << " to " << printType(LHS) << endl;
        }
        else if(LHS->getType() == Char)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", RHS, Char );
            addChild(LHS);
            addChild(mathOp);
            addChild(temp);
            outputStream << "WARNING: implicit conversion from " << printType(RHS) << " to " << printType(LHS) << endl;
        }
    } else
    {
        addChild(LHS);
        addChild(mathOp);
        addChild(RHS);
    }
}


bool ASTAssignNode::walk() const
{
    if( ( (ASTVariableNode*) children.front() )->getType() != ( (ASTVariableNode*) children.back() )->getType())
    {
        return false;
    }
    return true;
}

void ASTAssignNode::printNode (ASTNode *nodePtr, ofstream &treeOutFile)
{
    //cout << "MATH NODE" << endl;
    if(nodePtr)
    {
        treeOutFile << nodePtr->getNodeNum() << "[label = \"" << nodePtr->getLabel() << endl << "MATH NODE" <<"\"];" << endl;
        for (auto it = children.begin(); it != children.end(); ++it)
        {
            treeOutFile << nodeNum << " -> " << (*it)->getNodeNum() << endl;
            (*it)->printNode(*it, treeOutFile);
        }
    }
}


void ASTAssignNode::setType(int newType)
{
    type = newType;
}
int ASTAssignNode::getType() const
{
    return type;
}


int ASTAssignNode::getHigherType(ASTNode* LHS, ASTNode* RHS) const
{
    return LHS->getType();
}
string ASTAssignNode::printType() const
{
    switch (type)
    {
        case Void:
            return "void";
        case Char:
            return "char";
        case Short:
            return "short";
        case Int:
            return "int";
        case Long:
            return "long";
        case Float:
            return "float";
        case Double:
            return "double";
        case Struct:
            return "struct";
        case Enum:
            return "enum";
        default:
            return "type not found";
    }
}

string ASTAssignNode::printType(ASTNode*& node) const
{
    switch (node->getType())
    {
        case Void:
            return "void";
        case Char:
            return "char";
        case Short:
            return "short";
        case Int:
            return "int";
        case Long:
            return "long";
        case Float:
            return "float";
        case Double:
            return "double";
        case Struct:
            return "struct";
        case Enum:
            return "enum";
        default:
            return "type not found";
    }
}

ASTVariableNode::ASTVariableNode(string node_label) : ASTNode::ASTNode(move(node_label)), type(Int)
{
}

ASTVariableNode::ASTVariableNode(ASTNode*& RHS) : ASTNode::ASTNode(move( RHS->getLabel() )), type(Int)
{
}


ASTVariableNode::ASTVariableNode(string node_label, int inputType, string inputId)
: ASTNode::ASTNode(move(node_label)), type(inputType), id(inputId)
{

}

bool ASTVariableNode::walk() const
{
    return true;
}
int ASTVariableNode::getType() const
{
    return type;
}



string ASTVariableNode::getId() const
{
    return id;
}
void ASTVariableNode::setId(string inputId)
{
    id = inputId;
}

void ASTVariableNode::setType(int inputType)
{
    type = inputType;
}

void ASTVariableNode::printNode (ASTNode* nodePtr, ofstream& treeOutFile)
{
	//cout << "VARIABLE NODE" << endl;
	if(nodePtr)
	{
		treeOutFile << nodePtr->getNodeNum() << "[label = \"" << nodePtr->getLabel() << endl;
		treeOutFile << "ID: " << id << endl << "Type: " << printType() <<"\"];" << endl;
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			treeOutFile << nodeNum << " -> " << (*it)->getNodeNum() << endl;
			(*it)->printNode(*it, treeOutFile);
		}
	}
}

string ASTVariableNode::printType ()
{
	switch (type)
	{
		case Void:
			return "void";
		case Char:
			return "char";
		case Short:
			return "short";
		case Int:
			return "int";
		case Long:
			return "long";
		case Float:
			return "float";
		case Double:
			return "double";
		case Struct:
			return "struct";
		case Enum:
			return "enum";
		default:
			return "type not found";
	}
}


ASTConstNode::ASTConstNode(string node_label) : ASTNode::ASTNode(move(node_label))
{}
ASTConstNode::ASTConstNode(string node_label, int inputType, valueUnion value) : ASTNode::ASTNode(move(node_label)), type(inputType)
{
	setValue(value);
}

int ASTConstNode::getType() const
{
	return type;
}
void ASTConstNode::setType(int inputType)
{
	type = inputType;
}

valueUnion ASTConstNode::getValue() const
{
	return value;
}
void ASTConstNode::setValue(valueUnion inputValue)
{
	switch(type)
	{
		case Int:
			value.intVal = inputValue.intVal;
			break;
		case Char:
			value.charVal = inputValue.charVal;
			break;
		case Float:
			value.fVal = inputValue.fVal;
			break;
		default:
            outputStream << "Unsupported type " << printType() << endl;
			exit(-1);
	}
}

void ASTConstNode::printNode (ASTNode* nodePtr, ofstream& treeOutFile)
{
    //cout << "VARIABLE NODE" << endl;
    if(nodePtr)
    {
        treeOutFile << nodePtr->getNodeNum() << "[label = \"" << nodePtr->getLabel() << endl;
		treeOutFile << "Value: ";
        switch (type)
		{
			case Int:
				treeOutFile << value.intVal;
				break;
			case Char:
				treeOutFile << value.charVal;
				break;
			case Float:
				treeOutFile << value.fVal;
				break;
			default:
                outputStream << "Unsupported type for a constant" << endl;
				exit(-1);
		}
		treeOutFile << endl;
        treeOutFile << "Type: " << printType() <<"\"];" << endl;
        for (auto it = children.begin(); it != children.end(); ++it)
        {
            treeOutFile << nodeNum << " -> " << (*it)->getNodeNum() << endl;
            (*it)->printNode(*it, treeOutFile);
        }
    }
}

string ASTConstNode::printType()
{
	switch (type)
	{
		case Void:
			return "void";
		case Char:
			return "char";
		case Short:
			return "short";
		case Int:
			return "int";
		case Long:
			return "long";
		case Float:
			return "float";
		case Double:
			return "double";
		case Struct:
			return "struct";
		case Enum:
			return "enum";
		default:
			return "type not found";
	}
}

ASTSelectionNode::ASTSelectionNode(string node_label) : ASTNode::ASTNode(move(node_label))
{
    
}

bool ASTSelectionNode::walk() const
{
    
}

void ASTSelectionNode::printNode (ASTNode *nodePtr, ofstream &treeOutFile)
{
	//cout << "SELECTION NODE" << endl;
	if(nodePtr)
	{
		treeOutFile << nodeNum << "[label = \"" << label << endl << "SELECTION NODE" <<"\"];" << endl;
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			treeOutFile << nodeNum << " -> " << (*it)->getNodeNum() << endl;
			(*it)->printNode(*it, treeOutFile);
		}
	}
}

ASTIterationNode::ASTIterationNode(string node_label) : ASTNode::ASTNode(move(node_label))
{

}

bool ASTIterationNode::walk() const
{

}

void ASTIterationNode::printNode (ASTNode *nodePtr, ofstream &treeOutFile)
{
	//cout << "ITERATION NODE" << endl;
	if(nodePtr)
	{
		treeOutFile << nodeNum << "[label = \"" << label << endl << "ITERATION NODE" <<"\"];" << endl;
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			treeOutFile << nodeNum << " -> " << (*it)->getNodeNum() << endl;
			(*it)->printNode(*it, treeOutFile);
		}
	}
}


ASTIdNode::ASTIdNode(string node_label) : ASTNode::ASTNode(move(node_label))
{
}

ASTIdNode::ASTIdNode(string node_label, string inputId) : ASTNode::ASTNode(move(node_label)), id(inputId)
{
}

string ASTIdNode::getId() const
{
	return id;
}
void ASTIdNode::setId(string inputId)
{
	id = inputId;
}


int ASTIdNode::getType() const
{
    return type;
}
void ASTIdNode::setType( int inputType )
{
    type = inputType;
}

void ASTIdNode::printNode(ASTNode* nodePtr, ofstream& treeOutFile)
{
	if(nodePtr)
	{
		treeOutFile << nodePtr->getNodeNum() << "[label = \"" << nodePtr->getLabel() << endl;
		treeOutFile << "id: " << id << endl;
		treeOutFile << "type: " << printType(type) << "\"];" << endl;
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			treeOutFile << nodeNum << " -> " << (*it)->getNodeNum() << endl;
			(*it)->printNode(*it, treeOutFile);
		}
	}
}


ASTTypeNode::ASTTypeNode(string node_label) : ASTNode::ASTNode(move(node_label))
{}
ASTTypeNode::ASTTypeNode(string node_label, int inputType) : ASTNode::ASTNode(move(node_label)), type(inputType)
{}
int ASTTypeNode::getType() const
{
    return type;
}
void ASTTypeNode::setType(int inputType)
{
    type = inputType;
}


void ASTTypeNode::printNode(ASTNode* nodePtr, ofstream& treeOutFile)
{
	if(nodePtr)
	{
		treeOutFile << nodePtr->getNodeNum() << "[label = \"" << nodePtr->getLabel() << endl;
		treeOutFile << "type: " << printType() << endl <<"\"];" << endl;
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			treeOutFile << nodeNum << " -> " << (*it)->getNodeNum() << endl;
			(*it)->printNode(*it, treeOutFile);
		}
	}
}

string ASTTypeNode::printType() const
{
	switch (type)
	{
		case Void:
			return "void";
		case Char:
			return "char";
		case Short:
			return "short";
		case Int:
			return "int";
		case Long:
			return "long";
		case Float:
			return "float";
		case Double:
			return "double";
		case Struct:
			return "struct";
		case Enum:
			return "enum";
		default:
			return "type not found";
	}
}


ASTCastNode::ASTCastNode(string node_label) : ASTNode::ASTNode(move(node_label))
{}
ASTCastNode::ASTCastNode(string node_label, ASTNode* childNode, int castType) : ASTNode::ASTNode(move(node_label)), type( castType )
{
	addChild( childNode );
}
int ASTCastNode::getType() const
{
	return type;
}
void ASTCastNode::setType(int inputType)
{
	type = inputType;
}


void ASTCastNode::printNode(ASTNode* nodePtr, ofstream& treeOutFile)
{
	if(nodePtr)
	{
		treeOutFile << nodePtr->getNodeNum() << "[label = \"" << nodePtr->getLabel() << endl;
		treeOutFile << "type: " << printType() << endl <<"\"];" << endl;
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			treeOutFile << nodeNum << " -> " << (*it)->getNodeNum() << endl;
			(*it)->printNode(*it, treeOutFile);
		}
	}
}

string ASTCastNode::printType() const
{
	switch (type)
	{
		case Void:
			return "void";
		case Char:
			return "char";
		case Short:
			return "short";
		case Int:
			return "int";
		case Long:
			return "long";
		case Float:
			return "float";
		case Double:
			return "double";
		case Struct:
			return "struct";
		case Enum:
			return "enum";
		default:
			return "type not found";
	}
}