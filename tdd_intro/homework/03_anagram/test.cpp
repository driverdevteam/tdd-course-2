/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>
#include <stdexcept>
#include <algorithm>

namespace
{
    using AnagramList = std::vector<std::string>;

    std::string GetString()
    {
        static const std::string str("String");
        return str;
    }
}

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

    AnagramList foundAnagrams;

    for (std::string anagram : anagrams)
    {
        if (word == anagram)
        {
            foundAnagrams.push_back(anagram);
        }
    }

    return foundAnagrams;
}

TEST(GetAnagramFromListTest, InputEmptyString_ThrowException)
{
    EXPECT_THROW(GetAnagramFromList("", {"", ""}), std::runtime_error);
}

TEST(GetAnagramFromListTest, InputStringAndListWithoutString_ReturnEmptyList)
{
    EXPECT_EQ(AnagramList(), GetAnagramFromList(GetString(), {"1", "2"}));
}

TEST(GetAnagramFromListTest, InputWordAndEmptyList_ThrowException)
{
    EXPECT_THROW(GetAnagramFromList("Word", {}), std::runtime_error);
}

TEST(GetAnagramFromListTest, InputStringAndListWithString_ReturnListWithString)
{
    EXPECT_EQ(AnagramList{GetString()}, GetAnagramFromList(GetString(), {GetString()}));
}

TEST(GetAnagramFromListTest, InputStringAndListWithManyString_ReturnListWithString)
{
    EXPECT_EQ(AnagramList{GetString()},
              GetAnagramFromList(GetString(), {"0", GetString(), "1", "2"}));
}
