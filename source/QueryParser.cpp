#include "QueryParser.hpp"
#include "Tokenizer.hpp"

#include <stdexcept>
#include<iostream>

void deleteTree(QueryNode* node) {
    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

//Handles NOT, PARANTHESIS, TERMS
QueryNode* QueryParser::parseFactor() {
    if (tokenIndex >= tokens.size())
        throw std::runtime_error("Unexpected end of query.");

    // NOT
    if (tokens[tokenIndex] == "not") {
        tokenIndex++;

        QueryNode* node = new QueryNode;
        node->type = TokenType::NOT;
        node->right = parseFactor();

        return node;
    }

    // Parentheses
    if (tokens[tokenIndex] == "(") {
        tokenIndex++;

        QueryNode* node = parseExpression();

        if (tokenIndex >= tokens.size() || tokens[tokenIndex] != ")")
            throw std::runtime_error("Missing closing parenthesis.");

        tokenIndex++;
        return node;
    }

    // Search term
    if (tokens[tokenIndex] == ")" ||
        tokens[tokenIndex] == "and" ||
        tokens[tokenIndex] == "or") {
        throw std::runtime_error("Unexpected operator.");
    }

    QueryNode* node = new QueryNode;
    node->type = TokenType::TERM;
    node->value = tokens[tokenIndex++];

    return node;
}

//Handles AND operation
QueryNode* QueryParser::parseTerm() {
    QueryNode* left = parseFactor();

    while (tokenIndex < tokens.size()) {
        if (tokens[tokenIndex] == "or" || tokens[tokenIndex] == ")")
            break;

        if (tokens[tokenIndex] == "and")
            tokenIndex++;

        QueryNode* right = parseFactor();

        QueryNode* node = new QueryNode;
        node->type = TokenType::AND;
        node->left = left;
        node->right = right;

        left = node;
    }

    return left;
}

//Handles OR operation
QueryNode* QueryParser::parseExpression() {
    QueryNode* left = parseTerm();

    while (tokenIndex < tokens.size() && tokens[tokenIndex] == "or") {
        tokenIndex++;

        QueryNode* right = parseTerm();

        QueryNode* node = new QueryNode;
        node->type = TokenType::OR;
        node->left = left;
        node->right = right;

        left = node;
    }

    return left;
}

QueryNode* QueryParser::parse(const std::string& query) {
    tokens = Tokenizer::tokenize(query, true);
    tokenIndex = 0;

    if (tokens.empty())
        throw std::runtime_error("Empty query.");

    QueryNode* root = parseExpression();

    if (tokenIndex < tokens.size()) {
        deleteTree(root);
        throw std::runtime_error("Invalid query.");
    }

    return root;
}

