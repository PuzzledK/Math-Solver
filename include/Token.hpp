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
    LN,
    LOG,
    VAR,
    ASSIGN,
    IF,
    THEN,
    ELSE,
    EQ,NE,GT,LT,GTE,LTE,
    SEMICOLON,
    LCURLY,RCURLY,
    DEF,COMMA,
    NONE,
    END
};

struct Token {
    TokenType type = TokenType :: NONE;
    double num = 0;
    std::string str = "";
};

std::string tokenTypeToString(TokenType type);
