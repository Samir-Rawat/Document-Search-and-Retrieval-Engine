#include "SearchEngine.hpp"

SearchEngine::SearchEngine(const InvertedIndex &index) : m_index(index) {
}

std::unordered_map<int, int> SearchEngine::search(const std::string& searchString) const{
    const auto it = m_index.find(searchString);
    if (it == m_index.end()) {
        return {};
    }
    else {
        return it->second;
    }
}
