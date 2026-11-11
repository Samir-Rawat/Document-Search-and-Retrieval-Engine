/*
g++ -std=c++17 -Iheader test/QueryParserTest.cpp source/QueryParser.cpp source/Tokenizer.cpp -o QueryParserTest.exe
*/
#include "QueryParser.hpp"
#include <iostream>
using namespace std;

void printTree(const QueryNode* node, int depth = 0) {
    if (node == nullptr)
        return;

    for (int i = 0; i < depth; i++)
        std::cout << "  ";

    switch (node->type) {
        case TokenType::TERM:
            std::cout << node->value << '\n';
            break;
        case TokenType::AND:
            std::cout << "AND\n";
            break;
        case TokenType::OR:
            std::cout << "OR\n";
            break;
        case TokenType::NOT:
            std::cout << "NOT\n";
            break;
    }

    printTree(node->left, depth + 1);
    printTree(node->right, depth + 1);
}

int main() {

    std::string query;
    std::cin >> query;

    QueryParser parser;
    QueryNode* root = parser.parse(query);

    std::cout << "Tree created!\n";
    printTree(root);
    deleteTree(root);
}