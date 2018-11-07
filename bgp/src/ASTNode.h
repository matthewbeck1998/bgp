//
// Created by WIll on 10/30/2018.
//

#ifndef PROJECT_ASTNODE_H
#define PROJECT_ASTNODE_H

#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <cstring>
#include "SymbolNode.h"

using namespace std;
extern stringstream errorStream;
extern stringstream outputStream;

union valueUnion
{
    int intVal;
    char charVal;
    float fVal;
};


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
		    outputStream << "setType, YOU DID SOMETHING BAD" << endl;
		}

		virtual int getType() const {
		    outputStream << "getType, YOU DID SOMETHING BAD" << endl;
		}

		virtual void setId(string newId) {
		    outputStream << "setId, YOU DID SOMETHING BAD" << endl;
		}

		virtual  string getId() {
		    outputStream << "getId, YOU DID SOMETHING BAD" << endl;
		}

		virtual string getValue() {
		    outputStream << "getType, YOU DID SOMETHING BAD" << endl;
		}

		virtual void setValue(string newValue)
        {
		    outputStream << "getValue, YOU DID SOMETHING BAD" << endl;
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
        int getHigherType(ASTNode* LHS, ASTNode* RHS) const;
        string printType() const;
        string printType(ASTNode*& node) const;
        int type;
        string value;
};

class ASTAssignNode : public ASTNode
{
    public:
        ASTAssignNode(string node_label);
        ASTAssignNode(string node_label, ASTNode* LHS, ASTNode* mathOp, ASTNode* RHS);
        bool walk() const;
        void printNode(ASTNode* nodePtr, ofstream& treeOutFile) override;
        void setType(int newType);
        int getType() const;
    private:
        int getHigherType(ASTNode* LHS, ASTNode* RHS) const;
        string printType() const;
        string printType(ASTNode*& node) const;
        int type;
        string value;
};

class ASTVariableNode : public ASTNode
{
    public:
        ASTVariableNode(string node_label);
        ASTVariableNode(ASTNode*& RHS);
        ASTVariableNode(string node_label, int inputType, string inputId);
        bool walk() const;
        int getType() const;
        string getId() const;
        void setId(string inputId);
        void setType(int inputType);
        void printNode(ASTNode* nodePtr, ofstream& treeOutFile) override;
    private:
        string id;
        int type;
        string printType();
};

class ASTConstNode : public ASTNode
{
    public:
    ASTConstNode(string node_label);
    ASTConstNode(string node_label, int inputType, valueUnion value);

    int getType() const;
    void setType(int inputType);

    valueUnion getValue() const;
    void setValue(valueUnion inputValue);


    void printNode(ASTNode* nodePtr, ofstream& treeOutFile) override;

    private:
    int type;
    valueUnion value;
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
        void printNode(ASTNode* nodePtr, ofstream& treeOutFile);
        string getId() const;
        void setId(string inputId);
        int getType() const;
        void setType( int inputType );

    private:
        string id;
        int type;
};

class ASTTypeNode : public  ASTNode
{
    public:
        ASTTypeNode(string node_label);
        ASTTypeNode(string node_label, int inputType);
        bool walk() const{}
        void printNode(ASTNode* nodePtr, ofstream& treeOutFile);
        int getType() const;
        void setType( int inputType );
    private:
        string printType() const;
        int type;
};

class ASTCastNode : public ASTNode
{
    public:
        ASTCastNode(string node_label);
        ASTCastNode(string node_label, ASTNode* childNode, int castType);
        void printNode(ASTNode* nodePtr, ofstream& treeOutFile);
        int getType() const;
        void setType( int inputType );
    private:
        string printType() const;
        int type;
};

string printType(int type)
{
	switch (type)
	{
		case Void:
			return  "void";;
		case Char:
			return "char";
		case Short:
			return "short";
		case Int:
			return "int";
		case Long:
			return  "long";
		case Float:
			return "float";
		case Double:
			return "double";
		case Struct:
			return "struct";
		default:
			return "No type";
	}
}

/*class ASTSwitchNode : public ASTNode
{
    public:
        ASTSwitchNode();
        ASTSwitchNode(int node_label, int line_num, list<ASTNode*> child_list);
        bool walk();
};*/

#endif //PROJECT_ASTNODE_H
