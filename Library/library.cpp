/*
 This class implements all the method that we 
 included from library.h.
 add/remove books. print them out.
 check the entire array and find the index number of book
*/

#include <iostream>
#include <cassert>
#include "library.h"

using namespace std;

//calling constructor and just printing out "UWB"
//title. taking one parameter, string.
Library::Library(string name)
{
	cout << name << endl;
}

//getter
int Library::GetNumberOfBook()
{
	return numberOfBook;
}


/*
find book index method
just going thru all books and if the book is there
return the index number. if no book found,return -1,
so we can use it again for another method.
*/
int Library::findBookIndex(const string& name) const
{
	for (int i = 0; i < numberOfBook; i++)
	{
		if (arr[i] == name)
			return i;
	}
	return -1;
}


/*AddBook Method
use the findbookindex method, if the book
is not there, add it , increment the size 
and return true.
if you reach the max number, warn user and
return false.
if the book is there, return false
*/
bool Library::AddBook(const string& name)
{
	if (findBookIndex(name) == -1) {
		arr[numberOfBook++] = name;
		return true;
	}

	else if (GetNumberOfBook() >= MAXBOOK) {
		cout << "you reached the max. cannot add book!!" << endl;
		return false;
	}

	return false;
}


/*Remove Book Method
if the book not found, return false and do
nothing.
else copy the last book there and
decrese the size of number of book
*/
bool Library::RemoveBook(const string& name)
{
	int foundIndex = findBookIndex(name);
	if (foundIndex == -1)
		return false;

	arr[foundIndex] = arr[numberOfBook - 1];
	numberOfBook--;
	return true;

}


/*List all books
just going thru all boks and printing them out
one line at a time
*/
void Library::ListAllBooks() const
{
	for (int i = 0; i < numberOfBook; i++)
	{
		cout << arr[i] << endl;
	}
}



/*
is in library method is calling another method.
find book index method is taking a book name parameter,
and if it is not there return -1.
so if the book is not equal to -1 (no book)
means the book is already in library and return true.
*/
bool Library::IsInLibrary(const string& name) const
{
	if (findBookIndex(name) != -1) {
		cout << "already in library" << endl;
		return true;
	}

	return false;
}

/*
overloading << operator.
printing out all books in array
directly with referance 
*/
ostream& operator <<(ostream& out, const Library& lib)
{
	for (int i = 0; i < lib.numberOfBook; i++)
	{
		out << lib.arr[i] << endl;
	}
	return out;
}
