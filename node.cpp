#include "node.h"
#include "date.h"

void Node::Evalute(Date date, string str) {
	cout << "GAG";
}

class EmptyNode : public Node {

};

DateComparisonNode::DateComparisonNode (Comparison cmp, Date date) {
	comparison_ = cmp;
	date_= date;
}

EventComparisonNode::EventComparisonNode (Comparison cmp, string str) {
	comparison_ = cmp;
	value = str;
}
class LogicalOperationNode : public Node {

};
