#include "Trie.hpp"
#include <algorithm>

Trie::Trie() {
    nodes.emplace_back();
}

void Trie::insert(const std::string& word) {
    int current = 0;

    for (char ch : word) {
        if (nodes[current].children.find(ch) == nodes[current].children.end()) {
            nodes[current].children[ch] = static_cast<int>(nodes.size());
            nodes.emplace_back();
        }

        current = nodes[current].children[ch];
    }

    nodes[current].isEnd = true;
}

void Trie::getSuggestions(int current, const std::string& prefix,
    std::vector<std::string>& suggestions, int limit) const {

    if (nodes[current].isEnd) {
        suggestions.push_back(prefix);

        if (suggestions.size() >= limit)
            return;
    }

    for (const auto& [ch, child] : nodes[current].children) {
        getSuggestions(child, prefix + ch, suggestions, limit);

        if (suggestions.size() >= limit)
            return;
    }
}

std::vector<std::string> Trie::getSuggestions(const std::string& prefix, int limit) const {
    std::vector<std::string> suggestions;
    int current = 0;

    for (char ch : prefix) {
        if (nodes[current].children.find(ch) == nodes[current].children.end())
            return suggestions;

        current = nodes[current].children.at(ch);
    }

    getSuggestions(current, prefix, suggestions, limit);
    std::sort(suggestions.begin(), suggestions.end());
    return suggestions;
}

void Trie::clear() {
    nodes.clear();
    nodes.emplace_back();
}