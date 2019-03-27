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

	template <typename Func>
	int RemoveIf(Func& predicate) {
		int count = 0;

		return count;
	}

private:
	map<Date, vector<string>> database;
};
