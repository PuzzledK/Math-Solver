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
    END
};

struct Token {
    TokenType type;
    double num;
};

std::string tokenTypeToString(TokenType type);
