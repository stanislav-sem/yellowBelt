#pragma once

#include "token.h"
#include "date.h"
#include <memory>

using namespace std;

class Node { // @suppress("Class has a virtual method and non-virtual destructor")
public:
	Node();
	Node (TokenType, Comparison  );
	virtual bool Evaluate( Date , string );
	Comparison GetComparison() const ;
private:
	TokenType type;
	Comparison comparison_;

};


class EmptyNode : public Node { // @suppress("Class has a virtual method and non-virtual destructor")
public:
	EmptyNode();
	virtual bool Evaluate( Date , string );
};


class DateComparisonNode : public Node { // @suppress("Class has a virtual method and non-virtual destructor")
public:
	DateComparisonNode();
	DateComparisonNode(Comparison , Date );
	bool Evaluate( Date ,  string ) override;
	Date date_;

};


class EventComparisonNode : public Node { // @suppress("Class has a virtual method and non-virtual destructor")
public:
	EventComparisonNode();
	EventComparisonNode(Comparison , string);
	bool Evaluate( Date ,  string );
	string value;
};


class LogicalOperationNode : public Node { // @suppress("Class has a virtual method and non-virtual destructor")
public:
	LogicalOperationNode(LogicalOperation, shared_ptr<Node>, shared_ptr<Node>);
	bool Evaluate(Date , string);
	LogicalOperation logOp;
	shared_ptr<Node> leftForCompare;
	shared_ptr<Node> rightForCompare;
};
