//
// Created by WIll on 10/30/2018.
//

#ifndef PROJECT_ASTNODE_H
#define PROJECT_ASTNODE_H

#include <list>
#include <string>
#include <iostream>
#include <cstring>
#include "SymbolNode.h"

using namespace std;

class ASTNode
{
    public:
        ASTNode(string node_label); //Add line and col num when ready
        void addChild(ASTNode* addNode);
        string getLabel() const;
        virtual bool walk() const;
        list<ASTNode *> &getChildren ();
		static int totalNodeCount;

	int getColNum () const;

	void setColNum (int colNum);

	int getLineNum () const;

	void setLineNum (int lineNum);

	int getNodeNum () const;

protected:
	string label;
    int colNum; //Not implemented yet
    int lineNum; //Not implemented yet
	int nodeNum;

    list<ASTNode*> children;
        //friend ostream& operator<< (ostream &os, const ASTNode& output);
};

class ASTMathNode : public ASTNode
{
    public:
        ASTMathNode(string node_label);
        bool walk() const;
};

class ASTVariableNode : public ASTNode
{
    public:
        ASTVariableNode(string node_label);
        ASTVariableNode(ASTNode*& RHS);
        bool walk() const;
        int getType() const;
        string getValue() const;
        string getId() const;
        void setId(string inputId);
        void setValue(string inputValue);
        void setType(int inputType);
    private:
        string value;
        string id;
        int type;
};

class ASTSelectionNode : public ASTNode
{
    public:
        ASTSelectionNode(string node_label);
        bool walk() const;
};

class ASTIterationNode : public ASTNode
{
    public:
        ASTIterationNode(string node_label);
        bool walk() const;
};

/*class ASTSwitchNode : public ASTNode
{
    public:
        ASTSwitchNode();
        ASTSwitchNode(int node_label, int line_num, list<ASTNode*> child_list);
        bool walk();
};*/

#endif //PROJECT_ASTNODE_H
