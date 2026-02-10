#include "utilis.h"
#include <sstream>

#include "utilis.h"
#include <sstream>
#include <cctype>       // для tolower
#include <algorithm>    // для transform

std::vector<std::string> SplitIntoWords(const std::string& text) {
    std::vector<std::string> words;
    std::istringstream iss(text);
    std::string word;

    while (iss >> word) {
        std::transform(word.begin(), word.end(), word.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
            return std::ispunct(static_cast<unsigned char>(c));
        }), word.end());

        if (!word.empty()) {
            words.push_back(std::move(word));
        }
    }

    return words;
}