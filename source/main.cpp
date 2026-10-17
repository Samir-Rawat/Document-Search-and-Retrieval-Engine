#include <QApplication>
#include "SearchWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SearchWindow window;
    window.show();

    return app.exec();
}






// #include <filesystem>
// #include <iostream>
//
// namespace fs = std::filesystem;
//
// int main() {
//     InvertedIndex index;
//     SearchEngine searchEngine(index);
//     int i = 0;
//
//     std::string directory;
//     std::cout << "Enter Directory :: \t";
//     std::getline(std::cin, directory);
//     std::vector<std::unique_ptr<Document>> documents;
//     for(const auto& entry: fs::directory_iterator(directory)) {
//         documents.push_back( std::make_unique<Document>(++i, entry.path()) );
//         index.insert(*documents.back());
//     }
//
//     char ch;
//     do {
//         std::string query;
//         std::cout << "Query: ";
//         std::cin >> query;
//         auto result = searchEngine.search(query);
//
//         if(result == nullptr)
//             std::cout << "Not Found!\n";
//         else {
//             ResultRanker resultRanker;
//             const auto& res = resultRanker.rank(result);
//             for(const auto& [docID, frequency] : res) {
//                 std::cout << "Doc Title: " << documents[docID - 1]->getTitle() << ", Frequency: " << frequency << '\n';
//             }
//         }
//         std::cout << "Continue? (y/n) ";
//         std::cin >> ch;
//     } while (tolower(ch) == 'y');
// }