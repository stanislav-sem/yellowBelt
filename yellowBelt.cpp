#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}
template<class T, class U>
void AssertNotEqual(const T& t, const U& u, const string& hint = {}) {
  if (t == u) {
    ostringstream os;
    os << "Assertion failed: " << t << " == " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		// добавить факт изменения имени на first_name в год year
		name[year] = first_name;
	}
	void ChangeLastName(int year, const string& last_name) {
		// добавить факт изменения фамилии на last_name в год year
		surname[year] = last_name;
	}
	string GetFullName(int year) {
		// получить имя и фамилию по состоянию на конец года year
		string result_name = "", result_surname = "", result;
		for (const auto& i : name) {
			if (i.first > year){
				break;
			}
			result_name = i.second;
		}
		for (const auto& i : surname) {
			if (i.first > year){
				break;
			}
			result_surname = i.second;
		}
		if (result_name == "" && result_surname == "") {
			result = "Incognito";
		} else if (result_name == "") {
			result = result_surname + " with unknown first name";
		} else if (result_surname == "") {
			result = result_name + " with unknown last name";
		} else {
			result = result_name +" " + result_surname;
		}
		return result;

	}
private:
	map<int, string> name;
	map<int, string> surname;
};

void TestIncognito () {
	Person person;
	AssertEqual(person.GetFullName(0), "Incognito", "Not incognito at 0 year.");
	person.ChangeFirstName(2000, "Polina");
	AssertEqual(person.GetFullName(1999), "Incognito", "Not incognito at 1999 year.");
	AssertNotEqual(person.GetFullName(2001), "Incognito", "False incognito at 2001 year.");
}

int main() {
	TestRunner runner;
	runner.RunTest(TestIncognito, "TestIncognito");

	Person person;
	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : { 1900, 1965, 1990 }) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : { 1969, 1970 }) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : { 1969, 1970 }) {
		cout << person.GetFullName(year) << endl;
	}
	return 0;
}
