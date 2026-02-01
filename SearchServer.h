//
// Created by shoxk on 01.02.2026.
//

#ifndef GITIGNORE_SEARCHSERVER_H
#define GITIGNORE_SEARCHSERVER_H
#include "InvertedIndex.h"

struct RelativeIndex {
    size_t doc_id;
    float rank;

    bool operator==(const RelativeIndex& other) const {
        return doc_id == other.doc_id && rank == other.rank;
    }
};
class SearchServer {
public:
    SearchServer(InvertedIndex& idx) : _index(idx) {}
    std::vector<std::vector<RelativeIndex>>
    search(const std::vector<std::string>& queries_input);

private:
    InvertedIndex& _index;
};


#endif //GITIGNORE_SEARCHSERVER_H