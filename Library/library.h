#pragma once
using namespace std;

/*Library class interface. I did not add private, bcuz
private is default. variables are private
*/
class Library
{
	static const int MAXBOOK = 100;
	string arr[MAXBOOK];
	int numberOfBook = 0;

public:
	Library(string name);
	int GetNumberOfBook();
	bool AddBook(const string& name);
	bool RemoveBook(const string& name);
	int findBookIndex(const string& name) const;
	void ListAllBooks() const;
	bool IsInLibrary(const string& name) const;
	friend ostream& operator<<(ostream& out, const Library& lib);
};
