#include "ResultRanker.hpp"

#include <algorithm>

std::vector<std::pair<int, int>> ResultRanker::rank(const std::unordered_map<int, int>& result) const {
    std::vector<std::pair<int, int>> rankedResult;
    rankedResult.reserve(result.size());
    for(const auto& [ID, freq] : result) {
        rankedResult.emplace_back(ID, freq);
    }
    auto compare = [] (const std::pair<int, int>& a, const std::pair<int, int>& b) -> bool {
        return a.second > b.second;
    };
    std::sort(rankedResult.begin(), rankedResult.end(), compare);
    return rankedResult;
}
