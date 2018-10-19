//
// Created by WIll on 10/19/2018.
//

#include <sstream>
#include <fstream>
#include "symbolTable.h"
#include "node.h"

using namespace std;

stringstream errorStream;

int main()
{
	ofstream out;
	out.open("insertOutput.txt");
	symbolTable sym;
	node inode("test", 1,1);
	sym.insert(inode);
	out << "After insert" << endl;
	out << sym;
	node enode("test2", 2,2);
	sym.insert(enode);
	out << "After insert" << endl;
	out << sym;
	sym.pushLevel();
	node tnode("test", 1, 3);
	sym.insert(tnode);
	out << "After insert" << endl;
	out << sym;
	out << "Error stream" << endl;
	out << errorStream.str() << endl;
	errorStream.clear();
	node rnode("test", 1, 3);
	sym.insert(rnode);
	out << "After insert" << endl;
	out << sym;
	out << "Error stream" << endl;
	out << errorStream.str() << endl;


	out.close();




	return 0;
}