/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>
using Candidates = std::vector<std::string>;

Candidates GetAnagramList(const std::string& str, Candidates& candidates)
{
    return candidates;
}
TEST(AnagramTests, TakeListWithValue_Return_Value)
{
    Candidates vec = {"listen"};
    EXPECT_EQ(vec, GetAnagramList("listen", vec));
}

TEST(AnagramTests, TakeListWith2Values_Return_Value)
{
    Candidates vec = {"enlists", "google"};
    EXPECT_EQ(Candidates({"enlists"}), GetAnagramList("listen", vec));
}
