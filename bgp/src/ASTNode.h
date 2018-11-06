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
        explicit ASTNode(string node_label); //Add line and col num when ready
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

		virtual void setType(int newType) {
		    cout << "setType, YOU DID SOMETHING BAD" << endl;
		}

		virtual int getType() const {
		    cout << "getType, YOU DID SOMETHING BAD" << endl;
		}

		virtual void setId(string newId) {
		    cout << "setId, YOU DID SOMETHING BAD" << endl;
		}

		virtual  string getId() {
		    cout << "getId, YOU DID SOMETHING BAD" << endl;
		}

		virtual string getValue() {
		    cout << "getType, YOU DID SOMETHING BAD" << endl;
		}

		virtual void setValue(string newValue)
        {
		    cout << "getValue, YOU DID SOMETHING BAD" << endl;
        }

	virtual void printNode(ASTNode* nodePtr, ofstream& treeOutFile);

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
        ASTMathNode(string node_label, ASTNode* LHS, ASTNode* mathOp, ASTNode* RHS);
        bool walk() const;
        void printNode(ASTNode* nodePtr, ofstream& treeOutFile) override;
        void setType(int newType);
        int getType() const;
    private:
        int type;
        string value;
};

class ASTVariableNode : public ASTNode
{
    public:
        ASTVariableNode(string node_label);
        ASTVariableNode(ASTNode*& RHS);
        ASTVariableNode(string node_label, int inputType, string inputValue, string inputId);
        bool walk() const;
        int getType() const;
        string getValue() const;
        string getId() const;
        void setId(string inputId);
        void setValue(string inputValue);
        void setType(int inputType);
        void printNode(ASTNode* nodePtr, ofstream& treeOutFile) override;
    private:
        string value;
        string id;
        int type;
        string printType();
};

class ASTSelectionNode : public ASTNode
{
    public:
        ASTSelectionNode(string node_label);
        bool walk() const;
        void printNode(ASTNode* nodePtr, ofstream& treeOutFile) override;
};

class ASTIterationNode : public ASTNode
{
    public:
        ASTIterationNode(string node_label);
        bool walk() const;
        void printNode(ASTNode* nodePtr, ofstream& treeOutFile) override;
};

class ASTIdNode : public ASTNode
{
    public:
        ASTIdNode(string node_label);
        ASTIdNode(string node_label, string inputId);
        bool walk() const{}
        void printNode(ASTNode* nodePtr, ofstream& treeOutFile){}
        string getId() const;
        void setId(string inputId);

    private:
        string id;
};

/*class ASTSwitchNode : public ASTNode
{
    public:
        ASTSwitchNode();
        ASTSwitchNode(int node_label, int line_num, list<ASTNode*> child_list);
        bool walk();
};*/

#endif //PROJECT_ASTNODE_H
