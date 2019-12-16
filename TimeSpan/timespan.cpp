/*timespan cpp file has all
the functions and operator
overloads. All implementation is
in this file
*/

#include <iostream>
#include <sstream>
#include <cassert>
#include <iomanip>
#include "timespan.h"

using namespace std;

/*Constructor 
takes 3 valkues but these are
also have default values so only
one constructor will handle 
everything. also calling the 
private method in it for
calculation.
*/


TimeSpan::TimeSpan(double h, double m, double s)
{
	hours = h;
	minutes = m;
	seconds = s;
	simplify();
}

//Displaying operator

//overloading << operator
//setw and setfill is for
//2digit integer values
ostream& operator<<(ostream& theStream, TimeSpan const& obj)
{
	theStream <<  obj.hours << ":" << setw(2) << setfill('0') << 
		obj.minutes << ":" << setw(2) << setfill('0') << obj.seconds;
	return theStream;
}



//Equality operator
//return true if object and
//parameter object are equal
bool TimeSpan::operator== (TimeSpan const& obj)const
{
	return (hours == obj.hours &&
		minutes == obj.minutes &&
		seconds == obj.seconds);
}

//if it is not equal then its false.
//dont need to type reverse code all over again.
bool TimeSpan::operator!=(TimeSpan const& obj)const
{
	return !(*this == obj);
}


//Comparison operators..

/*
check if hours is bigger.
check if hours same and minutes bigger
check all same but seconds bigger
*/
bool TimeSpan::operator>(const TimeSpan& obj)const
{
	if (hours > obj.hours)
		return true;
	if (hours == obj.hours && minutes > obj.minutes)
		return true;
	if (hours == obj.hours && minutes == obj.minutes &&
		seconds > obj.seconds)
		return true;

	return false;
}

/*if left side is not bigger or 
equal to the right side
then return right side bigger.
*/
bool TimeSpan::operator<(const TimeSpan& obj)const
{
	return !(*this > obj) && !(*this == obj);
}

//if right side is not bigger,
//means left is bigger or equal
bool TimeSpan::operator>=(const TimeSpan& obj)const
{
	return !(*this < obj);
}

//if left side is not bigger, 
//means right is bigger or equal
bool TimeSpan::operator<=(const TimeSpan& obj)const
{
	return !(*this > obj);
}

//Addition-Subtraction Operators

/*
creating a class, sum values
in it, having calculations
and returning back
*/
TimeSpan TimeSpan::operator+ (const TimeSpan& obj)const
{
	TimeSpan spare;
	spare.hours = hours + obj.hours;
	spare.minutes = minutes + obj.minutes;
	spare.seconds = seconds + obj.seconds;
	spare.simplify();
	return spare;
}

/*
creating a class, subtract
the values,calculating
and returning back
*/
TimeSpan TimeSpan::operator- (const TimeSpan& obj)const
{
	TimeSpan spare;
	spare.hours = hours - obj.hours;
	spare.minutes = minutes - obj.minutes;
	spare.seconds = seconds - obj.seconds;
	spare.simplify();
	return spare;
}

/*
creating a class, sum the values
and modify it and returning back
*/
TimeSpan& TimeSpan::operator+= (const TimeSpan& obj)
{

	hours += obj.hours;
	minutes += obj.minutes;
	seconds += obj.seconds;
	simplify();
	return *this;
}

/*
creating a class, substract the values
and modify it and returning back
*/
TimeSpan& TimeSpan::operator-= (const TimeSpan& obj)
{

	hours -= obj.hours;
	minutes -= obj.minutes;
	seconds -= obj.seconds;
	simplify();
	return *this;
}

//Integer Multipication Operators

/*
Assignment note : 
Integer multiplication allows us to
multiply a ​TimeSpan​ with an integer
and is not commutative.
*/
TimeSpan TimeSpan::operator* (int num)
{
	TimeSpan spare;
	spare.hours = hours * num;
	spare.minutes = minutes * num;
	spare.seconds = seconds * num;
	spare.simplify();
	return spare;
}


/*
main calculation
the logis is : converting everything
to the seconds and then
converting back to hours, minutes
and seconds as a double.
at the end, casting to integer
*/
void TimeSpan::simplify()
{
	double total_seconds = (hours * 3600) + (minutes * 60) + seconds;

	//how many hours
	hours = total_seconds / 3600;
	//remainer
	double minutes_carrier = (int)total_seconds % 3600;
	//how many minutes
	minutes = minutes_carrier / 60;
	//remainer
	double seconds_carrier = (int)total_seconds % 60;

	seconds = seconds_carrier;


	//casting to integer after all calculations
	hours = (int)hours;
	minutes = (int)minutes;
	seconds = (int)seconds;

}


