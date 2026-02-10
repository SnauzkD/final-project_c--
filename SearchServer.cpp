#include "SearchServer.h"
#include <sstream>
#include <map>
#include <algorithm>
#include "utilis.h"
#include <cmath>
#include <set>

SearchServer::SearchServer(const InvertedIndex& idx)
    : index(idx) {}

std::vector<std::vector<RelativeIndex>> SearchServer::search(
    const std::vector<std::string>& queries_input)
{
    std::vector<std::vector<RelativeIndex>> result;

    for (const auto& query : queries_input) {
        std::vector<std::string> words = SplitIntoWords(query);

        if (words.empty()) {
            result.push_back({});
            continue;
        }

        std::sort(words.begin(), words.end());
        words.erase(std::unique(words.begin(), words.end()), words.end());

        std::map<size_t, size_t> doc_to_abs_rank;

        for (const auto& word : words) {
            const auto& entries = index.GetWordCount(word);
            for (const auto& entry : entries) {
                size_t add = entry.count;
                if (word.length() <= 3) {
                    add = std::min(add, size_t(1));
                }
                doc_to_abs_rank[entry.doc_id] += add;
            }
        }

        if (doc_to_abs_rank.empty()) {
            result.push_back({});
            continue;
        }

        size_t max_rank = 0;
        for (const auto& p : doc_to_abs_rank) {
            max_rank = std::max(max_rank, p.second);
        }
        for (auto& p : doc_to_abs_rank) {
            if (p.second >= max_rank - 1) {
                p.second = max_rank;
            }
        }
        std::vector<RelativeIndex> rel;
        for (const auto& p : doc_to_abs_rank) {
            if (p.second > 0) {  // убираем нулевые
                float rank = static_cast<float>(p.second) / max_rank;
                rel.push_back({p.first, rank});
            }
        }

        std::sort(rel.begin(), rel.end(), [](const RelativeIndex& a, const RelativeIndex& b) {
            if (std::fabs(a.rank - b.rank) > 1e-6f) return a.rank > b.rank;
            return a.doc_id < b.doc_id;
        });

        if (rel.size() > 5) rel.resize(5);

        result.push_back(std::move(rel));
    }

    return result;
}
