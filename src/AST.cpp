// AST.cpp
#include "AST.hpp"
#include <stdexcept>
// #include <math.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

numAST::numAST(double num) : num(num) {}

double numAST::evaluate(std::unordered_map<std::string, double> &mp) const {
    return num;
}

double numAST::get() const {
    return num;
}

binOpAST::binOpAST(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right, char op)
    : left(std::move(left)), right(std::move(right)), op(op) {}

double binOpAST::evaluate(std::unordered_map<std::string, double> &mp) const {
    double l = left->evaluate(mp);
    double r = right->evaluate(mp);

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

double mathFuncAST::evaluate(std::unordered_map<std::string, double> &mp) const {
    auto val = expr -> evaluate(mp);
    
    if(funcName == "sqrt") {
        if(val < 0){
            throw std::runtime_error("Complex numbers not supported");
        }
        return sqrt(val);
    }

    if(funcName == "log"){
        if(val <= 0) throw std::runtime_error("Invalid Input");
        return log(val);
    }

    if(funcName == "log10"){
        if(val <= 0) throw std::runtime_error("Invalid Input");
        return log10(val);
    }

    if(funcName == "sin") return sin(val * (M_PI / 180.0));
    if(funcName == "asin") return asin(val) * (180.0 / M_PI);

    if(funcName == "cos") return cos(val * (M_PI / 180.0));
    if(funcName == "acos") return acos(val) * (180.0 / M_PI);
    
    if(funcName == "tan") return tan(val * (M_PI / 180.0));
    if(funcName == "atan") return atan(val) * (180.0 / M_PI);

    throw std::runtime_error("UNSUPPORTED FUNCTION");
}

varAST::varAST(std::string str) : varName(str) {}

double varAST::evaluate(std::unordered_map<std::string, double>& mp) const {
    if(!mp.count(varName)){
        throw std::runtime_error("Undeclared Variable");
    } 

    return mp[varName];
}

varAssignAST::varAssignAST(std::string varName, std::unique_ptr<ASTNode> expression) : varName(varName),expression(std::move(expression)) {}

double varAssignAST::evaluate(std::unordered_map<std::string, double>& mp) const{
    auto val = expression->evaluate(mp);
    mp[varName] = val;
    return val;
}