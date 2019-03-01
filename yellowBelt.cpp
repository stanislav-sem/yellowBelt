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

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}
void AssertFalse(bool b, const string& hint) {
  AssertEqual(b, false, hint);
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

bool IsPalindrom (string x) {
	int l = x.size();
	for (int i = 0; i < l; i++) {
		if (x[i] != x[l - 1 - i]) {
			return false;
			}
		}
	return true;
}

void TestZeroString() {
	Assert(IsPalindrom(""), "Zero string");
}
void TestOneChar() {
	Assert(IsPalindrom("A"), "One char string");
}
void TestPalindrom() {
	Assert(IsPalindrom("madam"), "madam");
	Assert(IsPalindrom("wasitacaroracatisaw"), "wasitacaroracatisaw");
	Assert(IsPalindrom("LeveL"), "LeveL");
}
void TestWithSpace() {
	Assert(IsPalindrom("bep peb"), "bep peb");
	Assert(IsPalindrom("m1a1m"), "m1a1m");
	Assert(IsPalindrom("c1h2p3 3p2h1c"), "c1h2p3 3p2h1c");
}
void TestNotPalindrom() {
	AssertFalse(IsPalindrom("Not palindrom"), "Not palindrom");
	AssertFalse(IsPalindrom("aosdghfowfij"), "aosdghfowfij");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestZeroString, "TestZeroString");
  runner.RunTest(TestOneChar, "TestOneChar");
  runner.RunTest(TestPalindrom, "TestPalindrom");
  runner.RunTest(TestWithSpace, "TestWithSpace");
  runner.RunTest(TestNotPalindrom, "TestNotPalindrom");


  return 0;
}
