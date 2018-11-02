#include "ASTNode.h"

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

ASTSelectionNode::ASTSelectionNode(string node_label) : ASTNode::ASTNode(move(node_label))
{
    
}

bool ASTSelectionNode::walk() const
{
    
}

ASTIterationNode::ASTIterationNode(string node_label) : ASTNode::ASTNode(move(node_label))
{

}

bool ASTIterationNode::walk() const
{

}
