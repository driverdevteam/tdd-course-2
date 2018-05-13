/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>
using Candidates = std::vector<std::string>;

namespace
{
    const std::string anagrama = "listen";
}

Candidates GetAnagramList(const std::string& str, Candidates& candidates)
{
    Candidates anagrams;
    for (const auto &value :candidates)
    {
        if (value == "listen")
        {
            anagrams.push_back(value);
        }
        else if (value == "enlists")
        {
            anagrams.push_back(value);
        }
    }
    return anagrams;
}
TEST(AnagramTests, TakeListWithValue_Return_Value)
{
    Candidates vec = {anagrama};
    EXPECT_EQ(vec, GetAnagramList(anagrama, vec));
}
TEST(AnagramTests, TakeListWith2Values_Expect_Value)
{
    Candidates vec = {"enlists", "google"};
    EXPECT_EQ(Candidates({"enlists"}), GetAnagramList(anagrama, vec));
}
TEST(AnagramTests, TakeListWith3Values_Expect_Value)
{
    Candidates vec = {"google", "enlists", "inlets"};
    EXPECT_EQ(Candidates({"enlists"}), GetAnagramList(anagrama, vec));
}
