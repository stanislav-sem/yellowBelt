#include "token.h"

#include <stdexcept>

using namespace std;

/*
date >= 2017-01-01 AND date < 2017-07-01
{{"date", TokenType::COLUMN}, {">=", TokenType::COMPARE_OP}, {"2017-01-01", TokenType::DATE},
 {"AND", TokenType::LOGICAL_OP}, {"date", TokenType::COLUMN}, {"<", TokenType::COMPARE_OP},
 {"2017-07-01", TokenType::DATE}}
 */
vector<Token> Tokenize(istream& cl) {
  vector<Token> tokens;

  char c;
  // ��������� �� ������ ������� �� �������� ������
  while (cl >> c) {

	  // ���� �����, ������ � ������ ����������� ����
    if (isdigit(c)) {
    	//������� ���������� string date ����������� ������ �� ������
      string date(1, c);
      for (int i = 0; i < 3; ++i) {
        while (isdigit(cl.peek())) {
          date += cl.get();
        }
        if (i < 2) {
          date += cl.get(); // Consume '-'
        }
      }
      tokens.push_back({date, TokenType::DATE});
    }
    // ���� � ������ ����������� ����� " ������ ����������� �������� event'�
    else if (c == '"') {
      string event;
      getline(cl, event, '"');
      tokens.push_back({event, TokenType::EVENT});
    }
    // �������� �� ����� date
    else if (c == 'd') {
      if (cl.get() == 'a' && cl.get() == 't' && cl.get() == 'e') {
        tokens.push_back({"date", TokenType::COLUMN});
      } else {
        throw logic_error("Unknown token");
      }
      // �������� �� ����� event
    } else if (c == 'e') {
      if (cl.get() == 'v' && cl.get() == 'e' && cl.get() == 'n' &&
          cl.get() == 't') {
        tokens.push_back({"event", TokenType::COLUMN});
      } else {
        throw logic_error("Unknown token");
      }
    }
    // �������� �� ���������� AND
    else if (c == 'A') {
      if (cl.get() == 'N' && cl.get() == 'D') {
        tokens.push_back({"AND", TokenType::LOGICAL_OP});
      } else {
        throw logic_error("Unknown token");
      }
    }
    // ��������� �� ���������� OR
    else if (c == 'O') {
      if (cl.get() == 'R') {
        tokens.push_back({"OR", TokenType::LOGICAL_OP});
      } else {
        throw logic_error("Unknown token");
      }
    }
    else if (c == '(') {
      tokens.push_back({"(", TokenType::PAREN_LEFT});
    }
    else if (c == ')') {
      tokens.push_back({")", TokenType::PAREN_RIGHT});
    }
    else if (c == '<') {
      if (cl.peek() == '=') {
        cl.get();
        tokens.push_back({"<=", TokenType::COMPARE_OP});
      } else {
        tokens.push_back({"<", TokenType::COMPARE_OP});
      }
    }
    else if (c == '>') {
      if (cl.peek() == '=') {
        cl.get();
        tokens.push_back({">=", TokenType::COMPARE_OP});
      } else {
        tokens.push_back({">", TokenType::COMPARE_OP});
      }
    }
    else if (c == '=') {
      if (cl.get() == '=') {
        tokens.push_back({"==", TokenType::COMPARE_OP});
      } else {
        throw logic_error("Unknown token");
      }
    }
    else if (c == '!') {
      if (cl.get() == '=') {
        tokens.push_back({"!=", TokenType::COMPARE_OP});
      } else {
        throw logic_error("Unknown token");
      }
    }
  }

  return tokens;
}
