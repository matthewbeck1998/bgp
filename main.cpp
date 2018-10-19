#include <iostream>
#include <map>
#include <list>
#include <iterator>
#include <fstream>
#include <sstream>
#include "symbolTable.h"
#include "node.h"

using namespace std;

stringstream errorStream;

int main()
{
	node testNode1("testVar1", 13);
	testNode1.setVarScopeLevel(1);
	testNode1.setIsFunction(false);
	testNode1.setIsSigned(false);
	testNode1.setTypeQualifierIndex(Both);
	testNode1.setTypeStorageClassIndex(Static);
	testNode1.setTypeSpecifierIndex(Short);

	node testNode2("testVar1", 14);
	testNode1.setTypeStorageClassIndex(Both);
	testNode1.setTypeSpecifierIndex(Int);

	//cout << testNode1;
	symbolTable symbolTable1;
	symbolTable1.insert(testNode1);
	//symbolTable1.pushLevel();
	symbolTable1.insert(testNode2);
	cerr << "errorStream: " << errorStream.str() << " :end" << endl;
	cerr.flush();
	cout << symbolTable1;



	return 0;
}