// Parser.cpp
#include "Parser.hpp"
#include <stdexcept>

Parser::Parser(Lexer lex) : lexer(lex) {
    curTok = lexer.getNextToken();
}

void Parser::eat(TokenType tok) {
    if (curTok.type == tok) {
        curTok = lexer.getNextToken();
    } else {
        throw std::runtime_error("Expected token: " + tokenTypeToString(tok));
    }
}

std::unique_ptr<ASTNode> Parser::parse() {
    return parseExpression();
}

std::unique_ptr<ASTNode> Parser::parseExpression() {
    auto node = parseMulDiv();

    while (curTok.type == TokenType::PLUS || curTok.type == TokenType::MINUS) {
        char op = (curTok.type == TokenType::PLUS ? '+' : '-');
        eat(curTok.type);
        node = std::make_unique<binOpAST>(std::move(node), parseMulDiv(), op);
    }

    return node;
}

std::unique_ptr<ASTNode> Parser::parseMulDiv() {
    auto node = parsePow();

    while (curTok.type == TokenType::MULT || curTok.type == TokenType::DIV) {
        char op = (curTok.type == TokenType::MULT ? '*' : '/');
        eat(curTok.type);
        node = std::make_unique<binOpAST>(std::move(node), parsePow(), op);
    }

    return node;
}

std::unique_ptr<ASTNode> Parser::parsePow(){
    auto node = parseParenOrUnary();

    while(curTok.type == TokenType::POW){
        char op = '^';
        eat(curTok.type);

        node = std::make_unique<binOpAST>(std::move(node),parseParenOrUnary(),op);
    }

    return node;
}

std::unique_ptr<ASTNode> Parser::parseParenOrUnary() {
    if (curTok.type == TokenType::NUM) {
        auto node = std::make_unique<numAST>(curTok.num);
        eat(TokenType::NUM);
        return node;
    } 
    else if (curTok.type == TokenType::MINUS) {
        eat(TokenType::MINUS);
        return std::make_unique<binOpAST>(std::make_unique<numAST>(0), parseParenOrUnary(), '-');
    } 
    else if (curTok.type == TokenType::LBRAC) {
        eat(TokenType::LBRAC);
        auto node = parseExpression();
        eat(TokenType::RBRAC);
        return node;
    }
    else if(curTok.type == TokenType::SIN || curTok.type == TokenType::COS || curTok.type == TokenType::TAN || curTok.type == TokenType::ASIN || curTok.type == TokenType::ACOS || curTok.type == TokenType::ATAN || curTok.type == TokenType::SQRT){
        Token temp = curTok;
        eat(curTok.type);

        return std::make_unique<mathFuncAST>(temp.str,parseExpression());
    }

    throw std::runtime_error("Expected number or parenthesis");
}
