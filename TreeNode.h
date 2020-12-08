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
	bool IsLeftChild()
	{
		if(this -> parent != nullptr && this == this -> parent -> left)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void moveDown(TreeNode<x>* node)
	{
		if (parent != NULL)
		{
			if (IsLeftChild())
			{
				parent -> left = node;
			}
			else
			{
				parent -> right = node;
			}
		}
		node -> parent = parent;
		parent = node;
	}

	bool HasRedChild()
	{
		cerr << "TEEEEEEEEEEEEEEEEEEESHIrt\n";
		if((left != nullptr && left -> color == RED) || (right != nullptr && right -> color == RED))
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	x key;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	Color color;
};

#endif /* TREENODE_H_ */
