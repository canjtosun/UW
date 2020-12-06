//Can Tosun
//Jolly Banker
//This file contains Fund header
//contructor-desconstructor-
//getter and set
//and other methods for calculations
//show all balances

#pragma once
#include <string>
#include <vector>
using namespace std;


class Fund
{
public:

	Fund();
	Fund(const string& nameOfTheFund, const int& amount);
	~Fund();

	//getters
	string getnameOfTheFund()const;
	int getBalance()const;
	int getEntrySize()const;

	//set method
	bool SetFund(const string& nameOfTheFund);


	bool Withdraw(const int& amount);
	bool Deposit(const int& amount);
	void ShowFundHistory()const;
	
	void AddEntry(const string& record);

private:
	string nameOfTheFund;
	int sumOfTheMoney;
	vector<string> fundEntry;
};