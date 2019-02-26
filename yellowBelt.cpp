/*
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;
int main() {
  int q;
  cin >> q;

  map<string, vector<string>> buses_to_stops, stops_to_buses;

  for (int i = 0; i < q; ++i) {
    string operation_code;
    cin >> operation_code;

    if (operation_code == "NEW_BUS") {

      string bus;
      cin >> bus;
      int stop_count;
      cin >> stop_count;
      vector<string>& stops = buses_to_stops[bus];
      stops.resize(stop_count);
      for (string& stop : stops) {
        cin >> stop;
        stops_to_buses[stop].push_back(bus);
      }

    } else if (operation_code == "BUSES_FOR_STOP") {

      string stop;
      cin >> stop;
      if (stops_to_buses.count(stop) == 0) {
        cout << "No stop" << endl;
      } else {
        for (const string& bus : stops_to_buses[stop]) {
          cout << bus << " ";
        }
        cout << endl;
      }

    } else if (operation_code == "STOPS_FOR_BUS") {

      string bus;
      cin >> bus;
      if (buses_to_stops.count(bus) == 0) {
        cout << "No bus" << endl;
      } else {
        for (const string& stop : buses_to_stops[bus]) {
          cout << "Stop " << stop << ": ";
          if (stops_to_buses[stop].size() == 1) {
            cout << "no interchange";
          } else {
            for (const string& other_bus : stops_to_buses[stop]) {
              if (bus != other_bus) {
                cout << other_bus << " ";
              }
            }
          }
          cout << endl;
        }
      }

    } else if (operation_code == "ALL_BUSES") {

      if (buses_to_stops.empty()) {
        cout << "No buses" << endl;
      } else {
        for (const auto& bus_item : buses_to_stops) {
          cout << "Bus " << bus_item.first << ": ";
          for (const string& stop : bus_item.second) {
            cout << stop << " ";
          }
          cout << endl;
        }
      }

    }
  }

  return 0;
}
*/

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  string type;
  is >> type;
  if (type == "NEW_BUS") {
	  q.type = QueryType::NewBus;
	  int stops_count = 0;
	  is >> q.bus >> stops_count;
	  for (int i = 0; i < stops_count; i++) {
		  string stop;
		  is >> stop;
		  q.stops.push_back(stop);
	  }
  } else if (type == "BUSES_FOR_STOP") {
	  q.type = QueryType::BusesForStop;
	  is >> q.stop;
  } else if (type == "STOPS_FOR_BUS") {
	  q.type = QueryType::StopsForBus;
	  is >> q.bus;
  } else if (type == "ALL_BUSES") {
	  q.type = QueryType::AllBuses;
  }
  return is;
}

struct BusesForStopResponse {
  vector<string> vec;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if ( r.vec.size() == 0) {
		os << "No stop";
	} else {
		bool first = true;
		for (const auto&  el : r.vec) {
			if (!first) {
				os << ' ';
			}
			first = false;
			os << el;
		}
	}
	return os;
}

struct StopsForBusResponse {
  vector<string> vec_for_stops;
  map<string, vector<string>> map_for_buses;
  string bus;
};

ostream& operator <<(ostream& os, const StopsForBusResponse& r) {
	if (r.vec_for_stops.size() == 0) {
		os << "No bus";
	} else {
		for (const auto& st : r.vec_for_stops) {
			os << "Stop " << st << ": ";
			if (r.map_for_buses.count(st) == 1) {
				os << "no interchange";
			} else {
				for (const auto& b : r.map_for_buses.at(st)) {
					os << b << " ";
				}
			}
			os << endl;
		}
	}
	return os;
}

struct AllBusesResponse {
  map<string, vector<string>> all_buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.all_buses.size() == 0 ) {
	  os << "No buses";
  } else {
	  for (auto bus : r.all_buses) {
		  os << "Bus " << bus.first << ": ";
		  for (auto stop : bus.second) {
			  os << stop << " ";
		  }
		  os << endl;
	  }
  }
  return os;
}

class BusManager {
public:
	void AddBus(const string& bus, const vector<string>& stops) {
		buses_to_stops[bus] = stops;
		for (string stop : stops) {
			stops_to_buses[stop].push_back(bus);
		}
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		BusesForStopResponse response;
		if (stops_to_buses.count(stop) != 0) {
//			cout << stops_to_buses.at(stop).size() << endl;
			response.vec = stops_to_buses.at(stop);
		}
		return response;
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {
		StopsForBusResponse response;
		response.bus = bus;
		if (buses_to_stops.count(bus) != 0) {
			response.vec_for_stops = buses_to_stops.at(bus);
			response.map_for_buses = stops_to_buses;
		}
		return response;
  }

  AllBusesResponse GetAllBuses() const {
    AllBusesResponse response;
    response.all_buses = buses_to_stops;
    return response;
  }
private:
  map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
    	cout << "Adding " << q.stops.size()<< endl;
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}

