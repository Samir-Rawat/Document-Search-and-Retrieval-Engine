#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <filesystem>


namespace fs = std::filesystem;

class Document {
    private:
        int m_id;
        fs::path m_path;
        std::string m_content;
    public:
        Document(int id, const fs::path& path);

        bool load();
        int getID() const;
        std::string getContent() const;
        const fs::path& getPath() const;
};



#endif