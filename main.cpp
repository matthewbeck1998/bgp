#include <iostream>
#include <map>
#include <list>
#include <iterator>
#include <fstream>
#include "symbolTable.h"
#include "node.h"

using namespace std;

int main()
{
	//ofstream outFile;
	//outFile.open("Output.txt");
	symbolTable table;
	//table.pushLevel();
	node tempNode("charVar1", "char");
	table.insert(tempNode);
	tempNode("intVar1", "int");
	table.insert(tempNode);
	tempNode("floatVar1", "float");
	table.insert(tempNode);
	tempNode("doubleVar1", "double");
	table.insert(tempNode);
	table.pushLevel();
	tempNode("charVar2", "char");
	table.insert(tempNode);
	tempNode("intVar2", "int");
	table.insert(tempNode);
	tempNode("floatVar2", "float");
	table.insert(tempNode);
	tempNode("doubleVar2", "double");
	table.insert(tempNode);
	table.pushLevel();
	table.pushLevel();
	tempNode("doubleVar3", "double");
	table.insert(tempNode);
	table.pushLevel();
	cout << table;
	table.popLevel();
	table.popLevel();
	cout << "After Pop" << endl;
	cout << table;
	cout << "Add some more" << endl;
	tempNode("intVar3", "int");
	table.insert(tempNode);
	cout << table;


	return 0;
}