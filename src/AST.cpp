// AST.cpp
#include "AST.hpp"
#include <stdexcept>
// #include <math.h>
#include <cmath>
#include "Context.hpp"
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

numAST::numAST(double num) : num(num) {}

customType::Value numAST::evaluate(Context &context)
{
    return customType::Value(num);
}

double numAST::get()
{
    return num;
}

binOpAST::binOpAST(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right, char op)
    : left(std::move(left)), right(std::move(right)), op(op) {}

customType::Value binOpAST::evaluate(Context &context)
{
    double l = left->evaluate(context).getNumber();
    double r = right->evaluate(context).getNumber();

    switch (op)
    {
    case '+':
        return customType::Value(l + r);
    case '-':
        return customType::Value(l - r);
    case '*':
        return customType::Value(l * r);
    case '^':
        return customType::Value(pow(l, r));
    case '/':
        if (r == 0)
            throw std::runtime_error("Division by zero");
        return customType::Value(l / r);
    default:
        throw std::runtime_error("Invalid operator");
    }
}

mathFuncAST::mathFuncAST(std::string funcName, std::unique_ptr<ASTNode> expr) : funcName(funcName), expr(std::move(expr)) {}

customType::Value mathFuncAST::evaluate(Context &context)
{
    auto val = expr->evaluate(context).getNumber();

    if (funcName == "sqrt")
    {
        if (val < 0)
        {
            throw std::runtime_error("Complex numbers not supported");
        }
        return customType::Value(sqrt(val));
    }

    if (funcName == "log")
    {
        if (val <= 0)
            throw std::runtime_error("Invalid Input");
        return customType::Value(log(val));
    }

    if (funcName == "log10")
    {
        if (val <= 0)
            throw std::runtime_error("Invalid Input");
        return customType::Value(log10(val));
    }

    if (funcName == "sin")
        return customType::Value(sin(val * (M_PI / 180.0)));
    if (funcName == "asin")
        return customType::Value(asin(val) * (180.0 / M_PI));

    if (funcName == "cos")
        return customType::Value(cos(val * (M_PI / 180.0)));
    if (funcName == "acos")
        return customType::Value(acos(val) * (180.0 / M_PI));

    if (funcName == "tan")
        return customType::Value(tan(val * (M_PI / 180.0)));
    if (funcName == "atan")
        return customType::Value(atan(val) * (180.0 / M_PI));

    throw std::runtime_error("UNSUPPORTED FUNCTION");
}

varAST::varAST(std::string str) : varName(str) {}

customType::Value varAST::evaluate(Context &context)
{
    if (!context.variables.count(varName))
    {
        throw std::runtime_error("Undeclared Variable");
    }

    return customType::Value(context.variables[varName]);
}

varAssignAST::varAssignAST(std::string varName, std::unique_ptr<ASTNode> expression) : varName(varName), expression(std::move(expression)) {}

customType::Value varAssignAST::evaluate(Context &context)
{
    auto val = expression->evaluate(context).getNumber();
    context.variables[varName] = val;
    return customType::Value(val);
}

ifThenElseAST ::ifThenElseAST(std::unique_ptr<ASTNode> condition, std::unique_ptr<ASTNode> thenBlock, std::unique_ptr<ASTNode> elseBlock) : condition(std::move(condition)), thenBlock(std::move(thenBlock)), elseBlock(std::move(elseBlock)) {};

customType::Value ifThenElseAST ::evaluate(Context &context)
{

    auto val = condition->evaluate(context).getNumber();

    if (val)
    {
        return thenBlock->evaluate(context);
    }
    else
    {
        if (elseBlock)
            return elseBlock->evaluate(context);
        else
            return customType::Value(0);
    }

    return customType::Value();
}

ifCondAST ::ifCondAST(std::string op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right) : op(op), left(std::move(left)), right(std::move(right)) {}

customType::Value ifCondAST::evaluate(Context &context)
{
    auto l = left->evaluate(context).getNumber();
    
    if (!right) {
        return customType::Value(l != 0);
    }

    auto r = right->evaluate(context).getNumber();

    if (op == "EQ")
        return customType::Value(l == r);
    else if (op == "NE")
        return customType::Value(l != r);
    else if (op == "GT")
        return customType::Value(l > r);
    else if (op == "LT")
        return customType::Value(l < r);
    else if (op == "GTE")
        return customType::Value(l >= r);
    else if (op == "LTE")
        return customType::Value(l <= r);
    else
        throw std::runtime_error("Expected Comparison operator (AST.cpp)");
}


blockAST ::blockAST(std::vector<std::unique_ptr<ASTNode>> exprs) : exprs(std::move(exprs)) {}

customType::Value blockAST ::evaluate(Context &context)
{
    Context localContext = context.makeLocalContext();
    for (int i = 0; i < exprs.size(); i++)
    {
        exprs[i]->evaluate(localContext);
    }

    return customType::Value();
}

funcBlockAST::funcBlockAST(std::vector<std::unique_ptr<ASTNode>> exprs) : exprs(std::move(exprs)) {}

customType::Value funcBlockAST::evaluate(Context &context)
{
    // Context localContext;
    for (int i = 0; i < exprs.size(); i++)
    {
        exprs[i]->evaluate(context);
    }

    return customType::Value();
}

funcDefAST ::funcDefAST(std::string funcName, std::vector<std::string> args, std::unique_ptr<ASTNode> funcBody) : funcName(std::move(funcName)), args(std::move(args)), funcBody(std::move(funcBody)) {}

customType::Value funcDefAST ::evaluate(Context &context)
{
    context.functions[funcName] = std::make_pair(std::move(args), std::move(funcBody));

    return customType::Value();
}

funcCallAST ::funcCallAST(std::string funcName, std::vector<std::unique_ptr<ASTNode>> args) : funcName(std::move(funcName)), args(std::move(args)) {}

customType::Value funcCallAST::evaluate(Context &context)
{
    auto it = context.functions.find(funcName);

    if (it == context.functions.end())
    {
        throw std::runtime_error("Unrecognized Function " + funcName);
    }

    auto &[allArgs, funcBody] = it->second;

    if (args.size() != allArgs.size())
    {
        throw std::runtime_error("Invalid / Incomplete arguments to function " + funcName);
    }

    Context localContext;

    for (int i = 0; i < args.size(); i++)
    {
        localContext.variables[allArgs[i]] = args[i]->evaluate(context).getNumber();
    }

    return funcBody->evaluate(localContext);
}

printAST ::printAST(std::unique_ptr<ASTNode> expr) : expr(std::move(expr)) {}
customType::Value printAST ::evaluate(Context &context)
{
    auto eval = expr->evaluate(context).getNumber();

    std::cout << "--> " << eval << std::endl;

    return customType::Value();
}