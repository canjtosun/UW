//Can Tosun
//Jolly Banker
//This file contains Fund implementation
//contructor-desconstructor-
//getter and set
//and other methods for calculations
//show all balances

#include "Fund.h"
#include <iostream>
using namespace std;



//constructors
Fund::Fund()
{
	nameOfTheFund = "";
	sumOfTheMoney = 0;
}

Fund::Fund(const string& nameOfTheFund, const int& amount)
{
	this->nameOfTheFund = nameOfTheFund;
	Deposit(amount);
}

//desconstructor
Fund::~Fund()
{
}


//setting the fund
//and return true
bool Fund::SetFund(const string& nameOfTheFund)
{
	this->nameOfTheFund = nameOfTheFund;
	return true;
}

//getters
int Fund::getBalance()const { return sumOfTheMoney; }
int Fund::getEntrySize() const { return fundEntry.size(); }
string Fund::getnameOfTheFund()const { return nameOfTheFund; }


//withdraw calculation
bool Fund::Withdraw(const int& amount)
{
	//if amount is less than zero, throw error
	//else if the money is less than amount, dont let any transaction
	//otherwise make the transaction and modify
	if (amount < 0)
	{
		cout << "Error-> negative amount." << endl;
		return false;
	}
	else
	{
		if (sumOfTheMoney - amount < 0)
		{
			return false;
		}
		else
		{
			sumOfTheMoney -= amount;
			return true;
		}
	}
}

//deposit calculation
bool Fund::Deposit(const int& amount)
{
	//if amount is less than zero, throw error
	//otherwise just add the amount and modify
	if (amount < 0)
	{
		cout << "Error-> negative amount." << endl;
		return false;
	}
	else
	{
		sumOfTheMoney += amount;
		return true;
	}
}

//fund history printing out
void Fund::ShowFundHistory()const
{
	for (size_t i = 0; i < fundEntry.size(); i++)
	{
		cout << fundEntry.at(i) << endl;
	}
}



//every fund history, adding to vector
void Fund::AddEntry(const string& record)
{
	fundEntry.push_back(record);
}