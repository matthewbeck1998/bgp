#include "AST.h"
#include <fstream>

AST::AST (ASTNode* root)
{
	AST::root = root;
}

/*bool AST::walkTree() const
{
    if( root != nullptr)
    {

		for(auto it = root->getChildren().begin() ; it != root->getChildren().end() ; ++it)
		{
			if((*it)->walk() == false)
			{
				return false;
			}
		}
		return true;
    }
}*/

void AST::printTree ()
{
	if(root != nullptr)
	{
		ofstream treeOutFile;
		treeOutFile.open("output/treeOut.dot");
		treeOutFile << "digraph G {" << endl;
		root->printNode(treeOutFile);
		treeOutFile << '}';
		treeOutFile.flush();
		treeOutFile.close();
	}
}


void AST::printTreeHelper (ASTNode *nodePtr, ofstream& treeOutFile)
{
	if(nodePtr != nullptr)
	{
		treeOutFile << nodePtr->getNodeNum() << "[label = \"" << nodePtr->getLabel() << "\"];" << endl;
		for(auto it = nodePtr->getChildren().begin() ; it != nodePtr->getChildren().end() ; ++it)
		{
			treeOutFile << nodePtr->getNodeNum() << " -> " << (*it)->getNodeNum() << endl;
			printTreeHelper(*it, treeOutFile);
		}

	}
}

void AST::walk(string outputFile) const
{
	//cout << "walk" << endl;
	if(root != NULL)
	{
		//cout << "INSIDE IF" << endl;
		//cout << root->getLabel() << endl;
		ofstream IrOutputFile;
		IrOutputFile.open(outputFile);
		root->walk(IrOutputFile);
	}
	else
		cout << "NOOOOO" << endl;
}
