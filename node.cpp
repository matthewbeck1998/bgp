//
// Created by WIll on 10/3/2018.
//

#include "node.h"

node::node (const string &varName, const string &varType, bool funct) : varName(varName), varType(varType), function(funct)
{}

node::node (const string &varName, const string &varType, int level) : varName(varName), varType(varType), varLevel(level)
{}

const string &node::getVarName () const
{
	return varName;
}

void node::setVarName (const string &varName)
{
	node::varName = varName;
}

const string &node::getVarType () const
{
	return varType;
}

void node::setVarType (const string &varType)
{
	node::varType = varType;
}

ostream &operator<< (ostream &os, const node &node1)
{
	os << "(varName: " << node1.varName << ", varType: " << node1.varType << ", varLevel: " << node1.varLevel <<")";
	return os;
}

void node::operator() (const string &name, const string &type)
{
	varName = name;
	varType = type;
}

int node::getVarLevel () const
{
	return varLevel;
}

void node::setVarLevel (int varLevel)
{
	node::varLevel = varLevel;
}
