#include "Document.hpp"
#include <fstream>
#include <stdexcept>

Document::Document(int id, const fs::path& path):
    m_id{id}, m_path{path}, m_title{path.filename().string()}
{
}

int Document::getID() const {
    return m_id;
}

const fs::path& Document::getPath() const {
    return m_path;
}

const std::string& Document::getTitle() const {
    return m_title;
}

std::string Document::getContent() const {
    std::ifstream file(m_path);
    if(!file.is_open())
        throw std::runtime_error("Could not open file: " + m_path.string());

    std::string content;
    std::string line;
    while (std::getline(file, line)){
        content += line;
        content += '\n';
    }
    return content;
}

std::vector<Document> loadDirectory(const fs::path& directory) {
    if (directory.empty()) {
        throw std::invalid_argument("Directory path cannot be empty.");
    }

    if (!fs::exists(directory)) {
        throw std::runtime_error("Directory does not exist: \n" + directory.string());
    }

    if (!fs::is_directory(directory)) {
        throw std::runtime_error("Provided path is not a directory: \n" + directory.string());
    }

    std::vector<Document> documents;
    int id = 0;

    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (!entry.is_regular_file())
            continue;

        std::string extension = entry.path().extension().string();

        for (char& c : extension) {
            c = std::tolower(c);
        }

        if (extension != ".txt" && extension != ".md" && extension != ".csv" &&
            extension != ".log" && extension != ".ini")
            continue;

        documents.emplace_back(++id, entry.path());
    }
    return documents;
}
