// main.cpp
#include <iostream>
#include "Parser.hpp"

int main()
{   
    std::cout<<"ENTER ANY SUPPORTED MATHEMATICAL EXPRESSION"<<std::endl;
    std::cout<<"Type 'help' for supported expressions and 'exit' to quit"<<std::endl;
    while (true)
    {
        std::cout<<"INPUT : ";
        std::string s;
        std::getline(std::cin, s);

        if(s == "exit") break;
        if(s == "help"){
            std::cout << "\nSupported commands and functions:\n";
            std::cout << "\nOperators:\n";
            std::cout << "  +   Addition\n";
            std::cout << "  -   Subtraction\n";
            std::cout << "  *   Multiplication\n";
            std::cout << "  /   Division\n";
            std::cout << "  ^   Exponentiation\n";
            std::cout << "  ( ) Parentheses\n";
            std::cout << "\nFunctions:\n";
            std::cout << "  sin(x)   Sine\n";
            std::cout << "  cos(x)   Cosine\n";
            std::cout << "  tan(x)   Tangent\n";
            std::cout << "  asin(x)  Arcsine\n";
            std::cout << "  acos(x)  Arccosine\n";
            std::cout << "  atan(x)  Arctangent\n";
            std::cout << "  sqrt(x)  Square root\n";
            std::cout << "\nNumbers:\n";
            std::cout << "  Integer and floating-point numbers (e.g., 42, 3.14)\n";
            std::cout << "\nType an expression like: sin(0.5) + cos(0.5) or 2^3 + tan(1)\n";
            continue;
        }
        try
        {
            Lexer lexer(s);
            Parser parser(lexer);
            auto result = parser.parse();
            std::cout << "Result: " << result->evaluate() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
