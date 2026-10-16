#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <string>
#include <vector>
#include <cstddef>

#include "Document.hpp"

struct PostingNode {
    int documentID;
    int frequency;
    PostingNode* next;

    explicit PostingNode(int documentID)
        : documentID(documentID), frequency(1), next(nullptr) {}
};

class HashMap {
private:
    struct HashNode {
        std::string word;
        PostingNode* postings;
        HashNode* next;

        explicit HashNode(const std::string& word)
            : word(word), postings(nullptr), next(nullptr) {}
    };

    std::vector<HashNode*> buckets;
    std::size_t elementCount = 0;

    std::size_t getBucketIndex(const std::string& word) const;
    void rehash(std::size_t newCapacity);
    void clearPostings(PostingNode* head);
    void insertPosting(PostingNode*& head, int documentID);

public:
    explicit HashMap(std::size_t initialCapacity = 16);

    ~HashMap();

    HashMap(const HashMap&) = delete;
    HashMap& operator=(const HashMap&) = delete;

    void addOccurrence(const std::string& word, int documentID);

    PostingNode* find(const std::string& word);
    const PostingNode* find(const std::string& word) const;

    bool contains(const std::string& word) const;

    std::size_t size() const;
    std::size_t bucketCount() const;
    bool empty() const;

    void clear();
};

#endif
