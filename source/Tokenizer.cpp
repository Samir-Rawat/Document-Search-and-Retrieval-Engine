#include "Tokenizer.hpp"
#include <cctype>

std::vector<std::string> Tokenizer::tokenize(const std::string& text, bool preserveParentheses) {
    std::vector<std::string> list;
    std::string current;
    for(const auto& c : text) {
        if(std::isspace(c) || std::ispunct(c)) {
            if(!current.empty()) {
                list.push_back(current);
                current.clear();
            }

            if (preserveParentheses && (c == '(' || c == ')')) {
                list.push_back(std::string(1, c));
            }
        }
        else
            current.push_back(static_cast<char>(std::tolower(c)));
    }

    if (!current.empty())
        list.push_back(current);
    
    return list;
}