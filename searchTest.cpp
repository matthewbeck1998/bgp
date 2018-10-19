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
	out.open("searchOutput.txt");
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
	node tnode("test3", 1, 3);
	sym.insert(tnode);
	out << "After insert" << endl;
	out << sym;
	out << "SearchTop" << endl;
	auto rt = sym.searchTop("test3");
	out << "Level: " << rt.first << endl;
	out << rt.second->second;
	out << "Search All" << endl;
	auto yt = sym.searchAll("test");
	out << "Level: " << yt.first << endl;
	out << yt.second->second;



	out.close();




	return 0;
}