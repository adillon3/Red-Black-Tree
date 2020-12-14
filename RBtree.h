/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment Extra Credit
 *******************************/

#ifndef RBTREE_H_
#define RBTREE_H_

#include "TreeNode.h"

template <class x>
class RBtree
{
public:
	RBtree()
	{
		root = nullptr;
		numNodes = 0;
	}
	~RBtree()
	{
		DeleteSubTree(root);
	}
	void DeleteSubTree(TreeNode<x>* subRoot)
	{
		if(subRoot != nullptr)
		{
			DeleteSubTree(subRoot -> left);
			DeleteSubTree(subRoot -> right);
			delete subRoot;
			subRoot = nullptr;
		}
	}


	/****************
	 * Core Methods *
	 ****************/
	// Function to insert a new node with given value
	void Insert(const int &newValue)
	{
		if(SearchNode(newValue) != nullptr)
		{
			cout << newValue << " is already in the tree.\n\n";
			return;
		}

		TreeNode<x>* node = new TreeNode<x>(newValue);

    // Do a normal BST insert
    root = InsertRecursive(root, node);

    if(node -> parent)
    {
    	cout << "Adding " << newValue << " to the Tree\n";
    }

    // fix Red Black Tree violations
    FixInsertViolation(node);
		numNodes++;
	}
	void Delete(x value)
	{
		if(IsEmpty())
		{
			cout << "Sorry, nothing to delete, tree is empty.\n\n";
			return;
		}

		//Finding value in tree
		TreeNode<x>* deleteToNode = SearchNode(value);

		//Returning if not found on tree
		if(deleteToNode == nullptr)
		{
			cout << "Sorry, that value was not found in the tree and could not be deleted.\n\n";
			return;
		}

		//Delteting node if found
		DeleteNode(deleteToNode);
		--numNodes;
	}
	//Returns pointer to the node or nullptr if value is not found in the tree
	TreeNode<x>* SearchNode(x value)
  {
    if(IsEmpty())
    {
      return nullptr;
    }
    else
    {
      //tree is not empty, lets go looking for the node
      TreeNode<x>* current = root;
      while(current != nullptr && current -> key != value)
      {
        if(value < current -> key)
        {
          current = current -> left;
        }
        else
        {
          current = current -> right;
        }
      }
	    return current;
    }//END else of if(IsEmpty())
  }

	//Returns the number of nodes in the tree
	int GetNumNodes()
	{
		return numNodes;
	}

	//Returns the largest value in the tree
	x  GetMax()
	{
		if(IsEmpty())
		{
			throw "\n*Tree Empty: No Max Value";
		}

		TreeNode<x> *temp = root;
		while(temp -> right != nullptr)
		{
			temp = temp -> right;
		}

		return temp -> key;
	}
	//Returns the smallest value in the tree
	x  GetMin()
	{
		if(IsEmpty())
		{
			throw "\n*Tree Empty: No Minimum Value";
		}

		TreeNode<x> *temp = root;

		while(temp -> left != nullptr)
		{
			temp = temp -> left;
		}

		return temp -> key;
	}
	//Checks if the tree is empty
	bool IsEmpty()
	{
		if(root == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/*********************
	 * TRAVERSAL METHODS *
	 *********************/
	void PrintAllTraversals()
	{
		cout << "--PRINTING ALL TRAVERSALS--\n";
		if(root == nullptr)
		{
			cout << "*Tree empty*\n";
			return;
		}

		cout << "Preorder\n";
		PreOrderHelper(root);

		cout << "\n\nInorder\n";
		InOrderHelper(root);

		cout << "\n\nPostorder\n";
		PostOrderHelper(root);
	}
	void PreOrder()
	{
		cout << "Preorder:\n";

		if(root == nullptr)
		{
			cout << "*Tree empty*\n";
		}
		else
		{
			PreOrderHelper(root);
		}
	}
	void InOrder()
	{
     cout << "Inorder:\n";

		if(root == nullptr)
		{
			cout << "*Tree empty*\n";
		}
		else
		{
			InOrderHelper(root);
		}

	}
	void PostOrder()
	{
		cout << "Postorder:\n";

		if(root == nullptr)
		{
			cout << "*Tree empty*\n";
		}
		else
		{
			PostOrderHelper(root);
		}
	}



private:
	TreeNode<x>* root;
	int numNodes;

	/****************************
	 * TRAVERSAL HELPER METHODS *
	 ****************************/
	void PreOrderHelper(TreeNode<x>* subRoot)
	{
		if(subRoot != nullptr)
		{
			if(subRoot == root)
			{
				cout << "root:";
			}
			cout << subRoot -> key;

			if(subRoot -> color == RED)
			{
				cout << "R ";
			}
			else
			{
				cout << "B ";
			}

			PreOrderHelper(subRoot -> left);

			PreOrderHelper(subRoot -> right);
		}
	}
	void PostOrderHelper(TreeNode<x>* subRoot)
	{
		if(subRoot != nullptr)
		{
			PostOrderHelper(subRoot -> left);

			PostOrderHelper(subRoot -> right);

			if(subRoot == root)
			{
				cout << "root:";
			}
			cout << subRoot -> key;

			if(subRoot -> color == RED)
			{
				cout << "R ";
			}
			else
			{
				cout << "B ";
			}
		}
	}
	void InOrderHelper(TreeNode<x>* subRoot)
	{
		if(subRoot != nullptr)
		{
			InOrderHelper(subRoot -> left);

			if(subRoot == root)
			{
				cout << "root:";
			}
			cout << subRoot -> key;

			if(subRoot -> color == RED)
			{
				cout << "R ";
			}
			else
			{
				cout << "B ";
			}

			InOrderHelper(subRoot -> right);
		}
	}


	/*************************
	 * INSERT HELPER METHODS *
	 *************************/
	 //Recursivly inserting node to the leave level, just like non balanced BST
	 TreeNode<x>* InsertRecursive(TreeNode<x>* subroot, TreeNode<x>* newNode)
	 {
		 //Correct location to insert has been found
		 if(subroot == nullptr)
		 {
			 return newNode;
		 }

		 //Moving left if the new node is less than the current subroot and
		 // right if it is greater than the current subroot
		 if(newNode -> key < subroot -> key)
		 {
			 subroot -> left = InsertRecursive(subroot -> left, newNode);
			 subroot -> left -> parent = subroot;
		 }
		 else if(newNode -> key > subroot -> key)
		 {
			 subroot -> right = InsertRecursive(subroot -> right, newNode);
			 subroot -> right -> parent = subroot;
		 }
		 //Cannot add two of the same value
		 else
		 {
			 return nullptr;
		 }

		 return subroot;
	 }

	 //Called by main insret method to fix any violations caused by the most
	 // recent value inserted (node points to this most recent value)
	 void FixInsertViolation(TreeNode<x>* node)
 	 {
		  TreeNode<x>* nodeParent = nullptr;
		  TreeNode<x>* nodeGrandParent = nullptr;

			//Looping until back at root and all violations (baring root must be black) are fixed
 	    while ((node != root) && (node -> color != BLACK) &&
 	           (node -> parent -> color == RED))
 	    {
 	    	nodeParent = node -> parent;
        nodeGrandParent = node -> parent -> parent;

				//Parent is left child, uncle is righgt child
        if(nodeParent -> IsOnLeft())
				{
        	TreeNode<x>* nodeUncle = nodeGrandParent -> right;

					//If uncle is red, "move the black down"
					// This is done to keep the number of BLACK nodes in each path to each leaf node the same
					if(nodeUncle != nullptr && nodeUncle -> color == RED)
					{
						//Recolor
						nodeGrandParent -> color = RED;
						nodeParent -> color = BLACK;
						nodeUncle -> color = BLACK;
						node = nodeGrandParent;
					}//END else of if(nodeAunt != nullptr && nodeAunt -> color == RED)
					else
					{
						//If node is a right child
						if(!(node -> IsOnLeft()))
						{
							RotateLeft(nodeParent);
							node = nodeParent;
							nodeParent = node -> parent;
						}//END if(!(node -> IsOnLeft()))

						RotateRight(nodeGrandParent);
						//Values/ nodes placment is correct, now changing colors
						ExchangeColors(nodeParent, nodeGrandParent);
						node = nodeParent;
					}//END else of if(nodeAunt != nullptr && nodeAunt -> color == RED)
        }//END if (nodeParent -> IsOnLeft())
				//Parent is right child, uncle is left child
				else
        {
            TreeNode<x>* nodeUncle = nodeGrandParent -> left;

						//If uncle is red, "move the black down"
						// This is done to keep the number of BLACK nodes in each path to each leaf node the same
            if((nodeUncle != nullptr) && (nodeUncle -> color == RED))
            {
                nodeGrandParent -> color = RED;
                nodeParent -> color = BLACK;
                nodeUncle -> color = BLACK;
                node = nodeGrandParent;
            }
            else
            {
							//If node is on left
              if(node -> IsOnLeft())
              {
                RotateRight(nodeParent);
                node = nodeParent;
                nodeParent = node -> parent;
              }

              RotateLeft(nodeGrandParent);
							//Values/ nodes placment is correct, now changing colors
              ExchangeColors(nodeParent, nodeGrandParent);
              node = nodeParent;
            }//END else of if((uncle_pt != nullptr) && (uncle_pt -> color == RED))
        }//END else of if(nodeParent -> IsOnLeft())
 	    }//END  while ((node != root) && (node -> color != BLACK) && (node -> parent -> color == RED))

			//Root must always be black
 	    root -> color = BLACK;
 	}

	/*************************
	 * DELETE HELPER METHODS *
	 *************************/
	void DeleteNode(TreeNode<x>* nodeToDelete)
	{
		//Getting node that will replace the nodeToDelete
		TreeNode<x>* replacmentNode = BSTreplacementNode(nodeToDelete);

		// True when nodeToDelete(dNode) and replacmentNode(RNode) are both black
		bool dNodeAndRNodeBlack = ((replacmentNode == nullptr || replacmentNode -> color == BLACK) && (nodeToDelete -> color == BLACK));
		TreeNode<x>* parent = nodeToDelete -> parent;

		// replacmentNode is nullptr therefore nodeToDelete is leaf
		if(replacmentNode == nullptr)
		{
			// nodeToDelete is root, making root nullptr
			if(nodeToDelete == root)
			{
				root = nullptr;
				//Tree is now empty
			}
			else
			{
				if(dNodeAndRNodeBlack)
				{
					//NodeToDelete is leaf, fix double BLACK at nodeToDelete
					FixDoubleBlack(nodeToDelete);
				}
				else
				{
					// replacmentNode or nodeToDelete is RED
					if(GetSibling(nodeToDelete) != nullptr)
					{
						//sibling is not nullptr, make it RED
						GetSibling(nodeToDelete) -> color = RED;
					}

				}//END else if(dNodeAndRNodeBlack)

				// delete nodeToDelete from the tree
				if(nodeToDelete -> IsOnLeft())
				{
					parent -> left = nullptr;
				}
				else
				{
					parent -> right = nullptr;
				}
			}//END else of if(nodeToDelete == root)
			delete nodeToDelete;
			return;
		}//if(replacmentNode == nullptr)

		//if one or two children
		if(nodeToDelete -> left == nullptr || nodeToDelete -> right == nullptr)
		{
			if(nodeToDelete == root)
			{
				//Assigning the value of replacmentNode to nodeToDelete
				nodeToDelete -> key = replacmentNode -> key;
				nodeToDelete -> left = nodeToDelete -> right = nullptr;
				delete replacmentNode;
			}
			else
			{
				//Detach nodeToDelete from tree and move replacmentNode up
				if(nodeToDelete -> IsOnLeft())
				{
					parent -> left = replacmentNode;
				}
				else
				{
					parent -> right = replacmentNode;
				}//END else of if(nodeToDelete -> IsOnLeft())

				delete nodeToDelete;
				replacmentNode -> parent = parent;

				if(dNodeAndRNodeBlack)
				{
					//replacmentNode and nodeToDelete are both black, fix double black at replacmentNode
					FixDoubleBlack(replacmentNode);
				}
				else
				{
					//Either replacmentNode or nodeToDelete is RED, color replacmentNode BLACK
					replacmentNode -> color = BLACK;
				}//END else of if(dNodeAndRNodeBlack)
			}//END else of if(nodeToDelete == root)
			return;
		}//END if(nodeToDelete -> left == nullptr || nodeToDelete -> right == nullptr)

		//nodeToDelete has 2 children, swap values with successor and recurse
		SwapValues(replacmentNode, nodeToDelete);
		DeleteNode(replacmentNode);
	}//void DeleteNode(TreeNode<x>* nodeToDelete)

	//Converting Double black to regular BLACK, which is caused when deleting a
	// black node and replacing it with another black node, this messes up the
	// property of the RB tree that states that every path to a leaf node must
	// have the sane number of black nodes.  This is because the side on which
	// the delete occured now has one less BLACK node than the other side
	void FixDoubleBlack(TreeNode<x>* xNode)
	{
		//Reached root: Finished
		if(xNode == root)
		{
			return;
		}

		TreeNode<x>* sibling = GetSibling(xNode), *parent = xNode -> parent;
		if(sibling == nullptr)
		{
			// No sibiling, double black pushed up
			FixDoubleBlack(parent);
		}
		else
		{
			if(sibling -> color == RED)
			{
				// Sibling red
				parent -> color = RED;
				sibling -> color = BLACK;

				if(sibling -> IsOnLeft())
				{
					// left case
					RotateRight(parent);
				}
				else
				{
					// right case
					RotateLeft(parent);
				}
				FixDoubleBlack(xNode);
			}//END if(sibling -> color == RED)
			else
			{
				// Sibling black
				if(sibling -> HasRedChild())
				{
					// at least 1 red children
					if(sibling -> left != nullptr && sibling -> left -> color == RED)
					{
						if(sibling -> IsOnLeft())
						{
							// left left
							sibling -> left -> color = sibling -> color;
							sibling -> color = parent -> color;
							RotateRight(parent);
						}
						else
						{
							// right left
							sibling -> left -> color = parent -> color;
							RotateRight(sibling);
							RotateLeft(parent);
						}
					}
					else
					{
						if(sibling -> IsOnLeft())
						{
							// left right
							sibling -> right -> color = parent -> color;
							RotateLeft(sibling);
							RotateRight(parent);
						} else {
							// right right
							sibling -> right -> color = sibling -> color;
							sibling -> color = parent -> color;
							RotateLeft(parent);
						}
					}//END else of if(sibling -> left != nullptr && sibling -> left -> color == RED)

					parent -> color = BLACK;

				}
				else
				{
					// 2 black children
					sibling -> color = RED;

					if(parent -> color == BLACK)
					{
						FixDoubleBlack(parent);
					}
					else
					{
						parent -> color = BLACK;
					}//END else of if(parent -> color == BLACK)
				}//END else of if(sibling -> HasRedChild())
			}//END else of if(sibling -> color == RED)
		}//END else of f(sibling == nullptr)
	}//END void FixDoubleBlack(TreeNode<x>* xNode)

	//Finding the approprate replacment node when deleting
	TreeNode<x>* BSTreplacementNode(TreeNode<x>* xNode)
	{
		//When node to delete has 2 children, the sucessor must be found
		// (the smallest value that is larger than the node to be deleted)
		if(xNode -> left != nullptr && xNode -> right != nullptr)
		{
			return Successor(xNode -> right);
		}
		//When node to delete is a leaf, there is no node to replace it, return nullptr
		if(xNode -> left == nullptr && xNode -> right == nullptr)
		{
			return nullptr;
		}
		//When node to delete only has aone child, return that
		if(xNode -> left != nullptr)
		{
			return xNode -> left;
		}
		else
		{
			return xNode -> right;
		}
	}

	//Gets smallest value in the given node's subtree. Used to find the successor
	// for delete, getting the smallest value that is larger than the node to be
	// deleted.  The rgiht child of the delete node is passed in to this method
	TreeNode<x>* Successor(TreeNode<x>* xNode)
	{
		TreeNode<x>* temp = xNode;

		while (temp -> left != nullptr)
		{
			temp = temp -> left;
		}

		return temp;
	}

	/******************
	 * ROTATE METHODS *
	 ******************/

	//Moves a left child "up" and node "down", repositioning pointers
	// appropriatly to A) not lose data and B) keep the values in order
	void RotateRight(TreeNode<x>* &point)
	{
		TreeNode<x>* leftPointer = point -> left;

			point -> left = leftPointer -> right;

			if(point -> right != nullptr)
			{
					point -> right -> parent = point;
			}

			leftPointer -> parent = point -> parent;

			if(point -> parent == nullptr)
			{
					root = leftPointer;
			}
			else if(point == point -> parent -> left)
			{
					point -> parent -> left = leftPointer;
			}
			else
			{
					point -> parent -> right = leftPointer;
			}

			leftPointer -> right = point;
			point -> parent = leftPointer;
	}

 //Moves a right child "up" and node "down", repositioning pointers
 // appropriatly to A) not lose data and B) keep the values in order
	void RotateLeft(TreeNode<x>* &point)
	{
		TreeNode<x>* rightPointer = point -> right;

			point -> right = rightPointer -> left;

			if(point -> left != nullptr)
			{
					point -> left -> parent = point;
			}

			rightPointer -> parent = point -> parent;

			if(point -> parent == nullptr)
			{
					root = rightPointer;
			}
			else if(point == point -> parent -> left)
			{
					point -> parent -> left = rightPointer;
			}
			else
			{
					point -> parent -> right = rightPointer;
			}

			rightPointer -> left = point;
			point -> parent = rightPointer;
	}


	/********************
	 * AUXILARY METHODS *
	 ********************/
	//Swaps the key values of two nodes, leaving all other data members the same
	void SwapValues(TreeNode<x>* node1, TreeNode<x>* node2)
	{
		x temp;
		temp = node1 -> key;
		node1 -> key = node2 -> key;
		node2 -> key = temp;
	}
	//Swaps the colors of two nodes, leaving all other data members the same
	void ExchangeColors(TreeNode<x>* node1, TreeNode<x>* node2)
	{
		Color temp;
		temp = node1 -> color;
		node1 -> color = node2 -> color;
		node2 -> color = temp;
	}
	//Switches a nodes color from red to black or from clack to red
	void Recolor(TreeNode<x>* temp)
	{
		if(temp -> color == RED)
		{
			temp -> color = BLACK;
		}
		else
		{
			temp -> color = RED;
		}
	}
	TreeNode<x>* GetSibling(TreeNode<x>* node)
	{
		if(node -> IsOnLeft())
		{
			return node -> parent -> right;
		}
		else //right is child
		{
			return node -> parent -> left;
		}
	}



};//END RBtree class


#endif /* RBTREE_H_ */
