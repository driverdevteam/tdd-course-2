/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>
#include <stdexcept>

using AnagramList = std::vector<std::string>;

AnagramList GetAnagramFromList(const std::string& word, const AnagramList& anagrams)
{
    throw std::runtime_error("Word can not be empty.");
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
