#pragma once
#include <string>
#include "Token.hpp"

class Lexer {
private:
    std::string input;
    int pos;

    Token parseNum(char c);
    Token parseStr(char c);

public:
    Lexer();
    Lexer(std::string input);
    Token getNextToken();
};
