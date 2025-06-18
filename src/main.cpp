// main.cpp
#include <iostream>
#include "Parser.hpp"

int main()
{
    while (true)
    {
        std::string s;
        std::getline(std::cin, s);

        if(s == "exit") break;

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
