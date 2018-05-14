/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>

std::vector<std::string> GetAnagram(const std::string&, std::vector<std::string>&)
{
    return std::vector<std::string>();
}

TEST(ANAGRAM, GetAnagram)
{
    EXPECT_EQ(0,GetAnagram("", std::vector<std::string>()).size());
}
