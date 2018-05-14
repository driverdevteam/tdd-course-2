/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>

using Candidates = std::vector<std::string>;

Candidates GetAnagram(const std::string& anagrama, Candidates& candidates)
{
    std::string sortedAnagrama = anagrama;
    std::sort(sortedAnagrama.begin(), sortedAnagrama.end());
    Candidates result;

    for (const auto& value :candidates)
    {
        std::string sortedValue = value;
        std::sort(sortedValue.begin(), sortedValue.end());

        if(sortedValue == sortedAnagrama)
        {
            result.push_back(value);
        }
    }
    return result;
}

TEST(ANAGRAM, GetAnagram)
{
    EXPECT_EQ(0, GetAnagram("", Candidates()).size());
}

TEST(ANAGRAM, GetAnagramInput_A_and_A_candidatesReturnA)
{
    Candidates candidates;
    candidates.push_back("a");
    EXPECT_EQ(candidates, GetAnagram("a", candidates));
}

TEST(ANAGRAM, GetAnagramInput_B_and_B_candidatesReturnB)
{
    Candidates candidates;
    candidates.push_back("b");
    EXPECT_EQ(candidates, GetAnagram("b", candidates));
}

TEST(ANAGRAM, GetAnagramInput_A_and_B_candidatesReturnEMPTY)
{
    Candidates candidates;
    candidates.push_back("b");
    EXPECT_EQ(0, GetAnagram("a", candidates).size());
}

TEST(ANAGRAM, GetAnagramInput_A_and_B_A_candidatesReturnA)
{
    Candidates candidates;
    candidates.push_back("b");
    candidates.push_back("a");

    Candidates expect;
    expect.push_back("a");
    EXPECT_EQ(expect, GetAnagram("a", candidates));
}

TEST(ANAGRAM, GetAnagramInput_AB_and_B_A_candidatesReturnEMPTY)
{
    Candidates candidates;
    candidates.push_back("b");
    candidates.push_back("a");
    EXPECT_EQ(0, GetAnagram("ab", candidates).size());
}

TEST(ANAGRAM, GetAnagramInput_AB_and_B_BA_candidatesReturnBA)
{
    Candidates candidates;
    candidates.push_back("b");
    candidates.push_back("ba");

    Candidates expect;
    expect.push_back("ba");
    EXPECT_EQ(expect, GetAnagram("ab", candidates));
}
