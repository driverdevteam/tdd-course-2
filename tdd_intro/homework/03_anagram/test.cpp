/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>

#include <string>
#include <vector>

using String_vt = std::vector<std::string>;

String_vt GetAnagrams(const std::string& word,
                      const String_vt& wordList)
{
    return String_vt({word});
}

TEST(GetAnagrams, GiveOnlyOneWord_word_ReturnIt)
{
    String_vt expectedAnagrams;
    String_vt givenWords;

    const std::string word("word");

    givenWords.push_back(word);
    expectedAnagrams = givenWords;
    EXPECT_EQ(expectedAnagrams, GetAnagrams(word, givenWords));
}

TEST(GetAnagrams, GiveOnlyOneWord_hello_ReturnIt)
{
    String_vt expectedAnagrams;
    String_vt givenWords;

    const std::string word("hello");

    givenWords.push_back(word);
    expectedAnagrams = givenWords;
    EXPECT_EQ(expectedAnagrams, GetAnagrams(word, givenWords));
}

