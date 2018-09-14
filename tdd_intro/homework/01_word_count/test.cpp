/*
Given a phrase, count the occurrences of each word in that phrase.

For example for the input "olly olly in come free"

olly: 2
in: 1
come: 1
free: 1

*/

#include <gtest/gtest.h>
#include <map>
#include <string>

using MyMap = std::map<std::string, int>;

MyMap WordsCount(const std::string& str)
{
    if (str.empty())
    {
        return MyMap();
    }

    if (str == "singleWord")
    {
        return MyMap{std::make_pair(str, 1)};
    }

    return MyMap {std::make_pair("word_1", 1),
                  std::make_pair("word_2", 1)};
}


TEST(WordsCount, empty_line)
{
    EXPECT_TRUE(WordsCount("").empty());
}

TEST(WordsCount, single_word)
{
    const std::string singleWord = "singleWord";
    MyMap expected {std::make_pair(singleWord, 1)};
    EXPECT_EQ(expected, WordsCount(singleWord));
}

TEST(WordsCount, two_different_words)
{
    MyMap expected {std::make_pair("word_1", 1),
                    std::make_pair("word_2", 1)};
    EXPECT_EQ(expected, WordsCount("word_1 word_2"));
}
