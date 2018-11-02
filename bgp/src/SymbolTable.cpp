//
// Created by WIll on 10/2/2018.
//

using namespace std;

#include <sstream>
#include "SymbolTable.h"

#define FAILURE -1

extern stringstream errorStream;

/**
 * @brief A function to insert a Node into the current level of the symbol table
 * 			Will check for shadowing
 * 			Will check if the table is empty
 * @param insertNode The Node to be inserted
 * @return True if the Node was successfully inserted
 * 			False if the table was empty or the Node could not be inserted
 */
bool SymbolTable::insert (SymbolNode &insertNode)
{
	//cout << "SearchTop: " << searchTop(insertNode.getIdentifier()).first << endl;
	if(!table.empty() and insertMode)
	{
		insertNode.setVarScopeLevel(currentLevel);
		auto searchReturn = searchAllExceptTop(insertNode.getIdentifier());
		if(searchReturn.first != -1)
		{
			errorStream << "WARNING: Scope " << currentLevel << endl;
			errorStream << "\tShadowing identifier: \"" << insertNode.getIdentifier() << '\"';
			errorStream << " on line " << searchReturn.second->second.getLineNum();
			errorStream << " from scope " << searchReturn.second->second.getVarScopeLevel() << endl;
		}
		auto insertStatus = table.begin()->insert(pair<string, SymbolNode>(insertNode.getIdentifier(), insertNode));

		if(!insertStatus.second)
		{
			errorStream << "ERROR: Scope: " << currentLevel << endl;
			errorStream << "\tIdentifier: \"" << insertNode.getIdentifier() << "\" already exists on line ";
			errorStream << insertStatus.first->second.getLineNum() << endl;
		}

		return insertStatus.second;
	}
	else
	{
		if(!insertMode)
			errorStream << "Insert mode is not on" << endl;
		else
			errorStream << "Table is empty: can not insert" << endl;

		return false;
	}
}

/**
 * @brief A function to remove a level from the symbol table
 * 			Should be called when leaving a scope
 * 			Will check if the table is empty
 * @return True if the table is not empty and a level was successfully removed
 * 			False if the table is empty
 */
bool SymbolTable::popLevel ()
{
	if(!table.empty())
	{
		table.pop_front();
		currentLevel--;
		return true;
	}
	else
	{
		errorStream << "Table is empty" << endl;
		return false;
	}
}

/**
 * @brief Will push a new map onto the list
 * 			Should be called every time a new scope is entered
 */
void SymbolTable::pushLevel ()
{
	currentLevel++;
	map<string, SymbolNode> temp;
	table.push_front(temp);
}

/**
 * @brief An inseration operator to help print the table
 * @param os The ostream object
 * @param table The symbol table to be printed
 * @return The ostream with everything to print
 */
ostream &operator<< (ostream &os, const SymbolTable &table)
{
	if (!table.table.empty())
	{
		unsigned long long level = table.table.size();
		for (const auto &tableItr : table.table)
		{
			os << "Level: " << level-- << endl;
			for (auto mapItr = tableItr.begin(); mapItr != tableItr.end() and !tableItr.empty(); mapItr++)
			{
				os << "\tKey: " << mapItr->first << endl << "\tNode: ";
				os << '\t' << mapItr->second;
			}

		}
	}
	else
	{
		os << "Table is empty" << endl;
	}
	return os;
}
/**
 * @brief Will create a symbol table with 1 level for file level identifiers
 */
SymbolTable::SymbolTable () : currentLevel(0)
{
	insertMode = true;
	lastSearchValid = false;
	pushLevel();
}

/**
 * @brief A function to search the entire symbol table for a key
 * @param key A string to find in the symbol table (this will be the identifier name)
 * @return A pair:
 * 			first: an int that represents the level the key was found on
 * 					will return -1 if the key wasn't found
 * 			second: an iterator to the map where the key was found
 * 					will return an iterator to the end if the key wasn't found
 */
pair<int, map<string, SymbolNode>::iterator> SymbolTable::searchAll (string key)
{
	auto it = table.begin()->end();
	pair<int, map<string, SymbolNode>::iterator> rt;
	bool notFound = true;
	for(auto itr = table.begin(); itr != table.end() && notFound; itr++)
	{
		it = itr->find(key);
		if(it != itr ->end())
			notFound = false;
	}


	if(notFound)
	{
		rt.first = FAILURE;
		rt.second = it;
		lastSearchValid = false;
	}
	else
	{
		lastSearchValid = true;
		rt.first = it->second.getVarScopeLevel();
		rt.second = it;
	}
	return rt;
}

/**
 * @brief A function to search the top level of the symbol table
 * @param key A string to find in the symbol table (this will be the identifier name)
 * @return A pair:
 * 			first: an int that represents the level the key was found on
 * 					will return -1 if the key wasn't found
 * 			second: an iterator to the map where the key was found
 * 					will return an iterator to the end if the key wasn't found
 */
pair<int, map<string, SymbolNode>::iterator> SymbolTable::searchTop (string key)
{
	auto itr = table.begin()->find(key);
	pair<int, map<string, SymbolNode>::iterator> rt;
	if(itr == table.begin()->end())
	{
		lastSearchValid = false;
		rt.first = FAILURE;
		rt.second = itr;
	}
	else
	{
		lastSearchValid = true;
		rt.first = itr->second.getVarScopeLevel();
		rt.second = itr;
	}
	return rt;
}

int SymbolTable::getCurrentLevel () const
{
	return currentLevel;
}

bool SymbolTable::getInsertMode () const
{
	return insertMode;
}

void SymbolTable::setInsertMode (bool insertMode)
{
	SymbolTable::insertMode = insertMode;
}

/**
 * @brief A function to search every thing except the top level of the symbol table
 * @param key A string to find in the symbol table (this will be the identifier name)
 * @return A pair:
 * 			first: an int that represents the level the key was found on
 * 					will return -1 if the key wasn't found
 * 			second: an iterator to the map where the key was found
 * 					will return an iterator to the end if the key wasn't found
 */
pair<int, map<string, SymbolNode>::iterator> SymbolTable::searchAllExceptTop (string key)
{
	auto it = table.begin()->end();
	pair<int, map<string, SymbolNode>::iterator> rt;
	bool notFound = true;
	for(auto itr = ++table.begin(); itr != table.end() && notFound; itr++)
	{
		it = itr->find(key);
		if(it != itr ->end())
			notFound = false;
	}

	if(notFound)
	{
		lastSearchValid = false;
		rt.first = FAILURE;
		rt.second = it;
	}
	else
	{
		lastSearchValid = true;
		rt.first = it->second.getVarScopeLevel();
		rt.second = it;
	}
	return rt;
}

/**
 * @brief Resets the symbol table to an the way it was initialized
 */
void SymbolTable::resetTable ()
{
	while(!table.empty())
		popLevel();
	pushLevel();
}

bool SymbolTable::isLastSearchValid () const
{
	return lastSearchValid;
}
