//
// Created by WIll on 10/3/2018.
//

#ifndef PA5_NODE_H
#define PA5_NODE_H

#include <string>
#include <ostream>
#include <map>

using namespace std;

enum storage_class_specifier{Auto, Register, Static, Extern, Typedef};
enum type_specifier{Void, Char, Short, Int, Long, Float, Double, Struct};
enum type_qualifier{Const, Volatile, Both};


class node
{
public:
	node (const string &identifier, int lineNum, int typeSpecifier = 3);

	const string &getIdentifier () const;

	void setIdentifier (const string &identifier);

	int getTypeStorageClassIndex () const;

	void setTypeStorageClassIndex (int typeStorageClassIndex);

	int getTypeQualifierIndex () const;

	void setTypeQualifierIndex (int typeQualifierIndex);

	int getTypeSpecifierIndex () const;

	void setTypeSpecifierIndex (int typeSpecifierIndex);

	int getVarScopeLevel () const;

	void setVarScopeLevel (int varScopeLevel);

	int getLineNum () const;

	void setLineNum (int lineNum);

	bool getIsFunction () const;

	void setIsFunction (bool isFunction);

	bool getIsSigned () const;

	void setIsSigned (bool isSigned);

	friend ostream &operator<< (ostream &os, const node &node1);

private:
	string identifier;
	int typeStorageClassIndex;
	int typeQualifierIndex;
	int typeSpecifierIndex;
	int varScopeLevel;
	int lineNum;
	bool isFunction;
	bool isSigned;
	map<string, node> structVariables;
};


#endif //PA5_NODE_H
