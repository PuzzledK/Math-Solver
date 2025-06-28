// main.cpp
#include <iostream>
#include "Parser.hpp"
#include <unordered_map>
#include "Context.hpp"
#include "Value.hpp"

int main()
{
    std::cout << "ENTER ANY SUPPORTED MATHEMATICAL EXPRESSION" << std::endl;
    std::cout << "Type 'help' for supported expressions and 'exit' to quit" << std::endl;
    Context globalContext;

    while (true)
    {
        std::cout << ">>> ";
        std::string s;
        std::getline(std::cin, s);

        if (s == "exit")
            break;
        if (s == "help")
        {
            std::cout << "\nSupported commands and features:\n";
            std::cout << "\nOperators:\n";
            std::cout << "  +   Addition\n";
            std::cout << "  -   Subtraction\n";
            std::cout << "  *   Multiplication\n";
            std::cout << "  /   Division\n";
            std::cout << "  ^   Exponentiation\n";
            std::cout << "  ( ) Parentheses\n";
            std::cout << "  e   Euler's number\n";
            std::cout << "\nFunctions (input/output in degrees where applicable):\n";
            std::cout << "  sin(x), cos(x), tan(x)\n";
            std::cout << "  asin(x), acos(x), atan(x)\n";
            std::cout << "  sqrt(x), log(x) [base 10], ln(x) [base e]\n";
            std::cout << "\nVariables:\n";
            std::cout << "  Assignment: x = 5\n";
            std::cout << "  Usage: x + 2\n";
            std::cout << "  Variable names: alphabets only (e.g., foo, bar)\n";
            std::cout << "\nBlocks:\n";
            std::cout << "  { ... } to group multiple expressions/statements, separated by semicolons\n";
            std::cout << "\nIf-Then-Else Expressions:\n";
            std::cout << "  if(<condition>) then <expr> else <expr>\n";
            std::cout << "  Supported: ==, !=, >, <, >=, <=\n";
            std::cout << "\nUser-defined Functions:\n";
            std::cout << "  def f(x, y) { x + y; }\n";
            std::cout << "  f(2, 3)\n";
            std::cout << "\nCommands:\n";
            std::cout << "  help   Show this help message\n";
            std::cout << "  exit   Quit the program\n";
            std::cout << "\nNumbers:\n";
            std::cout << "  Integer and floating-point numbers (e.g., 42, 3.14)\n";
            std::cout << "\nType an expression like: sin(30) + cos(60), x = 2, def sq(x) x^2, or use blocks and if-then-else.\n";
            continue;
        }
        try
        {
            Lexer lexer(s);
            Parser parser(lexer);
            auto result = parser.parse();

            auto res = result -> evaluate(globalContext);
            
            if(res.isNumber()){
                std::cout << "--> " << res.getNumber()<< std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
