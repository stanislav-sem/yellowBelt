#include "node.h"
#include "date.h"

Node::Node() : type(TokenType::GAG), comparison_(Comparison::GAG) {};

Node::Node(TokenType inputType, Comparison cmp) : type(inputType), comparison_(cmp) {};

DateComparisonNode::DateComparisonNode() : Node(TokenType::DATE, Comparison::GAG) {
	date_ = Date();
};

DateComparisonNode::DateComparisonNode (Comparison cmp, Date date) :
		 date_(date), Node(TokenType::DATE, cmp) {};

EventComparisonNode::EventComparisonNode() : Node(TokenType::EVENT, Comparison::GAG) {
		value = "";
};

EventComparisonNode::EventComparisonNode (Comparison cmp, string str) :
		value(str),  Node(TokenType::EVENT, cmp) {};


LogicalOperationNode::LogicalOperationNode(LogicalOperation lo, shared_ptr<Node> a, shared_ptr<Node> b) {
	logOp = lo;
	leftForCompare = a;
	rightForCompare = b;
}

EmptyNode::EmptyNode() : Node() {};

Comparison Node::GetComparison() const {
	return comparison_;
}

bool EmptyNode::Evaluate(Date , string)  {
	return true;
}
bool DateComparisonNode::Evaluate(Date date_for_compare, string event_for_compare) {
	const Comparison cmp = GetComparison();
	switch(cmp) {
	case Comparison::Equal:
		return date_for_compare == date_;
	case Comparison::Greater:
		return date_for_compare > date_;
	case Comparison::GreaterOrEqual:
		return date_for_compare >= date_;
	case Comparison::Less:
		return date_for_compare < date_;
	case Comparison::LessOrEqual:
		return date_for_compare <= date_;
	case Comparison::NotEqual:
		return date_for_compare != date_;
	default:
		return false;
	}
}

bool EventComparisonNode::Evaluate(Date date_for_compare, string event_for_compare) {
	const Comparison cmp = GetComparison();
	switch(cmp) {
	case Comparison::Less:
		return event_for_compare < value;
	case Comparison::Equal:
		return event_for_compare == value;
	case Comparison::Greater:
		return event_for_compare > value;
	case Comparison::GreaterOrEqual:
		return event_for_compare >= value;
	case Comparison::LessOrEqual:
		return event_for_compare <= value;
	case Comparison::NotEqual:
		return event_for_compare != value;
	default:
		return false;
	}
}

bool LogicalOperationNode::Evaluate(Date date_for_compare, string event_for_compare) {
	switch (logOp) {
	case LogicalOperation::And:
		return leftForCompare->Evaluate(date_for_compare, event_for_compare) &&
				rightForCompare->Evaluate(date_for_compare, event_for_compare);
	case LogicalOperation::Or:
		return leftForCompare->Evaluate(date_for_compare, event_for_compare) ||
			   rightForCompare->Evaluate(date_for_compare, event_for_compare);
	default:
		return false;
	}
}


