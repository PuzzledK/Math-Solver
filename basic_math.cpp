#include<utility>
#include<iostream>
#include<vector>
#include<string>
#include<memory>
#include<stdexcept>

// MAKING A TOKEN ENUM
enum class TokenType{
    NUM,
    PLUS,
    MINUS,
    MULT,
    DIV,
    LBRAC,
    RBRAC,
    END
};

// DEFINING A STRUCT FOR TOKEN
struct Token{
    TokenType type;
    double num; // for NUM Token
};

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::NUM:   return "NUM";
        case TokenType::PLUS:  return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::MULT:  return "MULT";
        case TokenType::DIV:   return "DIV";
        case TokenType::LBRAC: return "LBRAC";
        case TokenType::RBRAC: return "RBRAC";
        case TokenType::END:   return "END";
        default:               return "UNKNOWN";
    }
}

// MAKING A LEXER (TOKENIZER) CLASS
class Lexer{
    private :
        std::string input;
        int pos;
    
        Token parseNum(char c){
            std::string num;
            num += c;

            bool dotSeen = (c == '.');

            while(pos < input.length() && (isdigit(input[pos]) || (!dotSeen && input[pos] == '.'))){
                if (input[pos] == '.') dotSeen = true;
                num += input[pos++];
            }

            return {TokenType::NUM,std::stod(num)};

        }
    public:
        Lexer() : input(""),pos(0) {}
        
        Lexer(std::string input) {
            this -> input = input;
            this -> pos = 0;
        }

        Token getNextToken(){
            while(pos < input.length() && isspace(input[pos])){
                pos++;
            }

            if(pos == input.length()){
                return {TokenType::END,0};
            }

            char c = input[pos++];

            switch(c){
                case '+' : return {TokenType::PLUS,0};
                case '-' : return {TokenType::MINUS,0};
                case '*' : return {TokenType::MULT,0};
                case '/' : return {TokenType::DIV,0};
                case '(' : return {TokenType::LBRAC,0};
                case ')' : return {TokenType::RBRAC,0};
                default :
                    if(isdigit(c) || c == '.'){
                        return parseNum(c);
                    }
                    else{
                        throw std::runtime_error("INVALID SYNTAX");
                    }
            }
        }
};

// THIS IS AN ABSTRACT BASE CLASS, AS IT HAS ALL PURE VIRTUAL FUNCTIONS
class ASTNode {
    public:
        virtual ~ASTNode() = default; // PURE VIRTUAL FUNCTION.
        virtual double evaluate() const = 0; // MEANS THIS FUNCTION IS VIRTUAL i.e. MUST BE IMPLEMENTED BY DERIVED CLASSES, ALSO const means that no changes in variables take place. = 0 means this is a PURE VIRTUAL FUNCTION.
};

// MAKING A CLASS FOR NUMBER NODE, IT WILL BE CHILD OF MAIN ASTNode CLASS.
class numAST : public ASTNode {
    double num;

    public:
    numAST(double num){
        this -> num = num;
    }

    double evaluate() const override {
        return num;
    }

    double get() const {
        return num;
    }
};

// MAKING CLASS FOR BINARY EXPRESSION, CHILD OF MAIN ASTNode CLASS.
class binOpAST : public ASTNode {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    char op;

    public:
        binOpAST(std::unique_ptr<ASTNode> left,std::unique_ptr<ASTNode> right,char op){
            this -> left = std::move(left);
            this -> right = std::move(right);
            this -> op = op;

        }

        double evaluate() const override {
            auto l = left -> evaluate();
            auto r = right -> evaluate();

            switch(op){
                case '+' : return l + r;
                case '-' : return l - r;
                case '*' : return l * r;
                case '/' : if (r == 0) throw std::runtime_error("Division by zero");
                           return l / r;
                default :
                    throw std::runtime_error("INVALID TOKEN");
            }
        }
};

class Parser{
    Lexer lexer;
    Token curTok;

    void eat(TokenType tok){
        if(curTok.type == tok){
            curTok = lexer.getNextToken();
        }
        else{
            throw std::runtime_error(std::string("Expected different token. Got: ") + 
                                  tokenTypeToString(curTok.type));
        }
    }

    std::unique_ptr<ASTNode> parseExpression(){
        auto node = parseMulDiv();
        
        while((curTok.type == TokenType::PLUS || curTok.type == TokenType::MINUS)){
            char op = curTok.type == TokenType::PLUS ? '+' : '-';
            eat(curTok.type);
            node = std::make_unique<binOpAST>(std::move(node),parseMulDiv(),op);
        }

        // if(curTok.type != TokenType::END){
        //     std::cerr<<tokenTypeToString(curTok.type)<<std::endl;
        //     throw std::runtime_error("Unexpected token at end of expression");
        // }

        return node;
    }

    std::unique_ptr<ASTNode> parseMulDiv(){
        auto node = parseParenOrUnary();
        
        while((curTok.type == TokenType::MULT || curTok.type == TokenType::DIV)){
            char op = curTok.type == TokenType::MULT ? '*' : '/';
            eat(curTok.type);
            node = std::make_unique<binOpAST>(std::move(node),parseParenOrUnary(),op);
        }

        return node;
    }

    std::unique_ptr<ASTNode> parseParenOrUnary(){
        if(curTok.type == TokenType::NUM){
            auto node = std::make_unique<numAST>(curTok.num);
            eat(TokenType::NUM);
            return node;
        }
        else if(curTok.type == TokenType::MINUS){
            eat(TokenType::MINUS);
            return std::make_unique<binOpAST>(std::make_unique<numAST>(0), parseParenOrUnary(), '-');
        }
        else if(curTok.type == TokenType::LBRAC){
            eat(TokenType::LBRAC);
            auto node = parseExpression();
            eat(TokenType::RBRAC);

            return node;
        }
        else{
            throw std::runtime_error("Expected number or parenthesis");
        }
    }

    public:
        Parser(Lexer lex) : lexer(lex) {
            curTok = this->lexer.getNextToken();
        }

        std::unique_ptr<ASTNode> parse(){
            return parseExpression();
        }

};

int main(){
    std::string s;
    std::getline(std::cin,s);

    try {
        Lexer lexer(s);
        Parser parser(lexer);
        auto res = parser.parse();
        std::cout << "Result: " << res->evaluate() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}