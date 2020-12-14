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
	//copy constructor
	
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
    FixViolation(root, node);
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
		if(subRoot != NULL)
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
		if(subRoot != NULL)
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
		if(subRoot != NULL)
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
	 TreeNode<x>* InsertRecursive(TreeNode<x>* subroot, TreeNode<x>* newNode)
	 {
		 if(subroot == nullptr)
		 {
			 return newNode;
		 }

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
		 else
		 {
			 return nullptr;
		 }

		 return subroot;
	 }

	//**********************************************************************************************************8
	 void FixRedRed(TreeNode<x>* node)
	 {
			if(node == root)
			{
				node -> color = BLACK;
				return;
			}

			TreeNode<x>* parent = node -> parent;
			TreeNode<x>* grandparent = parent -> parent;
			TreeNode<x>* aunt;

			if(grandparent -> left == parent)
			{
			 aunt = grandparent -> right;
			}
			else
			{
			 aunt = grandparent -> left;
			}

		 if(parent -> color != BLACK)
		 {
			 if(aunt != NULL && aunt -> color == RED)
			 {
				 parent -> color = BLACK;
				 aunt -> color = BLACK;
				 grandparent -> color = RED;
				 FixRedRed(grandparent);
			 }
			 else
			 {
				 if(parent -> parent -> left == parent)
				 {
					 if(node -> parent -> left == node)
					 {
						 ExchangeColors(parent, grandparent);
					 }
					 else
					 {
						 RotateLeft(parent);
						 ExchangeColors(node, grandparent);
					 }

					 RotateRight(grandparent);
				 }//END if(parent -> parent -> left == parent)
				 else
				 {
					 if(node -> parent -> left == node)
					 {
						 RotateRight(parent);
						 ExchangeColors(node, grandparent);
					 }
					 else
					 {
						 ExchangeColors(parent, grandparent);
					 }//END else of if(node -> parent -> left == node)

					 RotateLeft(grandparent);
				 }//END else of if(parent -> parent -> left == parent)
			 }//END else of if(aunt != NULL && aunt -> color == RED)
		 }//END if(parent -> color != BLACK)
	 }

	 void FixViolation(TreeNode<x>* &root, TreeNode<x>* &node)
 	{
 	    TreeNode<x>* nodeParent = nullptr;
 	    TreeNode<x>* nodeGrandParent = nullptr;

 	    while ((node != root) && (node -> color != BLACK) &&
 	           (node -> parent -> color == RED))
 	    {
 	    	nodeParent = node -> parent;
        nodeGrandParent = node -> parent -> parent;

        if(nodeParent == nodeGrandParent -> left)
        {

        	TreeNode<x>* nodeAunt = nodeGrandParent -> right;

					if(nodeAunt != NULL && nodeAunt -> color == RED)
					{
						nodeGrandParent -> color = RED;
						nodeParent -> color = BLACK;
						nodeAunt -> color = BLACK;
						node = nodeGrandParent;
					}//END else of if(nodeAunt != NULL && nodeAunt -> color == RED)
					else
					{
						if(node == nodeParent -> right)
						{
							RotateLeft(nodeParent);
							node = nodeParent;
							nodeParent = node -> parent;
						}

						RotateRight(nodeGrandParent);
						ExchangeColors(nodeParent, nodeGrandParent);
						node = nodeParent;
					}//END else of if(nodeAunt != NULL && nodeAunt -> color == RED)
        }//END if(nodeParent == nodeGrandParent -> left)
        else
        {
            TreeNode<x>* uncle_pt = nodeGrandParent -> left;

            if((uncle_pt != NULL) && (uncle_pt -> color == RED))
            {
                nodeGrandParent -> color = RED;
                nodeParent -> color = BLACK;
                uncle_pt -> color = BLACK;
                node = nodeGrandParent;
            }
            else
            {
              if(node == nodeParent -> left)
              {
                RotateRight(nodeParent);
                node = nodeParent;
                nodeParent = node -> parent;
              }

              RotateLeft(nodeGrandParent);
              ExchangeColors(nodeParent, nodeGrandParent);
              node = nodeParent;
            }//END else of if((uncle_pt != NULL) && (uncle_pt -> color == RED))
        }//END else of if(nodeParent == nodeGrandParent -> left)
 	    }//END  while ((node != root) && (node -> color != BLACK) && (node -> parent -> color == RED))

 	    root -> color = BLACK;
 	}

	/*************************
	 * DELETE HELPER METHODS *
	 *************************/
	void DeleteNode(TreeNode<x>* nodeToDelete)
	{
		TreeNode<x>* replacmentNode = BSTreplace(nodeToDelete);

		// True when nodeToDelete(dNode) and replacmentNode(RNode) are both black
		bool dNodeAndRNodeBlack = ((replacmentNode == NULL || replacmentNode -> color == BLACK) && (nodeToDelete -> color == BLACK));
		TreeNode<x>* parent = nodeToDelete -> parent;

		if(replacmentNode == NULL)
		{
			// replacmentNode is NULL therefore v is leaf
			if(nodeToDelete == root)
			{
				// nodeToDelete is root, making root null
				root = NULL;
			}
			else
			{
				if(dNodeAndRNodeBlack)
				{
					// replacmentNode and nodeToDelete both black
					// nodeToDelete is leaf, fix double black at nodeToDelete
					FixDoubleBlack(nodeToDelete);
				}
				else
				{
					// u or nodeToDelete is red
					if(GetSibling(nodeToDelete) != NULL)
					{
						// sibling is not null, make it red"
						GetSibling(nodeToDelete) -> color = RED;
					}

				}//END else if(uvBlack)

				// delete nodeToDelete from the tree
				if(nodeToDelete -> IsOnLeft())
				{
					parent -> left = NULL;
				}
				else
				{
					parent -> right = NULL;
				}
			}//END else of if(nodeToDelete == root)
			delete nodeToDelete;
			return;
		}//if(replacmentNode == NULL)

		if(nodeToDelete -> left == NULL || nodeToDelete -> right == NULL)
		{
			// nodeToDelete has 1 child
			if(nodeToDelete == root)
			{
				// nodeToDelete is root, assign the value of u to nodeToDelete, and delete u
				nodeToDelete -> key = replacmentNode -> key;
				nodeToDelete -> left = nodeToDelete -> right = NULL;
				delete replacmentNode;
			}
			else
			{
				// Detach nodeToDelete from tree and move u up
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
					// replacmentNode and nodeToDelete both black, fix double black at u
					FixDoubleBlack(replacmentNode);
				}
				else
				{
					// replacmentNode or nodeToDelete red, color u black
					replacmentNode -> color = BLACK;
				}//END else of if(dNodeAndRNodeBlack)
			}//END else of if(nodeToDelete == root)
			return;
		}//END if(nodeToDelete -> left == NULL || nodeToDelete -> right == NULL)

		// nodeToDelete has 2 children, swap values with successor and recurse
		SwapValues(replacmentNode, nodeToDelete);
		DeleteNode(replacmentNode);
	}//void DeleteNode(TreeNode<x>* nodeToDelete)

	void FixDoubleBlack(TreeNode<x>* xNode)
	{
		if(xNode == root)
		{
			// Reached root
			return;
		}


		TreeNode<x>* sibling = GetSibling(xNode), *parent = xNode -> parent;
		if(sibling == NULL)
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
					if(sibling -> left != NULL && sibling -> left -> color == RED)
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
					}//END else of if(sibling -> left != NULL && sibling -> left -> color == RED)

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
		}//END else of f(sibling == NULL)
	}//END void FixDoubleBlack(TreeNode<x>* xNode)


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

	void SwapValues(TreeNode<x>* node1, TreeNode<x>* node2)
	{
		x temp;
		temp = node1 -> key;
		node1 -> key = node2 -> key;
		node2 -> key = temp;
	}
	TreeNode<x>* BSTreplace(TreeNode<x>* xNode)
	{
		// when node have 2 children
		if(xNode -> left != NULL && xNode -> right != NULL)
		{
			return Successor(xNode -> right);
		}
		// when leaf
		if(xNode -> left == NULL && xNode -> right == NULL)
		{
			return NULL;
		}
		// when single child
		if(xNode -> left != NULL)
		{
			return xNode -> left;
		}
		else
		{
			return xNode -> right;
		}
	}

	TreeNode<x>* Successor(TreeNode<x>* xNode)
	{
		TreeNode<x>* temp = xNode;

		while (temp -> left != NULL)
		{
			temp = temp -> left;
		}

		return temp;
	}

	void RotateRight(TreeNode<x>* &point)
	{
		TreeNode<x>* leftPointer = point -> left;

	    point -> left = leftPointer -> right;

			if(point -> right != NULL)
			{
					point -> right -> parent = point;
			}

	    leftPointer -> parent = point -> parent;

	    if(point -> parent == NULL)
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

	void RotateLeft(TreeNode<x>* &point)
	{
		TreeNode<x>* rightPointer = point -> right;

	    point -> right = rightPointer -> left;

			if(point -> left != NULL)
			{
					point -> left -> parent = point;
			}

	    rightPointer -> parent = point -> parent;

	    if(point -> parent == NULL)
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

	void ExchangeColors(TreeNode<x>* node1, TreeNode<x>* node2)
	{
		Color temp;
		temp = node1 -> color;
		node1 -> color = node2 -> color;
		node2 -> color = temp;
	}
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
};


#endif /* RBTREE_H_ */
