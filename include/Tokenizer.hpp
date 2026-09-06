#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>
    
class Tokenizer {
    public:
        std::vector<std::string> tokenize(const std::string& text);
};

#endif