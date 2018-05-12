/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>
#include <stdexcept>
#include <algorithm>

using AnagramList = std::vector<std::string>;

AnagramList GetAnagramFromList(const std::string& word, const AnagramList& anagrams)
{
    if (word.empty())
    {
        throw std::runtime_error("Word can not be empty.");
    }
    else if (anagrams.empty())
    {
        throw std::runtime_error("Anagram list can not be empty.");
    }

    if (std::find(anagrams.begin(), anagrams.end(), word) != anagrams.end())
    {
        return anagrams;
    }

    return {};
}

TEST(GetAnagramFromListTest, InputEmptyString_ThrowException)
{
    EXPECT_THROW(GetAnagramFromList("", {"", ""}), std::runtime_error);
}

TEST(GetAnagramFromListTest, InputStringAndListWithoutString_ReturnEmptyList)
{
    EXPECT_EQ(AnagramList(), GetAnagramFromList("String", {"1", "2"}));
}

TEST(GetAnagramFromListTest, InputWordAndEmptyList_ThrowException)
{
    EXPECT_THROW(GetAnagramFromList("Word", {}), std::runtime_error);
}

TEST(GetAnagramFromListTest, InputStringAndListWithString_ReturnListWithString)
{
    EXPECT_EQ(AnagramList{"String"}, GetAnagramFromList("String", {"String"}));
}
