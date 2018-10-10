//
// Created by WIll on 10/3/2018.
//

#ifndef PA5_NODE_H
#define PA5_NODE_H

#include <string>
#include <ostream>

using namespace std;

class node
{
public:
	node (const string &varName, const string &varType, bool funct = false);
	node (const string &varName, const string &varType, int level);
	const string &getVarName () const;

	void setVarName (const string &varName);

	int getVarLevel () const;

	void setVarLevel (int varLevel);

	const string &getVarType () const;

	void setVarType (const string &varType);

	void operator()(const string &varName, const string &varType);

	friend ostream &operator<< (ostream &os, const node &node1);

private:
	string varName;
	string varType;
	int varLevel;
	bool function;
	node* next;
};


#endif //PA5_NODE_H
