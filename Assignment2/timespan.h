//Can Tosun Assignment 2
/*
The header file contains variables,
class definitions and functions.
*/

#pragma once

using namespace std;

class TimeSpan
{
	double hours, minutes, seconds; // private variables
	void simplify(); // private method for calculation

public:
	//default parameter will avoid us to use 4 diff constructor
	TimeSpan(double h = 0.0, double m = 0.0, double s = 0.0);
	
	//Display Operator
	friend ostream& operator<< (ostream& theStream, TimeSpan const& obj);

	//Equality Operators
	bool operator== (const TimeSpan& obj) const;
	bool operator!= (const TimeSpan& obj) const;

	//Comparison Operators
	bool operator> (const TimeSpan& obj)const;
	bool operator< (const TimeSpan& obj)const;
	bool operator>= (const TimeSpan& obj)const;
	bool operator<= (const TimeSpan& obj)const;

	//Addition-Subtraction Operators
	TimeSpan operator+ (const TimeSpan& obj)const;
	TimeSpan operator- (const TimeSpan& obj)const;
	TimeSpan& operator+= (const TimeSpan& obj);
	TimeSpan& operator-= (const TimeSpan& obj);

	//Integer Multipication Operators
	TimeSpan operator* (int num);
};
