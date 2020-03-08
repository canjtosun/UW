// ------------------------------------------------ polynomialDriver.cpp -------------------------------------------------------
// Can Tosun CSS 343 C
// Jan 11 2020
// Jan 18, 2020 - Date of Last Modification
// --------------------------------------------------------------------------------------------------------------------
// Purpose - This file is to test aritmatic, boolean and assignment operators,
// copy constructor circular doubly linked list with a dummy header.
// commented out for testing instructors test file
// --------------------------------------------------------------------------------------------------------------------



#include <iostream>
using namespace std;

#include "polynomial.h"

// commented out for testing instructors test file


int main()
{

	cout << "Checking changecoefficient, degree and power method" << endl;

	Polynomial p1;  // create a polynomial
	cout << "Polynomial 1: ";
	p1.changeCoefficient(1, 1); //add
	p1.changeCoefficient(3, 3); //add
	p1.changeCoefficient(2, 2); //add
	p1.changeCoefficient(4, 4); //add
	p1.changeCoefficient(400, 0); //add
	p1.changeCoefficient(10, 1); //replace
	p1.changeCoefficient(20, 2); //replace
	p1.changeCoefficient(30, 3); //replace
	p1.changeCoefficient(40, 4); //replace
	p1.changeCoefficient(0, 1); //remove
	p1.changeCoefficient(0, 3); //remove
	p1.changeCoefficient(5, 5); //add
	p1.changeCoefficient(6, 6); //add
	p1.changeCoefficient(-55, 69); //add
	p1.changeCoefficient(-20, 2);
	p1.changeCoefficient(6, 6); //add duplicate **doesnt let**


	
	cout << p1;

	cout << "Polynomial 1 degree:  " << p1.degree() << endl;
	cout << "Polynomial 1 coefficient of power 3:  " << p1.coefficient(3) << endl;
	cout << "Polynomial 1 coefficient of power 4:  " << p1.coefficient(4) << endl;
	cout << "Polynomial 1 coefficient of power 0:  " << p1.coefficient(0) << endl;

	cout << "--------------------------------------------------------" << endl;

	cout << "Checking = operator" << endl;

	Polynomial p2; 
	cout << "Polynomial 1: " << p1 << endl;
	cout << "Polynomial 2: " << p2 << endl;
	p2 = p1;
	cout << "After calling p2=p1" << endl;
	cout << "Polynomial 1: " << p1 << endl;
	cout << "Polynomial 2: " << p2 << endl;

	cout << "--------------------------------------------------------" << endl;

	cout << "Checking replace after using = operator" << endl;
	cout << "polynomial 2: ";
	p2.changeCoefficient(4.5, 4); //replace
	p2.changeCoefficient(3.5, 3); //add
	p2.changeCoefficient(3.5, 2); //add-replace

	cout << p2 << endl;

	cout << "--------------------------------------------------------" << endl;
	
	cout << "Creating another polynomial" << endl;
	Polynomial p3;
	cout << "polynomial 3: ";
	p3.changeCoefficient(3.0, 4);
	p3.changeCoefficient(2.0, 2);
	p3.changeCoefficient(10.0, 10);

	cout << p3 << endl;

	cout << "--------------------------------------------------------" << endl;

	cout << "Checking + operator" << endl;
	Polynomial p4;
	cout << "polynomial 4: " << p4 << endl;
	cout << "Polynomial 2: " << p2 << endl;
	cout << "Polynomial 3: " << p3 << endl;
	cout << "Polynomial 2 + Polynomial 3" << endl;
	p4 = p2 + p3;
	cout << p4 << endl;

	cout << "--------------------------------------------------------" << endl;

	cout << "Checking - operator" << endl;
	Polynomial p5;
	cout << "polynomial 5: " << p5 << endl;
	cout << "Polynomial 2: " << p2 << endl;
	cout << "Polynomial 3: " << p3 << endl;
	cout << "Polynomial 2 - Polynomial 3" << endl;
	p5 = p2 - p3;
	cout << p5 << endl;

	cout << "--------------------------------------------------------" << endl;

	cout << "Checking - operator" << endl;
	Polynomial p6;
	cout << "polynomial 6: " << p6 << endl;
	cout << "Polynomial 2: " << p2 << endl;
	cout << "Polynomial 3: " << p3 << endl;
	cout << "Polynomial 3 - Polynomial 2" << endl;
	p6 = p3-p2;
	cout << p6 << endl;

	cout << "--------------------------------------------------------" << endl;

	Polynomial p7;
	cout << "Creating another polynomial" << endl;
	cout << "polynomial 7: ";
	p7.changeCoefficient(3.0, 4);
	p7.changeCoefficient(2.0, 2);
	p7.changeCoefficient(10.0, 10);
	
	cout << p7 << endl;

	cout << "--------------------------------------------------------" << endl;

	Polynomial p8;
	cout << "Creating another polynomial" << endl;
	cout << "polynomial 8: ";
	p8.changeCoefficient(13.0, 4);
	p8.changeCoefficient(12.0, 2);
	p8.changeCoefficient(110.0, 10);

	cout << p8 << endl;

	cout << "--------------------------------------------------------" << endl;

	Polynomial p9;
	cout << "Creating another polynomial" << endl;
	cout << "polynomial 9: ";
	p9.changeCoefficient(-99.7, 99);

	cout << p9 << endl;

	cout << "--------------------------------------------------------" << endl;

	cout << "Checking == operator" << endl;
	cout << "?????? Polynomial 3 == Polynomial 7 ??????? "<<endl;
	cout << "polynomial 3: " << p3 << endl;
	cout << "polynomial 7: " << p7 << endl;
	if (p3 == p7)
		cout << "equal" << endl;
	else cout << "not equal" << endl;

	cout << "--------------------------------------------------------" << endl;

	cout << "Checking == operator" << endl;
	cout << "?????? Polynomial 7 == Polynomial 8 ??????? " << endl;
	cout << "polynomial 7: " << p7 << endl;
	cout << "polynomial 8: " << p8 << endl;
	if (p7 == p8)
		cout << "equal" << endl;
	else cout << "not equal" << endl;

	cout << "--------------------------------------------------------" << endl;

	cout << "Checking == operator" << endl;
	cout << "?????? Polynomial 1 == Polynomial 8 ??????? " << endl;
	cout << "polynomial 1: " << p1 << endl;
	cout << "polynomial 8: " << p8 << endl;
	if (p1 == p8)
		cout << "equal" << endl;
	else cout << "not equal" << endl;

	cout << "--------------------------------------------------------" << endl;

	cout << "Checking != operator" << endl;
	cout << "?????? Polynomial 3 != Polynomial 7 ??????? " << endl;
	cout << "polynomial 3: " << p3 << endl;
	cout << "polynomial 7: " << p7 << endl;
	if (p3 != p7)
		cout << "not equal" << endl;
	else cout << "equal" << endl;

	cout << "--------------------------------------------------------" << endl;

	cout << "Checking != operator" << endl;
	cout << "?????? Polynomial 7 != Polynomial 8 ??????? " << endl;
	cout << "polynomial 7: " << p7 << endl;
	cout << "polynomial 8: " << p8 << endl;
	if (p7 != p8)
		cout << "not equal" << endl;
	else cout << "equal" << endl;

	cout << "--------------------------------------------------------" << endl;

	cout << "Checking != operator" << endl;
	cout << "?????? Polynomial 1 != Polynomial 8 ??????? " << endl;
	cout << "polynomial 1: " << p1 << endl;
	cout << "polynomial 8: " << p8 << endl;
	if (p1 != p8)
		cout << "not equal" << endl;
	else cout << "equal" << endl;

	cout << "--------------------------------------------------------" << endl;

	cout << "Checking copy constructor" << endl;
	cout << "Creating a polynomial and copying polynomial 1 to there" << endl;

	Polynomial copyPol(p1);
	cout << "Copy constructor: " << copyPol << endl;

	cout << "--------------------------------------------------------" << endl;

	cout << "Checking += operator" << endl;
	cout << "Polynomial 7: " << p7;
	cout << "Polynomial 8: " << p8;
	cout << "New polynomial 7 after polynomial 7 += p8: ";
	p7 += p8;
	cout << p7 << endl;

	cout << "-----------------------------------------------------" << endl;

	cout << "Checking += operator" << endl;
	cout << "Polynomial 2: " << p2;
	cout << "Polynomial 5: " << p5;
	cout << "New polynomial 2 after polynomial 2 += p5: ";
	p2 += p5;
	cout << p2 << endl;

	cout << "-----------------------------------------------------" << endl;

	Polynomial p10;
	cout << "Creating another polynomial" << endl;
	cout << "polynomial 10: ";
	p10.changeCoefficient(99.7, 99);
	cout << "Polynomial 10: " << p10 << endl;

	cout << "-----------------------------------------------------" << endl;

	Polynomial p11;
	cout << "Polynomial 11: " << p11 << endl;
	cout << "Testing edge cases (-99) + 99 = 0" << endl;
	cout << "Polynomial 9: "<< p9 << endl;
	cout << "Polynomial 10: "<< p10 << endl;
	cout << "Polynomial 9 + Polynomial 10 : "<< endl;
	p11 = p9 + p10;
	cout << p11 << endl;

	return 0;
}

