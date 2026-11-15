#ifndef TRIE_HPP
#define TRIE_HPP

#include <string>
#include <vector>
#include <unordered_map>

class Trie {
private:
    struct Node {
        std::unordered_map<char, int> children;
        bool isEnd = false;
    };

    std::vector<Node> nodes;

    void getSuggestions(int current, const std::string& prefix,
    std::vector<std::string>& suggestions, int limit) const;

public:
    Trie();

    void insert(const std::string& word);
    std::vector<std::string> getSuggestions(const std::string& prefix, int limit = 10) const;
    void clear();
};

#endif
