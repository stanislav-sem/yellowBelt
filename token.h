#pragma once

#include <sstream>
#include <vector>
using namespace std;

enum class TokenType {
  DATE,
  EVENT,
  COLUMN,
  LOGICAL_OP,
  COMPARE_OP,
  PAREN_LEFT,
  PAREN_RIGHT,
  GAG
};

struct Token {
  const string value;
  const TokenType type;
};

vector<Token> Tokenize(istream& cl);

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
	GAG
};

enum class LogicalOperation {
	Or,
	And,
	GAG
};
