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

Token Lexer::parseFunc(char c){
    std::string func;
    func += c;

    while(pos < input.length() && isalpha(input[pos])){
        func += input[pos++];
    }

    if(func == "sin")  return {TokenType::SIN,0,"sin"};
    if(func == "cos")  return {TokenType::COS,0,"cos"};
    if(func == "tan")  return {TokenType::TAN,0,"tan"};
    if(func == "asin") return {TokenType::ASIN,0,"asin"};
    if(func == "acos") return {TokenType::ACOS,0,"acos"};
    if(func == "atan") return {TokenType::ATAN,0,"atan"};
    if(func == "sqrt") return {TokenType::SQRT,0,"sqrt"};

    else throw std::runtime_error("UNKNOWN FUNCTION ENTERED");
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
            if(isalpha(c)){
                return parseFunc(c);
            }
            throw std::runtime_error("INVALID SYNTAX");
    }
}
