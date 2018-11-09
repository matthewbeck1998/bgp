/*!
 * @file ASTNode.h
 * @brief Specification file for all of the AST nodes
 */

#ifndef PROJECT_ASTNODE_H
#define PROJECT_ASTNODE_H

#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <cstring>
#include "SymbolNode.h"

using namespace std;

/*!
 * Externs for the output/error streams.
 */
extern stringstream errorStream;
extern stringstream outputStream;


/*!
 * @name valueUnion
 * @brief Union to hold the values stored in constant nodes
 */
union valueUnion
{
    int intVal;
    char charVal;
    float fVal;
};


/*!
 * @name ASTNode
 * @brief ASTNode class to hold nodes in the AST
 */
class ASTNode
{
    public:
        /*!
         * @name ASTNode
         * @param node_label
         * @brief Constructs a new ASTNode and sets label to node_label
         */
        explicit ASTNode(string node_label); //Add line and col num when ready

        /*!
         * @name addChild
         * @param addNode
         * @brief adds a ASTNode to the children of the current node
         */
        void addChild(ASTNode* addNode);

        /*!
         * @name getLabel
         * @return returns the label
         */
        string getLabel() const;

        /*!
         * @name walk()
         * @return true or false if the table was correctly walked
         */
        virtual bool walk() const;

        /*!
         * @name getChildren
         * @return returns the list of children
         */
        list<ASTNode *> &getChildren ();

        /*!
         * static int to hold the total number of nodes
         */
		static int totalNodeCount;

		/*!
		 * @name getColNum
		 * @return returns the column number
		 */
		int getColNum () const;

		/*!
		 * @name setColNum
		 * @param colNum
		 * @brief sets the column number to colNum
		 */
		void setColNum (int colNum);

        /*!
         * @name getLineNum
         * @return returns the line number
         */
		int getLineNum () const;

		/*!
		 * @name setLineNum
		 * @param lineNum
		 */
		void setLineNum (int lineNum);

		/*!
		 * @name getNodeNum
		 * @return returns the node number
		 */
		int getNodeNum () const;

		/*!
		 * @name setType
		 * @param newType
		 * @brief virtual setType function, it should not ever be called.
		 */
		virtual void setType(int newType) {
		    outputStream << "setType, YOU DID SOMETHING BAD" << endl;
		}

		/*!
		 * @name getType
		 * @return does not return anything. It should never be called
		 */
		virtual int getType() const {
		    outputStream << "getType, YOU DID SOMETHING BAD" << endl;
		}

		/*!
		 * @name setId
		 * @param newId
		 * @brief does not do anything, should never be called
		 */
		virtual void setId(string newId) {
		    outputStream << "setId, YOU DID SOMETHING BAD" << endl;
		}

		/*!
		 * @name getDimensions
		 * @return should not ever be called, does nothing.
		 */
		virtual list<int> getDimensions();

		/*!
		 * @name getId
		 * @return returns "no Id. Base Node.". Should never be called.
		 */
		virtual  string getId() {
		    outputStream << "getId, YOU DID SOMETHING BAD" << endl;
		    return "no Id. Base Node.";
		}

		/*!
		 * @name getValue
		 * @return returns nothing, should never be called.
		 */
		virtual string getValue() {
		    outputStream << "getValue, YOU DID SOMETHING BAD" << endl;
		}

		/*!
		 * @name setValue
		 * @param newValue
		 * @brief does nothing should never be called.
		 */
		virtual void setValue(string newValue)
        {
		    outputStream << "setValue, YOU DID SOMETHING BAD" << endl;
        }

        /*!
         * @name printNode
         * @param treeOutFile
         * @brief prints the node formatted to dot type
         */
	virtual void printNode(ostream &treeOutFile = cout);

protected:
    /*!
     * String to hold the label
     */
	string label;
    int colNum; //Not implemented yet
    int lineNum; //Not implemented yet

    /*!
     * Holds the unique node number
     */
	int nodeNum;

	/*!
	 * //Holds the children nodes
	 */
    list<ASTNode*> children;
        //friend ostream& operator<< (ostream &os, const ASTNode& output);
};

class ASTMathNode : public ASTNode
{
    public:
        /*!
         * @name ASTMathNode
         * @param node_label
         * @brief creates a new object and sets label to node_label
         */
        ASTMathNode(string node_label);

        /*!
         * @name ASTMathNode
         * @param node_label
         * @param LHS
         * @param mathOp
         * @param RHS
         * @brief creates a new object. Sets label to node_label, adds a children LHS, mathOp, and RHS
         */
        ASTMathNode(string node_label, ASTNode* LHS, ASTNode* mathOp, ASTNode* RHS);

        /*!
         * @name walk
         * @return returns true or false based on whether the tree was walked correctly
         */
        bool walk() const;

        /*!
         * @name printNode
         * @param treeOutFile
         * @brief prints out the node formatted for a tree dot file
         */
        void printNode(ostream &treeOutFile = cout) override;

        /*!
         * @name setType
         * @param newType
         * @brief sets the type
         */
        void setType(int newType);

        /*!
         * @name getType.
         * @return returns the type.
         */
        int getType() const;
    private:

        /*!
         * @name getHigherType
         * @param LHS
         * @param RHS
         * @return returns the int that corresponds to the higher order type for implicit casting.
         */
        int getHigherType(ASTNode* LHS, ASTNode* RHS) const;

        /*!
         * @name printType
         * @return returns a string that corresponds to the int type
         */
        string printType() const;

        /*!
         * @name printType
         * @param node
         * @return returns a string that corresponds to the type from node
         */
        string printType(ASTNode*& node) const;

        /*!
         * int that corresponds to the type
         */
        int type;

        /*!
         * string to hold the value. Should be changed to valueUnion if any values are actually stored.
         */
        string value;
};

class ASTAssignNode : public ASTNode
{
    public:
        /*!
         * @name ASTAssignNode
         * @param node_label
         * @brief creates a new object with label equal to node_label
         */
        ASTAssignNode(string node_label);

        /*!
         * @name ASTAssignNode
         * @param node_label
         * @param LHS
         * @param mathOp
         * @param RHS
         * @brief creates a new object. Sets the label to node_label and adds children LHS, mathOp, and RHS.
         */
        ASTAssignNode(string node_label, ASTNode* LHS, ASTNode* mathOp, ASTNode* RHS);

        /*!
         * @name walk
         * @return returns true or false based on if the walk was successful
         */
        bool walk() const;

        /*!
         * @name printNode
         * @param treeOutFile
         * @brief prints the node in a tree dot format
         */
        void printNode(ostream &treeOutFile = cout) override;

        /*!
         * @name setType
         * @param newType
         * @brief sets the type to newType
         */
        void setType(int newType);

        /*!
         * @name getType
         * @return returns the int that corresponds to the type.
         */
        int getType() const;
    private:

        /*!
         * @name getHigherType
         * @param LHS
         * @param RHS
         * @return gets the int that corresponds to the dominant type
         */
        int getHigherType(ASTNode* LHS, ASTNode* RHS) const;

        /*!
         * @name printType
         * @return returns a string that corresponds to the type
         */
        string printType() const;

        /*!
         * @name printType
         * @param node
         * @return returns a string that corresponds to the type of node
         */
        string printType(ASTNode*& node) const;

        /*!
         * int that store the type
         */
        int type;

        /*!
         * string that stores the value. Should be removed.
         */
        string value;
};

class ASTVariableNode : public ASTNode
{
    public:
        /*!
         * @name ASTVariableNode
         * @param node_label
         * @brief Creates a new object and sets label equal to node_label
         */
        ASTVariableNode(string node_label);

        /*!
         * @name ASTVariableNode
         * @param RHS
         * @brief Creates a new object with a label equal to the label of RHS
         */
        ASTVariableNode(ASTNode*& RHS);

        /*!
         * @name ASTVariableNode
         * @param node_label
         * @param inputType
         * @param inputId
         * @brief Creates a new object. Sets label equal to node_label, type equal to inputType, and id equal to inputId.
         */
        ASTVariableNode(string node_label, int inputType, string inputId);

        /*!
         * @name walk
         * @return returns an bool based on if the tree was successfully walked or not
         */
        bool walk() const;

        /*!
         * @name getType
         * @return returns type
         */
        int getType() const;

        /*!
         * @name getId
         * @return returns the id
         */
        string getId() const;

        /*!
         * @name setId
         * @param inputId
         * @brief sets id equal to inputId
         */
        void setId(string inputId);

        /*!
         * @name setType
         * @param inputType
         * @brief sets type equal to inputType
         */
        void setType(int inputType);

        /*!
         * @name printNode
         * @param treeOutFile
         * @brief prints the node formatted to a tree dot
         */
        void printNode(ostream &treeOutFile = cout) override;
    private:
        /*!
         * string id to hold the id of the node
         */
        string id;
        /*!
         * int type to hold the type of the node
         */
        int type;

        /*!
         * @name printType
         * @return returns a string that corresponds to the type of the node.
         */
        string printType();
};

class ASTConstNode : public ASTNode
{
    public:
    /*!
     * @name ASTConstNode
     * @param node_label
     * @brief Creates a new object and sets the label equal to node_label
     */
    ASTConstNode(string node_label);

    /*!
     * @name ASTConstNode
     * @param node_label
     * @param inputType
     * @param value
     * @brief Creates a new object. Sets the label equal to node_label
     */
    ASTConstNode(string node_label, int inputType, valueUnion value);

    int getType() const;
    void setType(int inputType);

    valueUnion getValue() const;
    void setValue(valueUnion inputValue);


    void printNode(ostream &treeOutFile = cout) override;

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
        void printNode(ostream &treeOutFile = cout) override;
};

class ASTIterationNode : public ASTNode
{
    public:
        ASTIterationNode(string node_label);
        bool walk() const;
        void printNode(ostream &treeOutFile = cout) override;
};

class ASTIdNode : public ASTNode
{
    public:
        ASTIdNode(string node_label);
        ASTIdNode(string node_label, string inputId);
        bool walk() const{}
        void printNode(ostream &treeOutFile = cout) override;
        string getId() const;
        void setId(string inputId);
        int getType() const;
        void setType( int inputType );

    private:
        string printType() const; // I can only imagine you meant to do this. - Matt
        string id;
        int type;
};

class ASTTypeNode : public  ASTNode
{
    public:
        ASTTypeNode(string node_label);
        ASTTypeNode(string node_label, int inputType);
        bool walk() const{}
        void printNode(ostream &treeOutFile = cout) override;
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
        void printNode(ostream &treeOutFile  = cout);
        int getType() const;
        void setType( int inputType );
    private:
        string printType() const;
        int type;
};

class ASTArrayNode : public ASTNode
{
public:
	ASTArrayNode(string node_label, string id, int typeSet);
    ASTArrayNode(string node_label, ASTNode* inputNode);
	void printNode(ostream &treeOutFile = cout) override;
	void setType( int inputType );
	int getType() const;
	string getId() const;
	void setId(string inputId);
	list<int> getDimensions() const;
	void addDimension(int inputDim);
	void addDimensions(list<int> inputDimensions);

private:
	list<int> dimensions;
	string identifier;
	int type;
};

class ASTDeclarationNode : public ASTNode
{
	public:
		ASTDeclarationNode(string node_label, int inputType, ASTNode* childNode);
		void printNode(ostream &treeOutFile = cout) override;
		void setType( int inputType );
		int getType() const;
	private:
		int type;
		void constructorTypeSet( ASTNode* node, int inputType );
};



/* Will, what the hell are you doing? - Matt
 * If you write function definitions in header files,
 * the program won't compile because of multiple definitions
 * caused by including this header file in multiple other files.
string printType(int type)
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
		default:
			return "No type";
	}
}
*/
/*class ASTSwitchNode : public ASTNode
{
    public:
        ASTSwitchNode();
        ASTSwitchNode(int node_label, int line_num, list<ASTNode*> child_list);
        bool walk();
};*/

#endif //PROJECT_ASTNODE_H
