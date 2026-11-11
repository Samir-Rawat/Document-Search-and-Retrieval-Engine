#ifndef RESULT_RANKER_HPP
#define RESULT_RANKER_HPP
#include "SearchEngine.hpp"

class RankingStrategy {
public:
    virtual SearchResults rank(const SearchResults& results) const = 0;
    virtual ~RankingStrategy() = default;
};

class FrequencyRanker : public RankingStrategy {
public:
    SearchResults rank(const SearchResults& results) const override;

private:
    void heapify(SearchResults& results, int n, int i) const;
};

class TFIDFRanker : public RankingStrategy {
public:
    SearchResults rank(const SearchResults& results) const override;

private:
    void heapify(SearchResults& results, int n, int i) const;
};

#endif
