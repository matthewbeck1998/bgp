//
// Created by WIll on 10/19/2018.
//

#include <sstream>
#include <fstream>
#include "symbolTable.h"

using namespace std;

stringstream errorStream;

int main()
{
	ofstream out;
	out.open("push_and_popOutput.txt");
	symbolTable sym;
	sym.pushLevel();
	out << "After a level is pushed: " << endl;
	out << sym;
	sym.popLevel();
	out << "After 1 level is popped: " << endl;
	out << sym;
	out << "After 2 levels are popped" << endl;
	sym.popLevel();
	out << sym;
	out << "After 3 levels are popped" << endl;
	sym.popLevel();
	out << "errorStream" << endl;
	out << errorStream.str();
	out.close();




	return 0;
}