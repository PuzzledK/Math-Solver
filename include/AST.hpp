#pragma once
#include <memory>
#include <string>
#include <unordered_map>

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual double evaluate(std::unordered_map<std::string, double> &mp) const = 0;
};

class numAST : public ASTNode {
    double num;
public:
    numAST(double num);
    double evaluate(std::unordered_map<std::string, double> &mp) const override;
    double get() const;
};

class binOpAST : public ASTNode {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    char op;
public:
    binOpAST(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right, char op);
    double evaluate(std::unordered_map<std::string, double> &mp) const override;
};

class mathFuncAST : public ASTNode {
    std::string funcName;
    std::unique_ptr<ASTNode> expr;

    public:
        mathFuncAST(std::string funcName,std::unique_ptr<ASTNode> expr);
        double evaluate(std::unordered_map<std::string, double> &mp) const override;
};

class varAST : public ASTNode {
    std::string  varName;
    
    public:
        varAST(std::string str);
        double evaluate(std::unordered_map<std::string, double> &mp) const override;
};

class varAssignAST : public ASTNode {
    std::string varName;
    std::unique_ptr<ASTNode> expression;

    public:
        varAssignAST(std::string varName, std::unique_ptr<ASTNode> expression);
        double evaluate(std::unordered_map<std::string, double> &mp) const override;
};