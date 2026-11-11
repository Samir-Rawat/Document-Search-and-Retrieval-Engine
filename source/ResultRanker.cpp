#include "ResultRanker.hpp"

void FrequencyRanker::heapify(SearchResults& results, int n, int i) const{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && results[left].frequency < results[smallest].frequency)
        smallest = left;

    if (right < n && results[right].frequency < results[smallest].frequency)
        smallest = right;

    if (smallest != i) {
        std::swap(results[i], results[smallest]);
        heapify(results, n, smallest);
    }
}

SearchResults FrequencyRanker::rank(const SearchResults& results) const {
    SearchResults rankedResults = results;

    int n = rankedResults.size();

    // Build min-heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(rankedResults, n, i);

    // Extract elements
    for (int i = n - 1; i > 0; i--) {
        std::swap(rankedResults[0], rankedResults[i]);
        heapify(rankedResults, i, 0);
    }

    return rankedResults;
}

void TFIDFRanker::heapify(SearchResults& results, int n, int i) const {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && results[left].score < results[smallest].score)
        smallest = left;

    if (right < n && results[right].score < results[smallest].score)
        smallest = right;

    if (smallest != i) {
        std::swap(results[i], results[smallest]);
        heapify(results, n, smallest);
    }
}

SearchResults TFIDFRanker::rank(const SearchResults& results) const {
    SearchResults rankedResults = results;

    int n = rankedResults.size();

    // Build min-heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(rankedResults, n, i);

    // Extract elements
    for (int i = n - 1; i > 0; i--) {
        std::swap(rankedResults[0], rankedResults[i]);
        heapify(rankedResults, i, 0);
    }

    return rankedResults;
}