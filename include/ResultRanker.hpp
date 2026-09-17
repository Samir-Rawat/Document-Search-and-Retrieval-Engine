#ifndef RESULT_RANKER_HPP
#define RESULT_RANKER_HPP

#include <vector>
#include <unordered_map>

class ResultRanker {
public:
    std::vector<std::pair<int, int>> rank(const std::unordered_map<int, int>& result) const;
};
#endif
