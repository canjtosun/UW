//#include "stdafx.h"
#include "Transaction.h"
#include <iostream>

using namespace std;


//file has 6 different constructor
//first one default is just initializer
//other constructors are for each kind of transactions
Transaction::Transaction()
{
	pass = -1;
	firstName = "";
	lastName = "";
	ID = -1;
	IDTrans = -1;
	fundType = -1;
	fundTypeTrans = -1;
	amount = -1;
}

//constructor for open an account
Transaction::Transaction(const string& pass, const string& firstName, const string& lastName, const int& id)
{
	this->pass = pass;
	this->firstName = firstName;
	this->lastName = lastName;
	this->ID = id;
}

//constructor for Deposit and WithDraw
Transaction::Transaction(const string& pass, const int& id, const int& fundType, const int& amount)
{
	this->pass = pass;
	this->ID = id;
	this->fundType = fundType;
	this->amount = amount;
}

//Constructor for History
Transaction::Transaction(const string& pass, const int& id, const int& fundType)
{
	this->pass = pass;
	this->ID = id;
	this->fundType = fundType;
}

//constructor for transferring
Transaction::Transaction(const string& pass, const int& id, const int& fundType, const int& amount, const int& otherID, const int& otherFundType)
{
	this->pass = pass;
	this->ID = id;
	this->amount = amount;
	this->fundType = fundType;
	this->IDTrans = otherID;
	this->fundTypeTrans = otherFundType;
}

//
//Transaction::Transaction(const string& pass, const int& id)
//{
//	this->pass = pass;
//	this->ID = id;
//	this->fundType = -1;
//}


//Deconstructor
Transaction::~Transaction()
{
}

//all getters
string Transaction::getpass()const { return pass; }
string Transaction::getfirstName()const { return firstName; }
string Transaction::getlastName()const { return lastName; }
int Transaction::getID()const { return ID; }
int Transaction::getIDTrans()const { return IDTrans; }
int Transaction::getfundType()const { return fundType; }
int Transaction::getfundTypeTrans()const { return fundTypeTrans; }
int Transaction::getamount()const { return amount; }

//operator overloading for variables
ostream& operator<<(ostream& os, const Transaction& tran)
{
	os << "Transaction type: " << tran.pass << endl;
	os << "First Name: " << tran.firstName << endl;
	os << "Last Name: " << tran.lastName << endl;
	os << "ID: " << tran.ID << endl;
	os << "Transer ID: " << tran.IDTrans << endl;
	os << "Fund Type: " << tran.fundType << endl;
	os << "Transfer Fund Type: " << tran.fundTypeTrans << endl;
	os << "amount: $" << tran.amount;

	return os;
}