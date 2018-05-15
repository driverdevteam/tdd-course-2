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

    std::string tmpRight = right;
    tmpRight.erase(std::remove_if(tmpRight.begin(), tmpRight.end(), isspace));

    for (const auto& ch : left)
    {
        if (ch == ' ')
        {
            continue;
        }

        const size_t pos = tmpRight.find(ch);
        if (pos == std::string::npos)
        {
            return false;
        }

        tmpRight = tmpRight.erase(pos, 1);
    }

    return tmpRight.empty();
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

TEST(IsAnagramsTest, InsertSameWordsWithDifferentRegisterReturnFalse)
{
    EXPECT_FALSE(IsAnagrams("Word", "word"));
}

TEST(IsAnagramsTest, InsertSingleWordsAnagramsWithExtraCharacterReturnFalse)
{
    EXPECT_FALSE(IsAnagrams("restful", "flusterA"));
}
