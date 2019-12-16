#include "skiplist.h"
#include <iostream>
#include <time.h>
#include <limits.h>

//Constructor for SNode: set the data,
//set all other pointers to nullptr
SkipList::SNode::SNode(int data)
{
	this->data = data;
	next = prev = upLevel = downLevel = nullptr;
	
}


/*
first initializing
creating a new Node as frontguard value of int min
creating a new Node as rearguard value of int man
these are fron and back of the list
and then we are connecting them to each other
and initilaze to as an up/down level array
*/
SkipList::SkipList(int depth)
{
	this->depth = depth;
	frontGuards = new SNode * [depth];
	rearGuards = new SNode * [depth];

	for (int i = 0; i < depth; ++i)
	{
		SNode* frontGuard = new SNode(INT_MIN); //front guard
		SNode* rearGuard = new SNode(INT_MAX); // rear guard

		//connecting hem to each other linear
		frontGuard->next = rearGuard;
		rearGuard->prev = frontGuard;
		frontGuards[i] = frontGuard;
		rearGuards[i] = rearGuard;

		//connecting guards to each oether vertically
		if (i > 0) {
			frontGuards[i - 1]->upLevel = frontGuards[i];
			frontGuards[i]->downLevel = frontGuards[i - 1];
			rearGuards[i - 1]->upLevel = rearGuards[i];
			rearGuards[i]->downLevel = rearGuards[i - 1];
		}
	}
}

/*
helper method for distructor
we are deleting every node in the list
recursively and initilaze all of them to
nullpointer and at the end delete curr too
and return curr as nothing
*/
SkipList::SNode* SkipList::EraseHelp(SNode* curr)
{
	if (curr == nullptr)
		return nullptr;

	curr->next = EraseHelp(curr->next);
	curr->prev = nullptr;
	curr->upLevel = nullptr;
	curr->downLevel = nullptr;
	delete curr;
	curr = nullptr;

	return curr;

}

/*
removing each depth with helper method
removing arrays at the front and
at the end and assigning to nullptr
*/
SkipList::~SkipList()
{
	for (int i = 0; i < depth; ++i) {
		frontGuards[i] = EraseHelp(frontGuards[i]);
		rearGuards[i] = nullptr;
	}

	delete[] frontGuards;
	delete[] rearGuards;
	frontGuards = nullptr;
	rearGuards = nullptr;
}


/*
this is just coin toss for going
upper level or not.
*/
bool SkipList::alsoHigher() const
{
	if (rand() %2 == 1)
		return true;

	return false;
}

/*
Contain method starts from top left oLogN
iterating to the bottom level and checking each node.
if found, return true, else iterate to bottom.
if not found, return false;

*/
bool SkipList::Contains(int data)
{
	SNode* curr = frontGuards[depth-1];
	while (curr) {
		while (curr->next->data < data) {
			curr = curr->next;
		}
		if (curr->next->data == data)
			return true;
		curr = curr->downLevel;
	}
	return false;
	
}


/*
assign next to to head as frontguard[0]
and iterate untill the end or until
we find the bigger data and stop there
and connect these Nodes to each other
*/
void SkipList::addBefore(SNode* newNode, SNode* nextNode)
{

	while (nextNode->data < newNode->data) {
		nextNode = nextNode->next;
	}

	nextNode->prev->next = newNode;
	newNode->prev = nextNode->prev;
	newNode->next = nextNode;
	nextNode->prev = newNode;

}

/*
Add method explaining line by line
*/

bool SkipList::Add(int data)
{
	//we always at the bottom so curr at bottom frontguard
	SNode* curr = frontGuards[0]; 

	//iterating untill nullptr or smaller value
	while (curr->next != nullptr && curr->data < data)
		curr = curr->next;

	//if duplicate, return false and dont add
	if (curr->data == data)
		return false;

	//create a new node and add there ascending order
	SNode* newNode = new SNode(data);
	addBefore(newNode, curr);

	//index 2 means bottom level +1
	int index = 2;

	//as long as not passing the depth and coint toss 1
	while (index <= depth && alsoHigher())
	{
		//create a new node name newUpper
		SNode* newUpper = new SNode(data); 
		curr = newNode;
		//as long as newnode upper level null
		//iterate backward to front
		while (curr->upLevel == nullptr)
		{
			curr = curr->prev; 
		}
		//add the value to upper level 
		//and make the connections
		addBefore(newUpper, curr->upLevel);
		newUpper->downLevel = newNode;
		newNode->upLevel = newUpper;
		newNode = newUpper;
		++index; //increase index
	}
	
	return true;
}

/*
removing is similar to contain method
starting from top left
explaining line by line
*/

bool SkipList::Remove(int data)
{
	//start from top left
	SNode* curr = frontGuards[depth - 1];
	//iterating until find the value, if we find
	//stop the loop. otherwise going to bottom
	while (curr) {
		while (curr->next->data < data) {
			curr = curr->next;
		}
		if (curr->next->data == data)
			break;
		curr = curr->downLevel;
	}

	//if not, return false
	if(!curr)
		return false;

	//creating another node for found
	//iterating to next one
	SNode* found = curr->next;

	/*
	as long as found node happens
	deleting that and connecting rest of the
	nodes to each other and handling memory leak
	assigning them to nullptr and at the end
	removing the found node too
	*/

	while (found) {
		SNode* temp = found->downLevel;
		found->prev->next = found->next;
		found->next->prev = found->prev;
		found->prev = nullptr;
		found->next = nullptr;
		found->downLevel = nullptr;
		found->upLevel = nullptr;
		delete found;
		found = nullptr;
		found = temp;
	}
	return true;
}

//overloading operator/ printing start top left
ostream& operator<<(ostream& os, const SkipList& list)
{
	for (int i = list.depth - 1; i >= 0; --i)
	{
		SkipList::SNode* curr = list.frontGuards[i];
		os << "Level: " << i << " -- ";

		while (curr != nullptr)
		{
			os << curr->data << ", ";
			curr = curr->next;
		}
		os << endl;
	}

	return os;
}
