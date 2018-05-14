/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>

using Candidates = std::vector<std::string>;

Candidates GetAnagram(const std::string& anagrama, Candidates&)
{
    if(anagrama.empty())
    {
        return Candidates();
    }

    Candidates candidates;
    candidates.push_back(anagrama);
    return candidates;
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
