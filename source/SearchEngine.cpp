#include "SearchEngine.hpp"
#include "QueryProcessor.hpp"
SearchEngine::SearchEngine(const InvertedIndex &index) : m_index(index) {
}

const PostingNode* SearchEngine::search(const std::string& query) const{
    QueryProcessor processor;

    std::string searchString = processor.process(query);
    return  m_index.find(searchString);
}
