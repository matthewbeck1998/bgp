#include "ASTNode.h"
#include <fstream>

unsigned int ASTNode::ticketCounter = 0;
unsigned int ASTNode::labelCounter = 0;

int ASTNode::totalNodeCount = 0;

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
		case Enum:
			return "enum";
		default:
			return "type not found";
	}
}


ASTNode::ASTNode (string node_label) : label(move(node_label)), offset(0)
{
    lineNum = line;
	nodeNum = totalNodeCount++;
	activationFrameSize = 0;
}

void ASTNode::addChild (ASTNode *addNode)
{
    if( addNode->getLabel() == "compound_statement" or
        addNode->getLabel() == "declaration_list" or
        addNode->getLabel() == "Declaration" or
        addNode->getLabel() == "array_node" or
        addNode->getLabel() == "IDENTIFIER" or
        addNode->getLabel() == "direct_declarator" or
        addNode->getLabel() == "parameter_list" or
        addNode->getLabel() == "parameter_declaration") // If statement with all the nodes needed for the activation frame size.
        activationFrameSize += addNode -> getActivationFrameSize();
    if(addNode)
    {
        children.push_back(addNode);
    }
}


int ASTNode::getActivationFrameSize() const
{
    return activationFrameSize;
}

void ASTNode::setActivationFrameSize(int inputActivationFrameSize)
{
    activationFrameSize = inputActivationFrameSize;
}

void ASTNode::addOffset(int inputOffset)
{
    offset += inputOffset;
}

string ASTNode::getLabel () const
{
    return label;
}

list<ASTNode *> &ASTNode::getChildren ()
{
    return children;
}

void ASTNode::propegateActivation(int inputActivationSize)
{
    if(!children.empty())
    {
        for(auto it = children.begin() ; it != children.end() ; ++it)
        {
            if( label == "compound_statement" or
                label == "declaration_list" or
                label == "Declaration" or
                label == "array_node" or
                label == "IDENTIFIER" or
                label == "direct_declarator")
                (*it)->propegateActivation(inputActivationSize);
        }
    }
    offset += inputActivationSize;
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

void ASTNode::printNode(ostream &treeOutFile)
{
	//cout << "BASE NODE" << endl;

	treeOutFile << this->getNodeNum() << "[label = \"" << this->getLabel() << endl
	            << "Line: " << lineNum << endl
	            << "BASE NODE" << "\"];" << endl;
	for(auto &it : children)
	{
		treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
		it->printNode(treeOutFile);
	}
}


list<int> ASTNode::getDimensions()
{
    list<int> temp;
    temp.clear();
    return temp;
}


void ASTNode::setOffset(int inputOffset)
{
    offset = inputOffset;
}

int ASTNode::getOffset() const
{
    return offset;
}

ASTMathNode::ASTMathNode (string node_label) : ASTNode::ASTNode(move(node_label))
{
}

ASTMathNode::ASTMathNode(string node_label, ASTNode* LHS, ASTNode* mathOp, ASTNode* RHS) : ASTNode::ASTNode(move(node_label))
{
    activationFrameSize = LHS->getActivationFrameSize() + mathOp -> getActivationFrameSize() + RHS->getActivationFrameSize();
	setType( getHigherType(LHS, RHS) );
	if( LHS->getType() != RHS->getType() )
    {
	    if(LHS->getType() == Double)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", RHS, Double );
            addChild(LHS);
            addChild(mathOp);
            addChild(temp);
            outputStream << "WARNING: implicit conversion from " << printType(RHS) << " to " << printType(LHS) << " on line: " << line << endl;
        }
        else if(RHS->getType() == Double)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", LHS, Double );
            addChild(temp);
            addChild(mathOp);
            addChild(RHS);
            outputStream << "WARNING: implicit conversion from " << printType(LHS) << " to " << printType(RHS) << " on line: " << line << endl;
        }
	    if(LHS->getType() == Float)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", RHS, Float );
            addChild(LHS);
            addChild(mathOp);
            addChild(temp);
            outputStream << "WARNING: implicit conversion from " << printType(RHS) << " to " << printType(LHS) << " on line: " << line << endl;
        }
        else if(RHS->getType() == Float)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", LHS, Float );
            addChild(temp);
            addChild(mathOp);
            addChild(RHS);
            outputStream << "WARNING: implicit conversion from " << printType(LHS) << " to " << printType(RHS) << " on line: " << line << endl;
        }
        else if(LHS->getType() == Int)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", RHS, Int );
            addChild(LHS);
            addChild(mathOp);
            addChild(temp);
            outputStream << "WARNING: implicit conversion from " << printType(RHS) << " to " << printType(LHS) << " on line: " << line << endl;
        }
        else if(RHS->getType() == Int)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", LHS, Int );
            addChild(temp);
            addChild(mathOp);
            addChild(RHS);
            outputStream << "WARNING: implicit conversion from " << printType(LHS) << " to " << printType(RHS) << " on line: " << line << endl;
        }
        else if(LHS->getType() == Char)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", RHS, Char );
            addChild(LHS);
            addChild(mathOp);
            addChild(temp);
            outputStream << "WARNING: implicit conversion from " << printType(RHS) << " to " << printType(LHS) << " on line: " << line << endl;
        }
        else if(RHS->getType() == Char)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", LHS, Char );
            addChild(temp);
            addChild(mathOp);
            addChild(RHS);
            outputStream << "WARNING: implicit conversion from " << printType(LHS) << " to " << printType(RHS) << " on line: " << line << endl;
        }
        //outputStream << "Unsupported types: " << printType( LHS ) << ", " << printType( RHS ) << endl;
    } else
    {
	    addChild(LHS);
	    addChild(mathOp);
	    addChild(RHS);
    }
}

int ASTMathNode::getHigherType(ASTNode* LHS, ASTNode* RHS) const
{
    if(LHS->getType() == Double || RHS->getType() == Double)
    {
        return Double;
    }
	if(LHS->getType() == Float || RHS->getType() == Float)
	{
		return Float;
	}
	if(LHS->getType() == Int || RHS->getType() == Int)
	{
		return Int;
	}
	if(LHS->getType() == Char || RHS->getType() == Char)
	{
		return Char;
	}
	outputStream << "Unsupported types: " << LHS->getType() << ", " << RHS->getType() << endl;
}

void ASTMathNode::printNode(ostream &treeOutFile)
{
	treeOutFile << this->getNodeNum() << "[label = \"" << this->getLabel() << endl << "MATH NODE" << endl;
	treeOutFile << "Line: " << lineNum << "\"];" << endl;
	for(auto &it : children)
	{
		treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
		it->printNode(treeOutFile);
	}

}


string ASTMathNode::printType(ASTNode*& node) const
{
    switch (node->getType())
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


void ASTMathNode::setType(int newType)
{
    type = newType;
}
int ASTMathNode::getType() const
{
    return type;
}

string ASTMathNode::printType() const
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



ASTAssignNode::ASTAssignNode (string node_label) : ASTNode::ASTNode(move(node_label))
{
}

ASTAssignNode::ASTAssignNode(string node_label, ASTNode* LHS, ASTNode* mathOp, ASTNode* RHS) : ASTNode::ASTNode(move(node_label))
{
    activationFrameSize = LHS->getActivationFrameSize() + mathOp -> getActivationFrameSize() + RHS->getActivationFrameSize();
    setType( getHigherType(LHS, RHS) );
    if( LHS->getType() != RHS->getType() )
    {
        if(LHS->getType() == Double)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", RHS, Double );
            addChild(LHS);
            addChild(mathOp);
            addChild(temp);
            outputStream << "WARNING: implicit conversion from " << printType(RHS) << " to " << printType(LHS) << " on line: " << line << endl;
        }
        else if(LHS->getType() == Float)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", RHS, Float );
            addChild(LHS);
            addChild(mathOp);
            addChild(temp);
            outputStream << "WARNING: implicit conversion from " << printType(RHS) << " to " << printType(LHS) << " on line: " << line << endl;
        }
        else if(LHS->getType() == Int)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", RHS, Int );
            addChild(LHS);
            addChild(mathOp);
            addChild(temp);
            outputStream << "WARNING: implicit conversion from " << printType(RHS) << " to " << printType(LHS) << " on line: " << line << endl;
        }
        else if(LHS->getType() == Char)
        {
            ASTCastNode* temp = new ASTCastNode( "cast_node", RHS, Char );
            addChild(LHS);
            addChild(mathOp);
            addChild(temp);
            outputStream << "WARNING: implicit conversion from " << printType(RHS) << " to " << printType(LHS) << " on line: " << line << endl;
        } else
        {
            addChild(LHS);
            addChild(mathOp);
            addChild(RHS);
            outputStream << "WARNING: unsupported types: " << printType(LHS) << ", " << printType(RHS) << " on line: " << line << endl;
        }
    } else
    {
        addChild(LHS);
        addChild(mathOp);
        addChild(RHS);
    }
}

void ASTAssignNode::printNode(ostream &treeOutFile)
{

	treeOutFile << this->getNodeNum() << "[label = \"" << this->getLabel() << endl << "ASSIGN NODE" << endl
	            << "Line: " << lineNum << "\"];" << endl;
	for(auto &it : children)
	{
		treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
		it->printNode(treeOutFile);
	}

}


void ASTAssignNode::setType(int newType)
{
    type = newType;
}
int ASTAssignNode::getType() const
{
    return type;
}


int ASTAssignNode::getHigherType(ASTNode* LHS, ASTNode* RHS) const
{
    return LHS->getType();
}
string ASTAssignNode::printType() const
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

string ASTAssignNode::printType(ASTNode*& node) const
{
    switch (node->getType())
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

ASTVariableNode::ASTVariableNode(string node_label) : ASTNode::ASTNode(move(node_label)), type(Int)
{
}

ASTVariableNode::ASTVariableNode(ASTNode*& RHS) : ASTNode::ASTNode(move( RHS->getLabel() )), type(Int)
{
}


ASTVariableNode::ASTVariableNode(string node_label, int inputType, string inputId)
: ASTNode::ASTNode(move(node_label)), type(inputType), id(inputId)
{

}

int ASTVariableNode::getType() const
{
    return type;
}



string ASTVariableNode::getId() const
{
    return id;
}
void ASTVariableNode::setId(string inputId)
{
    id = inputId;
}

void ASTVariableNode::setType(int inputType)
{
    type = inputType;
}

void ASTVariableNode::printNode(ostream &treeOutFile)
{
	treeOutFile << this->getNodeNum() << "[label = \"" << this->getLabel() << endl;
	treeOutFile << "Line: " << lineNum << endl;
	treeOutFile << "VARIABLE NODE" << endl;
	treeOutFile << "ID: " << id << endl << "Type: " << printType() <<"\"];" << endl;
	for(auto &it : children)
	{
		treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
		it->printNode(treeOutFile);
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


ASTConstNode::ASTConstNode(string node_label) : ASTNode::ASTNode(move(node_label))
{}
ASTConstNode::ASTConstNode(string node_label, int inputType, valueUnion value) : ASTNode::ASTNode(move(node_label)), type(inputType)
{
	setValue(value);
}

int ASTConstNode::getType() const
{
	return type;
}
void ASTConstNode::setType(int inputType)
{
	type = inputType;
}

valueUnion ASTConstNode::getValue() const
{
	return value;
}
void ASTConstNode::setValue(valueUnion inputValue)
{
	switch(type)
	{
        case Double:
            value.dVal = inputValue.dVal;
		case Int:
			value.intVal = inputValue.intVal;
			break;
		case Char:
			value.charVal = inputValue.charVal;
			break;
		case Float:
			value.fVal = inputValue.fVal;
			break;
		default:
            outputStream << "Unsupported type " << printType() << endl;
			exit(-1);
	}
}

void ASTConstNode::printNode(ostream &treeOutFile)
{
	treeOutFile << this->getNodeNum() << "[label = \"" << this->getLabel() << endl;
	treeOutFile << "Line: " << lineNum << endl;
	treeOutFile << "CONST NODE" << endl;
	treeOutFile << "Value: ";
	switch (type)
	{
        case Double:
            treeOutFile <<value.dVal;
            break;
		case Int:
			treeOutFile << value.intVal;
			break;
		case Char:
			treeOutFile << value.charVal;
			break;
		case Float:
			treeOutFile << value.fVal;
			break;
		default:
			outputStream << "Unsupported type for a constant" << endl;
			exit(-1);
	}
	treeOutFile << endl;
	treeOutFile << "Type: " << printType() <<"\"];" << endl;
	for(auto &it : children)
	{
		treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
		it->printNode(treeOutFile);
	}
}

string ASTConstNode::printType()
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

void ASTSelectionNode::printNode(ostream &treeOutFile)
{
	treeOutFile << nodeNum << "[label = \"" << label << endl << "SELECTION NODE" << endl;
	treeOutFile << "Line: " << lineNum << "\"];" << endl;
	for(auto &it : children)
	{
		treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
		it->printNode(treeOutFile);
	}
}

ASTIterationNode::ASTIterationNode(string node_label) : ASTNode::ASTNode(move(node_label))
{

}

void ASTIterationNode::printNode(ostream &treeOutFile)
{
	treeOutFile << nodeNum << "[label = \"" << label << endl << "ITERATION NODE" << endl;
	treeOutFile << "Line: " << lineNum << "\"];" <<endl;
	for(auto &it : children)
	{
		treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
		it->printNode(treeOutFile);
	}
}


ASTIdNode::ASTIdNode(string node_label) : ASTNode::ASTNode(move(node_label))
{
}

ASTIdNode::ASTIdNode(string node_label, string inputId) : ASTNode::ASTNode(move(node_label)), id(inputId)
{
}

string ASTIdNode::getId() const
{
	return id;
}
void ASTIdNode::setId(string inputId)
{
	id = inputId;
}


int ASTIdNode::getType() const
{
    return type;
}
void ASTIdNode::setType( int inputType )
{
    type = inputType;
    activationFrameSize = typeToByteSize(type);
}

void ASTIdNode::printNode(ostream &treeOutFile)
{
    treeOutFile << this->getNodeNum() << "[label = \"" << this->getLabel() << endl;
    treeOutFile << "Line: " << lineNum << endl;
	treeOutFile << "ID NODE" << endl;
    treeOutFile << "id: " << id << endl;
    treeOutFile << "offset: " << offset << endl;
    treeOutFile << "type: " << printType() << "\"];" << endl;
    for(auto &it : children)
    {
        treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
        it->printNode(treeOutFile);
    }
}

string ASTIdNode::printType() const // You meant to write this, right? - Matt
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

ASTTypeNode::ASTTypeNode(string node_label) : ASTNode::ASTNode(move(node_label))
{}
ASTTypeNode::ASTTypeNode(string node_label, int inputType) : ASTNode::ASTNode(move(node_label)), type(inputType)
{}
int ASTTypeNode::getType() const
{
    return type;
}
void ASTTypeNode::setType(int inputType)
{
    type = inputType;
}


void ASTTypeNode::printNode(ostream &treeOutFile)
{
    treeOutFile << this->getNodeNum() << "[label = \"" << this->getLabel() << endl;
	treeOutFile << "Line: " << lineNum << endl;
	treeOutFile << "TYPE NODE" << endl;
    treeOutFile << "type: " << printType() << endl <<"\"];" << endl;
    for(auto &it : children)
    {
        treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
        it->printNode(treeOutFile);
    }
}

string ASTTypeNode::printType() const
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


ASTCastNode::ASTCastNode(string node_label) : ASTNode::ASTNode(move(node_label))
{}
ASTCastNode::ASTCastNode(string node_label, ASTNode* childNode, int castType) : ASTNode::ASTNode(move(node_label)), type( castType )
{
	addChild( childNode );
}
int ASTCastNode::getType() const
{
	return type;
}
void ASTCastNode::setType(int inputType)
{
	type = inputType;
}


void ASTCastNode::printNode(ostream &treeOutFile)
{
	treeOutFile << this->getNodeNum() << "[label = \"" << this->getLabel() << endl;
	treeOutFile << "Line: " << lineNum << endl;
	treeOutFile << "CAST NODE" << endl;
	treeOutFile << "type: " << printType() << endl <<"\"];" << endl;
	for(auto &it : children)
	{
		treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
		it->printNode(treeOutFile);
	}
}

string ASTCastNode::printType() const
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

ASTArrayNode::ASTArrayNode(string node_label, string id, int typeSet): ASTNode::ASTNode(move(node_label)),
                                                                       identifier(move(id)), type(typeSet)
{
    int bytesRequired = typeToByteSize( type );
    for(auto it = dimensions.begin() ; it != dimensions.end() ; ++it )
    {
        bytesRequired *= *it;
    }
    activationFrameSize = bytesRequired;
}



void ASTArrayNode::setOffset( int inputOffset)
{
    offset = inputOffset;
}

void ASTArrayNode::setTheArrayNodeActivationFrameSize()
{
    activationFrameSize = typeToByteSize( type );
    for( int arrayDimension : dimensions)
    {
        activationFrameSize *= arrayDimension;
    }
}

ASTArrayNode::ASTArrayNode(string node_label, ASTNode* inputNode): ASTNode::ASTNode(move(node_label)), type(Int)
{
    offset = inputNode->getOffset();
    for( auto it = inputNode->getChildren().begin() ; it != inputNode->getChildren().end() ; ++it )
    {
        addChild( *it );
    }
}

void ASTArrayNode::printNode(ostream &treeOutFile)
{
	treeOutFile << this->getNodeNum() << "[label = \"" << this->getLabel() << endl;
	treeOutFile << "Line: " << lineNum << endl;
	treeOutFile << "ARRAY NODE" << endl;
	treeOutFile << "id: " << this ->identifier << endl;
	treeOutFile << "offset: " << offset << endl;
	treeOutFile << "dimensions: ";
	for(auto dim = dimensions.rbegin() ; dim != dimensions.rend() ; dim++ )
	  treeOutFile << '[' << *dim << ']';
	treeOutFile << endl;
	treeOutFile << "type: " << printType(type) << endl <<"\"];" << endl;
	for(auto &it : children)
	{
		treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
		it->printNode(treeOutFile);
	}
}

void ASTArrayNode::setType(int inputType)
{
	type = inputType;
}


list<int> ASTArrayNode::getDimensions() const
{
    return dimensions;
}

void ASTArrayNode::setDimensions(list<int> inputDimensions)
{
    dimensions = inputDimensions;
    activationFrameSize = typeToByteSize( type );
    for(auto it = dimensions.begin() ; it != dimensions.end() ; ++it)
    {
        activationFrameSize *= (*it);
    }
}

void ASTArrayNode::addDimension(int inputDim)
{
    dimensions.push_back(inputDim);
}

void ASTArrayNode::addDimensions(list<int> inputDimensions)
{
    while( !inputDimensions.empty() )
    {
        int temp = inputDimensions.front();
        addDimension(temp);
        inputDimensions.pop_front();
    }
}

int ASTArrayNode::getType() const
{
	return type;
}


string ASTArrayNode::getId() const
{
    return identifier;
}


void ASTArrayNode::setId(string inputId)
{
    identifier = inputId;
}


ASTDeclarationNode::ASTDeclarationNode(string node_label, int inputType, ASTNode* childNode)
: type(inputType)
{
    label = node_label;
    lineNum = line;
    nodeNum = totalNodeCount++;
    activationFrameSize = typeToByteSize( inputType );
    if(childNode->getLabel() == "init_declarator_list")
    {
        for(auto it = childNode->getChildren().begin() ; it != childNode->getChildren().end() ; ++it)
        {
            addChild(*it);
            constructorTypeSet(*it, inputType);
        }
    } else if(childNode->getLabel() == "array_node")
    {
        list<int> dimensions = ( (ASTArrayNode*) childNode ) ->getDimensions();
        auto it = dimensions.begin();
        for(int i = 0 ; i < dimensions.size() ; ++i, ++it)
        {
            activationFrameSize *= *it;
        }
        addChild(childNode);
        constructorTypeSet(childNode, inputType);
    }
    else
    {
        addChild(childNode);
        constructorTypeSet(childNode, inputType);
    }
}

void ASTDeclarationNode::printNode(ostream &treeOutFile)
{

treeOutFile << this->getNodeNum() << "[label = \"" << this->getLabel() << endl;
treeOutFile << "Line: " << lineNum << endl;
treeOutFile << "DECLARATION NODE" << endl;
treeOutFile << "type: " << printType(type) << "\"];" << endl;
for(auto &it : children)
{
treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
it->printNode(treeOutFile);
}
}
void ASTDeclarationNode::setType( int inputType )
{
    type = inputType;
}
int ASTDeclarationNode::getType() const
{
    return type;
}


void ASTDeclarationNode::constructorTypeSet( ASTNode* node, int inputType )
{
    if( node->getLabel() != "ASSIGN" and
        node->getLabel() != "init_declarator_list")
    {
        node->setType( inputType );
    }
    for(auto it = node->getChildren().begin() ; it != node->getChildren().end() ; ++it)
    {
        constructorTypeSet(*it, inputType);
    }
}

void ASTDeclarationNode::setOffset(int inputOffset)
{
   children.front() -> setOffset( inputOffset );
}

ASTFunctionNode::ASTFunctionNode(string node_label, int inputType) : ASTNode(move(node_label)), type(inputType)
{
}

void ASTFunctionNode::printNode(ostream &treeOutFile)
{
    treeOutFile << this->getNodeNum() << "[label = \"" << this->getLabel() << endl;
    treeOutFile << "Line: " << lineNum << endl;
    treeOutFile << "FUNCTION NODE" << endl;
    treeOutFile << "type: " << printType(type) << endl;
    treeOutFile << "Activation frame size: " << activationFrameSize <<"\"];" << endl;
    for(auto &it : children)
    {
        treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
        it->printNode(treeOutFile);
    }
}

void ASTFunctionNode::setType( int inputType )
{
    type = inputType;
}

int ASTFunctionNode::getType() const
{
    return type;
}

/*void ASTFunctionNode::addChild(ASTNode *addNode)
{
    if(addNode)
    {
        children.push_back(addNode);
    }
    if(!addNode->getChildren().empty())
    {
        if( addNode->getLabel() == "direct_declarator" and
            addNode->getChildren().back()->getLabel() == "parameter_list" )
        {
            int currentActivation = 0;
            auto param_list_child = addNode->getChildren().back();
            for(auto it = param_list_child->getChildren().begin() ; it != param_list_child->getChildren().end() ; ++it)
            { //Loops through children of parameter list and gets the activation frame size.
                int childByteSize = (*it) -> getActivationFrameSize();
                //(*it) -> setOffset( currentActivation );
                currentActivation += childByteSize;
            }
        } else
        {
            //addNode->propegateActivation(activationFrameSize - addNode->getActivationFrameSize());
        }

    }
}*/


ASTArrayInitializerNode::ASTArrayInitializerNode(string node_label, ASTNode* parentNode, ASTConstNode* childNode, int inputType)
: ASTNode(move(node_label)), type(inputType)
{
    if(parentNode->getLabel() == "initializer_list")
    {
        ASTConstNode* tempParent = (ASTConstNode*) parentNode->getChildren().front();
        valueUnion tempValueUnion = tempParent->getValue();
        double value;
        switch( tempParent->getType() )
        {
            case Int:
                value = tempValueUnion.intVal;
                break;
            case Float:
                value = tempValueUnion.fVal;
                break;
            case Char:
                value = tempValueUnion.charVal;
                break;
            case Double:
                value = tempValueUnion.dVal;
                break;
            default:
                break;
        }
        values.push_back( value );
    } else
    {
        for (double value : ((ASTArrayInitializerNode *) parentNode)->getValues()) {
            values.push_back(value);
        }
    }
    valueUnion tempValueUnion = childNode->getValue();
    double value;
    switch( childNode->getType() )
    {
        case Int:
            value = tempValueUnion.intVal;
            break;
        case Float:
            value = tempValueUnion.fVal;
            break;
        case Char:
            value = tempValueUnion.charVal;
            break;
        case Double:
            value = tempValueUnion.dVal;
            break;
        default:
            break;
    }
    values.push_back( value );
}
int ASTArrayInitializerNode::getType() const
{
    return type;
}
void ASTArrayInitializerNode::setType( int inputType )
{
    type = inputType;
}
vector<double> ASTArrayInitializerNode::getValues() const
{
    return values;
}

void ASTArrayInitializerNode::printNode(ostream &treeOutFile)
{
    treeOutFile << this->getNodeNum() << "[label = \"" << this->getLabel() << endl;
    treeOutFile << "Line: " << lineNum << endl;
    treeOutFile << "Array Initializer Node" << endl;
    treeOutFile << "Type: " << printType(type) << endl;
    treeOutFile << "Values: ";
    for(int value : values)
    {
        treeOutFile << "[" << value << "] ";
    }

    treeOutFile <<"\"];" << endl;

    for(auto &it : children)
    {
        treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
        it->printNode(treeOutFile);
    }
}

void ASTNode::giveReturnNodeMyActivationFrameSize( int functionActivationSize )
{
    if(label == "RETURN")
    {
        activationFrameSize = functionActivationSize;
    } else
    {
        for(ASTNode* child : children)
        {
            child->giveReturnNodeMyActivationFrameSize( functionActivationSize );
        }
    }
}

void ASTNode::reverseTheOffsetSize(int functionActivationFrameSize)
{
    if( label == "IDENTIFIER" or
        label == "array_node")
    {
        offset = functionActivationFrameSize - offset;
    } else
    {
        for( ASTNode* child : children )
        {
            child->reverseTheOffsetSize(functionActivationFrameSize);
        }
    }
}

ASTReturnNode::ASTReturnNode(string node_label) : ASTNode(move(node_label))
{
}

ASTReturnNode::ASTReturnNode(string node_label, ASTNode *childNode) : ASTNode(move(node_label))
{
    addChild( childNode );
}

void ASTReturnNode::printNode(ostream &treeOutFile)
{
    treeOutFile << this->getNodeNum() << "[label = \"" << this->getLabel() << endl;
    treeOutFile << "Line: " << lineNum << endl;
    treeOutFile << "Return Node" << endl;
    treeOutFile << "Activation Frame Size: " << activationFrameSize << endl;

    treeOutFile <<"\"];" << endl;

    for(auto &it : children)
    {
        treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
        it->printNode(treeOutFile);
    }
}

string ASTNode::walk()
{
	//cout << "ASTNode: " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}
	return {};
}

string ASTMathNode::walk()
{
	//cout << "ASTMathNode: " << endl;
	vector<string> returnValues;
	for(auto it : children)
	{
		returnValues.push_back(it->walk());
	}

//	cout << "MATH NODE STUFF " << endl;
//	int i = 0;
//	for(const auto& rt: returnValues)
//	{
//		cout << i++ << " : " << rt << endl;
//	}

	if(children.front()->getLabel() == "IDENTIFIER" and
	   children.back()->getLabel() == "IDENTIFIER")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);
		string ticket3 = "$t" + to_string(ticketCounter++);
		string ticket4 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << children.front()->getOffset() << endl;
		//cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << children.front()->getOffset() << endl;

		cout << "addiu\t" << ticket1 + "\t" << "$sp\t" << children.back()->getOffset() << endl;
		//cout << "subiu\t" << ticket3 + "\t" << ticket2 + "\t" << children.back()->getOffset() << endl;

		cout << "lw\t" << ticket2 + "\t" << "0(" + ticket0 + ")" << endl;

		cout << "lw\t" << ticket3 + "\t" << "0(" + ticket1 + ")" << endl;

		cout << (*next(children.begin()))->getLabel() + "\t" << ticket4 + "\t"
			 << ticket2 + "\t" << ticket3 << endl;
		return ticket4;
	}
	else if(children.front()->getLabel() == "IDENTIFIER" and
			children.back()->getLabel() == "INT_CONSTANT")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);
		string ticket3 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << children.front()->getOffset() << endl;
		//cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << children.front()->getOffset() << endl;

		cout << "lw\t" << ticket1 + "\t" << "0(" + ticket0 + ")" << endl;

		cout << "li\t" << ticket2 + "\t" << returnValues[2] << endl;

		cout << (*next(children.begin()))->getLabel() + "\t" << ticket3 + "\t"
			 << ticket1 + "\t" << ticket2 << endl;
		return ticket3;
	}
	else if(children.front()->getLabel() == "IDENTIFIER" and
			children.back()->getLabel() == "array_node")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);
		string ticket3 = "$t" + to_string(ticketCounter++);
		string ticket4 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << children.front()->getOffset() << endl;
		//cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << children.front()->getOffset() << endl;

		cout << "addiu\t" << ticket1 + "\t" << "$sp\t" << returnValues[2] << endl;
		//cout << "subiu\t" << ticket3 + "\t" << ticket2 + "\t" << returnValues[2] << endl;

		cout << "lw\t" << ticket2 + "\t" << "0(" + ticket0 + ")" << endl;

		cout << "lw\t" << ticket3 + "\t" << "0(" + ticket1 + ")" << endl;

		cout << (*next(children.begin()))->getLabel() + "\t" << ticket4 + "\t"
			 << ticket2 + "\t" << ticket3 << endl;
		return ticket4;
	}
	else if(children.front()->getLabel() == "INT_CONSTANT" and
			children.back()->getLabel() == "INT_CONSTANT")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);

		cout << "li\t" << ticket0 + "\t" << returnValues[0] << endl;

		cout << "li\t" << ticket1 + "\t" << returnValues[2] << endl;

		cout << (*next(children.begin()))->getLabel() + "\t" << ticket2 + "\t"
			 << ticket0 + "\t" << ticket1 << endl;
		return ticket2;
	}
	else if(children.front()->getLabel() == "INT_CONSTANT" and
			children.back()->getLabel() == "IDENTIFIER")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);
		string ticket3 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << children.back()->getOffset() << endl;
		//cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << children.back()->getOffset() << endl;

		cout << "lw\t" << ticket1 + "\t" << "0(" + ticket0 + ")" << endl;

		cout << "li\t" << ticket2 + "\t" << returnValues[0] << endl;

		cout << (*next(children.begin()))->getLabel() + "\t" << ticket3 + "\t"
			 << ticket2 + "\t" << ticket1 << endl;
		return ticket3;
	}
	else if(children.front()->getLabel() == "INT_CONSTANT" and
			children.back()->getLabel() == "array_node")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);
		string ticket3 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << returnValues[2] << endl;
		//cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << returnValues[2] << endl;

		cout << "lw\t" << ticket1 + "\t" << "0(" + ticket0 + ")" << endl;
		cout << "li\t" << ticket2 + "\t" << returnValues[0] << endl;

		cout << (*next(children.begin()))->getLabel() + "\t" << ticket3 + "\t"
			 << ticket2 + "\t" << ticket1 << endl;
		return ticket3;
	}
	else if(children.front()->getLabel() == "array_node" and
			children.back()->getLabel() == "array_node")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);
		string ticket3 = "$t" + to_string(ticketCounter++);
		string ticket4 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << returnValues[0] << endl;
		//cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << returnValues[0] << endl;

		cout << "addiu\t" << ticket1 + "\t" << "$sp\t" << returnValues[2] << endl;
		//cout << "subiu\t" << ticket3 + "\t" << ticket2 + "\t" << returnValues[2] << endl;

		cout << "lw\t" << ticket2 + "\t" << "0(" + ticket0 + ")" << endl;
		cout << "LW\t" << ticket3 + "\t" << "0(" + ticket1 + ")" << endl;

		cout << (*next(children.begin()))->getLabel() + "\t" << ticket4 + "\t"
			 << ticket2 + "\t" << ticket3 << endl;
		return ticket4;
	}
	else if(children.front()->getLabel() == "array_node" and
			children.back()->getLabel() == "INT_CONSTANT")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);
		string ticket3 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << returnValues[0] << endl;
		//cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << returnValues[0] << endl;

		cout << "lw\t" << ticket1 + "\t" << "0(" + ticket0 + ")" << endl;
		cout << "li\t" << ticket2 + "\t" << returnValues[2] << endl;

		cout << (*next(children.begin()))->getLabel() + "\t" << ticket3 + "\t"
			 << ticket1 + "\t" << ticket2 << endl;
		return ticket3;
	}
	else if(children.front()->getLabel() == "array_node" and
			children.back()->getLabel() == "IDENTIFIER")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);
		string ticket3 = "$t" + to_string(ticketCounter++);
		string ticket4 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << returnValues[0] << endl;
		//cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << returnValues[0] << endl;

		cout << "addiu\t" << ticket1 +"\t" << "$sp\t" << children.back()->getOffset() << endl;
		//cout << "subiu\t" << ticket3 + "\t" << ticket2 + "\t" << children.back()->getOffset() << endl;

		cout << "lw\t" << ticket2 + "\t" << "0(" + ticket0 + ")" << endl;
		cout << "lw\t" << ticket3 + "\t" << "0(" + ticket1 + ")" << endl;

		cout << (*next(children.begin()))->getLabel() + "\t" << ticket4 + "\t"
			 << ticket2 + "\t" << ticket3 << endl;
		return ticket4;
	}
	else if((children.front()->getLabel() == "additive_expression"
			or children.front()->getLabel() == "multiplicative_expression")
			and children.back()->getLabel() == "INT_CONSTANT")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);

		cout << "li\t" << ticket0 + "\t" << returnValues[2] << endl;

		cout << (*next(children.begin()))->getLabel() + "\t" << ticket1 + "\t" << returnValues[0] + "\t"
			 << ticket0 << endl;
		return ticket1;
	}
	else if((children.front()->getLabel() == "additive_expression"
			 or children.front()->getLabel() == "multiplicative_expression")
			and children.back()->getLabel() == "IDENTIFIER")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << children.back()->getOffset() << endl;
		//cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << children.back()->getOffset() << endl;

		cout << "lw\t" << ticket1 + "\t" << "0(" + ticket0 + ")" << endl;

		cout << (*next(children.begin()))->getLabel() + "\t" << ticket2 + "\t" <<  returnValues[0] + "\t"
			 << ticket1 << endl;
		return ticket2;
	}
	else if((children.front()->getLabel() == "additive_expression"
			 or children.front()->getLabel() == "multiplicative_expression")
			and children.back()->getLabel() == "array_node")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << returnValues[2] << endl;
		//cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << returnValues[2] << endl;

		cout << "lw\t" << ticket1 + "\t" << "0(" + ticket0 + ")" << endl;

		cout << (*next(children.begin()))->getLabel() + "\t" << ticket2 + "\t" <<  returnValues[0] + "\t"
			 <<  ticket1 << endl;
		return ticket2;
	}
	else if(children.front()->getLabel() == "INT_CONSTANT" and
			(children.back()->getLabel() == "additive_expression"
			 or children.back()->getLabel() == "multiplicative_expression"))
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);

		cout << "li\t" << ticket0 + "\t" << returnValues[0] << endl;
		cout << (*next(children.begin()))->getLabel() + "\t" << ticket1 + "\t" << ticket0 + "\t"
			 << returnValues[2] << endl;
		return ticket1;
	}
	else if(children.front()->getLabel() == "IDENTIFIER" and
			(children.back()->getLabel() == "additive_expression"
			 or children.back()->getLabel() == "multiplicative_expression"))
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << children.front()->getOffset() << endl;
		//cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << children.front()->getOffset() << endl;
		cout << "lw\t" << ticket1 + "\t" << "0(" + ticket0 + ")" << endl;

		cout << (*next(children.begin()))->getLabel() + "\t" << ticket2 + "\t" << ticket1 + "\t"
			 << returnValues[2] << endl;
		return ticket2;
	}
	else if(children.front()->getLabel() == "array_node" and
			(children.back()->getLabel() == "additive_expression"
			 or children.back()->getLabel() == "multiplicative_expression"))
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << returnValues[0] << endl;
		//cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << returnValues[0] << endl;
		cout << "lw\t" << ticket1 + "\t" << "0(" + ticket0 + ")" << endl;

		cout << (*next(children.begin()))->getLabel() + "\t" << ticket2 + "\t" << ticket1 + "\t"
			 << returnValues[2] << endl;
		return ticket2;
	}
	else if((children.front()->getLabel() == "additive_expression"
			 or children.front()->getLabel() == "multiplicative_expression") and
			(children.back()->getLabel() == "additive_expression"
			 or children.back()->getLabel() == "multiplicative_expression"))
	{
		string ticket0 = "$t" + to_string(ticketCounter++);

		cout << (*next(children.begin()))->getLabel() + "\t" << ticket0 + "\t" << returnValues[0] + "\t"
			 << returnValues[2] << endl;
		return ticket0;
	}
	else
	{
		cout << "MATH NODE BROKEN" << endl;
		cout << "FRONT: " << children.front()->getLabel() << endl;
		cout << "BACK: " << children.back()->getLabel() << endl;
		return "MATH NODE BROKEN";
	}

}

string ASTIdNode::walk()
{
	//cout << "ASTIdNode: " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}
	//string ticket = {"t_" + to_string(ticketCounter++)};
	//vector<string> temp = {ticket, "LOAD", ticket, to_string(this->getOffset()) + " ## " + this->getId()};
	//threeAddressCode.push_back(temp);
	//cout << "ADDR " << ticket << " " << this->getId() << endl;

	//vector<string> rv = {"ADDR", ticket, };
	return {};
}

string ASTAssignNode::walk()
{
	vector<string> returnValues;

	//cout << "ASTAssignNode: " << endl;
	for(auto &it : children)
	{
		returnValues.push_back(it->walk());
	}

//	cout << "ASSIGN NODE STUFF" << endl;
//	int i = 0;
//	for(const auto& rt: returnValues)
//	{
//		cout << i++ << " : " << rt << endl;
//	}


	if(children.front()->getLabel() == "IDENTIFIER" and
		children.back()->getLabel() == "INT_CONSTANT")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << "FS" << endl;
		cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << children.front()->getOffset() << endl;
		cout << "li\t" << ticket2 + "\t" << returnValues[2] << endl;
		cout << "sw\t" << ticket2 + '\t' << "0(" + ticket1 + ")" << endl;
	}
	else if(children.front()->getLabel() == "IDENTIFIER" and
			children.back()->getLabel() == "array_node")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);
		string ticket3 = "$t" + to_string(ticketCounter++);
		string ticket4 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << "FS" << endl;
		cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << returnValues[2] << endl;
		cout << "addiu\t" << ticket2 + "\t" << "$sp\t" << "FS" << endl;
		cout << "subiu\t" << ticket3 + "\t" << ticket2 + "\t" << children.front()->getOffset() << endl;
		cout << "lw\t" << ticket4 + "\t" << "0(" + ticket1 + ")" << endl;
		cout << "sw\t" << ticket4 + "\t" << "0(" + ticket3 + ")" << endl;
	}
	else if(children.front()->getLabel() == "IDENTIFIER" and
			(children.back()->getLabel() == "additive_expression"
			 or children.back()->getLabel() == "multiplicative_expression"))
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << "FS" << endl;
		cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << children.front()->getOffset() << endl;
		cout << "sw\t" << returnValues[2] + "\t" << "0(" + ticket1 + ")" << endl;
	}
	else if(children.front()->getLabel() == "array_node" and
			children.back()->getLabel() == "INT_CONSTANT")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << "FS" << endl;
		cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << returnValues[0] << endl;
		cout << "li\t" << ticket2 + "\t" << returnValues[2] << endl;
		cout << "sw\t" << ticket2 << "0(" + ticket1 + ")" << endl;
	}
	else if(children.front()->getLabel() == "array_node" and
			children.back()->getLabel() == "IDENTIFIER")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);
		string ticket3 = "$t" + to_string(ticketCounter++);
		string ticket4 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << "FS" << endl;
		cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << children.back()->getOffset() << endl;
		cout << "addiu\t" << ticket2 + "\t" << "$sp\t" << "FS" << endl;
		cout << "subiu\t" << ticket3 + "\t" << ticket2 + "\t" << returnValues[0] << endl;
		cout << "lw\t" << ticket4 + "\t" << "0(" + ticket1 + ")" << endl;
		cout << "sw\t" << ticket4 << "0(" + ticket3 + ")" << endl;
	}
	else if(children.front()->getLabel() == "array_node" and
			(children.back()->getLabel() == "additive_expression"
			 or children.back()->getLabel() == "multiplicative_expression"))
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << "FS" << endl;
		cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << returnValues[0] << endl;
		cout << "sw\t" << returnValues[2] + "\t" << "0(" + ticket1 + ")" << endl;
	}
	else if(children.front()->getLabel() == "array_node" and
			children.back()->getLabel() == "array_node")
	{
		string ticket0 = "$t" + to_string(ticketCounter++);
		string ticket1 = "$t" + to_string(ticketCounter++);
		string ticket2 = "$t" + to_string(ticketCounter++);
		string ticket3 = "$t" + to_string(ticketCounter++);
		string ticket4 = "$t" + to_string(ticketCounter++);

		cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << "FS" << endl;
		cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << returnValues[2] << endl;
		cout << "addiu\t" << ticket2 + "\t" << "$sp\t" << "FS" << endl;
		cout << "subiu\t" << ticket3 + "\t" << ticket2 + "\t" << returnValues[0] << endl;
		cout << "lw\t" << ticket4 + "\t" << "0(" + ticket1 + ")" << endl;
		cout << "sw\t" << ticket4 + "\t" << "0(" + ticket3 + ")" << endl;
	}
	else
	{
		cout << "ASSIGN IS BROKEN" << endl;
		cout << "Front: " << children.front()->getLabel() << endl;
		cout << "Back: " << children.back()->getLabel() << endl;
		return "ASSIGN IS BROKEN";
	}

	return {};
}

string ASTVariableNode::walk()
{
	cout << "ASTVariable " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}
	return {};
}

string ASTConstNode::walk()
{
	//cout << "ASTConstNode " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}


	if(this->getType() == Int)
		return {to_string(this->getValue().intVal)};
	else if(this->getType() == Float)
		return {to_string(this->getValue().fVal)};
	else if(this->getType() == Char)
		return {to_string(this->getValue().charVal)};
	else if(this->getType() == Double)
		return {to_string(this->getValue().dVal)};
	else
		return {"ERROR IN CONST NODE WALK"};
}


string ASTIterationNode::walk()
{
	//cout << "ASTIterationNode: " << endl;
	for(auto it: children)
	{
		it->walk();
	}

//    auto name = children.begin();
//    auto expr1 = next(name, 1); // for loop init, while/do-while nothing
//    auto expr2 = next(name, 2); // condition in all three
//    auto expr3 = next(name, 3); // for loop do after iteration, while/do-while nothing
//    auto body = next(name, 4); // body in all three
//
//    string iterLabel = "l_" + to_string(labelCounter++);
//    string condLabel = "l_" + to_string(labelCounter++);
//    string exitLabel = "l_" + to_string(labelCounter++);
//
//
//    // walk(expr1)
//    (*expr1)->walk();
//
//    // do-while requires body to walk at least once
//    if ((*name)->getLabel() == "DO")
//    {
//        (*body)->walk();
//    }
//
//    // LABEL    L0
//    cout << "LABEL" << "\t" << iterLabel << endl;
//
//    // walk(expr2)
//    auto condVec = (*expr2)->walk();
//    string condReg = condVec[0];
//
//    // BEQ      R2
//    cout << "BEQ" << "\t" << condReg << "\t" << "1" << "\t" << condLabel << endl;
//
//    // B        L2
//    cout << "B" << "\t" << exitLabel << endl;
//
//    // LABEL    L1
//    cout << "LABEL" << "\t" << condLabel << endl;
//
//    // walk(body)
//    (*body)->walk();
//
//    // walk(expr3)
//    (*expr3)->walk();
//    // B        L0
//    cout << "B" << "\t" << iterLabel << endl;
//
//    // LABEL    L2
//    cout << "LABEL" << "\t" << exitLabel << endl;

	return {};
}

string ASTSelectionNode::walk()
{
	//cout << "ASTSelectionNode: " << endl;
	for(auto it: children)
	{
		it->walk();
	}

    // TODO: Edge case, if (1)
    auto relExprNode = next(children.begin(), 1);
    auto relExprVec = (*relExprNode)->walk();

    string returnedTicket = relExprVec;
    string trueLabel = "l_" + to_string(labelCounter++);
    string endLabel = "l_" + to_string(labelCounter++);

    cout << "BEQ" << "\t" << returnedTicket << "\t" << "1" << "\t" << trueLabel << endl;

    auto falseNode = prev(children.end(), 1);
    auto falseNodeVec = (*falseNode)->walk();

    cout << "B" << "\t" << endLabel << endl;
    cout << "LABEL" << "\t" << trueLabel << endl;

    auto trueNode = next(relExprNode, 1);
    auto trueNodeVec = (*trueNode)->walk();

    cout << "LABEL" << "\t" << endLabel << endl;

	return {};
}


string ASTDeclarationNode::walk()
{
	//cout << "ASTDeclarationNode " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}
	return {};
}

string ASTTypeNode::walk()
{
	//cout << "ASTTypeNode " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}

	return {};
}

string ASTCastNode::walk()
{
	//cout << "ASTCastNode " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}
	return {};
}

string ASTArrayNode::walk()
{
	if(!children.empty() and dimensions.size() != children.size())
	{
		cout << "ERROR: wrong dimensional access on line " << lineNum << endl;
		exit(EXIT_FAILURE);
	}


	//cout << "ASTArrayNode " << endl;
	vector<string> returnValues;
	for(auto it : children)
	{
		//cout << "LABEL: " << it->getLabel() << endl;
		returnValues.push_back(it->walk());
	}



//	cout << "ARRAY NODE STUFF Line: " << lineNum << endl;
//	int i = 0;
//	for(const auto& rt: returnValues)
//	{
//		cout << i++ << " : " << rt << endl;
//	}
//
//
//	for(auto dim = dimensions.rbegin() ; dim != dimensions.rend() ; dim++ )
//	{
//		cout << "[" <<  (*dim) << "]";
//	}
//
//	cout << endl;

	if(!children.empty())
	{
		if(children.size() == 1)
		{
			if(children.front()->getLabel() == "INT_CONSTANT")
			{
				string ticket0 = "$t" + to_string(ticketCounter++);
				string ticket1 = "$t" + to_string(ticketCounter++);
				string ticket2 = "$t" + to_string(ticketCounter++);

				cout << "li\t" << ticket0 + "\t" << returnValues[0] << endl;
				cout << "mul\t" << ticket1 + "\t" << ticket0 + "\t" << typeToByteSize(type) << endl;
				cout << "addiu\t" << ticket2 + "\t" << ticket1 + "\t" << offset << endl;
				return ticket2;
			}
			else if(children.front()->getLabel() == "IDENTIFIER")
			{
				string ticket0 = "$t" + to_string(ticketCounter++);
				string ticket1 = "$t" + to_string(ticketCounter++);
				string ticket2 = "$t" + to_string(ticketCounter++);
				string ticket3 = "$t" + to_string(ticketCounter++);
				string ticket4 = "$t" + to_string(ticketCounter++);

				cout << "addiu\t" << ticket0 +"\t" << "$sp\t" << "FS" << endl;
				cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << children.front()->getOffset() << endl;
				cout << "lw\t" << ticket2 + "\t" << "0(" + ticket1 + ")" << endl;
				cout << "mul\t" << ticket3 + "\t" << ticket2 + "\t" << typeToByteSize(type) << endl;
				cout << "addiu\t" << ticket4 + "\t" << ticket3 + "\t" << offset << endl;
				return ticket4;
			}
			else if(children.front()->getLabel() == "array_node")
			{
				string ticket0 = "$t" + to_string(ticketCounter++);
				string ticket1 = "$t" + to_string(ticketCounter++);
				string ticket2 = "$t" + to_string(ticketCounter++);
				string ticket3 = "$t" + to_string(ticketCounter++);
				string ticket4 = "$t" + to_string(ticketCounter++);

				cout << "addiu\t" << ticket0 +"\t" << "$sp\t" << "FS" << endl;
				cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << returnValues[0] << endl;
				cout << "lw\t" << ticket2 + "\t" << "0(" + ticket1 + ")" << endl;
				cout << "mul\t" << ticket3 + "\t" << ticket2 + "\t" << typeToByteSize(type) << endl;
				cout << "addiu\t" << ticket4 + "\t" << ticket3 + "\t" << offset << endl;
				return ticket4;
			}
			else
			{
				cout << "1D Array Broken on line: " << lineNum << endl;
				cout << "Front: " << children.front()->getLabel() << endl;
				return "ARRAY BROKEN";
			}
		}
		else
		{
			int prevTicketNum = 0;
			int currentReturnIndex = 0;
			int startingDim = 1;
			string returnTicket = "SOMETHING ARRAY WRONG TICKET";
			for(auto child: children)
			{
				string currentTicket = "AHHHHH";
				prevTicketNum = ticketCounter - 1;
				if(child->getLabel() == "INT_CONSTANT")
				{
					string ticket0 = "$t" + to_string(ticketCounter++);

					cout << "li\t" << ticket0 + "\t" << returnValues[currentReturnIndex] << endl;

					currentTicket.assign(ticket0);
				}
				else if(child->getLabel() == "IDENTIFIER")
				{
					string ticket0 = "$t" + to_string(ticketCounter++);
					string ticket1 = "$t" + to_string(ticketCounter++);
					string ticket2 = "$t" + to_string(ticketCounter++);

					cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << "FS" << endl;
					cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << returnValues[currentReturnIndex] << endl;
					cout << "lw\t" << ticket2 + "\t" << "0(" + ticket1 + ")" << endl;

					currentTicket.assign(ticket2);
				}
				else if(child->getLabel() == "array_node")
				{
					string ticket0 = "$t" + to_string(ticketCounter++);
					string ticket1 = "$t" + to_string(ticketCounter++);
					string ticket2 = "$t" + to_string(ticketCounter++);

					cout << "addiu\t" << ticket0 + "\t" << "$sp\t" << "FS" << endl;
					cout << "subiu\t" << ticket1 + "\t" << ticket0 + "\t" << returnValues[currentReturnIndex];
					cout << "lw\t" << ticket2 + "\t" << "0(" + ticket1 + ")" << endl;

					currentTicket.assign(ticket2);
				}


				for(auto dim = next(dimensions.rbegin(), startingDim); dim != dimensions.rend(); dim++)
				{
					string ticket0 = "$t" + to_string(ticketCounter++);
					cout << "mul\t" << ticket0 + "\t" << currentTicket + "\t" << *dim << endl;
					currentTicket.assign(ticket0);
				}
				if(child != children.front())
				{
					string previousTicket1 = "$t" + to_string(ticketCounter - 1);
					string previousTicket2 = "$t" + to_string(prevTicketNum);
					string ticket0 = "$t" + to_string(ticketCounter++);
					cout << "add\t" << ticket0 + "\t" << previousTicket1 + "\t" << previousTicket2 << endl;
					returnTicket.assign(ticket0);
				}
				currentReturnIndex++;
				startingDim++;
			}
			return returnTicket;
		}
	}

	return "ARRAY WRONG";
}

string ASTDeclListNode::walk()
{
	//cout << "ASTDeclarationListNode " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}
	return {};
}

string ASTFunctionCallNode::walk()
{
	//cout << "ASTFunctionCallNode " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}
	return {};
}

string ASTRelExprNode::walk()
{
	//cout << "ASTRelExprNode: " << endl;
	vector<string> returnValues;
	for (auto it : children)
	{
		returnValues.push_back(it->walk());
	}




//	cout << "ASTRelExprNode on line: " << lineNum << endl;
//	int i = 0;
//	for(auto it : returnValues)
//	{
//		cout << "i" << i << ": " << it << endl;
//	}


//	string ticket = {"t_" + to_string(ticketCounter++)};
//	string trueLabel = {"l_" + to_string(labelCounter++)};
//	string endLabel = {"l_" + to_string(labelCounter++)};
//	string branchFirstArg = "";
//	string branchSecondArg = "";
//
//	if (children.front()->getLabel() == "INT_CONSTANT")
//	{
//		branchFirstArg = returnValues[0];
//	}
//	else if (children.front()->getLabel() == "IDENTIFIER")
//	{
//		string leftCommand = returnValues[1];
//		string leftTemp = returnValues[2];
//		string leftName = returnValues[3];
//		branchFirstArg = "0(" + leftTemp + ")";
//		cout << leftCommand << "\t" << leftTemp << "\t" << leftName << endl;
//	}
//
//	if (children.back()->getLabel() == "INT_CONSTANT") // TODO: can only support int constant comparisons right now
//	{
//		branchSecondArg = returnValues[2][0];
//	}
//	else if (children.back()->getLabel() == "IDENTIFIER")
//	{
//		string rightCommand = returnValues[2][1];
//		string rightTemp = returnValues[2][2];
//		string rightName = returnValues[2][3];
//		branchSecondArg = "0(" + rightTemp + ")";
//		cout << rightCommand << "\t" << rightTemp << "\t" << rightName << endl;
//	}
//
//
//	auto it = ++(children.begin()); // get middle child (operator)
//	string label = (*it)->getLabel();
//	string op = label.substr(0, 2);
//	string command = "B" + op;
//	cout << command << "\t" << branchFirstArg << "\t" << branchSecondArg << "\t" << trueLabel << endl;
//	cout << "LOAD" << "\t" << ticket << "\t" << "0" << endl;
//	cout << "B" << "\t" << endLabel << endl;
//	cout << "LABEL" << "\t" << trueLabel << endl;
//	cout << "LOAD" << "\t" << ticket << "\t" << "1" << endl;
//	cout << "LABEL" << "\t" << endLabel << endl;
//
//	return ticket;
	return {};
}

string ASTUnaryNode::walk()
{
	//cout << "ASTUnaryNode: " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}
	return {};
}


string ASTFunctionNode::walk()
{
	//cout << "ASTFunctionNode: " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}
	return {};
}

ASTDeclListNode::ASTDeclListNode(string node_label, ASTNode *inputChild) : ASTNode(move(node_label))
{
    //( (ASTDeclarationNode*) inputChild ) -> setOffset(activationFrameSize);
    addChild(inputChild);
}

ASTDeclListNode::ASTDeclListNode(string node_label, ASTNode* leftChild, ASTNode* rightChild) : ASTNode(move(node_label))
{
    addChild(leftChild);
    //( (ASTDeclarationNode*) rightChild ) -> setOffset(activationFrameSize);
    addChild(rightChild);
}
void ASTDeclListNode::printNode(ostream &treeOutFile)
{

    treeOutFile << this->getNodeNum() << "[label = \"" << this->getLabel() << endl;
    treeOutFile << "Line: " << lineNum << endl;
    treeOutFile << "DECL LIST NODE" << endl;
    treeOutFile << "Activation frame size: " << activationFrameSize <<"\"];" << endl;
    for(auto &it : children)
    {
        treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
        it->printNode(treeOutFile);
    }
}

ASTFunctionCallNode::ASTFunctionCallNode(string node_label, ASTNode *inputChild) : ASTNode(move(node_label))
{
    addChild(inputChild);
    activationFrameSize = inputChild->getOffset();
}

ASTFunctionCallNode::ASTFunctionCallNode(string node_label, ASTNode* leftChild, ASTNode* rightChild) : ASTNode(move(node_label))
{
    addChild(leftChild);
    addChild(rightChild);
    activationFrameSize = leftChild->getOffset();
}

void ASTFunctionCallNode::printNode(ostream &treeOutFile)
{

    treeOutFile << this->getNodeNum() << "[label = \"" << this->getLabel() << endl;
    treeOutFile << "Line: " << lineNum << endl;
    treeOutFile << "FUNCTION CALL NODE" << endl;
    treeOutFile << "Offset: " << offset << endl;
    treeOutFile << "Activation frame size: " << activationFrameSize <<"\"];" << endl;
    for(auto &it : children)
    {
        treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
        it->printNode(treeOutFile);
    }
}

ASTRelExprNode::ASTRelExprNode(string node_label) : ASTNode(move(node_label))
{

}

void ASTRelExprNode::printNode(ostream& treeOutFile)
{
    treeOutFile << this->getNodeNum() 
                << "[label = \"" << this->getLabel() << endl
	            << "Line: " << lineNum << endl
	            << "RELATIONAL EXPRESSION NODE" << "\"];" << endl;
	for (auto &it : children)
	{
		treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
		it->printNode(treeOutFile);
	}
}


ASTUnaryNode::ASTUnaryNode(string node_label) : ASTNode(move(node_label))
{

}

void ASTUnaryNode::printNode(ostream& treeOutFile)
{
    treeOutFile << this->getNodeNum() 
                << "[label = \"" << this->getLabel() << endl
	            << "Line: " << lineNum << endl
	            << "RELATIONAL EXPRESSION NODE" << "\"];" << endl;
	for (auto &it : children)
	{
		treeOutFile << nodeNum << " -> " << it->getNodeNum() << endl;
		it->printNode(treeOutFile);
	}
}

int typeToByteSize( int type )
{
    switch( type )
    {
        case Char:
            return 1;

        case Short:
            return 4;

        case Int:
            return 4;

        case Long:
            return 4;

        case Float:
            return 4;

        case Double:
            return 8;

    }
    return 0;
}

string getLine( int lineNum )
{
    ifstream inputFile;
    inputFile.open(inputFileName);
    char returnString[255];
    for(int i = 0 ; i < lineNum ; ++i)
    {
        inputFile.getline(returnString, 255);
    }
    return returnString;
}
