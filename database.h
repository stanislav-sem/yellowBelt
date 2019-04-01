#pragma once

#include <map>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <utility>
#include <functional>
#include "date.h"
#include "token.h"

using namespace std;


class Database {
public:
	void Add (const Date, const string);
	ostream& Print(ostream&) const;

	int RemoveIf(std::function<bool(Date, string)> );

	vector<pair<Date, string>> FindIf(std::function<bool(Date, string)> ) const;

	string Last(Date ) const;

private:
	map<Date, vector<string>> databaseVec;
	map<Date, set<string>> databaseSet;
};

	ostream& operator << (ostream& , const pair<Date, string>& );
	ostream& operator << (ostream& , const map<Date, set<string>>);
