//Can Tosun
//Jolly Banker
//This file contains account implementation
//contructor-desconstructor-getters
//initilizations - operator overloading and
//transaction types entries
//end of all kind of transaction, we are
//adding every move to the fund history


#include "Account.h"
#include <iostream>

using namespace std;

//Account constructor.
//initilize everything to 0 and empty string
//resize vector to 10;
Account::Account()
{
	firstName = "";
	lastName = "";
	ID = 0000;
	fundTypes.resize(FUND_TYPES);
	setFundNames();
}

//Account constructor. we will use it for open account
//initilizers
Account::Account(const string& firstName, const string& lastName, const int& id)
{
	this->firstName = firstName;
	this->lastName = lastName;
	this->ID = id;
	fundTypes.resize(FUND_TYPES);
	setFundNames();
}

//desconstructor
Account::~Account()
{
}

//getters
string Account::getfirstName()const { return firstName; }
string Account::getlastName()const{ return lastName; }
int Account::getID()const { return ID; };


//Account deposit method
//make a deposit to amount of enter to the fund type
//add to the history and return true;
bool Account::Deposit(const int& fundType, const int& amount)
{
	fundTypes[fundType].Deposit(amount);
	fundTypes[fundType].AddEntry(" D " + to_string(getID()) + to_string(fundType) + " " + to_string(amount));
	return true;
}

//Account withdraw method
//make a withdraw an amount of enter from the fund type
//if you can, ,make transaction and add to history
//if not explanation in method
bool Account::Withdraw(const int& fundType, const int& amount)
{
	bool result = fundTypes[fundType].Withdraw(amount);
	if (result)
	{
		fundTypes[fundType].AddEntry(" W " + to_string(getID()) + to_string(fundType) + " "
			+ to_string(amount));
		return true;
	}
	else
	{
		if (fundType == 0)
		{
			//get the balance at money market
			int fundamount = fundTypes[0].getBalance(); 
			//try to withdraw some money from 1 to 0
			bool result = fundTypes[1].Withdraw(amount - fundTypes[0].getBalance()); 
			if (result) //if you can
			{
				//add to history for both account and do the transaction.
				fundTypes[1].AddEntry(" W $" + to_string(amount - fundTypes[0].getBalance()) + "."); 
				fundTypes[0].Withdraw(fundTypes[0].getBalance());
				fundTypes[0].AddEntry(" W $" + to_string(fundamount) + ".");
				return true;
			}
			else
			{
				//otherwise throw an error and add that to the history
				cout << "Error-> Inadequate funds withdraw $" << amount << " from " <<
					lastName << " " << firstName << " " << 
					fundTypes[fundType].getnameOfTheFund() << endl;
				fundTypes[fundType].AddEntry(" W " + to_string(getID()) + to_string(fundType) + " "
					+ to_string(amount) + " (Failed)");
				return false;
			}

		}
		//same as above. fund type changed now checking 
		//prime money market vs other funds
		//if transaction can go thru, we are doing it
		//otherwise we are adding both history and threing an error
		else if (fundType == 1)
		{
			int fundamount = fundTypes[1].getBalance();
			bool result = fundTypes[0].Withdraw(amount - fundTypes[1].getBalance());
			if (result)
			{
				fundTypes[0].AddEntry(" W $" + to_string(amount - fundTypes[1].getBalance()) + ".");
				fundTypes[1].Withdraw(fundTypes[1].getBalance());
				fundTypes[1].AddEntry(" W $" + to_string(fundamount) + ".");
				return true;
			}
			else
			{
				cout << "Error-> Inadequate funds withdraw $" << amount << " from " << 
					lastName << " " << firstName << " " <<
					fundTypes[fundType].getnameOfTheFund() << endl;
				fundTypes[fundType].AddEntry(" W " + to_string(getID()) + to_string(fundType) + " "
					+ to_string(amount) + " (Failed)");
				return false;
			}
		}

		//same as above. fund type changed now checking 
		//long term bond vs other funds
		//if transaction can go thru, we are doing it
		//otherwise we are adding both history and throwing an error
		else if (fundType == 2)
		{
			int fundamount = fundTypes[2].getBalance();
			bool result = fundTypes[3].Withdraw(amount - fundTypes[2].getBalance());
			if (result)
			{
				fundTypes[3].AddEntry(" W $" + to_string(amount - fundTypes[2].getBalance()) + ".");
				fundTypes[2].Withdraw(fundTypes[2].getBalance());
				fundTypes[2].AddEntry(" W $" + to_string(fundamount) + ".");
				return true;
			}
			else
			{
				cout << "Error-> Inadequate funds withdraw $" << amount << " from " <<
					lastName << " " << firstName << " " << fundTypes[fundType].getnameOfTheFund() << endl;
				fundTypes[fundType].AddEntry(" W " + to_string(getID()) + to_string(fundType) + " "
					+ to_string(amount) + " (Failed)");
				return false;
			}
		}
		//same as above. fund type changed now checking 
		//short term bond vs other funds
		//if transaction can go thru, we are doing it
		//otherwise we are adding both history and throwing an error
		else if (fundType == 3)
		{
			int fundamount = fundTypes[3].getBalance();
			bool result = fundTypes[2].Withdraw(amount - fundTypes[3].getBalance());
			if (result)
			{
				fundTypes[2].AddEntry(" W $" + to_string(amount - fundTypes[3].getBalance()) + ".");
				fundTypes[3].Withdraw(fundTypes[3].getBalance());
				fundTypes[3].AddEntry(" W $" + to_string(fundamount) + ".");

				return true;
			}
			else
			{
				cout << "Error-> Inadequate funds withdraw $" << amount << 
					" from " << lastName << " " << firstName <<
					" " << fundTypes[fundType].getnameOfTheFund() << endl;
				fundTypes[fundType].AddEntry(" W " + to_string(getID()) + to_string(fundType) + " "
					+ to_string(amount) + " (Failed)");

				return false;
			}
		}
		else
		{
			cout << "Error-> Inadequate funds withdraw $" << amount <<
				" from " << lastName << " " << firstName << " " <<
				fundTypes[fundType].getnameOfTheFund() << endl;
			fundTypes[fundType].AddEntry(" W $" + to_string(getID()) + to_string(fundType) + " "
				+ to_string(amount) + " (Failed)");

			return false;
		}
	}
	return true;
}

//transferring money from one account to another
bool Account::Transfer(const int& fundType, const int& amount, Account*& accOther, const int& fundTypeOther)
{
	//if this account is equal other account
	if (*this == *accOther)
	{
		//withdraw the amount from specific fund type
		bool result = fundTypes[fundType].Withdraw(amount);

		//if you cann not / insufficient fund
		//throw an error and add it to the history
		//anmd return false bcuz we could not make 
		//the transaction
		if (result == false)
		{
			cout << "Transfer of $" + to_string(amount) + " from "
				+ fundTypes[fundType].getnameOfTheFund() +
				" to " + fundTypes[fundTypeOther].getnameOfTheFund()
				+ " failed." << endl;


			fundTypes[fundType].AddEntry(" T " + to_string(getID()) +
				to_string(fundType) + " " + to_string(amount) + " " +
				to_string(accOther->getID()) + to_string(fundTypeOther));

			return false;
		}

		//if true, mean if we can make the transaction
		//we already can withdrawe the amount from source account
		//add(deposit the money) to other account
		//add to the history for both account
		else
		{

			fundTypes[fundTypeOther].Deposit(amount);

			fundTypes[fundType].AddEntry(" T " + to_string(getID()) + 
				to_string(fundType) + " " + to_string(amount) + " " +
			 to_string(accOther->getID()) + to_string(fundTypeOther));

			fundTypes[fundTypeOther].AddEntry(" T " + to_string(getID()) +
				to_string(fundType) + " " + to_string(amount) + " " +
				to_string(accOther->getID()) + to_string(fundTypeOther));
	
			return true;
		}

	}

	//another scenerio
	//if its not same account
	//do the same thing as above
	//add to the fund history
	else
	{
		bool result = fundTypes[fundType].Withdraw(amount);
		if (result == false)
		{
			cout << "Transfer of $" + to_string(amount) + " from Account " + 
				to_string(ID) + " fund " + fundTypes[fundType].getnameOfTheFund() +
				" to Account " + to_string(accOther->getID()) + " fund " + 
				fundTypes[fundTypeOther].getnameOfTheFund() + " failed." << endl;


			accOther->fundTypes[fundType].AddEntry("Transfer of $" + to_string(amount)
				+ " from Account " + to_string(ID) + " fund " + fundTypes[fundType].getnameOfTheFund() +
				" to Account " + to_string(accOther->getID()) + " fund " +
				fundTypes[fundTypeOther].getnameOfTheFund() + " failed.");

			return false;
		}
		else
		{
			accOther->fundTypes[fundTypeOther].Deposit(amount);
			fundTypes[fundType].AddEntry("Transfered $" + to_string(amount) +
				" from Account " + to_string(ID) + " fund " + fundTypes[fundType].getnameOfTheFund() +
				" to Account " + to_string(accOther->getID()) + " fund " +
				fundTypes[fundTypeOther].getnameOfTheFund() + ".");


			accOther->fundTypes[fundTypeOther].AddEntry("Transfered $" + 
				to_string(amount) + " from Account " + to_string(ID) + " fund "
				+ fundTypes[fundType].getnameOfTheFund() +
				" to Account " + to_string(accOther->getID()) + " fund "
				+ fundTypes[fundTypeOther].getnameOfTheFund() + ".");

			return true;
		}
	}
}

//Account History Method
//printing out the name last name and acc id

void Account::AccountHistory()
{

	string str = "Transaction History for " + getlastName() + " " + getfirstName() +  " by Fund.";
	cout << str << endl;

	for (size_t i = 0; i < fundTypes.size(); i++)
	{
		if (fundTypes[i].getEntrySize() != 0)
		{
			cout << fundTypes[i].getnameOfTheFund() << ": $" << fundTypes[i].getBalance() << endl;
			fundTypes.at(i).ShowFundHistory();
		}

	}
}

//displaying the history by fund
void Account::AccountHistoryByFund(const int& fundType)
{

	cout << "Transaction History for " << getlastName() << " " << getfirstName() << 
		" " << fundTypes[fundType].getnameOfTheFund() << ": $" << 
		fundTypes[fundType].getBalance() << endl;

	fundTypes[fundType].ShowFundHistory();
}

//Overloading operator for full history
//we are displaying everything in once 
//going thru each fund type 
ostream& operator<<(ostream& os, const Account& acc)
{
	os << acc.getlastName() << " " << acc.getfirstName() <<
		" Account ID: " << acc.getID() << endl;

	for (size_t i = 0; i < acc.fundTypes.size(); i++)
	{
		os << "	" << acc.fundTypes[i].getnameOfTheFund() << ": $" << 
			acc.fundTypes[i].getBalance() << endl;
	}
	return os;
}

//Overloading all comparison operators
bool Account::operator==(const Account& acc) const
{
	return ID == acc.getID();
}

bool Account::operator!=(const Account& acc) const
{
	return ID != acc.getID();;
}

bool Account::operator<(const Account& acc)const
{
	return ID < acc.getID();
}

bool Account::operator>(const Account& acc)const
{
	return ID > acc.getID();
}

//fund names initialization
void Account::setFundNames()
{
	fundTypes[0].SetFund("Money Market");
	fundTypes[1].SetFund("Prime Money Market");
	fundTypes[2].SetFund("Long-Term Bond");
	fundTypes[3].SetFund("Short-Term Bond");
	fundTypes[4].SetFund("500 Index Fund");
	fundTypes[5].SetFund("Capital Value Fund");
	fundTypes[6].SetFund("Growth Equity Fund");
	fundTypes[7].SetFund("Growth Index Fund");
	fundTypes[8].SetFund("Value Fund");
	fundTypes[9].SetFund("Value Stock Index");
}