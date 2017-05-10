//*******************************************************************************************************************************************************************//
//***************************************************************************************************************************//
//																															*//
// File name : BSTMUSIC.cpp																									*//
//																															*//
// Author: Ajinkya Nawarkar    		                	 date created: 09 / 25 / 2016										*//
//														 last updated : 11 / 21 / 2016										*//
//																															*//
// Program Description : This program defines the methods for the BST class													*//
//																															*//
//***************************************************************************************************************************//
//*********************************************************************************************************************************************************************//

//Binary Search Tree Program

#include <iostream>
#include <cstdlib>

using namespace std;

class BST
{
private:
	struct TreeNode
	{
		TreeNode* left;
		TreeNode* right;
		int data;
	};
	TreeNode* root;

public:
	BST()
	{
		root = NULL;
	}

	bool isEmpty() const { return root == NULL; }
	void print_tree();
	void printtree(TreeNode*);
	void insert(int);
	void remove(int);
};

// Smaller elements go left
// larger elements go right
void BST::insert(int d)
{
	TreeNode* t = new TreeNode;
	TreeNode* parent_current;
	t->data = d;
	t->left = NULL;
	t->right = NULL;
	parent_current = NULL;

	// is this a new tree?
	if (isEmpty()) 
		root = t;
	else
	{
		//Note: ALL insertions are as leaf nodes
		TreeNode* current;
		current = root;
		// Find the Node's parent
		while (current)
		{
			parent_current = current;
			if (t->data > current->data) 
				current = current->right;
			else 
				current = current->left;
		}

		if (t->data < parent_current->data)
			parent_current->left = t;
		else
			parent_current->right = t;
	}
}

void BST::remove(int d)
{
	//Locate the element
	int flag = 0;
	if (isEmpty())
	{
		cout << " This Tree is empty! " << endl;
		return;
	}

	TreeNode* current;
	TreeNode* parent=NULL;
	current = root;

	while (current != NULL)
	{
		if (current->data == d)
		{
			flag = 1;
			break;
		}
		else
		{
			parent = current;
			if (d > current->data) 
				current = current->right;
			else 
				current = current->left;
		}
	}
	if (flag==0)
	{
		cout << " Data not found! " << endl;
		return;
	}


	// 3 cases :
	// 1. We're removing a leaf node
	// 2. We're removing a node with a single child
	// 3. we're removing a node with 2 children

	// Node with single child
	if ((current->left == NULL && current->right != NULL) || (current->left != NULL
		&& current->right == NULL))
	{
		if (current->left != NULL && current->right == NULL)
		{
			if (parent->left == current)
			{
				parent->left = current->left;
				delete current;
			}
			else
			{
				parent->right = current->left;
				delete current;
			}
		}
		else // right child present, no left child
		{
			if (parent->left == current)
			{
				parent->left = current->right;
				delete current;
			}
			else
			{
				parent->right = current->right;
				delete current;
			}
		}
		return;
	}

	//We're looking at a leaf node
	if (current->left == NULL && current->right == NULL)
	{
		if (parent->left == current) parent->left = NULL;
		else parent->right = NULL;
		delete current;
		return;
	}


	//Node with 2 children
	// replace node with smallest value in right subtree
	if (current->left != NULL && current->right != NULL)
	{
		TreeNode* chkr;
		chkr = current->right;
		if ((chkr->left == NULL) && (chkr->right == NULL))
		{
			current = chkr;
			delete chkr;
			current->right = NULL;
		}
		else // right child has children
		{
			//if the node's right child has a left child
			// Move all the way down left to locate smallest element

			if ((current->right)->left != NULL)
			{
				TreeNode* lcurr;
				TreeNode* lcurrp;
				lcurrp = current->right;
				lcurr = (current->right)->left;
				while (lcurr->left != NULL)
				{
					lcurrp = lcurr;
					lcurr = lcurr->left;
				}
				current->data = lcurr->data;
				delete lcurr;
				lcurrp->left = NULL;
			}
			else
			{
				TreeNode* tmp;
				tmp = current->right;
				current->data = tmp->data;
				current->right = tmp->right;
				delete tmp;
			}

		}
		return;
	}

}

void BST::print_tree()
{
	printtree(root);
}

void BST::printtree(TreeNode* p)
{
	if (p != NULL)
	{
		if (p->left) printtree(p->left);
		cout << " " << p->data << " ";
		if (p->right) printtree(p->right);
	}
	else return;
}


int main()
{
	BST b;
	int ch, tmp, tmp1;
	while (1)
	{
		cout << endl << endl;
		cout << " Binary Search Tree Operations " << endl;
		cout << " ----------------------------- " << endl;
		cout << " 1. Insertion/Creation " << endl;
		cout << " 2. In-Order Traversal " << endl;
		cout << " 3. Pre-Order Traversal " << endl;
		cout << " 4. Post-Order Traversal " << endl;
		cout << " 5. Removal " << endl;
		cout << " 6. Exit " << endl;
		cout << " Enter your choice : ";
		cin >> ch;
		switch (ch)
		{
		case 1: cout << " Enter Number to be inserted : ";
			cin >> tmp;
			b.insert(tmp);
			break;
		case 2: cout << endl;
			cout << " In-Order Traversal " << endl;
			cout << " -------------------" << endl;
			b.print_tree();
			break;		
		case 3: cout << " Enter data to be deleted : ";
			cin >> tmp1;
			b.remove(tmp1);
			break;
		case 4:
			return 0;

		}
	}
}