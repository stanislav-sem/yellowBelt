#include "database.h"

void Database::Add(const Date date, const string event) {
	if (databaseSet[date].find(event) == databaseSet[date].end()) {
		databaseVec[date].push_back(event);
		databaseSet[date].insert(event);
	}
}

ostream& Database::Print(ostream& os) const{
	for (auto item : databaseVec) {
		for (auto el : item.second) {
			os << item.first << " " << el << endl;
		}
	}
	return os;
}

string Database::Last(Date date) const {
	stringstream _event;
	if (date < databaseVec.begin()->first) {
		throw invalid_argument("date < all existing");
	}

	auto it = databaseVec.upper_bound(date);
	if (!(--it)->second.empty()) {
		_event << it->first << " " << (databaseVec.at(it->first).back());
	}
	return _event.str();
}


ostream& operator << (ostream& os, const pair<Date, string>& input ) {
	os << input.first << " " << input.second;
	return os;
}

int Database::RemoveIf(std::function<bool(Date, string)> predicate) {
	int count = 0;
	for (auto& el : databaseVec) {
		if (el.second.size() != 0) {
			auto it =
					stable_partition(el.second.begin(), el.second.end(),
							[predicate, el](const string& str) {return !predicate(el.first, str);});

			for (auto deleter = --el.second.end(); deleter >= it; deleter--) {
				el.second.erase(deleter);
				count++;
			}
			if (el.second.size() == 0) {
				databaseVec.erase(el.first);
				databaseSet.erase(el.first);
			} else if (count != 0) {
				databaseSet[el.first] = set<string>(el.second.begin(),
						el.second.end());
			}
		}
	}
	return count;
}

vector<pair<Date, string>> Database::FindIf(std::function<bool(Date, string)> predicate) const {
	auto copyBase = databaseVec;
	vector<pair<Date, string>> result;
	for (auto& el : copyBase) {
		auto it = stable_partition(el.second.begin(), el.second.end(),
						[predicate, el](const string& str) {return !predicate(el.first, str); });
		for (auto i = it; i != el.second.end(); i++) {
			result.push_back(make_pair(el.first, *i));
		}
	}
	return result;
};
