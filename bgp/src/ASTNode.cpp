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
	addChild(LHS);
	addChild(mathOp);
	addChild(RHS);
	//cout << "Type " << LHS->getType() << " LHS type:  " << RHS->getType() << endl;
	setType( LHS->getType() );
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


void ASTMathNode::setType(int newType)
{
    type = newType;
}
int ASTMathNode::getType() const
{
    return type;
}


ASTVariableNode::ASTVariableNode(string node_label) : ASTNode::ASTNode(move(node_label)), type(Int)
{
    value = "NO_VALUE";
}

ASTVariableNode::ASTVariableNode(ASTNode*& RHS) : ASTNode::ASTNode(move( RHS->getLabel() )), type(Int)
{
    value = "NO_VALUE";
}


ASTVariableNode::ASTVariableNode(string node_label, int inputType, string inputValue, string inputId)
: ASTNode::ASTNode(move(node_label)), type(inputType), value(inputValue), id(inputId)
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


string ASTVariableNode::getValue() const
{
    return value;
}


string ASTVariableNode::getId() const
{
    return id;
}
void ASTVariableNode::setId(string inputId)
{
    id = inputId;
}

void ASTVariableNode::setValue(string inputValue)
{
    value = inputValue;
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
		treeOutFile << nodePtr->getNodeNum() << "[label = \"" << nodePtr->getLabel() << endl << "Value: " << value << endl;
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
