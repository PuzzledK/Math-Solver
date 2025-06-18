#pragma once
#include <string>

enum class TokenType {
    NUM,
    PLUS,
    MINUS,
    MULT,
    DIV,
    POW,
    LBRAC,
    RBRAC,
    SIN,
    ASIN,
    COS,
    ACOS,
    TAN,
    ATAN,
    SQRT,
    EXPO,
    END
};

struct Token {
    TokenType type;
    double num;
    std::string str = "";
};

std::string tokenTypeToString(TokenType type);
