#include "lexer.cpp"  // Assuming lexer.hpp is your header for Lexer
#include "parser.cpp" // Assuming parser.hpp is your header for Parser
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source file>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Failed to open file: " << argv[1] << '\n';
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    Lexer lexer(source);
    auto tokens = lexer.getTokens(); // Generate tokens

    Parser parser(tokens); // Correct instantiation using the tokens
    auto ast = parser.parse(); // Generate AST

    // Here you would add code to process the AST further (interpret it, compile it, etc.)
    Interpreter interpreter;
    interpreter.evaluate(ast); 

    return 0;
}

class Interpreter {
    std::unordered_map<std::string, int> variables;

public:
    int evaluate(const std::unique_ptr<ASTNode>& node) {
        if (!node) return 0;

        if (auto num = dynamic_cast<NumberNode*>(node.get())) {
            return std::stoi(num->value);
        } else if (auto binOp = dynamic_cast<BinaryOpNode*>(node.get())) {
            int left = evaluate(binOp->left);
            int right = evaluate(binOp->right);
            switch (binOp->op) {
                case '+': return left + right;
                case '-': return left - right;
                case '*': return left * right;
                case '/': return left / right;  // handle divide by zero
                default: throw std::runtime_error("Unsupported operator");
            }
        } else if (auto assign = dynamic_cast<AssignmentNode*>(node.get())) {
            int value = evaluate(assign->expression);
            variables[assign->identifier] = value;
            return value;
        } else if (auto print = dynamic_cast<PrintNode*>(node.get())) {
            int value = evaluate(print->expression);
            std::cout << value << std::endl;
            return value;
        }
        throw std::runtime_error("Unknown AST node type");
    }
};

struct AssignmentNode : public ASTNode {
    std::string identifier;
    std::unique_ptr<ASTNode> expression;

    AssignmentNode(const std::string& identifier, std::unique_ptr<ASTNode> expression)
    : identifier(identifier), expression(std::move(expression)) {}
};

struct PrintNode : public ASTNode {
    std::unique_ptr<ASTNode> expression;

    explicit PrintNode(std::unique_ptr<ASTNode> expression)
    : expression(std::move(expression)) {}
};
