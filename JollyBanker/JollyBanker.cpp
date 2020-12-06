//Can Tosun
//Jolly Banker
//This file contains main and compile


#include <iostream>
#include "Bank.h"
using namespace std;


int main()
{
	//Create an instance
	Bank bank_;

	//filename hard coded
	string fileName = "BankTransIn.txt";
	string fileName2 = "test1.txt";

	//read the file
	bank_.ReadFile(fileName);

	//process the transactions
	bank_.TransProcess();

	cout << endl;

	cout << "Processing Done. Final Balances." << endl;

	//show all balances for all acounts
	bank_.ShowAllBalances();
}