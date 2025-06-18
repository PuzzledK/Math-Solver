// AST.cpp
#include "AST.hpp"
#include <stdexcept>
// #include <math.h>
#include <cmath>

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
        case '^': return pow(l,r);
        case '/': 
            if (r == 0) throw std::runtime_error("Division by zero");
            return l / r;
        default:
            throw std::runtime_error("Invalid operator");
    }
}

mathFuncAST::mathFuncAST(std::string funcName,std::unique_ptr<ASTNode> expr) : funcName(funcName), expr(std::move(expr)) {}

double mathFuncAST::evaluate() const {
    auto val = expr -> evaluate();
    
    if(funcName == "sqrt") {
        if(val < 0){
            throw std::runtime_error("Complex numbers not supported");
        }
        return sqrt(val);
    }
    if(funcName == "sin") return sin(val * (M_PI / 180.0));
    if(funcName == "asin") return asin(val * (M_PI / 180.0));
    if(funcName == "cos") return cos(val * (M_PI / 180.0));
    if(funcName == "acos") return acos(val) * (180.0 / M_PI);
    if(funcName == "tan") return tan(val) * (180.0 / M_PI);
    if(funcName == "atan") return atan(val) * (180.0 / M_PI);

    throw std::runtime_error("UNSUPPORTED FUNCTION");
}