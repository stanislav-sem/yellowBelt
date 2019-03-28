#pragma once

#include <map>
#include <vector>
#include <string>
#include <set>
#include "date.h"
#include "token.h"

using namespace std;


class Database {
public:
	void Add (const Date, const string);
	ostream& Print(ostream&);

	template <typename Func>
	int RemoveIf(Func& predicate) {
		int count = 0;
		if (*predicate.type == "a") {
			for (auto el : databaseVec) {
				if (predicate(el.first, "")) {
					databaseVec.erase(el.first);
					databaseSet.erase(el.first);
				}
			}
		}

		return count;
	}

	void Last(Date);

private:
	map<Date, vector<string>> databaseVec;
	map<Date, set<string>> databaseSet;
};
