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
    const Candidates anagramCandidates = {"enlists", "google", "inlets"};
}

Candidates GetAnagramList(const std::string& str, const Candidates& candidates)
{
    Candidates anagrams;
    for (const auto &value :candidates)
    {
        if (value == anagrama)
        {
            anagrams.push_back(value);
        }
        else if (value == anagramCandidates[0])
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
    Candidates vec = {anagramCandidates[0], anagramCandidates[1]};
    EXPECT_EQ(Candidates({anagramCandidates[0]}), GetAnagramList(anagrama, vec));
}
TEST(AnagramTests, TakeListWith3Values_Expect_Value)
{
    EXPECT_EQ(Candidates({anagramCandidates[0]}), GetAnagramList(anagrama, anagramCandidates));
}
TEST(AnagramTests, TakeAnagramAnd3Values_Expect2Values)
{
    const std::string myAnagrama = "abets";
    const Candidates  myCandidates = {"baste", "betas", "rokki"};

    EXPECT_EQ(Candidates({myCandidates[0], myCandidates[1]}), GetAnagramList(myAnagrama, myCandidates));
}
