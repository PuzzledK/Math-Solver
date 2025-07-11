#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Context.hpp"
#include "Value.hpp"
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual customType::Value evaluate(Context &context)   = 0;
};

class numAST : public ASTNode {
    double num;
    public:
        numAST(double num);
        customType::Value evaluate(Context& context)   override;
        double get();
};

class binOpAST : public ASTNode {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    char op;
    public:
        binOpAST(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right, char op);
        customType::Value evaluate(Context& context)   override;
};

class mathFuncAST : public ASTNode {
    std::string funcName;
    std::unique_ptr<ASTNode> expr;

    public:
        mathFuncAST(std::string funcName,std::unique_ptr<ASTNode> expr);
        customType::Value evaluate(Context& context)   override;
};

class varAST : public ASTNode {
    std::string  varName;
    
    public:
        varAST(std::string str);
        customType::Value evaluate(Context& context)   override;
};

class varAssignAST : public ASTNode {
    std::string varName;
    std::unique_ptr<ASTNode> expression;

    public:
        varAssignAST(std::string varName, std::unique_ptr<ASTNode> expression);
        customType::Value evaluate(Context& context)   override;
};

class ifThenElseAST : public ASTNode{
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> thenBlock;
    std::unique_ptr<ASTNode> elseBlock;

    public:
        ifThenElseAST(std::unique_ptr<ASTNode> condition,std::unique_ptr<ASTNode> thenBlock,std::unique_ptr<ASTNode> elseBlock);

        customType::Value evaluate(Context& context)   override;
};

class ifCondAST : public ASTNode{
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

    public:
        ifCondAST(std::string op,std::unique_ptr<ASTNode> left,std::unique_ptr<ASTNode> right);
        customType::Value evaluate(Context& context)   override;
};

class blockAST : public ASTNode{
    std::vector<std::unique_ptr<ASTNode>> exprs;

    public:
        blockAST(std::vector<std::unique_ptr<ASTNode>> exprs);
        customType::Value evaluate(Context& context)   override;
};

class funcBlockAST : public ASTNode {
    std::vector<std::unique_ptr<ASTNode>> exprs;

    public:
        funcBlockAST(std::vector<std::unique_ptr<ASTNode>> exprs);
        customType::Value evaluate(Context& context)   override;
};

class funcDefAST : public ASTNode {
    std::string funcName;
    std::vector<std::string> args;
    std::unique_ptr<ASTNode> funcBody;
    
    public:
        funcDefAST(std::string funcName, std::vector<std::string> args, std::unique_ptr<ASTNode> funcBody);
        customType::Value evaluate(Context& context)   override;
};

class funcCallAST : public ASTNode {
    std::string funcName;
    std::vector<std::unique_ptr<ASTNode>> args;

    public:
        funcCallAST(std::string funcName, std::vector<std::unique_ptr<ASTNode>> args);
        customType::Value evaluate(Context& context)   override;
};

class printAST : public ASTNode{
    std::unique_ptr<ASTNode> expr;

    public:
        printAST(std::unique_ptr<ASTNode> expr);
        customType::Value evaluate(Context& context) override;
};