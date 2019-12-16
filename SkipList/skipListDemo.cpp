#include <iostream>
#include "skiplist.h"
#include <time.h>

using namespace std;


void test04()
{
	SkipList s(5);
	for (int i = 0; i <= 20; ++i) {
		int number = rand() % 100;
		s.Add(number);
		cout << "After adding " << number << endl;
		cout << s << endl;
	}

	/*
	//my test
	cout << "Contain?? 5 : " << s.Contains(5) << endl;
	cout << "Contain?? 41 : " << s.Contains(41) << endl;
	cout << "Contain?? 0 : " << s.Contains(0) << endl;

	cout << "Remove 5: "<< s.Remove(5) << endl;
	cout << "Remove 41: " << s.Remove(41) << endl;
	cout << "Remove 0: " << s.Remove(0) << endl;

	cout << s;
	*/

	//s.Add(5465465546546546);
	//cout << s;

}




int main()
{
	
	test04();
	return 0;
}
