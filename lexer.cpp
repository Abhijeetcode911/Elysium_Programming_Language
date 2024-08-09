#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "token.hpp"  // Ensure this header file correctly defines TokenType and Token
using namespace std;
class Lexer {
private:
    std::string input;
    std::vector<Token> tokens;  // Use Token instead of Token2
    std::smatch match;

public:
    Lexer(const std::string& input) : input(input) {}

    const std::vector<Token>& getTokens() {
        static const std::regex rgx(
            "(\\d+)|"                      // Numbers
            "([a-zA-Z_][a-zA-Z0-9_]*)|"   // Identifiers
            "(=)|"                         // Assignment
            "(;)|"                         // Semicolon
            "(\\+)|"                       // Addition operator
            "(-)|"                         // Subtraction operator
            "(\\*)|"                       // Multiplication operator
            "(/)|"                         // Division operator
            "(\\()|"                       // Left parenthesis
            "(\\))"                        // Right parenthesis
        );
        std::string::const_iterator start = input.begin();
        std::string::const_iterator end = input.end();

        while (std::regex_search(start, end, match, rgx)) {
            for (int i = 1; i < match.size(); ++i) {
                if (match[i].matched) {
                    TokenType type = static_cast<TokenType>(i - 1);
                    tokens.emplace_back(type, match[i].str());
                    break;
                }
            }
            start = match.suffix().first;
        }
        tokens.emplace_back(TokenType::END_OF_FILE, "");
        return tokens;
    }
};
