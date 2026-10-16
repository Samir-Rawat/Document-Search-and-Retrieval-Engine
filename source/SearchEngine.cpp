#include "SearchEngine.hpp"

SearchEngine::SearchEngine(const InvertedIndex &index) : m_index(index) {
}

const PostingNode* SearchEngine::search(const std::string& searchString) const{
    return  m_index.find(searchString);
}
