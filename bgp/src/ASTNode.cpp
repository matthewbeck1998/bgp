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
        if( (*it)->walk() == false )
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


ASTMathNode::ASTMathNode (string node_label) : ASTNode::ASTNode(node_label)
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
    strcpy(value, "NO_VALUE");
}
bool ASTVariableNode::walk() const
{
    return true;
}
int ASTVariableNode::getType() const
{
    return type;
}


const char* ASTVariableNode::getValue() const
{
    return value;
}
void ASTVariableNode::setValue(char* inputValue)
{
    strcpy(value, inputValue);
}

void ASTVariableNode::setType(int inputType)
{
    type = inputType;
}
