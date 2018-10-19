#include <iostream>
#include <map>
#include <list>
#include <iterator>
#include <fstream>
#include <sstream>
#include <random>
#include "symbolTable.h"
#include "node.h"

#define FAILURE -1

using namespace std;

///An error stream to be used by the symbol Table for errors and warnings
stringstream errorStream;


/**
 * @brief A function to build a table automatically
 * @param maxNumSymbols The max number of symbols for a scope
 * @param numScopes The number of scope to be generated
 * @param symbolTable The table to be built
 */
void insertSymbols(int maxNumSymbols, int numScopes, symbolTable &symbolTable);

/**
 * @brief A driver for the Symbol Table
 * @return 0
 */
int main()
{
	symbolTable symTable;
	int scopes, symbols, searchIndex, buildType, actionIndex;
	char again, searchAgain;
	string id;

	do
	{
		cout << "1 - Manually Build Symbol Table" << endl;
		cout << "2 - Automatically Build a Table" << endl;
		cout << "Enter Build Index: ";
		cin >> buildType;
	}while (buildType != 1 and buildType != 2);

	if(buildType == 1)
	{
		do
		{
			cout << "1 - Push a Level" << endl;
			cout << "2 - Pop a Level" << endl;
			cout << "3 - Create a node and insert it" << endl;
			cout << "4 - Done building table" << endl;
			cout << "Enter Action Index: ";
			cin >> actionIndex;
			switch (actionIndex)
			{
				case 1:
					symTable.pushLevel();
					cout << "Current Number of scopes: " << symTable.getCurrentLevel() << endl;
					break;
				case 2:
					if (symTable.popLevel())
						cout << "Current Number of scopes: " << symTable.getCurrentLevel() << endl;
					else
					{
						cout << errorStream.str() << endl;
						errorStream.clear();
					}
					break;
				case 3:
				{
					int line, col, store, type, qual, funct, sign;
					string identifier;
					cout << "Enter an identifier: ";
					cin >> identifier;
					cout << "Line number identifier is on: ";
					cin >> line;
					cout << "Column number identifier starts on: ";
					cin >> col;
					node insertNode(identifier, line, col);
					insertNode.setVarScopeLevel(symTable.getCurrentLevel());
					do
					{
						cout << "Is this a Function(0/1)?";
						cin >> funct;
					} while (funct != 0 and funct != 1);

					insertNode.setIsFunction((bool) funct);
					do
					{
						cout << "0: auto, 1: register, 2: static, 3: extern, 4: none" << endl;
						cout << "Storage Class index: ";
						cin >> store;
						if (store >= Auto and store <= Extern)
							insertNode.setTypeStorageClassIndex(store);
						else if (store < Auto or store > Typedef)
							cout << "Invalid index" << endl;
					} while (store < Auto or store > Typedef);

					do
					{
						cout << "0: void, 1: char, 2: short, 3: int, 4: long, 5: float, 6: double, 7: none" << endl;
						cout << "Type Specifier index: ";
						cin >> type;
						if (type >= Void and type <= Double)
							insertNode.setTypeSpecifierIndex(type);
						else if (type < Void or type > Struct)
							cout << "Invalid index" << endl;
					} while (type < Void or type > Struct);

					do
					{
						cout << "Is this identifier signed(0/1)?";
						cin >> sign;
					} while (sign != 0 and sign != 1);

					insertNode.setIsSigned((bool) sign);
					do
					{
						cout << "0: const, 1: volatile, 2: both, 3: none" << endl;
						cout << "Type Qualifier Index: ";
						cin >> qual;
						if (qual >= Const and qual <= Both)
							insertNode.setTypeQualifierIndex(qual);
						else if (qual < 0 or qual > 3)
							cout << "Invalid index" << endl;
					} while (qual < 0 or qual > 3);
				symTable.insert(insertNode);
				}
				case 4:
					break;
				default:
					cout << "Invalid index" << endl;
					break;

			}
			if(actionIndex >= 1 and actionIndex <= 3)
				cout << symTable;
		}while (actionIndex != 4);
	}
	else
	{

		do
		{
			symTable.resetTable();
			cout << "How many scopes for your symbol table? ";
			cin >> scopes;
			cout << "How many identifiers do you want to try and add to each scope? ";
			cin >> symbols;
			insertSymbols(symbols, scopes, symTable);
			do
			{
			cout << "Make a new symbol table(Y/N)? ";
			cin >> again;
			}while (toupper(again) != 'Y' and toupper(again) != 'N');

		} while (toupper(again) == 'Y');

		do
		{
			cout << "Would you like to search your symbol table(Y/N)? ";
			cin >> searchAgain;
		}while (toupper(searchAgain) != 'Y' and toupper(searchAgain) != 'N');

		while (toupper(searchAgain) == 'Y')
		{
			cout << "1 - Search Top Level" << endl;
			cout << "2 - Search All Levels Except Top" << endl;
			cout << "3 - Search All Levels" << endl;
			cout << "4 - End Search" << endl;
			cout << "Enter Search Index: ";
			cin >> searchIndex;
			cout << "Enter identifier to search for: ";
			cin >> id;

			switch (searchIndex)
			{
				case 1:
				{
					auto rt = symTable.searchTop(id);
					if (rt.first != FAILURE)
						cout << rt.second->second;
					else
						cout << '\"' << id << "\" not found" << endl;
					break;
				}
				case 2:
				{
					auto rt = symTable.searchAllExceptTop(id);
					if (rt.first != FAILURE)
						cout << rt.second->second;
					else
						cout << '\"' << id << "\" not found" << endl;
					break;
				}
				case 3:
				{
					auto rt = symTable.searchAll(id);
					if (rt.first != FAILURE)
						cout << rt.second->second;
					else
						cout << '\"' << id << "\" not found" << endl;
					break;
				}
				default:
					cout << "Invalid Index. Try Again" << endl;

			}
		}
	}

	char fileIndex;
	string fileName;
	do
	{
		cout << "Would you like to write to a file(Y/N): ";
		cin >> fileIndex;
	}while (toupper(fileIndex) != 'Y' and toupper(fileIndex) != 'N');

	if(toupper(fileIndex) == 'Y')
	{
		cout << "File name: ";
		cin >> fileName;
		ofstream ofile;
		ofile.open(fileName);
		if(ofile.good())
			ofile << symTable;
		else
			cout << "Could not open file: " << fileName << endl;
		ofile.close();
	}
	cout << "All Done" << endl;
	cout << "Thank you" << endl;
	return 0;
}

void insertSymbols(int maxNumSymbols, int numScopes, symbolTable &symbolTable)
{

	string variable = "identifier";
	bool notRepeated;

	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<int> randomLineNum(1,100); // distribution in range [1, 6]
	std::uniform_int_distribution<int> randomColNum(1,100);
	std::uniform_int_distribution<int> randomSpecifier(-1,Double);
	std::uniform_int_distribution<int> randomStorageClass(-1, Extern);
	std::uniform_int_distribution<int> randomQualifier(-1,Both);
	std::uniform_int_distribution<int> randomIsFunction(0,1);
	std::uniform_int_distribution<int> randomIsSigned(0,1);
	std::uniform_int_distribution<int> randomVarNum(0,maxNumSymbols);
	std::uniform_int_distribution<int> randomDontEndScope(0,5);

	for(int i = 0; i < numScopes; i++)
	{
		notRepeated = true;
		for (int j = 0; j < maxNumSymbols and notRepeated and randomDontEndScope(rng); j++)
		{
			bool function = (bool) randomIsFunction(rng);
			string inputVar(variable);
			inputVar += to_string(randomVarNum(rng));
			if (function)
				inputVar += "()";

			node insertNode(inputVar, randomLineNum(rng), randomColNum(rng));
			int type = randomSpecifier(rng);
			if(type != -1)
				insertNode.setTypeSpecifierIndex(type);
			insertNode.setTypeStorageClassIndex(randomStorageClass(rng));
			insertNode.setTypeQualifierIndex(randomQualifier(rng));
			insertNode.setIsFunction(function);
			insertNode.setIsSigned((bool) randomIsSigned(rng));
			notRepeated = symbolTable.insert(insertNode);
		}
		if(i + 1 != numScopes)
			symbolTable.pushLevel();
	}

	cout << "*******************************************************************************" << endl;
	cout << "                        Warnings and Errors" << endl;
	cout << errorStream.str() << endl;
	errorStream.clear();
	cout << "*******************************************************************************" << endl;
	cout << "                                 Symbol Table" << endl;
	cout << symbolTable;
	cout << "*******************************************************************************" << endl;
}
