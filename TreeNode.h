/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment Extra Credit
 *******************************/

#ifndef TREENODE_H_
#define TREENODE_H_

#include <iostream>
using namespace std;
#include <iomanip>
#include <string>

enum Color
{
	RED,
	BLACK
};

template <class x>
class TreeNode
{
public:
	bool isOnLeft()
	{
		return this == parent->left;
	}


	void moveDown(TreeNode<x>* nParent) {
	if (parent != NULL) {
	if (isOnLeft()) {
	parent->left = nParent;
	} else {
	parent->right = nParent;
	}
	}
	nParent->parent = parent;
	parent = nParent;
	}

	bool hasRedChild() {
	return (left != NULL and left->color == RED) or
	   (right != NULL and right->color == RED);
	}

	x key;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	Color color;
};

#endif /* TREENODE_H_ */
