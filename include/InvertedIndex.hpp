#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include "Document.hpp"
#include "Tokenizer.hpp"
#include <optional>
#include <vector>
#include <unordered_map>
#include <string>

class InvertedIndex {
    private:
        std::unordered_map<
            std::string, 
            std::unordered_map<int, int>
        > index;
        Tokenizer tokenizer;
    public:
        using ConstIterator = std::unordered_map<
            std::string,
            std::unordered_map<int, int>
        >::const_iterator;
    
        void insert(const Document& doc);
        ConstIterator find(const std::string& word) const;
        ConstIterator end() const;
};

#endif