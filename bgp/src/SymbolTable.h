//
// Created by WIll on 10/2/2018.
//
//using namespace std;

#ifndef PA5_SYMBOLTABLE_H
#define PA5_SYMBOLTABLE_H

#include <string>
#include <iostream>
#include <map>
#include <list>
#include <iterator>
#include "SymbolNode.h"

using namespace std;

class SymbolTable
{
public:
	SymbolTable ();

	friend ostream &operator<< (ostream &os, const SymbolTable &table);

	bool insert (Node &insertNode);
	bool popLevel ();
	void pushLevel();
	bool getInsertMode () const;
	void setInsertMode (bool insertMode);
	void resetTable();

	int getCurrentLevel () const;

	pair<int, map<string, Node>::iterator> searchAll(string key);
	pair<int, map<string, Node>::iterator> searchTop(string key);
	pair<int, map<string, Node>::iterator> searchAllExceptTop(string key);

private:
	list<map<string, Node>> table;
	int currentLevel;
	bool insertMode;

};


#endif //PA5_SYMBOLTABLE_H
