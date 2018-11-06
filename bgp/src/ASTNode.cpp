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
	cout << "BASE NODE" << endl;
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
	cout << "MATH NODE" << endl;
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


ASTVariableNode::ASTVariableNode(string node_label) : ASTNode::ASTNode(node_label), type(Int)
{
    value = "NO_VALUE";
}

ASTVariableNode::ASTVariableNode(ASTNode*& RHS) : ASTNode::ASTNode(RHS->getLabel()), type(Int)
{
    value = "NO_VALUE";
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
	cout << "VARIABLE NODE" << endl;
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
	cout << "SELECTION NODE" << endl;
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
	cout << "ITERATION NODE" << endl;
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
