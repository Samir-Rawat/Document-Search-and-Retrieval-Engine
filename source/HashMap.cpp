#include "HashMap.hpp"

#include <functional>
#include <utility>

HashMap::HashMap(const std::size_t initialCapacity)
    : buckets(initialCapacity == 0 ? 16 : initialCapacity, nullptr) {}

HashMap::~HashMap() {
    clear();
}

// ---------- Utility Methods ----------

std::size_t HashMap::size() const {
    return elementCount;
}

std::size_t HashMap::bucketCount() const {
    return buckets.size();
}

bool HashMap::empty() const {
    return elementCount == 0;
}


// ---------- Hashing ----------

std::size_t HashMap::getBucketIndex (const std::string& word) const {
    std::hash<std::string> hasher{};
    return hasher(word) % buckets.size();
}


// ---------- Posting List ----------

void HashMap::insertPosting(PostingNode*& head, int documentID) {
    PostingNode** current = &head;

    // Keep postings sorted by document ID.
    while (*current != nullptr &&
           (*current)->documentID < documentID) {
        current = &((*current)->next);
    }

    // This document already has a posting for the word.
    if (*current != nullptr && (*current)->documentID == documentID) {
        ++((*current)->frequency);
        return;
    }

    // Insert a new posting.
    PostingNode* node = new PostingNode(documentID);
    node->next = *current;
    *current = node;
}


// ---------- Insertion ----------

void HashMap::addOccurrence(const std::string& word, int documentID) {
    if (word.empty() || documentID <= 0)
        return;

    std::size_t index = getBucketIndex(word);

    // Check whether the word already exists.
    for (HashNode* current = buckets[index]; current != nullptr; current = current->next) {
        if (current->word == word) {
            insertPosting(current->postings, documentID);
            return;
        }
    }

    // Grow the table if the load factor would exceed 0.75.
    if ((elementCount + 1) * 4 > buckets.size() * 3) {
        rehash(buckets.size() * 2);
        index = getBucketIndex(word);
    }

    // Create a new hash-table entry.
    HashNode* node = new HashNode(word);

    node->next = buckets[index];
    buckets[index] = node;

    insertPosting(node->postings, documentID);
    ++elementCount;
}


// ---------- Searching ----------

PostingNode* HashMap::find(const std::string& word) {
    std::size_t index = getBucketIndex(word);

    for (HashNode* current = buckets[index]; current != nullptr; current = current->next) {
        if (current->word == word)
            return current->postings;
    }

    return nullptr;
}

const PostingNode* HashMap::find(const std::string& word) const {
    std::size_t index = getBucketIndex(word);

    for (const HashNode* current = buckets[index]; current != nullptr; current = current->next) {
        if (current->word == word)
            return current->postings;
    }

    return nullptr;
}

bool HashMap::contains(const std::string& word) const {
    return find(word) != nullptr;
}


// ---------- Rehashing ----------

void HashMap::rehash(std::size_t newCapacity) {
    std::vector<HashNode*> newBuckets(newCapacity, nullptr);

    for (HashNode* head : buckets) {
        while (head != nullptr) {
            HashNode* next = head->next;

            std::hash<std::string> hashFunction;
            std::size_t index = hashFunction(head->word) % newCapacity;

            head->next = newBuckets[index];
            newBuckets[index] = head;
            head = next;
        }
    }

    buckets = std::move(newBuckets);
}


// ---------- Memory Management ----------

void HashMap::clearPostings(PostingNode* head) {
    while (head != nullptr) {
        PostingNode* next = head->next;
        delete head;
        head = next;
    }
}

void HashMap::clear() {
    for (HashNode*& head : buckets) {
        while (head != nullptr) {
            HashNode* next = head->next;

            // Delete posting nodes, not the Documents they point to.
            clearPostings(head->postings);
            delete head;

            head = next;
        }
    }

    elementCount = 0;
}