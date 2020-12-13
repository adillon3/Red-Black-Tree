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
	TreeNode()
	{
		this -> left = nullptr;
		this -> right = nullptr;
		this -> parent = nullptr;
		this -> color = RED;
	}

	TreeNode(x newKey)
	{
		this -> key = newKey;
		this -> left = nullptr;
		this -> right = nullptr;
		this -> parent = nullptr;
		this -> color = RED;
	}



	bool IsOnLeft()
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


	void MoveDown(TreeNode<x>* node)
	{
		if (parent != NULL)
		{
			if (IsOnLeft())
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
		if((left != NULL && left -> color == RED) || (right != NULL && right -> color == RED))
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
