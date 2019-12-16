
#pragma once
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

class SkipList
{
private:

	class SNode {

	public:
		explicit SNode(int data); // SNoide stores int as data
		int data;  // data for SNode
		SNode* next; // link to next SNode
		SNode* prev;  // link to prev SNode
		SNode* upLevel;  // link to up one level
		SNode* downLevel;  // link to down one level

	};

	// depth of SkipList, levels are 0 to depth-1
	int depth;
	// array of depth SNode* objects as frontGuards linking levels
	// if depth = 2, we'd have frontGuards[0] and frontGuards[1]
	SNode** frontGuards;
	// array of depth SNode* objects as rearGuards linking levels
	SNode** rearGuards;
	// given a SNode, place it before the given NextNode
	void addBefore(SNode* newNode, SNode* nextNode);
	// return true 50% of time,
	// each node has a 50% chance of being at higher level
	bool alsoHigher() const;
	SNode* EraseHelp(SNode* curr); // helper method for destructor 


public:

	explicit SkipList(int depth = 1); // default SkipList has depth of 1, just one doubly-linked list
	virtual ~SkipList(); // destructor
	bool Add(int data);  // return true if successfully added, no duplicates
	bool Remove(int data);  // return true if successfully removed
	bool Contains(int data);  // return true if found in SkipList
	friend ostream& operator<<(ostream& os, const SkipList& list); //op overload

};


