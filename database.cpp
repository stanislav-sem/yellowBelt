#include "database.h"
#include <algorithm>

void Database::Add(const Date date, const string event) {
	if (find(database[date].begin(), database[date].end(), event) == database[date].end()) {
		database[date].push_back(event);
	}
}

ostream& Database::Print(ostream& os) {
	os << "GAG" << endl;
	return os;
}
