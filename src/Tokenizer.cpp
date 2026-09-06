#include "Tokenizer.hpp"
#include <cctype>

std::vector<std::string> Tokenizer::tokenize(const std::string& text) {
    std::vector<std::string> list;
    std::string current;
    for(auto i{text.begin()}; i != text.end(); i++) {

        if(isspace(*i) || *i == '.' || *i == '!' || *i == '?' || *i == ';') {
            if(!current.empty()) {
                list.push_back(current);
                current.clear();
            }
            else
                continue;
        }
        else
            current.push_back(std::tolower(*i));
    }    
    if (!current.empty())
        list.push_back(current);
    
    return list;
}