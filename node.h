#pragma once

#include "token.h"
#include "date.h"

using namespace std;

class Node {
public:
	void Evaluate(Date , string);
	TokenType type;
	string value;
};

class EmptyNode : public Node {};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(Comparison , Date );
public:
	Comparison comparison_;
	Date date_;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison , string);
	Comparison comparison_;
};

class LogicalOperationNode : public Node {};
