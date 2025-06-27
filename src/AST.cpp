// AST.cpp
#include "AST.hpp"
#include <stdexcept>
// #include <math.h>
#include <cmath>
#include "Context.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

numAST::numAST(double num) : num(num) {}

double numAST::evaluate(Context& context)   {
    return num;
}

double numAST::get()   {
    return num;
}

binOpAST::binOpAST(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right, char op)
    : left(std::move(left)), right(std::move(right)), op(op) {}

double binOpAST::evaluate(Context& context)   {
    double l = left->evaluate(context);
    double r = right->evaluate(context);

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

double mathFuncAST::evaluate(Context& context)   {
    auto val = expr -> evaluate(context);
    
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

double varAST::evaluate(Context& context)   {
    if(!context.variables.count(varName)){
        throw std::runtime_error("Undeclared Variable");
    } 

    return context.variables[varName];
}

varAssignAST::varAssignAST(std::string varName, std::unique_ptr<ASTNode> expression) : varName(varName),expression(std::move(expression)) {}

double varAssignAST::evaluate(Context& context)  {
    auto val = expression->evaluate(context);
    context.variables[varName] = val;
    return val;
}

ifThenElseAST :: ifThenElseAST(std::unique_ptr<ASTNode> condition,std::unique_ptr<ASTNode> thenBlock,std::unique_ptr<ASTNode> elseBlock) : condition(std::move(condition)),thenBlock(std::move(thenBlock)),elseBlock(std::move(elseBlock)) {};

double ifThenElseAST :: evaluate(Context& context)  {
    
    auto val = condition -> evaluate(context);

    if(val){
        return thenBlock -> evaluate(context);
    }
    else{
        if(elseBlock) return elseBlock -> evaluate(context);
        else return 0;
    }

    return 0;
}

ifCondAST :: ifCondAST(std::string op,std::unique_ptr<ASTNode> left,std::unique_ptr<ASTNode> right) : op(op),left(std::move(left)), right(std::move(right)) {}

double ifCondAST :: evaluate(Context& context)  {
    auto l = left -> evaluate(context);
    if(!right){
        return (l != 0);
    }
    auto r = right -> evaluate(context);
    
    if(op == "EQ")       return l == r;
    else if(op == "NE")  return l != r;
    
    else if(op == "GT")  return l > r;

    else if(op == "LT")  return l < r;
    else if(op == "GTE") return l >= r;
    else if(op == "LTE") return l <= r;

    else throw std::runtime_error("Expected Comparision operator (AST.cpp)");
}

blockAST :: blockAST(std::vector<std::unique_ptr<ASTNode>> exprs) : exprs(std::move(exprs)) {}

double blockAST :: evaluate(Context& context)   {
    Context localContext = context.makeLocalContext();
    for(int i = 0;i<exprs.size();i++){
        exprs[i] -> evaluate(localContext);
    }

    return 1;
}

funcBlockAST::funcBlockAST(std::vector<std::unique_ptr<ASTNode>> exprs) : exprs(std::move(exprs)) {}

double funcBlockAST::evaluate(Context& context) {
    //Context localContext;
    for (int i = 0;i < exprs.size();i++) {
        exprs[i]->evaluate(context);
    }

    return 1;
}

funcDefAST :: funcDefAST(std::string funcName, std::vector<std::string> args, std::unique_ptr<ASTNode> funcBody) : funcName(std::move(funcName)),args(std::move(args)), funcBody(std::move(funcBody)) {}

double funcDefAST :: evaluate(Context& context)  {
    context.functions[funcName] = std::make_pair(std::move(args),std::move(funcBody));

    return 0;
}

funcCallAST :: funcCallAST(std::string funcName, std::vector<std::unique_ptr<ASTNode>> args) : funcName(std::move(funcName)),args(std::move(args)) {}

double funcCallAST::evaluate(Context& context)   {
    auto it = context.functions.find(funcName);

    if (it == context.functions.end()) {
        throw std::runtime_error("Unrecognized Function " + funcName);
    }
        
    auto& [allArgs, funcBody] = it->second;

    if (args.size() != allArgs.size()) {
        throw std::runtime_error("Invalid / Incomplete arguments to function " + funcName);
    }

    Context localContext = context.makeLocalContext();

    for (int i = 0;i < args.size();i++) {
        localContext.variables[allArgs[i]] = args[i]->evaluate(context);
    }

    return funcBody->evaluate(localContext);
}