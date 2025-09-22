#include "tokenizer.h"
#include <cctype>
#include <stdexcept>
#include <cmath>

Tokenizer::Tokenizer(const std::string& input)
    : text(input), pos(0), currentChar(input.empty() ? '\0' : input[0]) {}

void Tokenizer::advance() {
    pos++;
    currentChar = (pos < text.size()) ? text[pos] : '\0';
}

void Tokenizer::skipWhitespace() {
    while (currentChar != '\0' && std::isspace(currentChar)) {
        advance();
    }
}

double Tokenizer::number() {
    std::string result;
    while (currentChar != '\0' && (std::isdigit(currentChar) || currentChar == '.')) {
        result.push_back(currentChar);
        advance();
    }
    return std::stod(result);
}

std::string Tokenizer::identifier() {
    std::string result;
    while (currentChar != '\0' && std::isalpha(currentChar)) {
        result.push_back(currentChar);
        advance();
    };
    return result;
}

Token Tokenizer::getNextToken() {
    while (currentChar != '\0') {
        if (std::isspace(currentChar)) { skipWhitespace(); continue;}
        if (std::isdigit(currentChar) || currentChar == '.') return {TokenType::NUMBER, number()};
        if (std::isalpha(currentChar)) {
            std::string name = identifier();
            return {TokenType::IDENTIFIER, 0, name};
        }
        if (currentChar == '+') { advance(); return {TokenType::PLUS, 0}; }
        if (currentChar == '-') { advance(); return {TokenType::MINUS, 0}; }
        if (currentChar == '*') { advance(); return {TokenType::TIMES, 0}; }
        if (currentChar == '/') { advance(); return {TokenType::DIVIDE, 0}; }
        if (currentChar == '(') { advance(); return {TokenType::LPAREN, 0}; }
        if (currentChar == ')') { advance(); return {TokenType::RPAREN, 0}; }
        if (currentChar == '^') { advance(); return {TokenType::HAT, 0}; }
        if (currentChar == '!') { advance(); return {TokenType::FACTORIAL, 0}; }

        throw std::runtime_error("unexpected character");
    }
    return {TokenType::END, 0};
}