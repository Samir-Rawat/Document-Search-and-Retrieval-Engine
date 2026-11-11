#ifndef SEARCH_ENGINE_HPP
#define SEARCH_ENGINE_HPP

#include <string>
#include <vector>
#include "Document.hpp"
#include "InvertedIndex.hpp"
#include "QueryParser.hpp"

struct SearchResult {
    int documentID;
    int frequency;
    double score;
};

using SearchResults = std::vector<SearchResult>;

class SearchEngine {
public:
    SearchEngine(const std::vector<Document>& documents, const InvertedIndex& index);
    SearchResults search(const std::string& query) const;

private:
    const std::vector<Document>& m_documents;
    const InvertedIndex& m_index;

    double calculateTFIDF(const std::string& term, int termFrequency) const;
    SearchResults evaluate(const QueryNode* node) const;
};

#endif