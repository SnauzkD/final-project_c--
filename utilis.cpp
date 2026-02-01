#include "utilis.h"
#include <sstream>

std::vector<std::string> SplitIntoWords(const std::string& text)
{
    std::stringstream ss(text);
    std::string word;
    std::vector<std::string> words;

    while (ss >> word)
        words.push_back(word);

    return words;
}