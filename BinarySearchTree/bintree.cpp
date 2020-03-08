// -------------------------nodedata.cpp ------------------------------
// Can Tosun CSS 343 C
// Jan 26 2020
// Feb 1, 2020 - Date of Last Modification
// ---------------------------------------------------------------------
// Purpose - This file contains all implementation about ->
// Constructor, Copy Constructor, Destructor
// insert no duplicate values to tree correct order
// find the given data and return if data is in the tree
// Empty the tree, find the heigh of the given data
// and overloading the assignment and comparison operators
// ----------------------------------------------------------------------

#include <iostream>
#include <string>
#include <algorithm>
#include "nodedata.h"
#include "bintree.h"

using namespace std;

//========================Default-Constructor=========================
// Creates a BinTree object with a null root.

// Preconditions:  None.	
// Postconditions: This BinTree object has been instantiated, and
//				root points to nullptr 		  
//==================================================================== 
BinTree::BinTree()
{
	root = nullptr;
}

//========================Copy-Constructor============================
// Copies obj BinTree object into this.

// Preconditions:  root points to NULL
// Postconditions: obj is copied into *this.
//====================================================================
BinTree::BinTree(const BinTree& obj)
{
	root = nullptr;
	*this = obj;
}

//========================Destructor==================================
// Cleans up and deallocates all dynamic memory. 

// Preconditions: root is pointing to NULL	
// Postconditions: This BinTree memory has been deallocated.
//====================================================================
BinTree::~BinTree()
{
	makeEmpty();
	root = nullptr;
}

//========================Destructor==================================
// Checks if the BinTree is empty 

// Preconditions: root points to NULL
// Postconditions: returns True if the tree is empty
//====================================================================
bool BinTree::isEmpty() const
{
	return root == nullptr;
}

//========================makeEmpty===================================
// Deallocates this BinTree and sets its root to NULL
// isEmpty() would then return true.

// Preconditions: root points to NULL
// Postconditions: All memory has been deallocated, root is NULL.
//==================================================================== 
void BinTree::makeEmpty()
{
	makeEmptyHelper(root);
}

//========================makeEmptyHelper=============================
// Deletes the nodes recursively and delete node and left-right

// Preconditions: root is not NULL.	 
// Postconditions: Empty the tree
//==================================================================== 
void BinTree::makeEmptyHelper(Node*&node)
{
	if (node != nullptr)
	{
		makeEmptyHelper(node->left);
		makeEmptyHelper(node->right);
		delete node->data;
		node->data = nullptr;
		node->left = node->right = nullptr;
		delete node;
		node = nullptr;
	}
}

//========================insert======================================
// Inserts the given/taken data to the tree. No duplicate allowed.
// Avoid duplicates and create a binary search tree.

// Preconditions: root points to NULL  
// Postconditions: Returns true if data is inserted in tree.
//		   If the data is in the tree, then return false;
//====================================================================
bool BinTree::insert(NodeData* newData)
{
	return insertHelper(newData, root);
}

//========================insert======================================
// A helper method for inserting the data to the right place.
// Inserts the given/taken data to the tree. No duplicate allowed.
// Avoid duplicates and create a binary search tree. Insert only unique
// data recursively.

// Preconditions: root points to NULL  
// Postconditions: Returns true if data is inserted in tree.
//		   If the data is in the tree, then return false;
//====================================================================
bool BinTree::insertHelper(NodeData* newData, Node*& root)
{
	if (!newData)
		return false;
	if(root == nullptr)
	{
		root = new Node();
		root->data = newData;
		root->left = nullptr;
		root->right = nullptr;
		return true;
	}
	
	else if (*root->data == *newData)
		return false;

	else if (*newData < *root->data) //insert to the left
		return	insertHelper(newData, root->left);

	else if (*newData > *root->data) // insert to the right
		return	insertHelper(newData, root->right);
}

//========================retrieve==================================== 
// Finds the provided object in this tree. Returns NULL if the item
// is not found.
// 
// Preconditions: call retrieveHelper
// Postconditions: Returns true if the data found,
//	 		return false otherwise 		 
//==================================================================== 
bool BinTree::retrieve(const NodeData& pointData, NodeData*& data) const
{
	return retrieveHelper(pointData,data,root);
}

//========================retrieveHelper==============================
// A helper method for retrieve. It recursively finds the provided
// object in this tree. Returns NULL if the item is not found.
// 
// Preconditions: The node is not NULL
// Postconditions: Find the data and Returns true if the data found,
//	 			return false otherwise.	 		 
//====================================================================													
bool BinTree::retrieveHelper(const NodeData& pointData, NodeData*& data, Node* root) const
{													//data will be garbage
	if (root != nullptr)
	{
		if (pointData == *root->data)
		{
			*root->data = pointData;
			return true;
		}
		else if (pointData < *(root->data))
		{
			return retrieveHelper(pointData, data, root->left);
		}
		else
		{
			return retrieveHelper(pointData, data, root->right);
		}
	}
	return false;
}

//========================inorderHelper===============================
// A helper method that recursively prints the tree in-order traversal	
//
// Preconditions: root is not NULL.
// Postconditions: Memorize the tree in-order traversal
// (Left,Root,Right)
//==================================================================== 
void BinTree::inorderHelper(Node* root)const
{
	if (root == nullptr)
		return;

	inorderHelper(root->left);
	cout << *root->data << " ";
	inorderHelper(root->right);
}

//========================getHeight===============================
// Find the height of a given value in the tree. the height of a 
//node at a leaf is 1, height of a node at the next level is 2, 
//and so on.  The height of a value not found is zero. 	
//
// Preconditions: calling the helper method
// Postconditions: return a height of the given value
//===================================================================
int BinTree::getHeight(const NodeData& data) const
{
	return getHeightHelper(root, data, false);
}

//========================getHeightHelper===============================
// Find the height of a given value in the tree. the height of a 
//node at a leaf is 1, height of a node at the next level is 2, 
//and so on.  The height of a value not found is zero. 	
//
// Preconditions: root is not null
// Postconditions: return a height of the given value
//===================================================================
int BinTree::getHeightHelper(Node* root, const NodeData& data, bool found)const
{
	if (root == nullptr) //if not found return false (0);
		return false;

	else if (*root->data == data) //if found return true (1)
		found = true; 

	else if (root->right == nullptr && root->left == nullptr)
		return found; //if leaf return found which is 1

	//check recursively, return the highest value + 1
	return max(getHeightHelper(root->left,data,found), 
		getHeightHelper(root->right,data, found)) + found;	
}

//========================bsTreeToArrayHelper=======================
// Fill an array of Nodedata* by using an inorder traversal
// of the tree. Same as in-order helper function but needs to
// keep track of right index
//
// Preconditions: root is not null
// Postconditions: Memorize the tree in-order traversal
// (Left,Root,Right) and pushes in order traversal to an array
//===================================================================
void BinTree::bstreeToArrayHelper(NodeData* arr[], Node* root, int &index)
{
	if (root == nullptr)
		return;

	bstreeToArrayHelper(arr, root->left, index);
	arr[index] = new NodeData();
	*arr[index++] = *root->data;
	bstreeToArrayHelper(arr, root->right, index);
}

//========================bsTreeToArray=============================
// Fill an array of Nodedata* by using an inorder traversal
// of the tree. Same as in-order helper function but needs to
// keep track of right index
//
// Preconditions: root is not null and index must be 0
// Postconditions: Memorize the tree in-order traversal
// (Left,Root,Right) and pushes in order traversal to an array
// After pushes data, cleans the tree(empty tree)
//===================================================================
void BinTree::bstreeToArray(NodeData* arr[])
{
	int index = 0;
	bstreeToArrayHelper(arr, root, index);
	makeEmpty();
}

//========================arrayToBSTreeHelper=======================
// Builds a balanced BinTree from a sorted array of NodeData* leaving
//the array filled with NULLs.The root(recursively) is
//at(low + high) / 2 where low is the lowest subscript 
//of the array range and high is the highest.
//
// Preconditions: starting integer cannot be bigger than ending
// Postconditions: Pushes the array to the tree as Balanced as
// possible. 
//===================================================================
void BinTree::arrayToBSTreeHelper(NodeData* arr[], int start, int end)
{
	if (start > end)
		return;

	int mid = (start + end) / 2;  //find mid value
	insert(arr[mid - 1]);

	arrayToBSTreeHelper(arr, start, mid - 1);
	arrayToBSTreeHelper(arr, mid+1, end);
}

//========================arrayToBSTree==========================
// Builds a balanced BinTree from a sorted array of NodeData* leaving
//the array filled with NULLs.The root(recursively) is
//at(low + high) / 2 where low is the lowest subscript 
//of the array range and high is the highest.
//
// Preconditions: start and end integers for tracking index
// Postconditions: Pushes the array to the tree as Balanced as
// possible. 
//===================================================================
void BinTree::arrayToBSTree(NodeData* arr[])
{
	int start = 1;
	int end = 0;

	//finding the array size
	while (arr[end] != 0)
		end++;

	arrayToBSTreeHelper(arr, start, end);
}

//======================operator<<================================
// Overloaded  output operator for Binary search tree.
// 
// Preconditions: root must be point to first value 		  
// Postconditions: calling the inorderHelper and prints out
// with output streamer in-order traversal
//===================================================================
ostream& operator << (ostream& output, const BinTree& obj)
{
	obj.inorderHelper(obj.root);
	output << endl;
	return output;
}

//========================operator(=)=================================
// Overloaded assignment operator.
// 
// Preconditions: rhs(righ hand side) must point first node or NULL 		
// Postconditions: rhs is copied into this. then return this	   
//==================================================================== 
BinTree& BinTree::operator=(const BinTree& rhs)
{
	if (this != &rhs) // this line fails to detect that "this" is in fact pointing to the same memory location as "rhs" and ends up deleting both "this" and "rhs"
	{
		this->makeEmpty(); // deletes both "this" and "rhs" because if statement fails to detect duplicate memory location
		this->root = copyFunction(rhs.root);
	}
	return *this;
}
//========================operator(==)=================================
// Checks if 2 trees are equal. If they have same data and same shape
// returns true. if it is not return false
// 
// Preconditions: rhs(righ hand side) must point first node or NULL 		
// Postconditions: If they have same data and same shape
// returns true. if it is not return false  
//==================================================================== 
bool BinTree::operator==(const BinTree& obj) const
{
	return isEqual(root, obj.root);
}

//========================operator(!=)=================================
// Checks if 2 trees are not equal. Same data and same shape
// 
// Preconditions: rhs(righ hand side) must point first node or NULL 		
// Postconditions: false is returned if the trees have the same data, 
// same shape. otherwise return true
//==================================================================== 
bool BinTree::operator!=(const BinTree& obj) const
{
	//we already overloaded ==, no need duplicate code
	return !(*this == obj);
}

//========================copyFunction=================================
// Crates a new root and clones everything to another tree and return
// new tree.
// 
// Preconditions: root is not NULL 		
// Postconditions: Clones the tree and return 
//==================================================================== 
BinTree::Node* BinTree::copyFunction(Node* root)
{
	if (root == nullptr)
		return root;

	else
	{
		Node* newNode = new Node();
		//creating a new Node Data for deep copy
		newNode->data = new NodeData();
		*newNode->data = *root->data;
		newNode->left = copyFunction(root->left);
		newNode->right = copyFunction(root->right);
		return newNode;
	}
}

//========================isEqual=================================
// A recursive method that compares two trees. Returns true
// if they are same. 
// 
// Preconditions: lhs(left hand side) and rhs(right hand side)
// are not NULL 		
// Postconditions: returns true if same, otherwise returns false 
//==================================================================== 
bool BinTree::isEqual(Node* lhs,Node* rhs)const
{
	if (lhs == nullptr && rhs == nullptr)
		return true;

	else if (lhs == nullptr && rhs != nullptr)
		return false;
	else if (lhs != nullptr && rhs == nullptr)
		return false;

	//recursive comparison
	else
	{	
		if (*lhs->data == *rhs->data && isEqual(lhs->left, rhs->left) && isEqual(lhs->right, rhs->right))
			return true;
		else
			return false;
	}
}


//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}


//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}








