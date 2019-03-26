#pragma once

#include <iomanip>
#include <iostream>
#include <istream>

using namespace std;

class Date{
public:
	Date(int , int , int );
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	int year;
	int month;
	int day;

};

Date ParseDate(istream is);

ostream& operator << (ostream& os, const Date& data);

bool operator == (Date&, Date&);
bool operator > (Date&, Date&);
bool operator >= (Date&, Date&);
bool operator < (Date&, Date&);
bool operator <= (Date&, Date&);
bool operator!=(Date&, Date&);
