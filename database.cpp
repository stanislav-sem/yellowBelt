#include "database.h"
#include <algorithm>

void Database::Add(const Date date, const string event) {
	if (databaseSet[date].find(event) == databaseSet[date].end()) {
		databaseVec[date].push_back(event);
		databaseSet[date].insert(event);

	}
}

ostream& Database::Print(ostream& os) {
	for (auto item : databaseVec) {
		for (auto el : item.second) {
			os << item.first << " " << el << endl;
		}
	}
	return os;
}

void Database::Last(Date date) {
	cout << "GAG Database::Last" << endl;
}
