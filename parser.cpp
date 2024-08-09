#include "token.hpp"
#include "ast.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

class Parser {
    const std::vector<Token>& tokens; // No change here, correctly using a const reference
    size_t current = 0;
    
public:
    explicit Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

    std::unique_ptr<ASTNode> parse() {
        auto result = parseExpression();
        if (current < tokens.size() && tokens[current].type != TokenType::END_OF_FILE) {
            throw std::runtime_error("Unexpected tokens at end of expression");
        }
        return result;
    }

private:
    std::unique_ptr<ASTNode> parseExpression() {
    auto node = parseTerm();
    while (!isAtEnd() && (match(TokenType::PLUS) || match(TokenType::MINUS))) {
        char op = previous().value[0];
        std::cout << "Parsing expression: Operator=" << op << std::endl;
        auto right = parseTerm();
        node = std::make_unique<BinaryOpNode>(std::move(node), op, std::move(right));
    }
    if (!isAtEnd()) {
        std::cerr << "Unexpected token: " << tokens[current].value << std::endl;
        throw std::runtime_error("Unexpected tokens at end of expression");
    }
    return node;
}

    std::unique_ptr<ASTNode> parseTerm() {
        auto node = parseFactor();
        while (match(TokenType::TIMES) || match(TokenType::DIVIDE)) {
            char op = previous().value[0];
            auto right = parseFactor();
            node = std::make_unique<BinaryOpNode>(std::move(node), op, std::move(right));
        }
        
        return node;
    }
   
    std::unique_ptr<ASTNode> parseFactor() {
        if (match(TokenType::NUMBER)) {
            return std::make_unique<NumberNode>(previous().value);
        }
        if (match(TokenType::IDENTIFIER)) {
            return std::make_unique<IdentifierNode>(previous().value);
        }
        if (match(TokenType::LPAREN)) {
            auto expr = parseExpression();
            consume(TokenType::RPAREN);
            return expr;
        }
        throw std::runtime_error("Unexpected token in expression");
    }

    bool match(TokenType expected) {
        if (check(expected)) {
            advance();
            return true;
        }
        return false;
    }

    bool check(TokenType expected) {
        if (isAtEnd()) return false;
        return tokens[current].type == expected;
    }

    const Token& advance() {
        if (!isAtEnd()) current++;
        return tokens[current - 1];
    }

    const Token& previous() {
        return tokens[current - 1];
    }

    bool isAtEnd() {
        return current >= tokens.size();
    }

    void consume(TokenType type) {
        if (check(type)) {
            advance();
        } else {
            throw std::runtime_error("Expected token not found");
        }
    }
};

