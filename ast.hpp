#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <memory>

// Base class for all AST nodes
struct ASTNode {
    virtual ~ASTNode() {}
};

// Expression node for numbers (literals)
struct NumberNode : public ASTNode {
    std::string value;

    explicit NumberNode(const std::string &value) : value(value) {}
};

// Expression node for binary operations (e.g., addition, subtraction)
struct BinaryOpNode : public ASTNode {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    char op;

    BinaryOpNode(std::unique_ptr<ASTNode> left, char op, std::unique_ptr<ASTNode> right)
        : left(std::move(left)), right(std::move(right)), op(op) {}
};

// Node for variable identifiers
struct IdentifierNode : public ASTNode {
    std::string name;

    explicit IdentifierNode(const std::string &name) : name(name) {}
};

// Node for assignment statements
struct AssignmentNode : public ASTNode {
    std::unique_ptr<IdentifierNode> left;
    std::unique_ptr<ASTNode> right;

    AssignmentNode(std::unique_ptr<IdentifierNode> left, std::unique_ptr<ASTNode> right)
        : left(std::move(left)), right(std::move(right)) {}
};

#endif // AST_HPP
