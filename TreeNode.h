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
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		color = RED;
	}

	TreeNode(x newKey)
	{
		key = newKey;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		color = RED;
	}

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

	//This method swaps the places of two nodes.
	//pointer to child node pointer is fixed in the calling method, either RotateLeft or RotateRight
	void MoveDown(TreeNode<x>* otherNode)
	{
		//Only reset parent pointer if not dealing with root
		if (this.parent != NULL)
		{
			if (IsLeftChild())
			{
				this.parent -> left = otherNode;
			}
			else
			{
				this.parent -> right = otherNode;
			}
		}
		otherNode -> parent = this.parent;
		this.parent = otherNode;
	}

	bool HasRedChild()
	{
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
