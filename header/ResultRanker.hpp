#ifndef RESULT_RANKER_HPP
#define RESULT_RANKER_HPP

#include "Document.hpp"
#include <vector>
#include "HashMap.hpp"

class ResultRanker {
public:
    std::vector<std::pair<int, int>> rank(const PostingNode* result) const;
};
#endif
