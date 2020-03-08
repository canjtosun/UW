// ------------------------------------------------ driver.cpp -------------------------------------------------------
// Can Tosun CSS 343 C
// Jan 11 2020
// Jan 18, 2020 - Date of Last Modification
// --------------------------------------------------------------------------------------------------------------------
// Purpose - This file is provided by instructor to test my implementation
// --------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "polynomial.h"

//inlcude unordered_map and set for key,element
//values. it is faster and to merge lists
#include <unordered_map> 
#include <set>
#include <sstream> //manipulate the output
using namespace std;

// ------------------------------------Constructor----------------------------------------------- 
// Description
// Constructor: Initilizing the values and creating dummy head
// preconditions: dummy head is the new term which is going to have
//                0,0 values. Also it will point to itself.
// postconditions: head will point to dummyhead and dummyhead will 
//				   be the first node. And size will be 0
// -------------------------------------------------------------------------------------------- 
Polynomial::Polynomial()
{
	Term* dummyHead = new Term;
	dummyHead->next = dummyHead;
	dummyHead->prev = dummyHead;
	dummyHead->coeff = 0.0;
	dummyHead->power = 0;
	head = dummyHead;	
	size = 0;
}
//end of Constructor

// ------------------------------------Copy Constructor----------------------------------------- 
// Description
// Copy Constructor: Deep copying right hand side polynomial
//					 to the left hand side
// preconditions:	initilize as a default constructor. the current pointer
//					will go thru each of node and copy to the left side
// postconditions:  it will deep copy the polynomial
//				   
// -------------------------------------------------------------------------------------------- 
Polynomial::Polynomial(const Polynomial& p) {

	Term* dummyHead = new Term;
	dummyHead->next = dummyHead;
	dummyHead->prev = dummyHead;
	dummyHead->coeff = 0.0;
	dummyHead->power = 0;
	head = dummyHead;
	size = 0;

	Term* currp = p.head->next;
	if (p.head->next == nullptr) {
		return;
	}
	
	for (int i = 0; i < p.size; i++) {
			changeCoefficient(currp->coeff, currp->power);
			currp = currp->next;
	}
}
//end of Copy Constructor

// ------------------------------------Destructor----------------------------------------- 
// Description
// Destructor:		Remove everything and deallocates the memory
// preconditions:	2 pointers needed
// postconditions:  removes everything iteratively and remove head
//					at the end and take care of memory leak				   
// -------------------------------------------------------------------------------------------- 
Polynomial::~Polynomial()
{
	Term* curr = head->next;
	Term* secondCurr = curr; //for dont lose the curr
							 //otherwise we delete curr and
							 //lose the connection
	while (secondCurr != head)
	{
		secondCurr = secondCurr->next;
		remove(curr);
		curr = secondCurr;
	}

	delete head; //delete head after delete everything
	head = nullptr;
}
//end of Destructor

// -------------------------------Degree of Polynomial------------------------------------ 
// Description
// Degree:		Returns the power of first node
// preconditions:	degree >= 0, struct by default
// postconditions:  adding values on descending order
//					thus, the first value will be highest degree				   
// --------------------------------------------------------------------------------------- 
int Polynomial::degree() const
{
	return head->next->power;
}
//end of Degree of Polynomial

// -------------------------------Coefficient of given power ----------------------------
// Description
// Coefficient:		Returns the coefficient of given power(degree)
// preconditions:	degree >= 0, struct by default
// postconditions:  search through list, find the power
//				and return the coefficient as double othwerwise return 0				   
// ---------------------------------------------------------------------------------------
double Polynomial::coefficient(const int power) const
{
	double result;
	Term* curr = head->next;
	
	while (curr != head)
	{
		if (curr->power == power)
		{
			result = curr->coeff;
			return result;
		}

		curr = curr->next;
	}
	return 0.0;
}
//end of Coefficient of given power

// -------------------------------Change the Coefficient ----------------------------
// Description
// changeCoefficient:	manipulpating the list
//						the conditions are:
//						if newcoefficient = 0 return false;
//						if power is different then insert
//						if power is same then change the coefficient
//						if coefficient is 0 given power then remove
// preconditions:		newcoefficient > 0
// postconditions:		insert,replace and remove the list
//
// ---------------------------------------------------------------------------------------
bool Polynomial::changeCoefficient(const double newCoefficient, const int power)
{
	Term* curr = head->next;

	while (curr != head && curr->power > power)
			curr = curr->next;

	if(curr->power != power || curr->power == 0 )
		insert(curr, newCoefficient, power);

	else if (curr->power == power && newCoefficient != 0)
		curr->coeff = newCoefficient;

	else if (curr->power == power && newCoefficient == 0)
		remove(curr);

	return true;
}
//end of change the coefficient

// -------------------------------insert----------------------------
// Description
// insert	:	insert the term to the polynomial
// preconditions:		newterm is the node to add in the list
// postconditions:		newterm is inserted at the position pointed by pos
// --------------------------------------------------------------------------
bool Polynomial::insert(Term* pos, const double newCoefficient, const int power)
{
	//create a new term and assign
	Term* newTerm = new Term();
	newTerm->coeff = newCoefficient;
	newTerm->power = power;

	//connections
	(pos->prev)->next = newTerm;
	newTerm->prev = (pos->prev);
	newTerm->next = pos;
	pos->prev = newTerm;

	size++; //increase the size after add
	return true;
}
//end of insert

// -------------------------------remove----------------------------
// Description
// remove	:	remove the term to the polynomial
// preconditions:		pos is the node to remove in the list
// postconditions:		pos is removed at the position 
// -------------------------------------------------------------------
bool Polynomial::remove(Term* pos)
{
	Term* prevTerm = pos->prev; // previous node from pos
	Term* nextTerm = pos->next; // next node after pos

	prevTerm->next = nextTerm;
	nextTerm->prev = prevTerm;

	delete pos; //delete pos after connections
	pos = nullptr;

	size--; //remove and decrease the size
	return true;
}
//end of remove

// -------------------------------operator "+"------------------------
// Description
// operator+	:	add two polynomial together
// preconditions:		curr = left hand side of the operator
//						currp = right hand side of the operator
// postconditions:		add 2 terms and return the polynomial 
// -------------------------------------------------------------------
Polynomial Polynomial::operator+(const Polynomial& p) const
{
	Polynomial temp; //temp polynomial
	Term* curr = this->head->next; //left hand side
	Term* currp = p.head->next; //right hand side

	//creating a map will make it faster time 
	//and easier to add elements
	//key is the power
	//element is the coefficient
	unordered_map<int, double> polyMap;

	//add left hand side and right hand side to the map
	//if the keys are the same then it will sum the elements
	while (curr != head)
	{
		polyMap[curr->power] += curr->coeff;
		curr = curr->next;
	}

	while (currp != p.head && currp->coeff != 0)
	{
		polyMap[currp->power] += currp->coeff;
		currp = currp->next;
	}

	//iterate the unordered map and assign
	//all the values to the temp polynomail and return it
	for (auto itr : polyMap)
	{
		temp.changeCoefficient(itr.second, itr.first);
	}

	return temp;
}
//end of operator "+"

// -------------------------------operator "-"------------------------
// Description
// operator-	:	substracts right hand side from left hand side
// preconditions:		curr = left hand side of the operator
//						currp = right hand side of the operator
// postconditions:		remove it and return the polynomial 
// -------------------------------------------------------------------
Polynomial Polynomial::operator-(const Polynomial& p) const
{
	Polynomial temp; //temp polynomial
	Term* curr = this->head->next; //left hand side
	Term* currp = p.head->next; //right hand side

	//it is same as + operator but only difference
	//is subtracting the value right hand side
	unordered_map<int, double> polyMap;

	while (curr != head)
	{
		polyMap[curr->power] += curr->coeff;
		curr = curr->next;
	}

	while (currp != head && currp->coeff != 0)
	{
		polyMap[currp->power] -= currp->coeff;
		currp = currp->next;
	}

	//iterate the unordered map and assign
	//all the values to the temp polynomail and return it
	for (auto itr : polyMap)
	{
		temp.changeCoefficient(itr.second, itr.first);
	}

	return temp;
}
//end of operator "-"

// -------------------------------operator "=="------------------------
// Description
// operator==	:	checks the left hands side of the == operator
//					and the right side of the operator are same
// preconditions:		curr = left hand side of the operator
//						currp = right hand side of the operator
// postconditions:		return true if they are equal
//						otherwise return false
// -------------------------------------------------------------------
bool Polynomial::operator==(const Polynomial& p) const
{
	Polynomial temp; //temp polynomial
	Term* curr = this->head->next; //left hand side
	Term* currp = p.head->next; //right hand side

		//   pow , coeff
	set<pair<int, double>> polySet1;
	set<pair<int, double>> polySet2;

	//insert to set pair all left hand side
	while (curr != head)
	{
		polySet1.insert({ curr->power, curr->coeff });
		curr = curr->next;
	}

	//insert to set pair all right hand side
	while (currp != head && currp->coeff != 0)
	{
		polySet2.insert({ currp->power, currp->coeff });
		currp = currp->next;
	}

	//check if size same
	if (polySet1.size() != polySet2.size())
		return false;

	//check if two sets are same or not
	for (auto p1p2pair : polySet1) {
		if (!polySet2.count(p1p2pair))
			return false;
	}
	return true;
}
//end of operator "=="+

// -------------------------------operator "!="------------------------
// Description
// operator!=	:	checks the left hands side of the != operator
//					and the right side of the operator are not same
// preconditions:		curr = left hand side of the operator
//						currp = right hand side of the operator
// postconditions:		return true if they are not equal
//						otherwise return false
// -------------------------------------------------------------------
bool Polynomial::operator!=(const Polynomial& p) const
{
	//we already overloaded == operator
	//this one will be only not equal
	return !(*this == p);
}
//end  of operator "!="

// -------------------------------operator "="------------------------
// Description
// operator=	:	copy the right side of the operator
//					to the left side
// preconditions:		lhs = left hand side of the operator
//						rhs = right hand side of the operator
// postconditions:		return left hand side	 after copy				
// -------------------------------------------------------------------
Polynomial& Polynomial::operator=(const Polynomial& p)
{
	//lhs = rhs
	//delete the left hand side
	Term* lhs = head->next;
	Term* secondLhs = lhs;

	while (secondLhs != head)
	{
		secondLhs = secondLhs->next;
		remove(lhs);
		lhs = secondLhs;
	}
	//copy right hand side to left hand side
	Term* copyRhs = p.head->next;

	for (int i = 0; i < p.size; i++) {
		changeCoefficient(copyRhs->coeff, copyRhs->power);
		copyRhs = copyRhs->next;
	}

	return *this;
}
//end of operator "="

// -------------------------------operator "+="------------------------
// Description
// operator+=	:	add the right hand side of the operator 
//					to the left hand side and modify it.
//					lhs = lhs + rhs
// preconditions:		rhs = right hand side of the operator
//						currp = right hand side pointer for iteration
// postconditions:		return modified left hand side (this)				
// -------------------------------------------------------------------
Polynomial& Polynomial::operator+=(const Polynomial& p)
{
	Polynomial rhs; //right hand side
	Term* currp = p.head->next;

	//iterating the right hand side terms
	while (currp != p.head && currp->coeff != 0)
	{
		rhs.changeCoefficient(currp->coeff, currp->power);
		currp = currp->next;
	}

	*this = *this + rhs;
	return *this;
}
//end of operator "+="

// -------------------------------operator "-="------------------------
// Description
// operator-=	:	same as += operator but substraction
//					substract the right hand side of the operator 
//					to the left hand side and modify it.
//					lhs = lhs - rhs
// preconditions:		rhs = right hand side of the operator
//						currp = right hand side pointer for iteration
// postconditions:		return modified left hand side (this)				
// -------------------------------------------------------------------
Polynomial& Polynomial::operator-=(const Polynomial& p)
{
	Polynomial rhs;// right hand side
	Term* currp = p.head->next;

	//iterating the right hand side terms
	while (currp != p.head && currp->coeff != 0)
	{
		rhs.changeCoefficient(currp->coeff, currp->power);
		currp = currp->next;
	}

	*this = *this - rhs;
	return *this;
}
//end of operator "-="

// -------------------------------operator "<<"------------------------
// Description
// operator-=	:	overloading << for appropiate output
//					- sign comes with integer. i am adding 
//					+ sign if the coeff > 0				
// preconditions:	- sign if the coeff < 0
//					+ sign if coeff > 0
//					if coeff = 0, removed already
// postconditions:	shows correct output with correct signs	
//					- and + sign and correct power output
// -------------------------------------------------------------------
ostream& operator<<(ostream& output, const Polynomial& p)
{

	stringstream result;

	//if the size is zero, list is empty.
	if (p.size == 0)
		cout << "Empty" << endl;

	else
	{
		//iteration. pointer to head->next
		Polynomial::Term* curr = p.head->next;

		while (curr != p.head)
		{
			//if coeff is bigger than 1
			if (curr->coeff > 1)
			{
				if (result.tellp() != std::streampos(0))
					result << " + "; //adding + sign

				if (curr->power > 1) // checking 2x^2
				{
					result << curr->coeff << "x^" << curr->power;
				}

				else if (curr->power == 0) //checking 2x^0
				{
					result << curr->coeff;
				}

				else if (curr->power == 1) //checking 2x^1
				{
					result << curr->coeff << "x";
				}
			}

			else if (curr->coeff == 1) //if coeff is 1
			{
				if (result.tellp() != std::streampos(0))
					result << " + "; // adding + sign

				if (curr->power == 0) //checking 1x^0
				{
					result << curr->coeff;
				}
				else if (curr->power == 1) // checking 1x^1
				{
					result << "x";
				}
				else if (curr->power > 1) //checking 1x^2
				{
					result << "x^" << curr->power;
				}
			}

			else if (curr->coeff < -1) // if coeff is less than -1
			{
				if (curr->power > 1) //checking -2x^2
				{
					result << (curr->coeff) << "x^" << curr->power;
				}

				else if (curr->power == 0) // checking -2x^0
				{
					result << (curr->coeff);
				}

				else if (curr->power == 1) // checking -2x^1
				{
					result << (curr->coeff) << "x";
				}
			}

			else if (curr->coeff == -1) //if coefficient is -1
			{
				if (curr->power == 0)
				{
					result << (curr->coeff); 
				}
				else if (curr->power == 1) // checking -1x^1
				{
					result << "x";
				}
				else if (curr->power > 1) // checking -1x^2
				{
					result << "x^" << (curr->power);
				}
			}
			curr = curr->next; //iteration
		}
		output << result.str() << endl;
	}
	return output;
}
//end of operator "<<"