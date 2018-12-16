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

string printType(int type);

/*!
 * Externs for the output/error streams.
 */
extern stringstream errorStream;
extern stringstream outputStream;
extern string inputFileName;

extern int line;


/*!
 * @name valueUnion
 * @brief Union to hold the values stored in constant nodes
 */
union valueUnion
{
    double dVal;
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

        ASTNode(){}
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

        int getActivationFrameSize() const;

        void setActivationFrameSize(int inputActivationFrameSize);

        void propegateActivation(int inputActivationSize);

        /*!
         * @name getLabel
         * @return returns the label
         */
        string getLabel() const;

        /*!
         * @name walk()
         * @return true or false if the table was correctly walked
         */
        virtual vector<string> walk();

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

        virtual void setOffset(int inputOffset);
		int getOffset() const;
		void addOffset( int inputOffset );

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
    int colNum; // Not implemented yet.
    int lineNum;

    /*!
     * Holds the unique node number
     */
	int nodeNum;

	/*!
	 * Holds the size required for the activation frame.
	 */
	int activationFrameSize;

	/*!
	 * //Holds the children nodes
	 */
    list<ASTNode*> children;
        //friend ostream& operator<< (ostream &os, const ASTNode& output);

   static unsigned int ticketCounter;
   static unsigned int labelCounter;
   static list<vector<string>> threeAddressCode;

    int offset;
};

/*!
 * @name ASTMathNode
 * @brief class to hold all the math operation nodes
 */
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
		vector<string> walk();

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


/*!
 * @name ASTAssignNode
 * @brief node to hold all assignment operations
 */
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
		vector<string> walk();

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

/*!
 * @name ASTVariableNode
 * @brief node to hold variables in
 */
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
		vector<string> walk() override;

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

/*!
 * @name ASTConstNode
 * @brief node to hold constant values
 */
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

    /*!
     * @name getType
     * @return returns the type of the node
     */
    int getType() const;

    /*!
     * @name setType
     * @param inputType
     * @brief sets the type of the node to inputType
     */
    void setType(int inputType);

    /*!
     * @name getValue
     * @return returns a union holding the value of the node.
     */
    valueUnion getValue() const;

    /*!
     * @name setValue
     * @param inputValue
     * @brief sets the value of the node equal to inputValue
     */
    void setValue(valueUnion inputValue);


    /*!
     * @name printNode
     * @param treeOutFile
     * @brief prints out the tree formatted for a dot file
     */
    void printNode(ostream &treeOutFile = cout) override;

    vector<string> walk() override;

    private:
    /*!
     * an int corresponding to the type of the node.
     */
    int type;

    /*!
     * valueUnion holding the value of the node
     */
    valueUnion value;

    /*!
     * @name printType
     * @return returns the type of the node as a string
     */
    string printType();
};

/*!
 * @name ASTSelectionNode
 * @brief node to hold selection statements
 */
class ASTSelectionNode : public ASTNode
{
    public:
        /*!
         * @name ASTSelectionNode
         * @param node_label
         * @brief Creates a new object and sets label equal to node_label
         */
        ASTSelectionNode(string node_label);

        /*!
         * @name walk
         * @return Walks the AST. Returns true if it succeeds and false if it does now
         */
		vector<string> walk() override;

        /*!
         * @name printNode
         * @param treeOutFile
         * @brief prints the node output to a tree dot file
         */
        void printNode(ostream &treeOutFile = cout) override;
};

/*!
 * @name ASTIterationNode
 * @brief Class to hold all the loop operations
 */
class ASTIterationNode : public ASTNode
{
    public:
        /*!
         * @name ASTIterationNode
         * @param node_label
         * @brief creates a new object and sets label equal to node_label
         */
        ASTIterationNode(string node_label);

        /*!
         * @name walk
         * @return returns true of false based on if the tree was successfully walked
         */
		vector<string> walk() override;

        /*!
         * @name printNode
         * @param treeOutFile
         * @brief prints the node formatted for a dot tree
         */
        void printNode(ostream &treeOutFile = cout) override;
};


/*!
 * @name ASTIdNode
 * @brief node to hold all the identifiers and their types
 */
class ASTIdNode : public ASTNode
{
    public:
        /*!
         * @name ASTIdNode
         * @param node_label
         * @brief creates a node and sets label equal to node_label
         */
        ASTIdNode(string node_label);

        /*!
         * @name ASTIdNode
         * @param node_label
         * @param inputId
         * @brief Creates a new node object. Sets label equal to node_label and id equal to inputId
         */
        ASTIdNode(string node_label, string inputId);

        /*!
         * @name walk
         * @return returns true or false based on if the tree was successfully walked ot not.
         */
		vector<string> walk() override;

        /*!
         * @name printNode
         * @param treeOutFile
         * @brief prints the node outputted for a tree dot file
         */
        void printNode(ostream &treeOutFile = cout) override;

        /*!
         * @name getId
         * @return returns the id of the node
         */
        string getId() const;

        /*!
         * @name setId
         * @param inputId
         * @brief sets the id of the node to inputId
         */
        void setId(string inputId);

        /*!
         * @name getType
         * @return returns the type of the node
         */
        int getType() const;

        /*!
         * @name setType
         * @param inputType
         * @brief sets the type of the node equal to inputType
         */
        void setType( int inputType );

    /*!
     * @name printType
     * @return returns a string the corresponds to the type of the node
     */
    string printType() const; // I can only imagine you meant to do this. - Matt

    private:

        /*!
         * a sting the holds the id of the node
         */
        string id;

        /*!
         * an int that stores the type of the node
         */
        int type;
};


/*!
 * @name ASTTypeNode
 * @brief Class to hold all the type nodes
 */
class ASTTypeNode : public  ASTNode
{
    public:
        /*!
         * @name ASTTypeNode
         * @param node_label
         * @brief creates an object and sets the label equal to node_label
         */
        ASTTypeNode(string node_label);

        /*!
         * @name ASTTypeNode
         * @param node_label
         * @param inputType
         * @brief creates an object. Sets the label equal to node_label and the type equal to inputType
         */
        ASTTypeNode(string node_label, int inputType);

        /*!
         * @name walk
         * @return returns a bool corresponding to whether the tree was successfully walked or not.
         */
		vector<string> walk() override;

        /*!
         * @name printNode
         * @param treeOutFile
         * @brief prints the node to a formatted tree dot file
         */
        void printNode(ostream &treeOutFile = cout) override;

        /*!
         * @name getType
         * @return returns the type of the node
         */
        int getType() const;

        /*!
         * @name setType
         * @param inputType
         * @brief sets the type of the node to inputType
         */
        void setType( int inputType );
    private:

        /*!
         * @name printType
         * @return returns a string corresponding to the type of the node
         */
        string printType() const;

        /*!
         * an int that holds the type of the node
         */
        int type;
};

class ASTCastNode : public ASTNode
{
    public:
        /*!
         * @name ASTCastNode
         * @param node_label
         * @brief creates an object and sets label equal to node_label
         */
        ASTCastNode(string node_label);

        /*!
         * @name ASTCastNode
         * @param node_label
         * @param childNode
         * @param castType
         * @brief creates an object. Sets label to node_label, adds child node childNode, and type to castType
         */
        ASTCastNode(string node_label, ASTNode* childNode, int castType);

        /*!
         * @name printNode
         * @param treeOutFile
         * @brief prints the node formatted for a tree dot file
         */
        void printNode(ostream &treeOutFile  = cout);

        /*!
         * @name getType
         * @return returns the type of the function
         */
        int getType() const;

        /*!
         * @name setType
         * @param inputType
         * @brief sets the type of the node to inputType
         */
        void setType( int inputType );

        vector<string> walk() override;
    private:
        /*!
         * @name printType
         * @return returns a string corresponding to the type of the node.
         */
        string printType() const;

        /*!
         * sets the type of the node
         */
        int type;
};

/*!
 * @name ASTArrayNode
 * @brief Class to hold all the array nodes
 */
class ASTArrayNode : public ASTNode
{
public:
    /*!
     * @name ASTArrayNode
     * @param node_label
     * @param id
     * @param typeSet
     * @brief creates an object. sets label to node_label, identifier to id, and type to typeSet
     */
	ASTArrayNode(string node_label, string id, int typeSet);

	/*!
	 * @name ASTArrayNode
	 * @param node_label
	 * @param inputNode
	 * @brief creates an object. sets label to node_label, adds all children from inputNode
	 */
    ASTArrayNode(string node_label, ASTNode* inputNode);

    /*!
     * @name printNode
     * @param treeOutFile
     * @brief prints the node formatted for a tree dot file
     */
	void printNode(ostream &treeOutFile = cout) override;

	/*!
	 * @name setType
	 * @param inputType
	 * @brief sets the type of the node to inputType
	 */
	void setType( int inputType );

	/*!
	 * @name getType
	 * @return the type of the node
	 */
	int getType() const;

	/*!
	 * @name getId
	 * @return returns the identifier of the node
	 */
	string getId() const;

	/*!
	 * @name setId
	 * @param inputId
	 * @brief sets identifier to inputId
	 */
	void setId(string inputId);

	/*!
	 * @name getDimensions
	 * @return returns the list of dimensions of the node
	 */
	list<int> getDimensions() const;

    void setDimensions(list<int> inputDimensions);

	/*!
	 * @name addDimension
	 * @param inputDim
	 * @brief adds a dimension to the node
	 */
	void addDimension(int inputDim);

	/*!
	 * @name addDimensions
	 * @param inputDimensions
	 * @brief adds all the dimensions in inputDimensions to the node
	 */
	void addDimensions(list<int> inputDimensions);


	vector<string> walk() override;

	void setOffset(int inputOffset);


private:
    /*!
     * list of ints of the dimensions of the array
     */
	list<int> dimensions;

	/*!
	 * string to hold the identifier of the array
	 */
	string identifier;

	/*!
	 * int to hold the type of the array
	 */
	int type;

};

/*!
 * @name ASTDeclarationNode
 * @brief class to hold the declaration node
 */
class ASTDeclarationNode : public ASTNode
{
	public:
        /*!
         * @name ASTDeclarationNode
         * @param node_label
         * @param inputType
         * @param childNode
         * @brief creates an object. sets label to node_label, type to inputType, and adds children from childNode.
         * Will propegate the type to all children of the node.
         */
		ASTDeclarationNode(string node_label, int inputType, ASTNode* childNode);

		/*!
		 * @name printNode
		 * @param treeOutFile
		 * @brief prints the node formatted for a tree dot file
		 */
		void printNode(ostream &treeOutFile = cout) override;

		/*!
		 * @name setType
		 * @param inputType
		 * @brief sets the type of the node.
		 */
		void setType(int inputType);

		/*!
		 * @name getType
		 * @return returns the type of the node
		 */
		int getType() const;
		vector<string> walk() override;

		void setOffset(int inputOffset);

	private:
        /*!
         * int to hold the type of the node in
         */
		int type;

		/*!
		 * @name constructorTypeSet
		 * @param node
		 * @param inputType
		 * @brief recursively sets node and all node's children's type to inputType.
		 */
		void constructorTypeSet( ASTNode* node, int inputType );
};

class ASTFunctionNode : public  ASTNode
{
    public:
    ASTFunctionNode(string node_label, int inputType);
    void printNode(ostream &treeOutFile = cout) override;
    void setType( int inputType );
    int getType() const;
    void addChild(ASTNode* addNode);

    vector<string> walk() override;
private:
    int type;

};

class ASTDeclListNode : public ASTNode
{
    public:
    ASTDeclListNode(string node_label, ASTNode* inputChild);
    ASTDeclListNode(string node_label, ASTNode* leftChild, ASTNode* rightChild);
    void printNode(ostream &treeOutFile = cout) override;
    vector<string> walk() override;
};

class ASTFunctionCallNode : public ASTNode
{
    public:
    ASTFunctionCallNode(string node_label, ASTNode* inputChild);
    ASTFunctionCallNode(string node_label, ASTNode* leftChild, ASTNode* rightChild);
    void printNode(ostream &treeOutFile = cout) override;
    vector<string> walk() override;
};

class ASTRelExprNode : public ASTNode
{
    public:
        ASTRelExprNode(string node_label);
        void printNode(ostream& treeOutFile = cout) override;
        vector<string> walk() override;
};

class ASTUnaryNode : public ASTNode
{
    public:
        ASTUnaryNode(string node_label);
        void printNode(ostream& treeOutFile = cout) override;
        vector<string> walk() override;       
};

int typeToByteSize( int type );

string getLine( int lineNum );

#endif //PROJECT_ASTNODE_H
