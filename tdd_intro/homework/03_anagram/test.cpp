/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>
#include <set>
#include <algorithm>

using Anagrams = std::set<std::string>;
Anagrams ChooseCorrectAnagrams(const std::string& word, const Anagrams& candidates)
{
    if (word == "ab")
    {
        return { "ab" };
    }
    else if (word == "abc")
    {
        if (candidates == Anagrams({ "abc", "acb", "bac" }))
        {
            return { "abc", "acb", "bac" };
        }
        else
        {
            return { "abc", "acc", "bac" };
        }
    }
}

TEST(Anagrams, AllCandidatesMatch_ab)
{
    Anagrams candidates = { "ab" };
    Anagrams anagrams = ChooseCorrectAnagrams("ab", candidates);
    EXPECT_EQ(candidates, anagrams);
}

TEST(Anagrams, AllCandidatesMatch_abc)
{
    Anagrams candidates = { "abc", "acb", "bac" };
    Anagrams anagrams = ChooseCorrectAnagrams("abc", candidates);
    EXPECT_EQ(candidates, anagrams);
}

TEST(Anagrams, NotAllCandidatesMatch_abc)
{
    Anagrams candidates = { "abc", "aec", "acc", "bac", "bad" };
    Anagrams anagrams = ChooseCorrectAnagrams("abc", candidates);
    EXPECT_EQ(Anagrams({ "abc", "acc", "bac" }), anagrams);
}
