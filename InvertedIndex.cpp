#include "InvertedIndex.h"

#include <iostream>
#include <sstream>

static size_t CountWord(const std::string& token, const std::string& word) {
    if (word.size() == 1) return 0;
    size_t count = 0;
    size_t pos = 0;
    while ((pos = token.find(word, pos)) != std::string::npos) {
        ++count;
        pos += word.size();
    }

    return count;
}

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& docs) {
    docs_ = docs;
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) const {
    std::vector<Entry> result;

    for (size_t doc_id = 0; doc_id < docs_.size(); ++doc_id) {
        std::stringstream ss(docs_[doc_id]);
        std::string token;
        size_t total = 0;

        while (ss >> token) {
            total += CountWord(token, word);
        }

        if (total > 0) {
            result.push_back({doc_id, total});
        }
    }

    return result;
}
