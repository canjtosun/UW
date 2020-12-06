//Can Tosun
//Jolly Banker
//This file contains Bank implementation
//contructor-desconstructor-
//read the file- process transactions
//show all balances


#include "Bank.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

//constructor
Bank::Bank()
{
}

//descontructor
Bank::~Bank()
{
}


bool Bank::ReadFile(const string& fileName)
{
	ifstream readFile;
	readFile.open(fileName);

	//if no file. throw error
	if (!readFile.good())
	{
		cout << "File Not Found" << endl;
		return false;
	}

	string line;
	//while the file is not empty
	while (!readFile.eof())
	{
		getline(readFile, line);
		istringstream ss(line);

		//while the line is not empty
		while (!ss.eof())
		{
			string TransType;
			getline(ss, TransType, ' ');
			//if first is "O" for open account
			if (TransType == "O") 
			{
				//get the name last name id 
				//and check if Id is 4 digit
				string firstName;
				getline(ss, firstName, ' ');
				string lastName;
				getline(ss, lastName, ' ');
				string ID;
				getline(ss, ID, ' ');


				//open transaction
				//and push to queue
				Transaction openT(TransType, firstName, lastName, atoi(ID.c_str()));
				q.push(openT);
				
			}

			//deposit has 3 words and 4 entries
			//if first word is D
			else if (TransType == "D")
			{

				string idNumfundNum;
				getline(ss, idNumfundNum, ' ');

				string id = idNumfundNum.substr(0, 4);
				string fund = idNumfundNum.substr(4, 1);
				string amount;
				getline(ss, amount, ' ');

				//if amount less than zero
				if (atoi(amount.c_str()) < 0)
				{
					cout << "Error-> negative amount." << endl;
				}
				//otherwise
				else
				{
					//add to deposit transaction and push it to queue
					Transaction depositeT(TransType, atoi(id.c_str()), atoi(fund.c_str()), atoi(amount.c_str()));
					q.push(depositeT);
				}

			//withdraw is same as deposit 
			//for reading from file
			}
			else if (TransType == "W")
			{
				string idNumfundNum;
				getline(ss, idNumfundNum, ' ');
				
				string id = idNumfundNum.substr(0, 4);
				string fund = idNumfundNum.substr(4, 1);
				string amount;
				getline(ss, amount, ' ');
				if (atoi(amount.c_str()) < 0)
				{
					cout << "Error-> negative amount." << endl;
				}
				else
				{
					//adding deposit transaction
					Transaction depositeT(TransType, atoi(id.c_str()), atoi(fund.c_str()), atoi(amount.c_str()));
					q.push(depositeT);
				}

			//transfer is different becuase there are 5 words
			//need to read second wors as a sourcce
			//and the word after amount as a destination 
			//need to make sure we are correct of using
			//substring for right word
			}
			else if (TransType == "T")
			{
				
				string idNumfundNum;
				getline(ss, idNumfundNum, ' ');
				
				//reading for source
				string sourceID = idNumfundNum.substr(0, 4);
				string sourcefund = idNumfundNum.substr(4, 1);

				string amount;
				getline(ss, amount, ' ');
				if (atoi(amount.c_str()) < 0)
				{
					cout << "Error-> negative amount." << endl;
				}
				else
				{
					//this reading for destination
					string idNumfundNumTrans;
					getline(ss, idNumfundNumTrans, ' ');

					string destId = idNumfundNumTrans.substr(0, 4);
					string destfund = idNumfundNumTrans.substr(4, 1);

					//adding to transfer transaction
					Transaction TransferT(TransType, atoi(sourceID.c_str()), atoi(sourcefund.c_str()), atoi(amount.c_str()), atoi(destId.c_str()), atoi(destfund.c_str()));
					q.push(TransferT);
					
				}
			}

			//history
			//2 different history here
			//first one all history
			//second one history with fund type
			else if (TransType == "H")
			{
				string idNumfundNum;
				getline(ss, idNumfundNum, ' ');

				string id = idNumfundNum.substr(0, 4);
				string fund = "-1";

				//this checks if 5 digit
				//means history with fund type
				if (idNumfundNum.size() > 4)
				{
					fund = idNumfundNum.substr(4, 1);
				}
				Transaction HistoryT(TransType, atoi(id.c_str()), atoi(fund.c_str()));
				q.push(HistoryT);
			}
		}
	}

	//close the file
	readFile.close();
	return true;
}

//after read the file
//we are processing line by line as queue
bool Bank::TransProcess()
{
	//we will go thru end of the queue
	while (!q.empty())
	{
		//getting the front. first line. and processing
		Transaction t = q.front();

		//if the first is O (open account)
		if (t.getpass() == "O")
		{
			//initilize first name, last name and id
			string firstName = t.getfirstName();
			string lastName = t.getlastName();
			int ID = t.getID();
			//open a new account with firstname, lastname and id
			Account* acc = new Account(firstName, lastName, ID);

			//if this account is already in tree, means already opened
			//throw error message
			if (tree.Retrieve(ID, acc))
			{
				cout << "Error-> Account " << ID << " already open. Transaction refused." << endl;
			}
			//otherwise, insert to BSTree
			else
			{
				tree.Insert(acc);
			}
		}

		//if the first is D (Deposit)
		else if (t.getpass() == "D")
		{
			//get the ID, fund type and amount
			int ID = t.getID();
			int fund = t.getfundType();
			int amount = t.getamount();
			//get temp account and search if the account is there
			Account* acc;

			bool result = tree.Retrieve(ID, acc);
			//if it is not there, throw error message
			if (!result)
			{
				cout << "Error-> Account " << ID << " does not exist." << endl;
			}
			//if it is there, then deposit it
			else
			{
				acc->Deposit(fund, amount);
			}


			
		}

		//if the first is W (Withdraw)
		else if (t.getpass() == "W")
		{
			//get the ID, fund type and amount
			int ID = t.getID();
			int fund = t.getfundType();
			int amount = t.getamount();
			//get temp account and search if the account is there
			Account* acc;

			bool result = tree.Retrieve(ID, acc);
			//if it is not there, throw error message
			if (!result)
			{
				cout << "Error-> Account " << ID << " does not exist." << endl;
			}
			//if it is there, then withdraw the amount
			else
			{
				acc->Withdraw(fund, amount);
			}
		}

		//if the first is T (Transfer)
		//it is different then others because
		//we have source and dest account
		else if (t.getpass() == "T")
		{
			//get the ID, fund type (source)
			int ID = t.getID();
			int fund = t.getfundType();
			//get the amount
			int amount = t.getamount();
			//get the ID, fund type (dest)
			int destID = t.getIDTrans();
			int destFund = t.getfundTypeTrans();

			//create 2 temop for source and dest
			Account* sourceAcc;
			Account* destAcc;

			//check both source and dest accId is there or not
			bool sourceResult = tree.Retrieve(ID, sourceAcc);
			bool destResult = tree.Retrieve(destID, destAcc);

			//if not there, throw error message
			if (!sourceResult || !destResult)
				cout << "Error-> Account " << destID << " not found. Transferal refused." << endl;
			//otherwise make the transfer from source to dest
			else
				sourceAcc->Transfer(fund, amount, destAcc, destFund);

		}

		//if the first is H (History)
		//2 different scenerio here
		//full history or fund history for specific account
		else if (t.getpass() == "H")
		{
			//get the ID, fund type (source)
			int ID = t.getID();
			int fund = t.getfundType();

			//create an temp account
			Account* acc;
			//check the account is there
			bool result = tree.Retrieve(ID, acc);

			//if not there, throw an error message
			if (!result)
			{
				cout << "Error-> Account history does not exist for " << ID << "." << endl;
			}

			//if the account is there
			else
			{
				//scenerio 1: show full history
				if (fund == -1)
				{
					acc->AccountHistory();
				}
				//scenerio 2: show fund history of the account
				else
				{
					acc->AccountHistoryByFund(fund);
				}
			}
		}
		//after we finish processing the line.
		//we have to pop that line from queue and 
		//read the next line and process
		//until the queue is empty
		q.pop();
	}
	return true;
}

//show all balances, calling the tree display method
void Bank::ShowAllBalances()const
{
	tree.Display();
}