/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>

using Candidates = std::vector<std::string>;

 Candidates GetAnagram(const std::string&, Candidates&)
{
    return Candidates();
}

TEST(ANAGRAM, GetAnagram)
{
    EXPECT_EQ(0, GetAnagram("", Candidates()).size());
}
