// Parser.cpp
#include "Parser.hpp"
#include <stdexcept>
#include <cmath>
#include "Token.hpp"
#include <iostream>
#include <unordered_map>

#ifndef M_E
#define M_E 2.71828182845904523536
#endif 

std::unordered_map<char,int> precedence;


Parser::Parser(Lexer lex) : lexer(lex) {
    curTok = lexer.getNextToken();
    precedence['+'] = 1;
    precedence['-'] = 1;
    precedence['*'] = 2;
    precedence['/'] = 2;
    precedence['^'] = 3;
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

std::unique_ptr<ASTNode> Parser::parseBlock(){
    
    std::vector<std::unique_ptr<ASTNode>> exprs;
    do{
        auto expr = parseExpression();
        exprs.push_back(std::move(expr));

        eat(TokenType::SEMICOLON);
    }while(curTok.type != TokenType::RCURLY);

    return std::make_unique<blockAST>(std::move(exprs));
}

std::unique_ptr<ASTNode> Parser::parseCondition(){
    auto left = parseExpressionNonCurly();

    Token temp = curTok;

    if(curTok.type == TokenType::RBRAC){
        return std::make_unique<ifCondAST>("None",std::move(left),nullptr);
    }

    if(curTok.type == TokenType::EQ || curTok.type == TokenType::NE || curTok.type == TokenType::GT || curTok.type == TokenType::LT || curTok.type == TokenType::GTE || curTok.type == TokenType::LTE){
        eat(curTok.type);
    }
    else throw std::runtime_error("Expected comparision operators (Parser.cpp)");

    std::string op = temp.str;

    auto right = parseExpressionNonCurly();

    return std::make_unique<ifCondAST>(op,std::move(left),std::move(right));
}

std::unique_ptr<ASTNode> Parser::parseExpressionNonCurly(int minPrec) {
    if (curTok.type == TokenType::LCURLY) {
        throw std::runtime_error("Invalid expression");
    }

    return parseExpression(minPrec);
}

std::unique_ptr<ASTNode> Parser::parseExpression(int minPrec) {
    auto left = parseTopLevel();

    Token tempTok = curTok;

    while(true){
        char op = '0';
        int prec = -1;

        if (curTok.type == TokenType::PLUS)      { op = '+'; prec = precedence[op]; }
        else if (curTok.type == TokenType::MINUS){ op = '-'; prec = precedence[op]; }
        else if (curTok.type == TokenType::MULT) { op = '*'; prec = precedence[op]; }
        else if (curTok.type == TokenType::DIV)  { op = '/'; prec = precedence[op]; }
        else if (curTok.type == TokenType::POW)  { op = '^'; prec = precedence[op]; }
        else break;

        if (prec < minPrec) break;

        eat(curTok.type);

        auto right = parseExpression(prec + (op == '^' ? 0 : 1)); // right-associative ^

        left = std::make_unique<binOpAST>(std::move(left), std::move(right), op);
    }

    return left;
}

std::unique_ptr<ASTNode> Parser::parseTopLevel() {

    if(curTok.type == TokenType::LCURLY){
        eat(TokenType::LCURLY);
        auto res = parseBlock();
        eat(TokenType::RCURLY);

        return res;
    }

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
        auto node = parseExpressionNonCurly();
        eat(TokenType::RBRAC);
        return node;
    }
    
    else if(curTok.type == TokenType::SIN || curTok.type == TokenType::COS || curTok.type == TokenType::TAN || curTok.type == TokenType::ASIN || curTok.type == TokenType::ACOS || curTok.type == TokenType::ATAN || curTok.type == TokenType::SQRT || curTok.type == TokenType::LN || curTok.type == TokenType::LOG){
        Token temp = curTok;
        eat(curTok.type);

        eat(TokenType::LBRAC);
        auto arg = parseExpressionNonCurly();
        eat(TokenType::RBRAC);

        return std::make_unique<mathFuncAST>(temp.str,std::move(arg));
    }

    else if(curTok.type == TokenType::VAR){
        Token temp = curTok;
        eat(TokenType::VAR);

        // If assignment is to be done
        if(curTok.type == TokenType::ASSIGN){
            eat(TokenType::ASSIGN);

            auto expr = parseExpressionNonCurly();

            return std::make_unique<varAssignAST>(temp.str,std::move(expr));
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