// Parser.cpp
#include "Parser.hpp"
#include <stdexcept>
#include <cmath>

#ifndef M_E
#define M_E 2.71828182845904523536
#endif 


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

std::unique_ptr<ASTNode> Parser::parseCondition(){
    auto left = parseExpression();

    Token temp = curTok;
    if(curTok.type == TokenType::EQ || curTok.type == TokenType::NE || curTok.type == TokenType::GT || curTok.type == TokenType::LT || curTok.type == TokenType::GTE || curTok.type == TokenType::LTE){
        eat(curTok.type);
    }
    else throw std::runtime_error("Expected comparision operators");

    std::string op = temp.str;

    auto right = parseExpression();

    return std::make_unique<ifCondAST>(op,std::move(left),std::move(right));
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
    auto node = parseTopLevel();

    while(curTok.type == TokenType::POW){
        char op = '^';
        eat(curTok.type);

        node = std::make_unique<binOpAST>(std::move(node),parseTopLevel(),op);
    }

    return node;
}

std::unique_ptr<ASTNode> Parser::parseTopLevel() {
    if (curTok.type == TokenType::NUM) {
        auto node = std::make_unique<numAST>(curTok.num);
        eat(TokenType::NUM);
        return node;
    }
    
    else if (curTok.type == TokenType::EXPO) {
        auto node = std::make_unique<numAST>(M_E);
        eat(TokenType::EXPO);
        return node;
    }

    else if (curTok.type == TokenType::MINUS) {
        eat(TokenType::MINUS);
        return std::make_unique<binOpAST>(std::make_unique<numAST>(0), parseTopLevel(), '-');
    } 

    else if (curTok.type == TokenType::LBRAC) {
        eat(TokenType::LBRAC);
        auto node = parseExpression();
        eat(TokenType::RBRAC);
        return node;
    }
    
    else if(curTok.type == TokenType::SIN || curTok.type == TokenType::COS || curTok.type == TokenType::TAN || curTok.type == TokenType::ASIN || curTok.type == TokenType::ACOS || curTok.type == TokenType::ATAN || curTok.type == TokenType::SQRT || curTok.type == TokenType::LN || curTok.type == TokenType::LOG){
        Token temp = curTok;
        eat(curTok.type);

        eat(TokenType::LBRAC);
        auto arg = parseExpression();
        eat(TokenType::RBRAC);

        return std::make_unique<mathFuncAST>(temp.str,std::move(arg));
    }

    else if(curTok.type == TokenType::VAR){
        Token temp = curTok;
        eat(TokenType::VAR);

        // If assignment is to be done
        if(curTok.type == TokenType::ASSIGN){
            eat(TokenType::ASSIGN);

            auto expr = parseExpression();

            return std::make_unique<varAssignAST>(temp.str,std::move(expr));
        }


        if(curTok.type == TokenType::EQ || curTok.type == TokenType::NE || curTok.type == TokenType::GT || curTok.type == TokenType::LT || curTok.type == TokenType::GTE || curTok.type == TokenType::LTE){
            auto left = std::make_unique<varAST>(temp.str);
            temp = curTok;
            eat(curTok.type);

            std::string op = temp.str;

            auto right = parseExpression();

            return std::make_unique<ifCondAST>(op,std::move(left),std::move(right));
        }


        // If variable access
        return std::make_unique<varAST>(temp.str);
    }

    else if(curTok.type == TokenType :: IF){
        eat(TokenType::IF);

        eat(TokenType::LBRAC);
        auto cond = parseCondition();
        eat(TokenType::RBRAC);

        eat(TokenType::THEN);

        auto thenBlock = parseExpression();

        std::unique_ptr<ASTNode> elseBlock = nullptr;
        if(curTok.type == TokenType::ELSE){
            eat(TokenType::ELSE);

            elseBlock = parseExpression();
        }

        return std::make_unique<ifThenElseAST>(std::move(cond),std::move(thenBlock),std::move(elseBlock));
    }

    throw std::runtime_error("Expected number or parenthesis");
}