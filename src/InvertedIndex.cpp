#include "InvertedIndex.hpp"

void InvertedIndex::insert(const Document& doc){
    std::vector<std::string> list{tokenizer.tokenize(doc.getContent())};

    for (const auto& token : list)  {
        index[token][doc.getID()]++;
    }
}
InvertedIndex::ConstIterator InvertedIndex::end() const {
    return index.end();
}
InvertedIndex::ConstIterator InvertedIndex::find(const std::string& word) const{
    return index.find(word);
}