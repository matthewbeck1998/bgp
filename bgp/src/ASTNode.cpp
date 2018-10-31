#include "ASTNode.h"

/*ASTNode::ASTNode() {}
ASTNode::ASTNode(int node_label, int line_num, list<ASTNode*> child_list)
{
    label = node_label;
    lineNum = line_num;
    children = child_list;
}


list<ASTNode*> ASTNode::getChildren() const
{
    return children;
}

int ASTNode::getLabel() const
{
    return label;
}

int ASTNode::getLineNum() const
{
    return lineNum;
}

ostream& operator<< (ostream &os, const ASTNode& output)
{
    for(auto it = output.getChildren().begin() ; it != output.getChildren().end() ; ++it)
    {
        os << "Label: " << (**it).getLabel() << " Line number: " << (**it).getLineNum() << endl;
    }
}

ASTSwitchNode::ASTSwitchNode(int node_label, int line_num, list<ASTNode*> child_list) : ASTNode::ASTNode(node_label, line_num, child_list){}
bool ASTSwitchNode::walk() {}

ASTMathNode::ASTMathNode(int node_label, int line_num, list<ASTNode *> child_list, int operator_type) : ASTNode::ASTNode(node_label, line_num, child_list)
{
    operatorType = operator_type;
}
bool ASTMathNode::walk() {}



ASTSingleMathNode::ASTSingleMathNode(int node_label, int line_num, list<ASTNode *> child_list, int operator_type) : ASTNode::ASTNode(node_label, line_num, child_list)
{
    operatorType = operator_type;
}
bool ASTSingleMathNode::walk() {}


ASTDeclaritors::ASTDeclaritors(int node_label, int line_num, list<ASTNode *> child_list, SymbolNode inputSymbolNode) :
    ASTNode::ASTNode(node_label, line_num, child_list),
    variable(inputSymbolNode.getIdentifier(), inputSymbolNode.getLineNum(), 0, inputSymbolNode.getTypeSpecifierIndex()) // This calls the SymbolTableNode constructor. The 0 is column num
{}
bool ASTDeclaritors::walk() {}

ASTFunctionNode::ASTFunctionNode(int node_label, int line_num, list<ASTNode*> child_list, SymbolNode inputSymbolNode) :
        ASTNode::ASTNode(node_label, line_num, child_list),
        function(inputSymbolNode.getIdentifier(), inputSymbolNode.getLineNum(), 0, inputSymbolNode.getTypeSpecifierIndex()) // This calls the SymbolTableNode constructor. The 0 is column num
{}
bool ASTFunctionNode::walk() {}*/

int ASTNode::totalNodeCount = 0;

ASTNode::ASTNode (string node_label) : label(move(node_label))
{
	nodeNum = totalNodeCount++;
}

void ASTNode::addChild (ASTNode *addNode)
{
    children.push_front(addNode);
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

/*int ASTNode::getLineNum () const
{
    return 0;
}*/
