#ifndef QUERY_PARSER_HPP
#define QUERY_PARSER_HPP

#include <string>
#include <vector>

enum class TokenType {
    TERM,
    AND,
    OR,
    NOT
};

struct QueryNode {
    TokenType type;
    std::string value;

    QueryNode *left = nullptr;
    QueryNode *right = nullptr;
};

void deleteTree(QueryNode* node);

class QueryParser {
public:
    QueryNode* parse(const std::string& query);

private:
    std::vector<std::string> tokens;
    size_t tokenIndex = 0;

    QueryNode* parseExpression();
    QueryNode* parseTerm();
    QueryNode* parseFactor();
};

#endif
