#include "SearchEngine.hpp"
#include <cmath>
#include <unordered_set>
#include <stdexcept>

double SearchEngine::calculateTFIDF(const std::string& term, int termFrequency) const {
    const PostingNode* current = m_index.find(term);

    int documentFrequency = 0;

    while (current != nullptr) {
        documentFrequency++;
        current = current->next;
    }

    if (documentFrequency == 0)
        return 0.0;

    double tf = termFrequency;

    double idf = std::log(
        static_cast<double>(m_documents.size()) / documentFrequency
    );

    return tf * idf;
}

SearchEngine::SearchEngine(const std::vector<Document>& documents, const InvertedIndex& index)
    :m_documents(documents), m_index(index) {
}

SearchResults SearchEngine::search(const std::string& query) const {
    QueryParser parser;

    QueryNode* root = parser.parse(query);

    SearchResults results = evaluate(root);

    deleteTree(root);

    return results;
}

SearchResults SearchEngine::evaluate(const QueryNode* node) const {
    if (node->type == TokenType::TERM) {
        SearchResults results;

        const PostingNode* current = m_index.find(node->value);

        while (current != nullptr) {
            results.push_back({
                current->documentID, current->frequency,
                calculateTFIDF(node->value, current->frequency)
            });
            current = current->next;
        }

        return results;
    }

// ---- Evaluate AND ----
    if (node->type == TokenType::AND) {
        SearchResults left = evaluate(node->left);
        SearchResults right = evaluate(node->right);

        SearchResults results;

        int i = 0;
        int j = 0;

        while (i < left.size() && j < right.size()) {
            if (left[i].documentID == right[j].documentID) {
                results.push_back({
                    left[i].documentID,
                    left[i].frequency + right[j].frequency,
                    left[i].score + right[j].score
                });

                i++;
                j++;
            }
            else if (left[i].documentID < right[j].documentID) {
                i++;
            }
            else {
                j++;
            }
        }

        return results;
    }

// ---- Evaluate OR ----
    if (node->type == TokenType::OR) {
        SearchResults left = evaluate(node->left);
        SearchResults right = evaluate(node->right);

        SearchResults results;

        std::size_t i = 0;
        std::size_t j = 0;

        while (i < left.size() && j < right.size()) {
            if (left[i].documentID == right[j].documentID) {
                results.push_back({
                    left[i].documentID,
                    left[i].frequency + right[j].frequency,
                    left[i].score + right[j].score
                });

                i++;
                j++;
            }
            else if (left[i].documentID < right[j].documentID) {
                results.push_back(left[i]);
                i++;
            }
            else {
                results.push_back(right[j]);
                j++;
            }
        }

        while (i < left.size()) {
            results.push_back(left[i]);
            i++;
        }

        while (j < right.size()) {
            results.push_back(right[j]);
            j++;
        }

        return results;
    }

// ---- Evaluate NOT ----
    if (node->type == TokenType::NOT) {
        SearchResults excludedResults = evaluate(node->right);

        std::unordered_set<int> excludedIDs;

        for (const auto& result : excludedResults)
            excludedIDs.insert(result.documentID);

        SearchResults results;

        for (const auto& document : m_documents) {
            if (excludedIDs.find(document.getID()) == excludedIDs.end()) {
                results.push_back({document.getID(), 0});
            }
        }

        return results;
    }

    throw std::runtime_error("Unknown query node type.");
}



