/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>

bool IsAnagrams(const std::string& left, const std::string& right)
{
    if (left.empty() || right.empty() || left == right)
    {
        return false;
    }

    for (const auto& ch : left)
    {
        if (right.find(ch) == std::string::npos)
        {
            return false;
        }
    }

    return true;
}

TEST(IsAnagramsTest, InsertEmptyStringsReturnFalse)
{
    EXPECT_FALSE(IsAnagrams(std::string(), std::string()));
}

TEST(IsAnagramsTest, InsertSingleWordsAnagramsReturnTrue)
{
    EXPECT_TRUE(IsAnagrams("restful", "fluster"));
}

TEST(IsAnagramsTest, InsertSingleWordAndPhraseAnagramsReturnTrue)
{
    EXPECT_TRUE(IsAnagrams("adultery", "true lady"));
}

TEST(IsAnagramsTest, InsertSameWordsReturnFalse)
{
    EXPECT_FALSE(IsAnagrams("word", "word"));
}
