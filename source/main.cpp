#include "Document.hpp"
#include "InvertedIndex.hpp"
#include "SearchEngine.hpp"
#include "ResultRanker.hpp"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main() {
    InvertedIndex index;
    SearchEngine searchEngine(index);
    int i = 0;

    std::string directory;
    std::cout << "Enter Directory: ";
    std::getline(std::cin, directory);
    std::vector<std::unique_ptr<Document>> documents;
    for(const auto& entry: fs::directory_iterator("./sample/dictionary")) {
        documents.push_back(
            std::make_unique<Document>(++i, entry.path())
        );
        index.insert(*documents.back());
    }

    while(true) {
        std::string query;
        std::cout << "Query: ";
        std::cin >> query;
        auto result = searchEngine.search(query);

        if(result.empty())
            std::cout << "Not Found!\n";
        else {
            ResultRanker resultRanker;
            const auto& res = resultRanker.rank(result);
            for(const auto& [doc, frequency] : res) {
                std::cout << "Doc Title: " << doc->getTitle() << ", Frequency: " << frequency << '\n';
            }
        }
    }
}