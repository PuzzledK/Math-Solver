// AST.cpp
#include "AST.hpp"
#include <stdexcept>

numAST::numAST(double num) : num(num) {}

double numAST::evaluate() const {
    return num;
}

double numAST::get() const {
    return num;
}

binOpAST::binOpAST(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right, char op)
    : left(std::move(left)), right(std::move(right)), op(op) {}

double binOpAST::evaluate() const {
    double l = left->evaluate();
    double r = right->evaluate();

    switch (op) {
        case '+': return l + r;
        case '-': return l - r;
        case '*': return l * r;
        case '/': 
            if (r == 0) throw std::runtime_error("Division by zero");
            return l / r;
        default:
            throw std::runtime_error("Invalid operator");
    }
}
