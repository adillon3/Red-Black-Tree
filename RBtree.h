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
	/**********************************************
	 * Constructors and Destructors (and Helpers) *
	 **********************************************/
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
	RBtree(const RBtree& other)
	{
		CopyBinaryTree(root, other.root);

		numNodes = other.numNodes;
	}

	//Recursive method that copies each node in the tree one at a time
	void CopyHelper(TreeNode<x>* copiedTreeNode, TreeNode<x>* otherTreeNode)
	{
		if(otherTreeNode == nullptr)
		{
			copiedTreeNode = nullptr;
		}
		else
		{
			copiedTreeNode = new TreeNode<x>;
			copiedTreeNode -> key = otherTreeNode -> key;
			CopyHelper(copiedTreeNode -> left, otherTreeNode -> left);
			CopyHelper(copiedTreeNode -> right, otherTreeNode -> right);
		}
	}
	//move constructor
	RBtree(RBtree&& other)
	{
		root = other.root;
		other.root = nullptr;
		numNodes = other.numNodes;
	}



	/****************
	 * CORE METHODS *
	 ****************/
	// Function to insert a new node with given value
	void Insert(const int &newValue)
	{
		if(SearchNode(newValue) != nullptr)
		{
			cout << newValue << " is already in the tree.\n\n";
			return;
		}

		TreeNode<x>* node = CreateNewNode(newValue);

    // Do a normal BST insert and tell user
    root = InsertRecursive(root, node);
  	cout << "Adding " << newValue << " to the Tree\n";

    // fix Red Black Tree violations
    FixViolation(node);
	}

	//public delate method
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
	}

	TreeNode<x>* SearchNode(x value)
  {
		//Can't find node if no nodes to look through
    if(IsEmpty())
    {
      return nullptr;
    }

    //tree is not empty, lets go looking for the node
    TreeNode<x>* current = root;

		//searching through tree
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
    }//END while(current != nullptr && current -> key != value)

		//Mode found, or returning nullptr
    return current;
  }

	x GetMax()
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

	x GetMin()
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

	/*******************
	 * PRIVATE METHODS *
	 *******************/
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
		}//END else if(newNode -> key < subroot -> key)

		return subroot;
	}

	// deletes the given node
	void DeleteNode(TreeNode<x>* nodeToDelete)
	{
		TreeNode<x>* replacementNode = BSTreplace(nodeToDelete);

		// True when nodeToDelete (dNode) and replacementNode(RNode) are both black
		bool dNodeAndRNodeBlack = ((nodeToDelete -> color == BLACK) && (replacementNode == nullptr || replacementNode -> color == BLACK));
		TreeNode<x>* parent = nodeToDelete -> parent;

		if(replacementNode == nullptr)
		{
			// replacementNode is nullptr therefore nodeToDelete is leaf
			if(nodeToDelete == root)
			{
				// nodeToDelete is root, making root nullptr
				root = nullptr;
			}
			else
			{
				if(dNodeAndRNodeBlack)
				{
				  // replacementNode and nodeToDelete both black
				  // nodeToDelete is leaf, fix double black at nodeToDelete
				  FixDoubleBlack(nodeToDelete);
				}
				else
				{
					// replacementNode or nodeToDelete is red
					if(GetSibling(nodeToDelete) != nullptr)
					{
						// sibling is not nullptr, make it red
						GetSibling(nodeToDelete) -> color = RED;
					}
				}//END else of if(dNodeAndRNodeBlack)

				// delete nodeToDelete from the tree
				if(nodeToDelete -> IsLeftChild())
				{
					parent -> left = nullptr;
				}
				else
				{
					parent -> right = nullptr;
				}//END if(nodeToDelete -> IsLeftChild())
			}//END else ofif(nodeToDelete == root)
			delete nodeToDelete;
			return;
		}//END if(replacementNode == nullptr)

		if(nodeToDelete -> left == nullptr || nodeToDelete -> right == nullptr)
		{
			// nodeToDelete has 1 child
			if(nodeToDelete == root)
			{
				// nodeToDelete is root, assign the value of u to nodeToDelete, and delete u
				nodeToDelete -> key = replacementNode -> key;
				nodeToDelete -> left = nodeToDelete -> right = nullptr;
				delete replacementNode;
			}//END if(nodeToDelete == root)
			else
			{
				// Detach nodeToDelete from tree and move u up
				if(nodeToDelete -> IsLeftChild())
				{
					parent -> left = replacementNode;
				}
				else
				{
					parent -> right = replacementNode;
				}//END else of if(nodeToDelete -> IsLeftChild())

				delete nodeToDelete;
				replacementNode -> parent = parent;

				if(dNodeAndRNodeBlack)
				{
					// u and nodeToDelete both black, fix double black at u
					FixDoubleBlack(replacementNode);
				}
				else
				{
					// u or nodeToDelete red, color u black
					replacementNode -> color = BLACK;
				}//END else of if(dNodeAndRNodeBlack)
			}//END else of if(nodeToDelete == root)

			return;
		}//if(nodeToDelete -> left == nullptr or nodeToDelete -> right == nullptr)

		// node has 2 children, swap values with successor and recurse
		ExchangeValues(replacementNode, nodeToDelete);
		DeleteNode(replacementNode);
	}//END void DeleteNode(TreeNode<x>* nodeToDelete)

	//Recursive method used to fix errors when removing a node
	void FixDoubleBlack(TreeNode<x>* xNode)
	{
		// Reached root, all nodes fixed, end recurssion
		if(xNode == root)
		{
			return;
		}

		TreeNode<x>* sibling = GetSibling(xNode), *parent = xNode -> parent;
		if(sibling == nullptr)
		{
			// No sibiling, double black pushed up
			FixDoubleBlack(parent);
		}//if(sibling == nullptr)
		else
		{
			if(sibling -> color == RED)
			{
				// Sibling red
				parent -> color = RED;
				sibling -> color = BLACK;

				if(sibling -> IsLeftChild())
				{
					// left case
					RotateRight(parent);
				}//END if(sibling -> IsLeftChild())
				else
				{
					// right case
					RotateLeft(parent);
					//leftRotate(parent);
				}//END else of if(sibling -> IsLeftChild())

				FixDoubleBlack(xNode);
			}//END if(sibling -> color == RED)
			else
			{
				// Sibling black
				if(sibling -> HasRedChild())
				{
					// at least 1 red children
					if(sibling -> left != nullptr and sibling -> left -> color == RED)
					{
						if(sibling -> IsLeftChild())
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
							//leftRotate(parent);
							RotateLeft(parent);
						}//END else of if(sibling -> IsLeftChild())
					}//END if(sibling -> left != nullptr and sibling -> left -> color == RED)
					else
					{
						if(sibling -> IsLeftChild())
						{
							// left right
							sibling -> right -> color = parent -> color;
							//leftRotate(sibling);
							RotateLeft(sibling);
							RotateRight(parent);
						}
						else
						{
							// right right
							sibling -> right -> color = sibling -> color;
							sibling -> color = parent -> color;
							//leftRotate(parent);
							RotateLeft(parent);
						}//END else of if(sibling -> IsLeftChild())
					}//END else of if(sibling -> left != nullptr and sibling -> left -> color == RED)
					parent -> color = BLACK;
				}//END if(sibling -> HasRedChild())
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
		}//END else of (sibling == nullptr)
	}//END void FixDoubleBlack(TreeNode<x>* xNode)

	//This method swaps the key values of two nodes
	void ExchangeValues(TreeNode<x>* node1, TreeNode<x>* node2)
	{
		x tempValue = node1 -> key;
		node1 -> key = node2 -> key;
		node2 -> key = tempValue;
	}

	TreeNode<x>* BSTreplace(TreeNode<x>* xNode)
	{
		// when node have 2 children, chosing the best successor
		if((xNode -> left != nullptr) && (xNode -> right != nullptr))
		{
			return Successor(xNode -> right);
		}

		// when leaf, no need to get a replacement node
		if((xNode -> left == nullptr) && (xNode -> right == nullptr))
		{
			return nullptr;
		}

		// when single child, picking the non null child
		if(xNode -> left != nullptr)
		{
			return xNode -> left;
		}
		else
		{
			return xNode -> right;
		}
	}

	void FixRedRed(TreeNode<x>* node)
	{
		//Root must always be black
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
    }//END else of if(grandparent -> left == parent)

		if(parent -> color != BLACK)
		{
			if(aunt != nullptr && aunt -> color == RED)
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
					}//END else of if(node -> parent -> left == node)

					RotateRight(grandparent);
				}
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
			}//END else of if(aunt != nullptr && aunt -> color == RED)
		}//END if(parent -> color != BLACK)
	}//END void FixRedRed(TreeNode<x>* node)

	//Getting the smallest value, that is bigger than the initial node
	TreeNode<x>* Successor(TreeNode<x>* node)
	{
	  TreeNode<x>* temp = node;

		while (temp -> left != nullptr)
		{
		  temp = temp -> left;
		}

		return temp;
	}

	//Recursivly deletes a subtree with a post order traversal
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

	void FixViolation(TreeNode<x>* node)
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

          if(nodeAunt != nullptr && nodeAunt -> color == RED)
          {
              nodeGrandParent -> color = RED;
              nodeParent -> color = BLACK;
              nodeAunt -> color = BLACK;
              node = nodeGrandParent;
          }
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
          }//END else of if(nodeAunt != nullptr && nodeAunt -> color == RED)
      }//eND if(nodeParent == nodeGrandParent -> left)
      else
      {
        TreeNode<x>* nodeAunt = nodeGrandParent -> left;

        if((nodeAunt != nullptr) && (nodeAunt -> color == RED))
        {
            nodeGrandParent -> color = RED;
            nodeParent -> color = BLACK;
            nodeAunt -> color = BLACK;
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
        }//END else of if((nodeAunt != nullptr) && (nodeAunt -> color == RED))
      }//END else of if(nodeParent == nodeGrandParent -> left)
  	}//END while ((node != root) && (node -> color != BLACK) && (node -> parent -> color == RED))

  	root -> color = BLACK;
	}

	void TransplantNodes(TreeNode<x>* deleteNode, TreeNode<x>* replacementNode)
	{
		if(deleteNode -> parent == nullptr)
		{
			root = replacementNode;
		}
		else if(deleteNode)
		{
			deleteNode -> parent -> left = replacementNode;
		}
		else
		{
			deleteNode -> parent -> right = replacementNode;
		}

		//ifnew node is nullptr (we are deleting a leaf node)
		if(replacementNode != nullptr)
		{
			replacementNode -> parent = deleteNode -> parent;
		}
	}

	void RotateLeft(TreeNode<x>* point)
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

	void RotateRight(TreeNode<x>* point)
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

	TreeNode<x>* CreateNewNode(int newKey)
	{
		TreeNode<x>* node = new TreeNode<x>;
		node -> key = newKey;
		node -> left = nullptr;
		node -> right = nullptr;
		node -> parent = nullptr;
		node -> color = RED;

		return node;
	}

	void PreOrderHelper(const TreeNode<x>* subRoot)
	{
		if(subRoot != nullptr)
		{
			cout << subRoot -> key;

			if(subRoot == root)
			{
				cout << "root:";
			}

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
	void PostOrderHelper(const TreeNode<x>* subRoot)
	{
		if(subRoot != nullptr)
		{
			PostOrderHelper(subRoot -> left);

			PostOrderHelper(subRoot -> right);

			cout << subRoot -> key;

			if(subRoot == root)
			{
				cout << "root:";
			}

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
	void InOrderHelper(const TreeNode<x>* subRoot)
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

	void ExchangeColors(TreeNode<x>* node1, TreeNode<x>* node2)
	{
		Color temp;
		temp = node1 -> color;
		node1 -> color = node2 -> color;
		node2 -> color = temp;
	}

	TreeNode<x>* GetSibling(TreeNode<x>* node)
	{
		if(node -> IsLeftChild())
		{
			return node -> parent -> right;
		}
		else //right is child
		{
			return node -> parent -> left;
		}
	}

	void Restructure(TreeNode<x>* temp)
	{
		FixViolation(root);
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


#endif/* RBTREE_H_ */
