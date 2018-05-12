/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>
#include <stdexcept>


std::string GetAnagramFromList(const std::string& word, const std::vector<std::string>& anagrams)
{
    return {};
}

TEST(GetAnagramFromListTest, InputEmptyString_ThrowException)
{
    EXPECT_THROW(GetAnagramFromList("", {"", ""}), std::runtime_error);
}
