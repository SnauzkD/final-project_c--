//
// Created by shoxk on 01.02.2026.
//

#include "SearchServer.h"
#include "utilis.h"
#include <algorithm>

std::vector<std::vector<RelativeIndex>>
SearchServer::search(const std::vector<std::string>& queries_input)
{
    std::vector<std::vector<RelativeIndex>> result;

    for (const auto& query : queries_input) {
        std::vector<std::string> words = SplitIntoWords(query);

        std::sort(words.begin(), words.end());
        words.erase(std::unique(words.begin(), words.end()), words.end());

        std::sort(words.begin(), words.end(),
            [&](const std::string& a, const std::string& b) {
                return _index.GetWordCount(a).size() <
                       _index.GetWordCount(b).size();
            });

        std::map<size_t, float> doc_relevance;

        for (const auto& word : words) {
            for (const auto& [doc_id, count] : _index.GetWordCount(word)) {
                doc_relevance[doc_id] += count;
            }
        }

        float max_rank = 0;
        for (const auto& [_, rank] : doc_relevance)
            max_rank = std::max(max_rank, rank);

        std::vector<RelativeIndex> answer;
        for (const auto& [doc_id, rank] : doc_relevance) {
            answer.push_back({doc_id, rank / max_rank});
        }

        std::sort(answer.begin(), answer.end(),
            [](auto& a, auto& b) {
                return a.rank > b.rank;
            });

        if (answer.size() > 5)
            answer.resize(5);

        result.push_back(answer);
    }

    return result;
}
