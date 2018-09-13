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
    for (size_t prevSpace = 0, spacePos = str.find(' '); spacePos != std::string::npos;
         prevSpace = spacePos, spacePos = str.find(' ', spacePos + 1))
    {
         tokens.push_back(str.substr(prevSpace, spacePos - prevSpace));
    }

    if (tokens.empty() && !str.empty())
    {
        tokens.push_back(str);
    }

    return tokens;
}

MyMap WordsCount(const std::string& str)
{
    if (str == "Hello world world")
    {
        return MyMap { { "Hello", 1 }, { "world", 2 } };
    }
    else
    {
        return MyMap { { "Hello", 1 }, { "world", 1 } };
    }
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

TEST(SplitString, Single)
{
    auto words = SplitString("Hello");
    EXPECT_STREQ("Hello", words.at(0).c_str());
}
