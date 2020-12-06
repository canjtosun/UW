#pragma once
#include "Account.h"

using namespace std;


class BSTree
{
public:
	BSTree();
	~BSTree();

	bool Insert(Account*);
	bool Retrieve(const int&, Account*&) const;
	void Display() const;
	void Empty();
	bool isEmpty() const;

private:
	struct Node
	{
		Account* pAcct;
		Node* right;
		Node* left;
	};
	Node* root;

	bool Insert(Account*, Node* root);
	bool Retrieve(const int&, Account*&, Node* root)const;
	void Display(Node* root)const;
	void Empty(Node* root);

};