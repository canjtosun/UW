//Can Tosun
//Jolly Banker
//This file contains account implementation
//contructor-desconstructor-getters
//initilizations - operator overloading and
//tr4ansaction types entries

#pragma once
#include <string>
#include <vector>
#include "Fund.h"
using namespace std;
//const size because we have 10 different funds
const int FUND_TYPES = 10;
class Account
{
	friend ostream& operator<<(ostream& os, const Account& acc);
public:
	Account();
	Account(const string& firstName, const string& lastName, const int& id);
	~Account();

	string getfirstName()const;
	string getlastName()const;
	int getID()const;

	bool Deposit(const int& fundType, const int& amount);
	bool Withdraw(const int& fundType, const int& amount);
	bool Transfer(const int& fundType, const int& amount, Account*& accB, const int& fundTypeB);
	void AccountHistory();
	void AccountHistoryByFund(const int& fundType);

	bool operator<(const Account& acc)const;
	bool operator>(const Account& acc)const;
	bool operator==(const Account& acc)const;
	bool operator!=(const Account& acc)const;

private:

	string firstName;
	string lastName;
	int ID;
	vector<Fund> fundTypes;
	void setFundNames();
};
