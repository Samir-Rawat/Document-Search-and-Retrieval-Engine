#include "InvertedIndex.hpp"
#include "Tokenizer.hpp"

void InvertedIndex::insert(const Document& document){
    const std::vector<std::string> list{Tokenizer::tokenize(document.getContent())};

    for (const auto& token : list)  {
        m_index.addOccurrence(token, document.getID());
    }
}

const PostingNode* InvertedIndex::find(const std::string& word) const{
    return m_index.find(word);
}