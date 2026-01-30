//
// Created by shoxk on 30.01.2026.
//

#include "InvertedIndex.h"
#include <sstream>
void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    docs = std::move(input_docs);
    freq_dictionary.clear();

    for (size_t doc_id = 0; doc_id < docs.size(); doc_id++) {
        std::map<std::string,size_t> word_count;
        std::stringstream ss(docs[doc_id]);
        std::string word;

        while (ss >> word) {
            ++word_count[word];
        }
        for (const auto& [key,count]: word_count) {
            freq_dictionary[key].push_back({doc_id,count});
        }
    }
}
std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {
    if (freq_dictionary.count(word) == 0)
        return{};

    return freq_dictionary.at(word);
}

