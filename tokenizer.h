#pragma once
#include <string>
#include <vector>

enum class TokenType {
    NUMBER, PLUS, MINUS, TIMES, DIVIDE, LPAREN, RPAREN, HAT, FACTORIAL, IDENTIFIER, END
};

struct Token {
    TokenType type;
    double value; // only used if type == NUMBER
    std::string name;
};

class Tokenizer {
public:
    Tokenizer(const std::string& input);
    Token getNextToken();

private:
    std::string text;
    size_t pos;
    char currentChar;
    void advance();
    void skipWhitespace();
    double number();
    std::string identifier();
};
