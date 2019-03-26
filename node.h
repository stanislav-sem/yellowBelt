#pragma once

#include "token.h"
#include "date.h"

using namespace std;

class Node {
public:
	template<typename T1, typename T2>
	virtual bool Evaluate(T1 inputLeft, T2 inputRight) {

	}
	TokenType type;
	string eventValue;
};


class EmptyNode : public Node {};


class DateComparisonNode : public Node {
public:
	DateComparisonNode(Comparison , Date );
	bool Evaluate(const Date& , const string& );
public:
	Comparison comparison_;
	Date date_;
};


class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison , string);
	Date date_;
	Comparison comparison_;
	bool Evaluate(const Date& , const string& );
};


class LogicalOperationNode : public Node {};
