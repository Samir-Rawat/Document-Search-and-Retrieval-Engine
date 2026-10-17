#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class Document {
private:
    int m_id;
    fs::path m_path;
    std::string m_title;
public:
    Document(int id, const fs::path& path);

    int getID() const;
    const fs::path& getPath() const;
    const std::string& getTitle() const;
    std::string getContent() const;

    static std::vector<std::unique_ptr<Document>> loadDirectory(const fs::path& directory);
};

#endif