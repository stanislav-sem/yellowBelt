#pragma once

#include "token.h"

using namespace std;

class Node {
public:
	TokenType type;
	string value;
};

class EmptyNode : public Node {};

class DateComprasionNode : public Node {};

class EventComprasionNode : public Node {};

class LogicalOperationNode : public Node {};
