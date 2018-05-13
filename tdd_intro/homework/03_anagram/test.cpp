/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>

std::vector<std::string> GetAnagramList(const std::string& str, std::vector<std::string>& candidates)
{
    return {};
}
TEST(AnagramTests, TakeListWithValue_Return_Value)
{
    std::vector<std::string> vec = {"listen"};
    EXPECT_EQ(vec, GetAnagramList("listen", vec));
}
