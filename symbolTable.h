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
#include "node.h"

using namespace std;

class symbolTable
{
public:
	symbolTable ();

	friend ostream &operator<< (ostream &os, const symbolTable &table);

	bool insert (node &insertNode);
	bool popLevel ();
	void pushLevel();

	int getCurrentLevel () const;

	pair<int, map<string, node>::iterator> searchAll(string key);
	pair<int, map<string, node>::iterator> searchTop(string key);

private:
	list<map<string, node>> table;
	int currentLevel;

};


#endif //PA5_SYMBOLTABLE_H
