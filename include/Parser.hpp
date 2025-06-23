// Parser.hpp
#pragma once
#include "Lexer.hpp"
#include "AST.hpp"
#include <memory>

class Parser {
    Lexer lexer;
    Token curTok;

    void eat(TokenType tok);
    std::unique_ptr<ASTNode> parseExpression(int minPrec = 0);
    std::unique_ptr<ASTNode> parseTopLevel();
    std::unique_ptr<ASTNode> parseCondition();

public:
    Parser(Lexer lex);
    std::unique_ptr<ASTNode> parse();
};
