#ifndef SEARCH_ENGINE_HPP
#define SEARCH_ENGINE_HPP

#include <string>
#include "Document.hpp"
#include "InvertedIndex.hpp"

class SearchEngine {
public:
    SearchEngine(const InvertedIndex& index);
    const PostingNode* search(const std::string& searchString) const;

private:
    const InvertedIndex& m_index;
};

#endif