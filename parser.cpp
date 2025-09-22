#include "parser.h"
#include <stdexcept>
#include <cmath>
#include <numbers>
#include <numeric>

Parser::Parser(Tokenizer& tokenizer) : tokenizer(tokenizer) {
    currentToken = tokenizer.getNextToken();
}

void Parser::eat(TokenType type) {
    if (currentToken.type == type) {
        currentToken = tokenizer.getNextToken();
    } else {
        throw std::runtime_error("Unexpected token");
    }
}


double Parser::factor() {
    double result;

    if (currentToken.type == TokenType::NUMBER) {
        result = currentToken.value;
        eat(TokenType::NUMBER);
    } else if (currentToken.type == TokenType::IDENTIFIER) {
        std::string funcName = currentToken.name;
        eat(TokenType::IDENTIFIER);
        
        if (currentToken.type == TokenType::LPAREN) {
            eat(TokenType::LPAREN);
            double arg = expr();
            eat(TokenType::RPAREN);

            if (funcName == "sqrt") result = std::sqrt(arg);
            if (funcName == "cbrt") result = std::cbrt(arg);
            if (funcName == "exp") result = std::exp(arg);
            if (funcName == "ln") result = std::log(arg);
            if (funcName == "sin") result = std::sin(arg);
            if (funcName == "cos") result = std::cos(arg);
            if (funcName == "tan") result = std::tan(arg);
            if (funcName == "sec") result = 1.0 / std::cos(arg);
            if (funcName == "csc") result = 1.0 / std::sin(arg);
            if (funcName == "cot") result = 1.0 / std::tan(arg);
            if (funcName == "asin") result = std::asin(arg);
            if (funcName == "acos") result = std::acos(arg);
            if (funcName == "atan") result = std::atan(arg);
            if (funcName == "acsc") result = std::asin(1.0 / arg);
            if (funcName == "asec") result = std::acos(1.0 / arg);
            if (funcName == "acot") result = std::atan(1.0 / arg);
            if (funcName == "sinh") result = std::sinh(arg);
            if (funcName == "cosh") result = std::cosh(arg);
            if (funcName == "tanh") result = std::tanh(arg);
            if (funcName == "csch") result = 1.0 / std::sinh(arg);
            if (funcName == "sech") result = 1.0 / std::cosh(arg);
            if (funcName == "coth") result = 1.0 / std::tanh(arg);
            if (funcName == "asinh") result = std::asinh(arg);
            if (funcName == "acosh") result = std::acosh(arg);
            if (funcName == "atanh") result = std::atanh(arg);
            if (funcName == "acsch") result = std::asinh(1.0 / arg);
            if (funcName == "asech") result = std::acosh(1.0 / arg);
            if (funcName == "acoth") result = std::atanh(1.0 / arg);
            if (funcName == "round") result = std::round(arg);
            if (funcName == "ceil") result = std::ceil(arg);
            if (funcName == "floor") result = std::floor(arg);
            if (funcName == "trunc") result = std::trunc(arg);
        } else if (funcName == "e") {
            result = M_E;
        } else if (funcName == "pi") {
            result = M_PI;
        } else {
            throw std::runtime_error("Unexpected Token");
        }
        

    } else if (currentToken.type == TokenType::LPAREN) {
        eat(TokenType::LPAREN);
        result = expr();
        eat(TokenType::RPAREN);
    } else if (currentToken.type == TokenType::MINUS) {
        eat(TokenType::MINUS);
        result = -factor();
    } else {
        throw std::runtime_error("Invalid syntax in factor()");
    }

    while (currentToken.type == TokenType::FACTORIAL) {
        eat(TokenType::FACTORIAL);
        result = std::tgamma(result + 1);
    }

    return result;
    
}

double Parser::term() {
    double result = factor();
    while (currentToken.type == TokenType::TIMES || currentToken.type == TokenType::DIVIDE || currentToken.type == TokenType::HAT || currentToken.type == TokenType::FACTORIAL) {
        if (currentToken.type == TokenType::HAT) {
            eat(TokenType::HAT);
            result = pow(result,factor());
        } else if(currentToken.type == TokenType::TIMES) {
            eat(TokenType::TIMES);
            result *= factor();
        } else if(currentToken.type == TokenType::DIVIDE) {
            eat(TokenType::DIVIDE);
            result /= factor();
        };
    };
    return result;
}

double Parser::expr() {
    double result = term();
    while (currentToken.type == TokenType::PLUS || currentToken.type == TokenType::MINUS) {
        if (currentToken.type == TokenType::PLUS) {
            eat(TokenType::PLUS);
            result += term();
        } else {
            eat(TokenType::MINUS);
            result -= term();
        };
    };
    return result;
}

double Parser::parse() {
    return expr();
}