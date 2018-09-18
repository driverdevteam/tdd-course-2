/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <set>

using String_vt = std::vector<std::string>;
using Char_mst = std::multiset<char>;

Char_mst GetCharSet(std::string str)
{
    Char_mst result;
    for (const char chr : str)
    {
        result.insert(chr);
    }
    return result;
}

String_vt GetAnagrams(const std::string& word,
                      const String_vt& wordList)
{
    String_vt result;

    const Char_mst wordCharSet = GetCharSet(word);

    for (const std::string& curWord : wordList)
    {
        if (GetCharSet(curWord) == wordCharSet)
        {
            result.push_back(curWord);
        }
    }

    return result;
}

TEST(GetAnagrams, GiveOnlyOneWord_word_ReturnIt)
{
    const std::string word("word");

    String_vt expectedAnagrams({word});
    String_vt givenWords = expectedAnagrams;

    EXPECT_EQ(expectedAnagrams, GetAnagrams(word, givenWords));
}

TEST(GetAnagrams, GiveOnlyOneWord_hello_ReturnIt)
{
    const std::string word("hello");

    String_vt expectedAnagrams({word});
    String_vt givenWords = expectedAnagrams;

    EXPECT_EQ(expectedAnagrams, GetAnagrams(word, givenWords));
}

TEST(GetAnagrams, GiveTwoAnagrams_ReturnThem)
{
    const std::string word("word");
    const std::string anagram("rowd");

    String_vt expectedAnagrams({word, anagram});
    String_vt givenWords = expectedAnagrams;

    EXPECT_EQ(expectedAnagrams, GetAnagrams(word, givenWords));
}

TEST(GetAnagrams, GiveOneAnagramOfTwoWords_ReturnOne)
{
    const std::string word("word");
    const std::string nonAnagram("rowdd");

    String_vt expectedAnagrams({word});
    String_vt givenWords({word, nonAnagram});

    EXPECT_EQ(expectedAnagrams, GetAnagrams(word, givenWords));
}

TEST(GetCharSet, GiveWord_hello_ReturnItsLetters)
{
    const std::string word = "hello";

    Char_mst expectedSet({'e', 'h', 'l', 'l', 'o'});

    EXPECT_EQ(expectedSet, GetCharSet(word));
}

TEST(GetCharSet, GiveWord_world_ReturnItsLetters)
{
    const std::string word = "world";

    Char_mst expectedSet({'d', 'l', 'o', 'r', 'w'});

    EXPECT_EQ(expectedSet, GetCharSet(word));
}

TEST(GetCharSet, AcceptanceTest)
{
    const std::string word = "listen";

    String_vt expectedAnagrams({"inlets"});
    String_vt givenWords({"enlists", "google", "inlets", "banana"});

    EXPECT_EQ(expectedAnagrams, GetAnagrams(word, givenWords));
}
