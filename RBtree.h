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
	//copy assignment operator
	RBtree& operator=(const RBtree& other)
	{
		if(this != &other)
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
            TreeNode<x>* uncle_pt = nodeGrandParent -> left;

            if((uncle_pt != nullptr) && (uncle_pt -> color == RED))
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
            }//END else of if((uncle_pt != nullptr) && (uncle_pt -> color == RED))
        }//END else of if(nodeParent == nodeGrandParent -> left)
    }//END while ((node != root) && (node -> color != BLACK) && (node -> parent -> color == RED))

    root -> color = BLACK;
	}

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

// deletes the given node
void DeleteNode(TreeNode<x>* nodeToDelete)
{
	TreeNode<x>* u = BSTreplace(nodeToDelete);

	// True when u and nodeToDelete are both black
	bool uvBlack = ((u == nullptr or u -> color == BLACK) and (nodeToDelete -> color == BLACK));
	TreeNode<x>* parent = nodeToDelete -> parent;

	if(u == nullptr)
	{
		// u is nullptr therefore nodeToDelete is leaf
		if(nodeToDelete == root)
		{
		// nodeToDelete is root, making root nullptr
		root = nullptr;
		}
		else
		{
			if(uvBlack)
			{
			  // u and v both black
			  // nodeToDelete is leaf, fix double black at nodeToDelete
			  FixBlackBlack(nodeToDelete);
			}
			else
			{
				// u or nodeToDelete is red
				if(GetSibling(nodeToDelete) != nullptr)
				{
					// sibling is not nullptr, make it red"
					GetSibling(nodeToDelete) -> color = RED;
				}
			}//END if(uvBlack)

			// delete nodeToDelete from the tree
			if(nodeToDelete -> IsLeftChild())
			{
				parent -> left = nullptr;
			}
			else
			{
				parent -> right = nullptr;
			}//END if(nodeToDelete -> IsLeftChild())
		}
		delete nodeToDelete;
		return;
	}//END if(u == nullptr)

	if(nodeToDelete -> left == nullptr or nodeToDelete -> right == nullptr)
	{
		// nodeToDelete has 1 child
		if(nodeToDelete == root)
		{
			// nodeToDelete is root, assign the value of u to nodeToDelete, and delete u
			nodeToDelete -> key = u -> key;
			nodeToDelete -> left = nodeToDelete -> right = nullptr;
			delete u;
		}//END if(nodeToDelete == root)
		else
		{
			// Detach nodeToDelete from tree and move u up
			if(nodeToDelete -> IsLeftChild())
			{
				parent -> left = u;
			}
			else
			{
				parent -> right = u;
			}

			delete nodeToDelete;
			u -> parent = parent;

			if(uvBlack)
			{
				// u and nodeToDelete both black, fix double black at u
				FixBlackBlack(u);
			}
			else
			{
				// u or nodeToDelete red, color u black
				u -> color = BLACK;
			}
		}//END else of if(nodeToDelete == root)
		return;
	}//if(nodeToDelete -> left == nullptr or nodeToDelete -> right == nullptr)

	// v has 2 children, swap values with successor and recurse
	ExchangeValues(u, nodeToDelete);
	DeleteNode(u);
}//END void DeleteNode(TreeNode<x>* nodeToDelete)

void FixBlackBlack(TreeNode<x>* xNode) {
if(xNode == root)
// Reached root
return;

TreeNode<x>* sibling = GetSibling(xNode), *parent = xNode -> parent;
if(sibling == nullptr)
{
// No sibiling, double black pushed up
FixBlackBlack(parent);
}
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
rightRotate(parent);
}
else
{
// right case
leftRotate(parent);
}
FixBlackBlack(xNode);
}
else
{
// Sibling black
if(sibling -> HasRedChild())
{
// at least 1 red children
if(sibling -> left != nullptr and sibling -> left -> color == RED) {
if(sibling -> IsLeftChild())
{
// left left
sibling -> left -> color = sibling -> color;
sibling -> color = parent -> color;
rightRotate(parent);
}
else
{
// right left
sibling -> left -> color = parent -> color;
rightRotate(sibling);
leftRotate(parent);
}
}
else
{
if(sibling -> IsLeftChild())
{
// left right
sibling -> right -> color = parent -> color;
leftRotate(sibling);
rightRotate(parent);
}
else
{
// right right
sibling -> right -> color = sibling -> color;
sibling -> color = parent -> color;
leftRotate(parent);
}
}
parent -> color = BLACK;
}
else
{
// 2 black children
sibling -> color = RED;
if(parent -> color == BLACK)
FixBlackBlack(parent);
else
parent -> color = BLACK;
}
}
}
}

void ExchangeValues(TreeNode<x>* u, TreeNode<x>* v)
{
	x temp;
	temp = u -> key;
	u -> key = v -> key;
	v -> key = temp;
}

TreeNode<x>* BSTreplace(TreeNode<x>* xNode)
{
	// when node have 2 children
	if((xNode -> left != nullptr) && (xNode -> right != nullptr))
	{
		return successor(xNode -> right);
	}


	// when leaf
	if((xNode -> left == nullptr) && (xNode -> right == nullptr))
	{
		return nullptr;
	}


	// when single child
	if(xNode -> left != nullptr)
	{
		return xNode -> left;
	}
	else
	{
		return xNode -> right;
	}
}



TreeNode<x>* successor(TreeNode<x>* xNode)
{
TreeNode<x>* temp = xNode;

while (temp -> left != nullptr)
  temp = temp -> left;

return temp;
}



// left rotates the given node
void leftRotate(TreeNode<x>* xNode) {
  // new parent will be node's right child
  TreeNode<x>* nParent = xNode -> right;

  // update root ifcurrent node is root
  if(xNode == root)
    root = nParent;

  xNode -> moveDown(nParent);

  // connect x with new parent's left element
  xNode -> right = nParent -> left;
  // connect new parent's left element with node
  // ifit is not nullptr
  if(nParent -> left != nullptr)
    nParent -> left -> parent = xNode;

  // connect new parent with x
  nParent -> left = xNode;
}

void rightRotate(TreeNode<x>* xNode) {
  // new parent will be node's left child
  TreeNode<x>* nParent = xNode -> left;

  // update root ifcurrent node is root
  if(xNode == root)
    root = nParent;

  xNode -> moveDown(nParent);

  // connect x with new parent's right element
  xNode -> left = nParent -> right;
  // connect new parent's right element with node
  // ifit is not nullptr
  if(nParent -> right != nullptr)
    nParent -> right -> parent = xNode;

  // connect new parent with x
  nParent -> right = xNode;
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

			//Returning ifnot found on tree
			if(deleteToNode == nullptr)
			{
				cout << "Sorry, that value was not found in the tree and could not be deleted.\n\n";
				return;
			}

			//Delteting node iffound
			DeleteNode(deleteToNode);
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
					}

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
					}

					RotateLeft(grandparent);
				}//END else of if(parent -> parent -> left == parent)
			}//END else of if(aunt != nullptr && aunt -> color == RED)
		}//END if(parent -> color != BLACK)
	}

	TreeNode<x>* Successor(TreeNode<x>* node)
	{
	  TreeNode<x>* temp = node;

		while (temp -> left != nullptr)
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



private:
	TreeNode<x>* root;
	int numNodes;


	void PreOrderHelper(TreeNode<x>* subRoot)
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
	void PostOrderHelper(TreeNode<x>* subRoot)
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

	void ExchangeColors(TreeNode<x>* node1, TreeNode<x>* node2)
	{
		Color temp;
		temp = node1 -> color;
		node1 -> color = node2 -> color;
		node2 -> color = temp;
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


#endif/* RBTREE_H_ */
