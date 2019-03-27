#pragma once

#include "token.h"
#include "date.h"
#include <memory>

using namespace std;

class Node { // @suppress("Class has a virtual method and non-virtual destructor")
public:
	Node ();
	virtual bool Evaluate( Date , string );
	TokenType type;
	string value;
};


class EmptyNode : public Node {}; // @suppress("Class has a virtual method and non-virtual destructor")


class DateComparisonNode : public Node { // @suppress("Class has a virtual method and non-virtual destructor")
public:
	DateComparisonNode(Comparison , Date );
	bool Evaluate( Date ,  string );
	Date date_;
	Comparison comparison_;
};


class EventComparisonNode : public Node { // @suppress("Class has a virtual method and non-virtual destructor")
public:
	EventComparisonNode(Comparison , string);
	bool Evaluate( Date ,  string );
	Comparison comparison_;
};


class LogicalOperationNode : public Node { // @suppress("Class has a virtual method and non-virtual destructor")
public:
	LogicalOperationNode(LogicalOperation, shared_ptr<Node>, shared_ptr<Node>);
	bool Evaluate(Date , string);
	LogicalOperation logOp;
	shared_ptr<Node> leftForCompare;
	shared_ptr<Node> rightForCompare;
};
