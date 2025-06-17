#include "Lexer.hpp"
#include <stdexcept>
#include <cctype>

Lexer::Lexer() : input(""), pos(0) {}

Lexer::Lexer(std::string input) : input(input), pos(0) {}

Token Lexer::parseNum(char c) {
    std::string num;
    num += c;

    bool dotSeen = (c == '.');

    while (pos < input.length() && (isdigit(input[pos]) || (!dotSeen && input[pos] == '.'))) {
        if (input[pos] == '.') dotSeen = true;
        num += input[pos++];
    }

    return {TokenType::NUM, std::stod(num)};
}

Token Lexer::getNextToken() {
    while (pos < input.length() && isspace(input[pos])) {
        pos++;
    }

    if (pos == input.length()) {
        return {TokenType::END, 0};
    }

    char c = input[pos++];

    switch (c) {
        case '+': return {TokenType::PLUS, 0};
        case '-': return {TokenType::MINUS, 0};
        case '*': return {TokenType::MULT, 0};
        case '/': return {TokenType::DIV, 0};
        case '(': return {TokenType::LBRAC, 0};
        case ')': return {TokenType::RBRAC, 0};
        case '^': return {TokenType::POW,0};
        default:
            if (isdigit(c) || c == '.') {
                return parseNum(c);
            }
            throw std::runtime_error("INVALID SYNTAX");
    }
}
