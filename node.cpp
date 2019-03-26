#include "node.h"
#include "date.h"

virtual void Node::Evaluate(Date date, string str) {
	cout << "GAG";
}

class EmptyNode : public Node {

};

DateComparisonNode::DateComparisonNode (Comparison cmp, Date date) {
	comparison_ = cmp;
	date_= date;
}
//bool DateComparisonNode::Evaluate(const Date& date_for_compare, const string& event_for_compare) {
//	switch(comparison_) {
//	case Comparison::Equal:
//		return date_ == date_for_compare;
//	case Comparison::Greater:
//		return date_ > date_for_compare;
//	case Comparison::GreaterOrEqual:
//		return date_ == date_for_compare;
//	case Comparison::Less:
//		return date_ < date_for_compare;
//	}
//}

EventComparisonNode::EventComparisonNode (Comparison cmp, string str) {
	comparison_ = cmp;
	eventValue = str;
}
//bool EventComparisonNode::Evaluate(const Date& date_for_compare, const string& event_for_compare) {
//	date_ = date_for_compare;
//	switch(comparison_)	{
//	case Comparison::Less:
//		return eventValue < event_for_compare;
//	case Comparison::Equal:
//		return eventValue == event_for_compare;
//	case Comparison::Greater:
//		return eventValue > event_for_compare;
//	case Comparison::GreaterOrEqual:
//		return eventValue >= event_for_compare;
//	case Comparison::LessOrEqual:
//		return eventValue <= event_for_compare;
//	case Comparison::NotEqual:
//		return eventValue != event_for_compare;
//	}


//	if (comparison_ == Comparison::Less) {
//		return eventValue < event_for_compare;
//	} else if (comparison_ == Comparison::LessOrEqual) {
//		return eventValue <= event_for_compare;
//	}
}
class LogicalOperationNode : public Node {

};
