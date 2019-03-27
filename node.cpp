#include "node.h"
#include "date.h"

Node::Node() {
	type = TokenType::GAG;
	value = "GAG";
}

DateComparisonNode::DateComparisonNode (Comparison cmp, Date date) : comparison_(cmp), date_(date) {};

EventComparisonNode::EventComparisonNode (Comparison cmp, string str) {
	comparison_ = cmp;
	value = str;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation lo, shared_ptr<Node>, shared_ptr<Node>) {
	logOp = lo;
}

bool Node::Evaluate(Date , string) {
	cout << "GAG Node::Evaluate"<< endl;
	return false;
}

bool DateComparisonNode::Evaluate(Date date_for_compare, string event_for_compare) {
	switch(comparison_) {
	case Comparison::Equal:
		return date_ == date_for_compare;
	case Comparison::Greater:
		return date_ > date_for_compare;
	case Comparison::GreaterOrEqual:
		return date_ >= date_for_compare;
	case Comparison::Less:
		return date_ < date_for_compare;
	case Comparison::LessOrEqual:
		return date_ <= date_for_compare;
	case Comparison::NotEqual:
		return date_ != date_for_compare;
	case Comparison::GAG:
		cout << "something went wrong!";
		break;
	}
}

bool EventComparisonNode::Evaluate(Date date_for_compare, string event_for_compare) {
	switch(comparison_)	{
	case Comparison::Less:
		return value < event_for_compare;
	case Comparison::Equal:
		return value == event_for_compare;
	case Comparison::Greater:
		return value > event_for_compare;
	case Comparison::GreaterOrEqual:
		return value >= event_for_compare;
	case Comparison::LessOrEqual:
		return value <= event_for_compare;
	case Comparison::NotEqual:
		return value != event_for_compare;
	case Comparison::GAG:
		cout << "something went wrong!";
		break;
	}
}


