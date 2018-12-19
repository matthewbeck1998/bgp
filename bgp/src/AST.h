/* TODO
 * Node for single input math operations(like ++)
 * Node for declaritors
 * Different node for =? and stuff like /=, +=
 * Node for selections(if/switch) If is mandatory, switch is not.
 * Node for comparitors?
 * Make will get discord?
 * Node for functions?
 * Node for loops
 * Node for labels?
 */

#ifndef PROJECT_AST_H
#define PROJECT_AST_H


#include "ASTNode.h"

class AST
{
    public:
        explicit AST(ASTNode* root);
        //bool walkTree() const;
        void printTree();
        void printTreeHelper(ASTNode* nodePtr, ofstream& treeOutFile);
        void walk(string outputFile) const;


    private:
		ASTNode* root;


};


#endif //PROJECT_AST_H
