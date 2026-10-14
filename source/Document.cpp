#include "Document.hpp"
#include <fstream>

Document::Document(int id, const fs::path& path):
    m_id{id}, m_path{path}, m_title{path.filename().string()}
{
}

int Document::getID() const { return m_id; }

const std::string& Document::getTitle() const { return m_title; }

std::string Document::getContent() const { return m_content; }

const fs::path& Document::getPath() const { return m_path; }

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