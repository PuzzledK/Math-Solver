#include "Lexer.hpp"
#include <stdexcept>
#include <cctype>

Lexer::Lexer() : input(""), pos(0) {}

Lexer::Lexer(std::string input) : input(input), pos(0) {}

Token Lexer::parseNum(char c) {
    std::string num;
    num += c;

    bool dotSeen = (c == '.');

    while (pos < input.length() && (isdigit(input[pos]) || input[pos] == '.')) {
        if (input[pos] == '.') {
            if(dotSeen){
                throw std::runtime_error("Invalid Syntax");
            }
            dotSeen = true;
        }
        num += input[pos++];
    }

    return {TokenType::NUM, std::stod(num)};
}

Token Lexer::parseStr(char c){
    std::string str;
    str += c;

    while(pos < input.length() && isalpha(input[pos])){
        str += input[pos++];
    }

    if(str == "sin")  return {TokenType::SIN,0,"sin"};
    if(str == "cos")  return {TokenType::COS,0,"cos"};
    if(str == "tan")  return {TokenType::TAN,0,"tan"};
    if(str == "asin") return {TokenType::ASIN,0,"asin"};
    if(str == "acos") return {TokenType::ACOS,0,"acos"};
    if(str == "atan") return {TokenType::ATAN,0,"atan"};
    if(str == "sqrt") return {TokenType::SQRT,0,"sqrt"};
    if(str == "e")    return {TokenType::EXPO,0,"exp"};
    if(str == "log")  return {TokenType::LOG,0,"log10"};
    if(str == "ln")   return {TokenType::LN,0,"log"};
    if(str == "if")   return {TokenType::IF,0};
    if(str == "then") return {TokenType::THEN,0};
    if(str == "else") return {TokenType::ELSE,0};
    if(str == "def")  return { TokenType::DEF,0};
    if(str == "print") return {TokenType::PRINT,0};

    else{
        return {TokenType::VAR,0,str};
    }
    
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
        case '{': return {TokenType::LCURLY, 0};
        case '}': return {TokenType::RCURLY, 0};
        case '^': return {TokenType::POW,0};
        case ';': return {TokenType::SEMICOLON,0};
        case ',': return { TokenType::COMMA,0 };
        case '=': {
            if(pos < input.length()){
                if(input[pos] == '='){
                    pos++;
                    return {TokenType::EQ,0,"EQ"};
                }
            }
            return {TokenType::ASSIGN,0};
        }
        case '>' : {
            if(pos < input.length()){
                if(input[pos] == '='){
                    pos++;
                    return {TokenType::GTE,0,"GTE"};
                }
                else return {TokenType::GT,0,"GT"};
            }
            throw std::runtime_error("INVALID SYNTAX");
        }
        case '<' : {
            if(pos < input.length()){
                if(input[pos] == '='){
                    pos++;
                    return {TokenType::LTE,0,"LTE"};
                }
                else return {TokenType::LT,0,"LT"};
            }
            throw std::runtime_error("INVALID SYNTAX");
        }
        case '!' : {
            if(pos < input.length()){
                if(input[pos] == '='){
                    pos++;
                    return {TokenType::NE,0,"NE"};
                }
            }
            throw std::runtime_error("INVALID SYNTAX");
        }
        default:
            if (isdigit(c) || c == '.') {
                return parseNum(c);
            }
            if(isalpha(c)){
                return parseStr(c);
            }
            throw std::runtime_error("INVALID SYNTAX");
    }
}
