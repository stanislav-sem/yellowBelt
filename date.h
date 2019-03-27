#pragma once

#include <iomanip>
#include <iostream>
#include <istream>

using namespace std;

class Date{
public:
	Date(int a, int b, int c);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	int year;
	int month;
	int day;

};

Date ParseDate(istringstream& is);

ostream& operator << (ostream& os, const Date& data);

bool operator == (const Date& , const Date& );
bool operator > (const Date& , const Date& );
bool operator >= (const Date& , const Date& );
bool operator < (const Date& , const Date& );
bool operator <= (const Date& , const Date& );
bool operator!=(const Date& , const Date& );
