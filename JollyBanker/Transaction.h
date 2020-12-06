//Can Tosun
//Jolly Banker
//This file contains Transaction header
//contructors-desconstructor-
//and all getters for private variables


#pragma once
#include <vector>
#include "Account.h"
using namespace std;


class Transaction
{
	friend ostream& operator<<(ostream& os, const Transaction& tran);
public:

	//constructors
	Transaction();
	Transaction(const string& pass, const string& firstName, const string& lastName, const int& id);
	Transaction(const string& pass, const int& id, const int& fundType, const int& amount);
	Transaction(const string& pass, const int& id, const int& fundType);
	Transaction(const string& pass, const int& id, const int& amount, const int& fundType, const int& idtrans, const int& fundTypetrans);


	//Transaction(const string& pass, const int& id);
	~Transaction();

	//getters
	string getpass()const;
	string getfirstName()const;
	string getlastName()const;
	int getID()const;
	int getIDTrans()const;
	int getfundType()const;
	int getfundTypeTrans()const;
	int getamount()const;

private:

	//private variables
	string firstName;
	string lastName;
	int ID;
	int IDTrans;
	int fundType;
	int fundTypeTrans;
	int amount;
	string pass;

};
