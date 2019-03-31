#pragma once

#include <iomanip>
#include <iostream>
#include <istream>

using namespace std;

class Date{
public:
	Date();
	Date(int , int , int );
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	int year=0;
	int month=0;
	int day=0;

};

Date ParseDate(istream& is);

ostream& operator << (ostream& os, const Date& data);

bool operator == (const Date& , const Date& );
bool operator > (const Date& , const Date& );
bool operator >= (const Date& , const Date& );
bool operator < (const Date& , const Date& );
bool operator <= (const Date& , const Date& );
bool operator!=(const Date& , const Date& );
