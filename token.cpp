#include "token.h"

#include <stdexcept>

using namespace std;

/*
date != 2017-11-18
{{date, TokenType::DATE}, {"!=", TokenType::COMPARE_OP}, {"2017-11-18", TokenType::DATE}}
 */
vector<Token> Tokenize(istream& cl) {
  vector<Token> tokens;

  char c;
  // считываем по одному символу из входного потока
  while (cl >> c) {

	  // Если цифра, значит в потоке содержиться дата
    if (isdigit(c)) {
    	//создаем переменную string date сохраняющую символ из потока
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
    // если в потоке содержиться сивол " значит содержиться название event'а
    else if (c == '"') {
      string event;
      getline(cl, event, '"');
      tokens.push_back({event, TokenType::EVENT});
    }
    // проверка на слово date
    else if (c == 'd') {
      if (cl.get() == 'a' && cl.get() == 't' && cl.get() == 'e') {
        tokens.push_back({"date", TokenType::COLUMN});
      } else {
        throw logic_error("Unknown token");
      }
      // проверка на слово event
    } else if (c == 'e') {
      if (cl.get() == 'v' && cl.get() == 'e' && cl.get() == 'n' &&
          cl.get() == 't') {
        tokens.push_back({"event", TokenType::COLUMN});
      } else {
        throw logic_error("Unknown token");
      }
    }
    // проверка на логическое AND
    else if (c == 'A') {
      if (cl.get() == 'N' && cl.get() == 'D') {
        tokens.push_back({"AND", TokenType::LOGICAL_OP});
      } else {
        throw logic_error("Unknown token");
      }
    }
    // провекрка на логическое OR
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
