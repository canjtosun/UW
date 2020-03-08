// ------------------------------------------------ bintree.h -------------------------------------------------------
// Can Tosun CSS 343 C
// Jan 26 2020
// Feb 1, 2020 - Date of Last Modification
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The header file has the extension of .h 
// and contains class definitionsand functions.
// --------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "nodedata.h"

using namespace std;


class BinTree {				// you add class/method comments and assumptions

	friend ostream& operator << (ostream& output, const BinTree& data);

public:
	BinTree();								// constructor
	BinTree(const BinTree& obj);				// copy constructor
	~BinTree();								// destructor, calls makeEmpty	
	bool isEmpty() const;					// true if tree is empty, otherwise false
	void makeEmpty();						// make the tree empty so isEmpty returns true
	BinTree& operator=(const BinTree&);
	bool operator==(const BinTree&) const;
	bool operator!=(const BinTree&) const;
	bool insert(NodeData*);
	bool retrieve(const NodeData& pointData, NodeData*& data) const;
	void displaySideways() const;			// provided below, displays the tree sideways
	int getHeight(const NodeData&) const;
	void bstreeToArray(NodeData* []);
	void arrayToBSTree(NodeData* []);


private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree

// utility functions
	
//helper methods
	void inorderHelper(Node* root) const;   
	void sideways(Node*, int) const;			// provided below, helper for displaySideways()
	void makeEmptyHelper(Node*&root);
	bool insertHelper(NodeData* newData, Node*& root);
	bool retrieveHelper(const NodeData& pointData, NodeData*& data, Node* root)const;
	int getHeightHelper(Node* root, const NodeData& data, bool found)const;
	void bstreeToArrayHelper(NodeData* [], Node* root, int &index);
	Node* copyFunction(Node* root);
	bool isEqual(Node* lhs,Node* rhs)const;
	void arrayToBSTreeHelper(NodeData* arr[], int start, int end);
	
};

