#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include "Document.hpp"
#include "HashMap.hpp"
#include <string>

class InvertedIndex {
private:
    HashMap m_index;
public:

    void insert(const Document& doc);
    const PostingNode* find(const std::string& word) const;
};

#endif