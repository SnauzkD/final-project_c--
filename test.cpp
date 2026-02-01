#include <gtest/gtest.h>
#include "InvertedIndex.h"
#include <vector>
#include <string>
#include "utilis.h"

using namespace std;

void TestInvertedIndexFunctionality(
    const vector<string>& docs,
    const vector<string>& requests,
    const vector<vector<Entry>>& expected)
{
    vector<vector<Entry>> result;
    InvertedIndex idx;

    idx.UpdateDocumentBase(docs);

    for (const auto& request : requests) {
        result.push_back(idx.GetWordCount(request));
    }

    ASSERT_EQ(result, expected);
}
TEST(TestCaseInvertedIndex, TestBasic) {
    const vector<string> docs = {
        "london is the capital of great britain",
        "big ben is the nickname for the great bell of the striking clock"
    };

    const vector<string> requests = {"london", "the"};

    const vector<vector<Entry>> expected = {
        {
            {0, 1}
        },
        {
                {0, 1}, {1, 3}
        }
    };

    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestBasic2) {
    const vector<string> docs = {
        "milk milk milk milk water water water",
        "milk water water",
        "milk milk milk milk milk water water water water",
        "americano cappuccino"
    };

    const vector<string> requests = {"milk", "water", "cappuccino"};

    const vector<vector<Entry>> expected = {
        {
            {0,4},{1,1},{2,5}
        },
        {
                {0,3},{1,2},{2,4}
        },
        {
                {3,1}
        }
    };

    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestMissingWord) {
    const vector<string> docs = {
        "abcdefghijkl",
        "statement"
    };

    const vector<string> requests = {"m", "statement"};

    const vector<vector<Entry>> expected = {
        {},
        {
                {1,1}
        }
    };

    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(UtilsTests, SplitIntoWordsBasic)
{
    std::string text = "milk water sugar";
    std::vector<std::string> expected = {"milk", "water", "sugar"};

    auto result = SplitIntoWords(text);

    ASSERT_EQ(result, expected);
}
TEST(UtilsTests, SplitIntoWordsSingle)
{
    std::string text = "milk";
    std::vector<std::string> expected = {"milk"};

    auto result = SplitIntoWords(text);

    ASSERT_EQ(result, expected);
}
TEST(UtilsTests, SplitIntoWordsEmpty)
{
    std::string text = "";
    std::vector<std::string> expected = {};

    auto result = SplitIntoWords(text);

    ASSERT_EQ(result, expected);
}
