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
	RBtree(const RBtree& other)
	{
		CopyBinaryTree(root, other.root);

		numNodes = other.numNodes;
	}
	void CopyHelper(TreeNode<x>* copiedTreeNode, TreeNode<x>* otherTreeNode)
	{
		if (otherTreeNode == NULL)
		{
			copiedTreeNode = NULL;
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
	//copy assignment operator
	RBtree& operator=(const RBtree& other)
	{
		if (this != &other)
		{
			DeleteSubTree(root);

			CopyHelper(root, other.root);
			numNodes = other.numNodes;
		}

		return *this;
	}
	//move assignment operator
	RBtree& operator=(RBtree&& other)
	{
		if(this != &other)
		{
			DeleteSubTree(root);

			CopyHelper(root, other.root);
			numNodes = other.numNodes;

			CopyHelper(other.root);
			other.numNodes = 0;
		}

		return *this;
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
	void FixViolation(TreeNode<x>* &root, TreeNode<x>* &node)
	{
	    TreeNode<x>* nodeParent = nullptr;
	    TreeNode<x>* nodeGrandParent = nullptr;

	    while ((node != root) && (node -> color != BLACK) &&
	           (node -> parent -> color == RED))
	    {
	    	nodeParent = node -> parent;
	        nodeGrandParent = node -> parent -> parent;

	        if (nodeParent == nodeGrandParent -> left)
	        {

	            TreeNode<x>* nodeAunt = nodeGrandParent -> right;

	            if (nodeAunt != NULL && nodeAunt -> color == RED)
	            {
	                nodeGrandParent -> color = RED;
	                nodeParent -> color = BLACK;
	                nodeAunt -> color = BLACK;
	                node = nodeGrandParent;
	            }

	            else
	            {
	            	if (node == nodeParent -> right)
	                {
	                    RotateLeft(nodeParent);
	                    node = nodeParent;
	                    nodeParent = node -> parent;
	                }

	                RotateRight(nodeGrandParent);
	                SwapColors(nodeParent, nodeGrandParent);
	                node = nodeParent;
	            }
	        }
	        else
	        {
	            TreeNode<x>* uncle_pt = nodeGrandParent -> left;

	            if ((uncle_pt != NULL) && (uncle_pt -> color == RED))
	            {
	                nodeGrandParent -> color = RED;
	                nodeParent -> color = BLACK;
	                uncle_pt -> color = BLACK;
	                node = nodeGrandParent;
	            }
	            else
	            {
	                if (node == nodeParent -> left)
	                {
	                    RotateRight(nodeParent);
	                    node = nodeParent;
	                    nodeParent = node -> parent;
	                }

	                RotateLeft(nodeGrandParent);
	                SwapColors(nodeParent, nodeGrandParent);
	                node = nodeParent;
	            }
	        }
	    }

	    root -> color = BLACK;
	}


	void SwapColors(TreeNode<x>* node1, TreeNode<x>* node2)
	{
		Color tempColor = node1 -> color;
		node1 -> color = node2 -> color;
		node2 -> color = tempColor;
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
	        point->parent -> left = leftPointer;
			}
	    else
			{
	        point->parent -> right = leftPointer;
			}

	    leftPointer -> right = point;
	    point -> parent = leftPointer;
	}

	// Function to insert a new node with given value
	void Insert(const int &newValue)
	{
		if(SearchNode(newValue) != nullptr)
		{
			cout << newValue << " is already in the tree.\n\n";
			return;
		}

		TreeNode<x>* node = CreateNewNode(newValue);

    // Do a normal BST insert
    root = InsertRecursive(root, node);

    if(node -> parent)
    {
    	cout << "Adding " << newValue << " to the Tree\n";
    }

    // fix Red Black Tree violations
    FixViolation(root, node);
	}

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


	void Delete(x value)
	{
		if(IsEmpty())
		{
			cout << "Sorry, nothing to delete, tree is empty.\n\n";
			return;
		}

		//Finding value in tree
		TreeNode<x>* deleteNode = SearchNode(value);

		//Returning if not found on tree
		if(deleteNode == nullptr)
		{
			cout << "Sorry, that value was not found in the tree and could not be deleted.\n\n";
			return;
		}

		//Delteting node if found
		DeleteHelper(deleteNode);
	}

	void DeleteHelper(TreeNode<x>* nodeToDelete)
	{
		cerr << "*void DeleteHelper(TreeNode<x>* nodeToDelete)\n";
		//If only node in list
		if(nodeToDelete == root && nodeToDelete -> left == nullptr && nodeToDelete -> right == nullptr)
		{
			delete root;
			root = nullptr;
			return;
		}

		//Saving nodeToDelete's color, needed to know if we need to call DeleteFix
		Color origrinalColor = nodeToDelete -> color;
		TreeNode<x>* xNode = nullptr;
		TreeNode<x>* yNode = nullptr;


		//Left child is null
		if(nodeToDelete -> left == nullptr)
		{
			cerr << "if(nodeToDelete -> left == nullptr)\n";
			xNode = nodeToDelete -> right;
			cerr << "xNode = nodeToDelete -> right;\n";
			TransplantNodes(nodeToDelete, xNode);
			cerr << "TransplantNodes(nodeToDelete, xNode);\n";
		}
		else if(nodeToDelete -> right == nullptr)
		{
			cerr << "else if(nodeToDelete -> right == nullptr)\n";
			xNode = nodeToDelete -> left;
			cerr << "xNode = nodeToDelete -> left;\n";

			TransplantNodes(nodeToDelete, xNode);
			cerr << "TransplantNodes(nodeToDelete, xNode);\n";
		}
		else
		{
			yNode = GetMinNode(nodeToDelete -> right);
      origrinalColor = yNode -> color;
      xNode = yNode -> right;
      if(yNode -> parent == nodeToDelete)
			{
        xNode->parent = yNode;
      }
			else
			{
        TransplantNodes(yNode, yNode -> right);
        yNode -> right = nodeToDelete -> right;
        yNode -> right -> parent = yNode;
      }

      TransplantNodes(nodeToDelete, yNode);
      yNode -> left = nodeToDelete -> left;
      yNode -> left -> parent = yNode;
      yNode -> color = nodeToDelete -> color;

		}//END else of if(nodeToDelete -> left == nullptr)

		if(origrinalColor == BLACK)
		{
			DeleteFix(xNode);
		}

	}

	void DeleteFix(TreeNode<x>* node)
	{
		TreeNode<x>* wNode;

		while(node != root && node -> color != RED)
		{
			//IS left child
			if(IsOnLeft(node))//CASE 1
			{
				wNode = GetSibling(node);

				if(wNode -> color == RED)
				{
					node -> parent -> right -> color = BLACK;
					node -> parent -> color = RED;

					RotateLeft(node -> parent);

					node -> parent -> right = wNode;
				}
			}//END if(IsOnLeft(node)) is LEFT child
			else if(wNode -> right -> color == BLACK && wNode -> left -> color == BLACK)//CASE 2
			{
				wNode -> color = RED;
				node = node -> parent;
			}//END else if(wNode -> right -> color == BLACK && wNode -> left -> color == BLACK)//CASE 2
			else if (wNode -> left -> color == BLACK)
			{
				wNode -> left -> color = BLACK;
				wNode -> color = RED;

				RotateRight(wNode);

				wNode = node -> parent -> right;
			}//else if (wNode -> left -> color == BLACK)
			else
			{
				wNode -> color = node -> color;
				node -> parent -> color = BLACK;
				wNode -> left -> color = BLACK;
				RotateRight(node -> parent);
				node = root;
			}//END else of if(IsOnLeft(node))//CASE 1
		}//END while(node != root && node -> color != RED)
	}

	TreeNode<x>* GetSibling(TreeNode<x>* node)
	{
		if(IsOnLeft(node))
		{
			return node -> parent -> right;
		}
		else //right is child
		{
			return node -> parent -> left;
		}
	}

	TreeNode<x>* GetMinNode(TreeNode<x>* node)
	{
	 while (node -> left != nullptr)
	 {
		 node = node -> left;
	 }
	 return node;
 }

	void TransplantNodes(TreeNode<x>* deleteNode, TreeNode<x>* replacementNode)
	{
		cerr << "TransplantNodes(TreeNode<x>* deleteNode, TreeNode<x>* replacementNode)\n";

		if(deleteNode -> parent == nullptr)
		{
			cerr << "if(deleteNode -> parent == nullptr)\n";
			root = replacementNode;
			cerr << "root = replacementNode;\n";
		}
		else if(IsOnLeft(deleteNode))
		{
			cerr << "else if(IsOnLeft(deleteNode))\n";
			deleteNode -> parent -> left = replacementNode;
			cerr << "deleteNode -> parent -> left = replacementNode;\n";
		}
		else
		{
			cerr << "else\n";
			deleteNode -> parent -> right = replacementNode;
			cerr << "deleteNode -> parent -> right = replacementNode;\n";
		}

		//If new node is null (we are deleting a leaf node)
		if(replacementNode != nullptr)
		{
			replacementNode -> parent = deleteNode -> parent;
			cerr << "replacementNode -> parent = deleteNode -> parent;\n";
		}

	}


	TreeNode<x>* GetSuccessor(TreeNode<x>* nodeToDelete)//helper function for delete.  d is node to delete
	{
		 TreeNode<x>* sp = nodeToDelete;
		 TreeNode<x>* successor = nodeToDelete;
		 TreeNode<x>* current = nodeToDelete -> right;

		 while(current != nullptr)
		 {
			 sp = successor;
			 successor = current;
			 current = current -> left;
		 }

		 if(successor != nodeToDelete -> right)
		 {
			 sp -> left = successor -> right;
			 successor -> right = nodeToDelete -> right;
		 }
		 return successor;
	}

	//Checks if the given node is a left child, retruns true if it is, returns false if it a right child or the root
	bool IsOnLeft(TreeNode<x>* node)
	{
		if(node -> parent != nullptr && node == node -> parent -> left)
		{
			return true;
		}
		else
		{
			return false;
		}
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

	void FixRedRed(TreeNode<x>* node)
	{
	    if (node == root)
	    {
	      node -> color = BLACK;
	      return;
	    }

	    TreeNode<x>* parent = node->parent;
	    TreeNode<x>* grandparent = parent->parent;
	    TreeNode<x>* aunt;

	    if(grandparent -> left == parent)
	    {
	    	aunt = grandparent -> right;
	    }
	    else
	    {
	    	aunt = grandparent -> left;
	    }

		if (parent -> color != BLACK)
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
						SingleLeftRotation(parent);
						ExchangeColors(node, grandparent);
					}

					SingleRightRotation(grandparent);
				}
				else
				{
					if(node -> parent -> left == node)
					{
						SingleRightRotation(parent);
						ExchangeColors(node, grandparent);
					}
					else
					{
						ExchangeColors(parent, grandparent);
					}

					SingleLeftRotation(grandparent);
				}//END else of if(parent -> parent -> left == parent)
			}//END else of if(aunt != NULL && aunt -> color == RED)
		}//END if (parent -> color != BLACK)
	}

	void FixBlackBlack(TreeNode<x>* node)
	{

	}

	TreeNode<x>* Successor(TreeNode<x>* node)
	{
	  TreeNode<x>* temp = node;

		while (temp -> left != NULL)
		{
		  temp = temp -> left;
		}

		return temp;
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

	void PreOrderHelper(TreeNode<x>* subRoot)
	{
		if (subRoot != NULL)
		{
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
		if (subRoot != NULL)
		{
			PostOrderHelper(subRoot -> left);

			PostOrderHelper(subRoot -> right);

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
		if (subRoot != NULL)
		{
			InOrderHelper(subRoot -> left);

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

private:
	TreeNode<x>* root;
	int numNodes;

	void ExchangeColors(TreeNode<x>* node1, TreeNode<x>* node2)
	{
		Color temp;
		temp = node1->color;
		node1->color = node2->color;
		node2->color = temp;
	}

	TreeNode<x>* SingleRightRotation(TreeNode<x>* temp)
	{
		TreeNode<x>* temp2 = temp -> left;

		temp -> left = temp2 -> right;

		temp2 -> right = temp;

		temp = temp2;

		temp2 = nullptr;

		return temp;
	}
	TreeNode<x>* SingleLeftRotation(TreeNode<x>* temp)
	{
		TreeNode<x>* temp2 = temp -> right;

		temp -> right = temp2 -> left;

		temp2 -> left = temp;

		temp = temp2;

		temp2 = nullptr;

		return temp;
	}
	TreeNode<x>* DoubleLeftRotation(TreeNode<x>* temp)
	{
		TreeNode<x>* temp2 = temp -> left;
		TreeNode<x>* temp3 = temp2 -> right;

		temp2 -> right = temp3 -> left;

		temp -> left = temp3;

		temp3 -> left = temp2;

		temp = SingleRightRotation(temp);

		return temp;
	}
	TreeNode<x>* DoubleRightRotation(TreeNode<x>* temp)
	{
		TreeNode<x>* temp2 = temp -> right;
		TreeNode<x>* temp3 = temp2 -> left;

		temp2 -> left = temp3 -> right;

		temp -> right = temp3;

		temp3 -> right = temp2;

		temp = SingleLeftRotation(temp);

		return temp;
	}

	void Restructure(TreeNode<x>* temp)
	{
		FixViolation(root, root);
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
