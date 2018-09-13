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

std::vector<std::string> SplitString(const std::string& str)
{
    std::vector<std::string> tokens;

    size_t prevSpace = 0;
    for (size_t spacePos = str.find(' '); spacePos != std::string::npos;
         prevSpace = spacePos + 1, spacePos = str.find(' ', prevSpace))
    {
        tokens.push_back(str.substr(prevSpace, spacePos - prevSpace));
    }
    tokens.push_back(str.substr(prevSpace, str.size() - prevSpace));

    return tokens;
}

MyMap WordsCount(const std::string& str)
{
    auto words = SplitString(str);
    MyMap countedWords;
    for (auto word : words)
    {
        ++countedWords[word];
    }
    return countedWords;
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

TEST(WordsCount, SplitString_Single)
{
    auto words = SplitString("Hello");
    EXPECT_STREQ("Hello", words.at(0).c_str());
}

TEST(WordsCount, SplitString_Several)
{
    auto words = SplitString("Hello world world");
    EXPECT_STREQ("Hello", words.at(0).c_str());
    EXPECT_STREQ("world", words.at(1).c_str());
    EXPECT_STREQ("world", words.at(2).c_str());
}

TEST(WordsCount, Acceptance)
{
    auto words = WordsCount("olly olly in come free");
    EXPECT_EQ(2, words["olly"]);
    EXPECT_EQ(1, words["in"]);
    EXPECT_EQ(1, words["come"]);
    EXPECT_EQ(1, words["free"]);
}
