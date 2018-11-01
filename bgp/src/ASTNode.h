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
        bool walk() const;
        int getType() const;
        const char* getValue() const;
        void setValue(char* inputValue);
        void setType(int inputType);
    private:
        char value[256];
        int type;
};

/*class ASTSwitchNode : public ASTNode
{
    public:
        ASTSwitchNode();
        ASTSwitchNode(int node_label, int line_num, list<ASTNode*> child_list);
        bool walk();
};*/

#endif //PROJECT_ASTNODE_H
