/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>
#include <algorithm>
using Candidates = std::vector<std::string>;

namespace
{
    const std::string s_anagrama = "listen";
    const Candidates s_anagramCandidates = {"inlets", "google", "enlists"};
    const std::string s_additionalAnagrama = "abets";
    const Candidates  s_additionalCandidates = {"baste", "betas", "rokki"};
}

Candidates GetAnagramList(const std::string& anagrama, const Candidates& candidates)
{
    Candidates anagrams;
    std::string sortedValue;
    std::string sortedAnagrama = anagrama;
    std::sort(sortedAnagrama.begin(), sortedAnagrama.end());

    for (const auto& value :candidates)
    {
        sortedValue = value;
        std::sort(sortedValue.begin(), sortedValue.end());

        if (sortedValue == sortedAnagrama)
        {
            anagrams.push_back(value);
        }
    }
    return anagrams;
}
TEST(AnagramTests, TakeListWithValue_Return_Value)
{
    Candidates vec = {s_anagrama};
    EXPECT_EQ(vec, GetAnagramList(s_anagrama, vec));
}
TEST(AnagramTests, TakeListWith2Values_Expect_Value)
{
    Candidates vec = {s_anagramCandidates[0], s_anagramCandidates[1]};
    EXPECT_EQ(Candidates({s_anagramCandidates[0]}), GetAnagramList(s_anagrama, vec));
}
TEST(AnagramTests, TakeListWith3Values_Expect_Value)
{
    EXPECT_EQ(Candidates({s_anagramCandidates[0]}),
              GetAnagramList(s_anagrama, s_anagramCandidates));
}
TEST(AnagramTests, TakeAnagramAnd3Values_Expect2Values)
{


    EXPECT_EQ(Candidates({s_additionalCandidates[0], s_additionalCandidates[1]}),
              GetAnagramList(s_additionalAnagrama, s_additionalCandidates));
}
TEST(AnagramTests, TakeAnagramAnd3Values_Expect3Values)
{
    const Candidates myCandidates({s_additionalCandidates[0],
                                   s_additionalCandidates[1],
                                   "abste"});
    EXPECT_EQ(myCandidates,
              GetAnagramList(s_additionalAnagrama, myCandidates));
}

TEST(AnagramTests, TakeEmptyAnagrama_Expect_empty)
{
    EXPECT_EQ(Candidates(), GetAnagramList("", s_anagramCandidates));
}
