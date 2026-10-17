#include "QueryProcessor.hpp"

#include <cctype>

std::string QueryProcessor::process(const std::string& query) const
{
    std::string result = query;

    for (char& ch : result) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }

    return result;
}
