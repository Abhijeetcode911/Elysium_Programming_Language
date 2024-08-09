// token.hpp
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenType {
    NUMBER,
    IDENTIFIER,
    ASSIGN,
    SEMICOLON,
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    LPAREN,
    RPAREN,
    END_OF_FILE,
    INVALID  // Used to handle unexpected tokens
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType type, std::string value) : type(type), value(std::move(value)) {}
};

#endif // TOKEN_HPP
