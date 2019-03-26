#pragma once

#include "token.h"
#include "date.h"
#include <memory>

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
	bool Evaluate( Date ,  string );
};


class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison , string);
	bool Evaluate( Date ,  string );
};


class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(LogicalOperation, shared_ptr<Node>, shared_ptr<Node>);
	LogicalOperation logOp;
};
