#pragma once
#include "tokenizer.h"

class Parser {
    public:
        Parser(Tokenizer& tokenizer);
        double parse();
    
    private:
        Token currentToken;
        Tokenizer& tokenizer;

        void eat(TokenType type);
        double factor();
        double term();
        double expr();
};