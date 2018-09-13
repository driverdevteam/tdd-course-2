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
    return MyMap { { "Hello", 1 }, { "world", 1 } };
}

TEST(WordsCount, Single)
{
    std::string word = "Hello";
    auto words = WordsCount(word);
    EXPECT_EQ(1, words[word]);
}

TEST(WordsCount, TwoDifferentWords)
{
    auto words = WordsCount("Hello world");
    EXPECT_EQ(1, words["Hello"]);
    EXPECT_EQ(1, words["world"]);
}

TEST(WordsCount, RepeatingWord)
{
    auto words = WordsCount("Hello world world");
    EXPECT_EQ(1, words["Hello"]);
    EXPECT_EQ(2, words["world"]);
}
