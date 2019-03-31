#include "date.h"

Date ParseDate(istream& is) {
	int year, month, day;
	is >> year;
	is.ignore(1);
	is >> month;
	is.ignore(1);
	is >> day;
	return Date(year, month, day);
}

Date::Date() : year(666), month(66), day(66) {};

Date::Date(int a, int b, int c) : year(a), month(b), day(c) {};

int Date::GetYear() const{
	return year;
}

int Date::GetMonth() const {
	return month;
}

int Date::GetDay() const {
	return day;
}

ostream& operator << (ostream& os, const Date& data) {
	os << setfill('0');
	os << setw(4) << data.GetYear() << '-' << setw(2) << data.GetMonth() << '-' << data.GetDay();
	return os;
}

bool operator ==(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() == rhs.GetDay();
		}
	}
	return false;
}
bool operator >(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() > rhs.GetDay();
		} else {
			return lhs.GetMonth() > rhs.GetMonth();
		}
	}
	return lhs.GetYear() > rhs.GetYear();
}
bool operator >=(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() >= rhs.GetDay();
		} else {
			return lhs.GetMonth() >= rhs.GetMonth();
		}
	}
	return lhs.GetYear() >= rhs.GetYear();
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() < rhs.GetDay();
		} else {
			return lhs.GetMonth() < rhs.GetMonth();
		}
	}
	return lhs.GetYear() < rhs.GetYear();
}

bool operator <=(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() <= rhs.GetDay();
		} else {
			return lhs.GetMonth() <= rhs.GetMonth();
		}
	}
	return lhs.GetYear() <= rhs.GetYear();
}

bool operator!=(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() != rhs.GetDay();
		}
	}
	return true;
}
