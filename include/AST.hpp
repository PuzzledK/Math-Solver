#pragma once
#include <memory>

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual double evaluate() const = 0;
};

class numAST : public ASTNode {
    double num;
public:
    numAST(double num);
    double evaluate() const override;
    double get() const;
};

class binOpAST : public ASTNode {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    char op;
public:
    binOpAST(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right, char op);
    double evaluate() const override;
};
