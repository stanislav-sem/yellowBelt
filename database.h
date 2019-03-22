#pragma once

#include <map>
#include <vector>
#include <string>
#include "date.h"

using namespace std;


class Database {
public:
	void Add (const Date, const string);

	ostream& Print(ostream&);

private:
	map<Date, vector<string>> database;
};
