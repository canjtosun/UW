//Can Tosun
//Jolly Banker
//This file contains BSTree implementation



#include "BSTree.h"
#include <iostream>

using namespace std;

//assign to nullptr
BSTree::BSTree()
{
	root = nullptr;
}

//call empty method for destruction
BSTree::~BSTree()
{
	void Empty();
}

//if root is empty, then there is nothing there
bool BSTree::isEmpty()const
{
	return root == nullptr;
}

//Empty the whole tree
void BSTree::Empty()
{
	Empty(root);
}

//empty helper method
//go each left and right node and remove from bottom to top
void BSTree::Empty(Node* root)
{
	if (root != nullptr)
	{
		Empty(root->left);
		Empty(root->right);
		delete root->pAcct;
		delete root;
	}
}

//insert method, inserting to the tree
bool BSTree::Insert(Account* acc)
{
	//if root is not epty
	//then insert
	if (root != nullptr)
	{
		Insert(acc, root);
	}
	//if root is empty
	//then create new node and assign it to new root
	//and left and right children are null
	else
	{
		root = new Node;
		root->pAcct = acc;
		root->left = nullptr;
		root->right = nullptr;
	}
	return true;
}

//insert helper
bool BSTree::Insert(Account* acc, Node* root)
{
	//if acc id is less the root pointer acc id
	//then insert left because small goes left
	if (acc->getID() < root->pAcct->getID())
	{
		//insert left
		if (root->left != nullptr)
		{
			Insert(acc, root->left);
		}
		//or create new node and assign children nullptr
		else
		{
			root->left = new Node;
			root->left->pAcct = acc;
			root->left->left = nullptr;
			root->right->right = nullptr;
		}
	}

	//if acc id is NOT less the root pointer acc id
	//then insert right 
	else if (acc->getID() > root->pAcct->getID())
	{
		//insert right
		if (root->right != nullptr)
		{
			Insert(acc, root->right);
		}
		//or create new node and assign children nullptr
		else
		{
			root->right = new Node;
			root->right->pAcct = acc;
			root->right->left = nullptr;
			root->right->right = nullptr;
		}
	}
	return true;
}

//display tree
void BSTree::Display()const
{
	Display(root);
}

//Display Helper
//goes until the last node
//inorder traversal
void BSTree::Display(Node* root)const
{
	if (root != nullptr)
	{
		Display(root->left);
		cout << *(root->pAcct) << endl;
		Display(root->right);
	}
}

//search/retrieve tree
bool BSTree::Retrieve(const int& id, Account*& acc) const
{
	return Retrieve(id, acc, root);
}

//retrieve tree helper
bool BSTree::Retrieve(const int& id, Account*& acc, Node* root)const
{
	//if root is not null
	if (root != nullptr)
	{
		//then if accId number is equal to other accID number
		if (id == root->pAcct->getID())
		{
			//find and return true;
			acc = root->pAcct;
			return true;
		}

		//if accId number is less than other accID number
		//then recursively check all left children
		//otherwise check all right children
		//retrieve returns true;
		if (id < root->pAcct->getID())
		{
			return Retrieve(id, acc, root->left);
		}
		else
		{
			return Retrieve(id, acc, root->right);
		}
	}
	//if no acc there (id) then return false
	return false;
}