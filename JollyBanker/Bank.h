//Can Tosun
//Jolly Banker
//This file contains Bank header
//contructor-desconstructor-
//read the file- process transactions
//show all balances

#pragma once
#include <string>
#include <queue>  
#include "BSTree.h"
#include "Account.h"
#include "Transaction.h"
using namespace std;

class Bank
{
public:

	Bank();
	~Bank();

	//read, processs and print out
	bool ReadFile(const string& fileName);
	bool TransProcess();
	void ShowAllBalances()const;

private:
	queue<Transaction> q;
	BSTree tree;

};