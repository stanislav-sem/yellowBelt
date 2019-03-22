#include "database.h"

void Database::Add(const Date date, const string event) {
	database[date].push_back(event);
}

ostream& Database::Print(ostream& os) {
	os << "GAG" << endl;
	return os;
}
