#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

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


int GetDistinctRealRootCount(double a, double b, double c) {
	set<double> korni;
	double DD = b * b - 4 * a * c;
	if (DD < 0) {
		return 0;
	}
	if (a == 0 && b != 0) {
		korni = {0, -c/b};
	} else if (a == 0 && b == 0) {
		return 0;
	} else {
		double D = sqrt(DD);
		double x1 = (-b + D)/(2 * a);
		double x2 = (-b - D)/(2 * a);
		set<double> korni = {x1, x2};
	}
//  cout << korni << endl;
	return korni.size();
}
void Test1() {
	//проверяем правильность решения в классическом случае
	AssertEqual(GetDistinctRealRootCount(1, 3, -4), 2, "Test1.1");
	AssertEqual(GetDistinctRealRootCount(-6, -5, -1), 2, "Test1.2");
}

void Test2() {
	//c=0
	AssertEqual(GetDistinctRealRootCount(1, -4, 0), 2, "Test2.1");
	AssertEqual(GetDistinctRealRootCount(1, -9, 0), 2, "Test2.2");
	AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1, "Test2.3");
}
void Test3() {
	//b=0
	AssertEqual(GetDistinctRealRootCount(1, 0, -9), 2, "Test3.1");
	AssertEqual(GetDistinctRealRootCount(1, 0, 9), 0, "Test3.2");
	AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1, "Test3.3");
}
void Test4() {
	// a=0
	AssertEqual(GetDistinctRealRootCount(0, 1, 1), 1, "Test4.1");
	AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1, "Test4.2");
}


int main() {
  TestRunner runner;
//  cout << GetDistinctRealRootCount(1, 3, -4);
  runner.RunTest(Test1, "Test1");
  runner.RunTest(Test2, "Test2");
  runner.RunTest(Test3, "Test3");
  runner.RunTest(Test4, "Test4");
//  double a = 1, b = 0, c = 9;
//  cout << sqrt(b*b - 4 * a * c);
  return 0;
}
