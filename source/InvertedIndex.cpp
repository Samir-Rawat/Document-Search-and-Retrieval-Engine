#include "InvertedIndex.hpp"
#include "Tokenizer.hpp"

void InvertedIndex::insert(const Document& document){
    const std::vector<std::string> tokens = Tokenizer::tokenize(document.getContent());

    for (const auto& token : tokens) {
        if (token.empty())
            continue;

        m_index.addOccurrence(token, document.getID());
    }
}

const PostingNode* InvertedIndex::find(const std::string& word) const{
    return m_index.find(word);
}

void InvertedIndex::clear() {
    m_index.clear();
}
