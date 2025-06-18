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
        case TokenType::POW: return "POW";
        case TokenType::SIN: return "SIN";
        case TokenType::COS: return "COS";
        case TokenType::TAN: return "TAN";
        case TokenType::ASIN: return "ASIN";
        case TokenType::ACOS: return "ACOS";
        case TokenType::ATAN: return "ATAN";
        case TokenType::SQRT: return "SQRT";
        case TokenType::END: return "END";
		case TokenType::EXPO: return "EXPO";
        default: return "UNKNOWN";        
    }
}