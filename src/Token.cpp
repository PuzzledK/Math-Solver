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
		case TokenType::LOG: return "LOG10";
		case TokenType::LN: return "LN";
        case TokenType::VAR: return "VAR";
        case TokenType::ASSIGN: return "ASSIGN";
        case TokenType::IF: return "IF";
        case TokenType::THEN: return "THEN";
        case TokenType::ELSE: return "ELSE";
        case TokenType::EQ: return "EQ";
        case TokenType::NE: return "NQ";
        case TokenType::GT: return "GT";
        case TokenType::LT: return "LT";
        case TokenType::LTE: return "LTE";
        case TokenType::GTE: return "GTE";
        case TokenType::SEMICOLON: return "SEMI-COLON";
        case TokenType::LCURLY: return "LCURLY";
        case TokenType::RCURLY: return "RCURLY";
        case TokenType::DEF: return "DEF";
        case TokenType::COMMA: return "COMMA";
        default: return "UNKNOWN";        
    }
}