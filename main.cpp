#include <iostream>
#include <string>
#include "tokenizer.h"
#include "parser.h"

int main() {
    std::cout << "Calculatema. type 'exit' to quite. \n";
    std::string input;
    while (true) {
        std::getline(std::cin, input);
        if (input == "exit") break;

        try {
            Tokenizer tokenizer(input);
            Parser parser(tokenizer);
            double result = parser.parse();
            std::cout << "Result: " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error" << e.what() << "\n";
        };
    };
};