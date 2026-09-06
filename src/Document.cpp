#include "Document.hpp"
#include <fstream>

Document::Document(int id, const fs::path& path):
    m_id{id}, m_path{path}
{
}

int Document::getID() const {
    return m_id;
}
std::string Document::getContent() const {
    return m_content;
}
const fs::path& Document::getPath() const {
    return m_path;
}

bool Document::load() {
    std::ifstream file(m_path);

    if(!file.is_open())
        return false;
    
    std::string line;
    while (std::getline(file, line)){
        m_content += line;
        m_content += '\n';
    }
    return true;
}