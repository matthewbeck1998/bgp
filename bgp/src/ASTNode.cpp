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
    if( node->getLabel() != "ASSIGN" )
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

void ASTFunctionNode::addChild(ASTNode *addNode)
{
    activationFrameSize += addNode -> getActivationFrameSize();
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
}

vector<string> ASTNode::walk()
{
	//cout << "ASTNode " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}
	return {};
}

vector<string> ASTMathNode::walk()
{
	//cout << "ASTMathNode " << this->getLabel() << endl;
	/*if( ( (ASTVariableNode*) children.front() )->getType() != ( (ASTVariableNode*) children.back() )->getType())
	{
		return false;
	}*/

	vector<vector<string>> returnValues;
	for(auto it : children)
	{
		returnValues.push_back(it->walk());
	}


	string ticket = {"t_" + to_string(ticketCounter++)};
	//vector<string> temp = {"ADD", ticket, returnValues[0][0], returnValues[2][0]};
	/*cout << "MATH NODE STUFF " << endl;
	cout << "FRONT CHILD: " << getChildren().front()->getLabel() << endl;
	cout << "BACK CHILD: " << getChildren().back()->getLabel() << endl;
	int i = 0;
	for(auto it: returnValues)
	{
		int j = 0;
		//cout << it.front() << endl;
		for(auto& rt: it)
		{
			cout << "i " << i << " " << "j " << j++ << " " << rt << endl;
		}
		i++;
	}*/


	if(getChildren().front()->getLabel() == "IDENTIFIER")
	{
		cout << returnValues[0][1] << '\t' << returnValues[0][2] << '\t' << returnValues[0][3] << endl;
	}
	if(getChildren().back()->getLabel() == "IDENTIFIER")
	{
		cout << returnValues[2][1] << '\t' << returnValues[2][2] << '\t' << returnValues[2][3] << endl;
	}



	if((getChildren().back()->getLabel() == "IDENTIFIER" || getChildren().back()->getLabel() == "array_node") &&
		(getChildren().front()->getLabel() == "IDENTIFIER" || getChildren().front()->getLabel() == "array_node"))
	{
		cout << (*next(getChildren().begin()))->getLabel() << '\t' << ticket << "\t0(" << returnValues[0][0] << ")\t0(" << returnValues[2][0] << ")" << endl;
	}
	else if(getChildren().back()->getLabel() == "IDENTIFIER" || getChildren().back()->getLabel() == "array_node")
	{
		cout << (*next(getChildren().begin()))->getLabel() << '\t' << ticket << "\t" << returnValues[0][0] << "\t0(" << returnValues[2][0] << ")" << endl;

	}
	else if(getChildren().front()->getLabel() == "IDENTIFIER" || getChildren().front()->getLabel() == "array_node")
	{
		cout << (*next(getChildren().begin()))->getLabel() << '\t' << ticket << "\t0(" << returnValues[0][0] << ")\t" << returnValues[2][0] << endl;

	}
	else
	{
		cout << (*next(getChildren().begin()))->getLabel() << '\t' << ticket << "\t" << returnValues[0][0] << "\t" << returnValues[2][0] << endl;
	}


	return {ticket};
}

vector<string> ASTIdNode::walk()
{
	//cout << "ASTIdNode " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}
	string ticket = {"t_" + to_string(ticketCounter++)};
	vector<string> temp = {ticket, "ADDR", ticket, this->getId()};
	//threeAddressCode.push_back(temp);
	//cout << "ADDR " << ticket << " " << this->getId() << endl;

	//vector<string> rv = {"ADDR", ticket, };
	return temp;
}

vector<string> ASTAssignNode::walk()
{
	vector<vector<string>> returnValues;

	for(auto it : children)
	{
		returnValues.push_back(it->walk());
	}

	/*cout << "ASSIGN NODE STUFF" << endl;
	int i = 0;
	for(auto it: returnValues)
	{
		int j = 0;
		for(auto rt: it)
		{
			cout << "i " << i << " " << "j " << j++ << " " << rt << endl;
		}
		i++;
	}*/

	string ticket = {"t_" + to_string(ticketCounter++)};
	if(getChildren().front()->getLabel() == "IDENTIFIER")
	{
		cout << returnValues[0][1] << '\t' << returnValues[0][2] << '\t' << returnValues[0][3] << endl;
	}
	if(getChildren().back()->getLabel() == "IDENTIFIER")
	{
		cout << returnValues[2][1] << '\t' << returnValues[2][2] << '\t' << returnValues[2][3] << endl;
	}



	if((getChildren().back()->getLabel() == "IDENTIFIER" || getChildren().back()->getLabel() == "array_node") &&
	   (getChildren().front()->getLabel() == "IDENTIFIER" || getChildren().front()->getLabel() == "array_node"))
	{
		cout << (*next(getChildren().begin()))->getLabel() << '\t' << ticket << "\t0(" << returnValues[0][0] << ")\t0(" << returnValues[2][0] << ")" << endl;
	}
	else if(getChildren().back()->getLabel() == "IDENTIFIER" || getChildren().back()->getLabel() == "array_node")
	{
		cout << (*next(getChildren().begin()))->getLabel() << '\t' << ticket << "\t" << returnValues[0][0] << "\t0(" << returnValues[2][0] << ")" << endl;

	}
	else if(getChildren().front()->getLabel() == "IDENTIFIER" || getChildren().front()->getLabel() == "array_node")
	{
		cout << (*next(getChildren().begin()))->getLabel() << '\t' << ticket << "\t0(" << returnValues[0][0] << ")\t" << returnValues[2][0] << endl;

	}
	else
	{
		cout << (*next(getChildren().begin()))->getLabel() << '\t' << ticket << "\t" << returnValues[0][0] << "\t" << returnValues[2][0] << endl;
	}

	return {};
}

vector<string> ASTVariableNode::walk()
{
	//cout << "ASTVariable " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}
	return {};
}

vector<string> ASTConstNode::walk()
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


vector<string> ASTIterationNode::walk()
{
    auto name = children.begin();
    auto expr1 = next(name, 1); // for loop init, while/do-while nothing
    auto expr2 = next(name, 2); // condition in all three
    auto expr3 = next(name, 3); // for loop do after iteration, while/do-while nothing
    auto body = next(name, 4); // body in all three

    string iterLabel = "l_" + to_string(labelCounter++);
    string condLabel = "l_" + to_string(labelCounter++);
    string exitLabel = "l_" + to_string(labelCounter++);


    // walk(expr1)
    (*expr1)->walk();

    // do-while requires body to walk at least once
    if ((*name)->getLabel() == "DO")
    {
        (*body)->walk();
    }

    // LABEL    L0
    cout << "LABEL" << "\t" << iterLabel << endl;

    // walk(expr2)
    auto condVec = (*expr2)->walk();
    string condReg = condVec[0];

    // BEQ      R2
    cout << "BEQ" << "\t" << condReg << "\t" << "1" << "\t" << condLabel << endl;

    // B        L2
    cout << "B" << "\t" << exitLabel << endl;

    // LABEL    L1
    cout << "LABEL" << "\t" << condLabel << endl;

    // walk(body)
    (*body)->walk();
    
    // walk(expr3)
    (*expr3)->walk();
    // B        L0
    cout << "B" << "\t" << iterLabel << endl;

    // LABEL    L2
    cout << "LABEL" << "\t" << exitLabel << endl;

	return {};
}

vector<string> ASTSelectionNode::walk()
{
    // TODO: Edge case, if (1)
    auto relExprNode = next(children.begin(), 1);
    auto relExprVec = (*relExprNode)->walk();

    string returnedTicket = relExprVec[0];
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

vector<string> ASTDeclarationNode::walk()
{
	//cout << "ASTDeclarationNode " << this->getLabel() << endl;
	for(auto it : children)
	{

		it->walk();
		//cout << "LABEL: " << it->getLabel() << endl;
		if(it->getLabel() == "IDENTIFIER" /*or it->getLabel() == "array_node"*/)
			ticketCounter--;
	}
	return {};
}

vector<string> ASTTypeNode::walk()
{
	//cout << "ASTTypeNode " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}
	return {};
}

vector<string> ASTCastNode::walk()
{
	//cout << "ASTCastNode " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}
	return {};
}

vector<string> ASTArrayNode::walk()
{
	//cout << "ASTArrayNode " << this->getLabel() << endl;
	vector<vector<string>> returnValues;
	for(auto it : children)
	{
		//cout << "LABEL: " << it->getLabel() << endl;
		returnValues.push_back(it->walk());
	}



//	cout << "ARRAY NODE STUFF Line: " << lineNum << endl;
//	int i = 0;
//	for(const auto& it: returnValues)
//	{
//		int j = 0;
//		for(const auto& rt: it)
//		{
//			cout << "i " << i << " " << "j " << j++ << " " << rt << endl;
//		}
//		i++;
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
			if(children.front()->getLabel() == "INT_CONSTANT" or
			   children.front()->getLabel() == "additive_expression" )
			{
				string ticket1 = {"t_" + to_string(ticketCounter++)};
				string ticket2 = {"t_" + to_string(ticketCounter++)};
				string ticket3 = {"t_" + to_string(ticketCounter++)};

				cout << "MULT\t" << ticket1 << "\tsizeof(" << printType(type) << ")\t" << returnValues[0][0] << endl;
				cout << "ADDR\t" << ticket2 << '\t' << identifier << endl;
				cout << "ADD\t" << ticket3 << '\t' << ticket1 << '\t' << ticket2 << endl;
				return {ticket3};
			}
			else if(children.front()->getLabel() == "IDENTIFIER" or
				children.front()->getLabel() == "array_node")
			{
				if(children.front()->getLabel() == "IDENTIFIER")
					cout << returnValues[0][1] << "\t" << returnValues[0][2] << "\t" << returnValues[0][3] << endl;
				string ticket1 = {"t_" + to_string(ticketCounter++)};
				string ticket2 = {"t_" + to_string(ticketCounter++)};
				string ticket3 = {"t_" + to_string(ticketCounter++)};
				cout << "MULT\t" << ticket1 << "\t0(" << returnValues[0][0] << ")\tsizeof(" << printType(type)
						<< ")" << endl;
				cout << "ADDR\t" << ticket2 << '\t' << identifier << endl;
				cout << "ADD\t" << ticket3 << '\t' << ticket1 << "\t" << ticket2 << endl;
				return {ticket3};
			}
		}
		else
		{
			int num = 0;
			for(auto child: children)
			{
				if(child->getLabel() == "IDENTIFIER")
				{
					cout << returnValues[num][1] << "\t" << returnValues[num][2] << "\t" << returnValues[num][3]
						 << endl;
				}
				num++;
			}
			int startingDim = 1;
			int rVal = 0;
			for(auto child: children)
			{

				int ticketReturnNumber = 2;
				for(auto dim = next(dimensions.rbegin(), startingDim); dim != dimensions.rend(); dim++)
				{
					ticketReturnNumber++;
					string previousTicket = {"t_" + to_string(ticketCounter - 1)};
					if(child->getLabel() == "INT_CONSTANT" or
					   child->getLabel() == "additive_expression")
					{
						string currentTicket = {"t_" + to_string(ticketCounter++)};
						if(dim == next(dimensions.rbegin(), startingDim))
						{
							cout << "MULT\t" << currentTicket << "\t" << returnValues[rVal][0] << "\t" << *dim << endl;
						}
						else
						{
							cout << "MULT\t" << currentTicket << "\t" << previousTicket << "\t" << *dim << endl;
						}
					}
					else if(child->getLabel() == "IDENTIFIER" or child->getLabel() == "array_node")
					{
//						cout << returnValues[rVal][1] << "\t" << returnValues[rVal][2] << "\t" << returnValues[rVal][3]
//							 << endl;
						string currentTicket = {"t_" + to_string(ticketCounter++)};
						if(dim == next(dimensions.rbegin(), startingDim))
						{
							cout << "MULT\t" << currentTicket << "\t0(" << returnValues[rVal][0] << ")\t" << *dim << endl;
						}
						else
						{
							cout << "MULT\t" << currentTicket << "\t" << previousTicket << "\t" << *dim << endl;
						}
					}
					else
					{
						cout << "AHHHHHHHHH" << endl;
					}

				}
				if(child == children.back())
				{
					if(child->getLabel() == "INT_CONSTANT" or
					   child->getLabel() == "additive_expression")
					{
						cout << "ADD\t" << "t_" + to_string(ticketCounter++) + '\t'
							 << "t_" + to_string(ticketCounter - 2) + '\t'
							 << returnValues[rVal][0] << endl;
					}
					else if(child->getLabel() == "IDENTIFIER" or child->getLabel() == "array_node")
					{
						string ticket = {"t_" + to_string(ticketCounter++)};
						//cout << "ADDR\t" << ticket + '\t' << returnValues[rVal][3] << endl;
						cout << "ADD\t" << ticket + '\t' << "t_" + to_string(ticketCounter - 2) + '\t'
										<< "0("	<< returnValues[rVal][0] << ")" << endl;


					}
				}
				else if(child != children.front())
				{
					string ticket = {"t_" + to_string(ticketCounter++)};
					//cout << endl << "Counter: " << ticketCounter << endl;
					//cout << "Rval: " << rVal << endl;
					//cout << "Dim size: " << dimensions.size() << endl << endl;
					cout << "ADD\t" << ticket  + '\t'
						 << "t_" + to_string(ticketCounter - ticketReturnNumber) + '\t'
						 << "t_" + to_string(ticketCounter - 2) + '\t' << endl;
					ticketReturnNumber = 0;
				}
				startingDim++;
				rVal++;
			}

			string ticket1 = {"t_" + to_string(ticketCounter++)};
			string ticket2 = {"t_" + to_string(ticketCounter++)};
			string ticket3 = {"t_" + to_string(ticketCounter++)};

			cout << "MULT\t" << ticket1 << "\t" << "t_" + to_string(ticketCounter - 4) + '\t'
				 << "sizeof(" << printType(type) << ")" << endl;
			cout << "ADDR\t" << ticket2 << "\t" << identifier << endl;
			cout << "ADD\t" << ticket3 << "\t" << ticket2 << '\t' << ticket1 << endl;

			return {ticket3};
		}

//		for(const auto &it: returnValues)
//		{
//			for(auto dim = dimensions.rbegin() + 1; dim != dimensions.rend() ; dim++ )
//			{
//				string previousTicket = {to_string(ticketCounter)};
//				if(children.front()->getLabel() == "INT_CONSTANT" or
//				   children.front()->getLabel() == "additive_expression")
//				{
//					string ticket1 = {"t_" + to_string(ticketCounter++)};
//					string ticket2 = {"t_" + to_string(ticketCounter++)};
//					string ticket3 = {"t_" + to_string(ticketCounter++)};
//					cout << "MULT\t" << "t_" + to_string(++ticketCounter) + '\t' << *dim  << '\t'
//						<< returnValues[0][0] << endl;
//					cout << "MULT\t" << ticket1 << "\tsizeof(" << printType(type) << ")\t" << returnValues[0][0] << endl;
//					cout << "ADDR\t" << ticket2 << '\t' << identifier << endl;
//					cout << "ADD\t" << ticket3 << '\t' << ticket1 << '\t' << ticket2 << endl;
//					return {ticket3};
//				}
//				else if(children.front()->getLabel() == "IDENTIFIER")
//				{
//					cout << returnValues[0][1] << "\t" << returnValues[0][2] << "\t" << returnValues[0][3] << endl;
//					cout << "MULT\t" << "t_" + to_string(ticketCounter++) + '\t' << *dim  << '\t'
//						<< returnValues[0][0] << endl;
//					string ticket1 = {"t_" + to_string(ticketCounter++)};
//					string ticket2 = {"t_" + to_string(ticketCounter++)};
//					string ticket3 = {"t_" + to_string(ticketCounter++)};
//					cout << "MULT\t" << ticket1 << "\tsizeof(" << printType(type) << ")\t0(" << returnValues[0][0]
//						 << ")"
//						 << endl;
//					cout << "ADDR\t" << ticket2 << '\t' << identifier << endl;
//					cout << "ADD\t" << ticket3 << '\t' << ticket1 << "\t" << ticket2 << endl;
//					return {ticket3};
//				}
//			}
//		}
	}


	return {};
}

vector<string> ASTFunctionNode::walk()
{
	//cout << "ASTFunctionNode " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
		ticketCounter--;
	}
	return {};
}

vector<string> ASTDeclListNode::walk()
{
	//cout << "ASTDeclarationListNode " << this->getLabel() << endl;
	for(auto it : children)
	{
		it->walk();
	}
	return {};
}

ASTDeclListNode::ASTDeclListNode(string node_label, ASTNode *inputChild) : ASTNode(move(node_label))
{
    ( (ASTDeclarationNode*) inputChild ) -> setOffset(activationFrameSize);
    addChild(inputChild);
}

ASTDeclListNode::ASTDeclListNode(string node_label, ASTNode* leftChild, ASTNode* rightChild) : ASTNode(move(node_label))
{
    addChild(leftChild);
    ( (ASTDeclarationNode*) rightChild ) -> setOffset(activationFrameSize);
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


vector<string> ASTFunctionCallNode::walk()
{
    //cout << "ASTFunctionCallNode " << this->getLabel() << endl;
    for(auto it : children)
    {
        it->walk();
    }
    return {};
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

vector<string> ASTRelExprNode::walk()
{
    vector<vector<string>> returnValues;
	for (auto it : children)
	{
		returnValues.push_back(it->walk());
	}

    string ticket = {"t_" + to_string(ticketCounter++)};
    string trueLabel = {"l_" + to_string(labelCounter++)};
    string endLabel = {"l_" + to_string(labelCounter++)};
    string branchFirstArg = "";
    string branchSecondArg = "";

    if (children.front()->getLabel() == "INT_CONSTANT")
    {
        branchFirstArg = returnValues[0][0];
    }
    else if (children.front()->getLabel() == "IDENTIFIER")
    {
        string leftCommand = returnValues[0][1];
        string leftTemp = returnValues[0][2];
        string leftName = returnValues[0][3];
        branchFirstArg = "0(" + leftTemp + ")";
        cout << leftCommand << "\t" << leftTemp << "\t" << leftName << endl;
    }

    if (children.back()->getLabel() == "INT_CONSTANT") // TODO: can only support int constant comparisons right now
    {
        branchSecondArg = returnValues[2][0];
    }
    else if (children.back()->getLabel() == "IDENTIFIER")
    {
        string rightCommand = returnValues[2][1];
        string rightTemp = returnValues[2][2];
        string rightName = returnValues[2][3];
        branchSecondArg = "0(" + rightTemp + ")";
        cout << rightCommand << "\t" << rightTemp << "\t" << rightName << endl;
    }

    
    auto it = ++(children.begin()); // get middle child (operator)
    string label = (*it)->getLabel();
    string op = label.substr(0, 2);
    string command = "B" + op;
    cout << command << "\t" << branchFirstArg << "\t" << branchSecondArg << "\t" << trueLabel << endl;
    cout << "LOAD" << "\t" << ticket << "\t" << "0" << endl;
    cout << "B" << "\t" << endLabel << endl;
    cout << "LABEL" << "\t" << trueLabel << endl;
    cout << "LOAD" << "\t" << ticket << "\t" << "1" << endl;
    cout << "LABEL" << "\t" << endLabel << endl;

    return {ticket};
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

vector<string> ASTUnaryNode::walk()
{
    return {};
}


int typeToByteSize( int type )
{
    switch( type )
    {
        case Char:
            return 1;

        case Short:
            return 2;

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
