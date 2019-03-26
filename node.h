#pragma once

#include "token.h"
#include "date.h"

using namespace std;

class Node {
public:
	Node ();
	virtual bool Evaluate( Date , string );
	TokenType type;
	string value;
	Comparison comparison_;
	Date date_;
};


class EmptyNode : public Node {};


class DateComparisonNode : public Node {
public:
	DateComparisonNode(Comparison , Date );
	virtual bool Evaluate( Date ,  string );
};


class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison , string);
	virtual bool Evaluate( Date ,  string );
};


class LogicalOperationNode : public Node {
public:
	LogicalOperation logOp;
};
