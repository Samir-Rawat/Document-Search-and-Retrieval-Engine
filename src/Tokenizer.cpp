#include "Tokenizer.hpp"
#include <cctype>

std::vector<std::string> Tokenizer::tokenize(const std::string& text) {
    std::vector<std::string> list;
    std::string current;
    for(const auto& c : text) {
        if(isspace(c) || c == '.' || c == '!' || c == '?' || c == ';') {
            if(!current.empty()) {
                list.push_back(current);
                current.clear();
            }
        }
        else
            current.push_back(static_cast<char>(std::tolower(c)));
    }    
    if (!current.empty())
        list.push_back(current);
    
    return list;
}