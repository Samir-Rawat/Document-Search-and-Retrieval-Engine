#include "Trie.hpp"
#include <iostream>

int main() {
    Trie trie;

    trie.insert("harry");
    trie.insert("hard");
    trie.insert("harmony");
    trie.insert("hardly");
    trie.insert("potter");

    const auto suggestions = trie.getSuggestions("har");

    for (const auto& word : suggestions)
        std::cout << word << '\n';

    return 0;
}