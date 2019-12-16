#ifndef LIST_INTERFACE_H
#define LIST_INTERFACE_H

#include <stdexcept>

template < class TYPE>
class  ListInterface {
public:

	// Note this one is not a pure virtual. 
	virtual ~ListInterface() { } //done

	// The easy way to access an element
	virtual TYPE& operator[] (int) const = 0; //done

	// Tell of it is empty
	virtual bool isEmpty() const = 0; //done

	// Return the number of elements in the list
	virtual int getSize() const = 0;  //done

	// Inserts at the location. 
	virtual void insertAt(int index, const TYPE& newEntry) = 0; //done

	// delete at location
	virtual void removeAt(int index) = 0; //done

	// Append to end
	virtual void append(const TYPE&) = 0; //done

	virtual void swap(int from, int to) = 0;

	// Get an item at location
	virtual TYPE& getAt(int index) const = 0; //done

	// Clear everything
	virtual void clearAll() = 0; //done


	// Clear out any instrumentation
	virtual void clearStatistics() = 0; //done

	// Provide statistics on number of times method was performed
	virtual int getNumAccess() const = 0;    // operator [] OR getAt
	virtual int getNumSwap() const = 0; // done
	virtual int getNumRemove() const = 0; //done
	virtual int getNumInsertAt() const = 0; //done
	virtual int getNumAppends() const = 0; //done

};
#endif




