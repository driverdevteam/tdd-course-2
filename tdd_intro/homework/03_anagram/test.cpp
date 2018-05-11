/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>
#include <set>
#include <string>
#include <algorithm>

using Anagrams = std::set<std::string>;
Anagrams ChooseCorrectAnagrams(const std::string& word, const Anagrams& candidates)
{
    Anagrams anagrams;
    for (std::string candidate : candidates)
    {
        bool matched = true;
        auto candidateLettersSet = candidate;
        for (auto letter : word)
        {
            auto letterPos = candidateLettersSet.find(letter);
            if (letterPos == candidateLettersSet.npos)
            {
                matched = false;
                break;
            }
            else
            {
                candidateLettersSet.erase(letterPos, 1);
            }
        }
        if (matched)
        {
            anagrams.insert(candidate);
        }
    }
    return anagrams;
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
    Anagrams candidates = { "abc", "aec", "cab", "bac", "bad" };
    Anagrams anagrams = ChooseCorrectAnagrams("abc", candidates);
    EXPECT_EQ(Anagrams({ "abc", "cab", "bac" }), anagrams);
}

TEST(Anagrams, AcceptanceTest)
{
    Anagrams candidates = { "enlists", "google", "inlets", "banana" };
    Anagrams anagrams = ChooseCorrectAnagrams("listen", candidates);
    EXPECT_EQ(Anagrams({ "inlets" }), anagrams);
}
