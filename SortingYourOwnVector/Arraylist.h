#ifndef _ARRAY_LIST_H
#define _ARRAY_LIST_H

#include "listInterface.h"
#include <iostream>
#include <fstream>
#include <string>



using namespace std;


template<class TYPE>
class ArrayList : public ListInterface<TYPE>
{

private:
	
	static const int DEFAULT_CAPACITY = 100;
	TYPE *items; //array
	int itemCount; // Current count of list items
	int maxItems; // Maximum capacity of the list 
	static int numAccess;
	static int numSwap;
	static int numRemove;
	static int numInsertAt;
	static int numAppends;


public:

	/*
	copy constructor
	assign rhs maxitems and itemcount to lhs
	initilize array and make it same array
	*/
	ArrayList(ArrayList<TYPE>& other)
	{
		maxItems = other.maxItems;
		itemCount = other.itemCount;
		items = new TYPE[maxItems];
		for (int i = 0; i < itemCount; ++i)
			items[i] = other[i];
	}

	// Default Constructor
	ArrayList() : itemCount(0), maxItems(DEFAULT_CAPACITY) {
		items = new TYPE[maxItems];
	}

	//one parameter instructor
	ArrayList(int max) : itemCount(0), maxItems(max) {
		items = new TYPE[maxItems];
	}

	
	//destructor
	~ArrayList() {
		delete[] items;
		items = nullptr;
	}


	TYPE& getAt(int index) const
	{
		//handling out of range exception
		if (index < 0 || index >= itemCount)
			throw out_of_range("The index you are trying to access is out of bounds");

		//increasing numAccess
		numAccess++;

		//return the item at index
		return items[index];
	}

	//that is same code at getAt
	TYPE& operator[](int index) const {
		return getAt(index);
	}

	//equality operator
	ArrayList<TYPE>& operator = (const ArrayList<TYPE> &other)
	{
		//if list equal the other list just return
		if (this == &other)
			return *this;

		//delete lhs list items
		delete[] this->items;

		//assign rht maxitem and itemcount
		//to lhs maxitem and itemcount
		this->maxItems = other.maxItems;
		this->itemCount = other.itemCount;

		//create new list
		this->items = new TYPE[this->maxItems];

		//copy everything to the list
		for (int i = 0; i < itemCount; i++)
			items[i] = other[i];
	
		//return 
		return *this;
	}

	/*
	this is a helper method for doubling
	the array size and handle memory leak
	*/
	void doubleArray() {
		maxItems *= 2;
		TYPE* tempArr = new TYPE[maxItems];
		
		for (int i = 0; i < itemCount; i++)
			tempArr[i] = items[i];


		delete[]items;
		items = tempArr;
		tempArr = nullptr;

	}

	//if no item return true as empty list
	bool isEmpty() const
	{
		return itemCount == 0;
	}

	//return the item count as getter
	int getSize() const
	{
		return itemCount;
	}

	//assign itemcount to 0 and clear all
	void clearAll()
	{
		itemCount = 0;
	} 

	//this method adds the item to end of the list
	void append(const TYPE& item)
	{
		//if list is full, double the size
		if (itemCount == maxItems)
			doubleArray();

		//add the item to the end and
		//increase the itemcount
		items[itemCount++] = item;

		//increase the numappends
		numAppends++;
	}

	// Inserts at the location. 
	void insertAt(int index, const TYPE& newEntry)
	{
		//handling the outside of the list error
		if (index < 0 || index > itemCount)
			throw out_of_range("invalid index");
		
		//if list is full, double the size
		if (itemCount == maxItems)
			doubleArray();

		//this for loop is shifting everything 
		//to the right side and have space for new item
		for (int i = itemCount; i > index; i--) {
			items[i] = items[i - 1];
		}

		//add the newitem to the index point
		items[index] = newEntry;

		//increasae the itemcount
		itemCount++;

		//increase the inserat
		numInsertAt++;

	}

	// delete at location
	void removeAt(int index)
	{

		//handling the outside of the list error
		if (index < 0 || index >= itemCount)
			throw out_of_range("invalid index");

		//this for loop is copying everything 
		//to the left and remove the item
		for (int i = index; i < itemCount - 1; i++)
			items[i] = items[i + 1];
		
		//because we remove the item, decrease the itemcount
		itemCount--;

		//increase the numRemove
		numRemove++;
	}

	//swapping 2 location
	void swap(int from, int to)
	{
		//if from and to are outside of the list, handle exception
		if(from < 0 || to < 0 || from >= itemCount || to >= itemCount)
			throw out_of_range("invalid index");

		//swap the items
		TYPE temp = items[from];
		items[from] = items[to];
		items[to] = temp;

		//increase the numswap
		numSwap++;
	}

	// Clear out any instrumentation
	void clearStatistics()
	{
		//assign everything to zero
		numAccess = numSwap = numRemove
			= numInsertAt = numAppends = 0;
	}
	
	//getters for stat
	int getNumAccess() const { return numAccess;  }
	int getNumSwap() const { return numSwap;  }
	int getNumRemove()const { return numRemove;  }
	int getNumInsertAt() const { return numInsertAt;  }
	int getNumAppends() const { return numAppends;  }
	
	
};

//initilizing static variables
template<class TYPE> int ArrayList<TYPE>::numAccess = 0;
template<class TYPE> int ArrayList<TYPE>::numSwap = 0;
template<class TYPE> int ArrayList<TYPE>::numRemove = 0;
template<class TYPE> int ArrayList<TYPE>::numInsertAt = 0;
template<class TYPE> int ArrayList<TYPE>::numAppends = 0;


#endif

		


		

