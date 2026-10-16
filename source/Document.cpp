#include "Document.hpp"
#include <fstream>

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
        return "";

    std::string content;
    std::string line;
    while (std::getline(file, line)){
        content += line;
        content += '\n';
    }
    return content;
}
