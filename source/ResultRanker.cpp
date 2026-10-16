#include "ResultRanker.hpp"

#include <algorithm>

std::vector<std::pair<int, int>> ResultRanker::rank(const PostingNode* result) const {
    std::vector<std::pair<int, int>> rankedResult;
    for(; result != nullptr; result = result->next) {
        rankedResult.emplace_back(result->documentID, result->frequency);
    }

    auto compare = [] (const std::pair<int, int>& a, const std::pair<int, int>& b) -> bool {
        return a.second > b.second;
    };

    std::sort(rankedResult.begin(), rankedResult.end(), compare);
    return std::move(rankedResult);
}
