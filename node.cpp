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

LogicalOperationNode::LogicalOperationNode(LogicalOperation lo, shared_ptr<Node> a, shared_ptr<Node> b) {
	logOp = lo;
	leftForCompare = a;
	rightForCompare = b;
}

bool Node::Evaluate(Date , string) {
	cout << "GAG Node::Evaluate"<< endl;
	return false;
}

bool DateComparisonNode::Evaluate(Date date_for_compare, string event_for_compare) {
	switch(comparison_) {
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
	case Comparison::GAG:
		cout << "something went wrong!";
		break;
	}
}

bool EventComparisonNode::Evaluate(Date date_for_compare, string event_for_compare) {
	switch(comparison_)	{
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
	case Comparison::GAG:
		cout << "something went wrong!";
		break;
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
	}
}


