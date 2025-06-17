#include "Token.hpp"

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::NUM: return "NUM";
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::MULT: return "MULT";
        case TokenType::DIV: return "DIV";
        case TokenType::LBRAC: return "LBRAC";
        case TokenType::RBRAC: return "RBRAC";
        case TokenType::END: return "END";
        default: return "UNKNOWN";
    }
}