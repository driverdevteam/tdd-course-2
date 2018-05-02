/*
Given a phrase, count the occurrences of each word in that phrase.

For example for the input "olly olly in come free"

olly: 2
in: 1
come: 1
free: 1

*/

#include <gtest/gtest.h>
#include <sstream>
#include <map>
#include <string>

using MyMap = std::map<std::string, int>;

MyMap WordsCount(const std::string& str)
{
    if (str.empty())
    {
        return {};
    }

    MyMap result;

    std::istringstream f(str);
    std::string s;

    while(std::getline(f, s, ' '))
    {
        if (!s.empty())
        {
            ++result[s];
        }
    }


    return result;
}


TEST(WordsCountTests, TakeEmptyString_ReturnEmptyMap)
{
    EXPECT_EQ(MyMap(), WordsCount(""));
}

TEST(WordsCountTests, TakeOneWord_ReturnOneOccurForThisWord)
{
    const std::string word = "Word";
    MyMap myMap;
    myMap[word] = 1;
    EXPECT_EQ(myMap, WordsCount(word));
}

TEST(WordsCountTests, TakeOneWord_Hello_ReturnOneOccurForThisWord)
{
    const std::string word = "Hello";
    MyMap myMap;
    myMap[word] = 1;
    EXPECT_EQ(myMap, WordsCount(word));
}

TEST(WordsCountTests, TakeOneWithSpaceInTheEnd_ReturnOneOccur)
{
    const std::string word = "word ";
    MyMap myMap;
    myMap["word"] = 1;
    EXPECT_EQ(myMap, WordsCount(word));
}

TEST(WordsCountTests, TakeOneWithSpace_ReturnOneOccur)
{
    const std::string word = " word";
    MyMap myMap;
    myMap["word"] = 1;
    EXPECT_EQ(myMap, WordsCount(word));
}

TEST(WordsCountTests, TakeTwoDiffWords_ReturnOneOccurForEach)
{
    const std::string word = "Hello word";
    MyMap myMap;
    myMap["word"] = 1;
    myMap["Hello"] = 1;
    EXPECT_EQ(myMap, WordsCount(word));
}

TEST(WordsCountTests, TakeALotOfDifferentWords_ReturnOneOccurForEach)
{
    const std::string word = "qwerty qwerty1 qwerty2 qwerty3 qwerty4 qwerty5";
    EXPECT_EQ(1, WordsCount(word).at("qwerty"));
    EXPECT_EQ(1, WordsCount(word).at("qwerty1"));
    EXPECT_EQ(1, WordsCount(word).at("qwerty2"));
    EXPECT_EQ(1, WordsCount(word).at("qwerty3"));
    EXPECT_EQ(1, WordsCount(word).at("qwerty4"));
    EXPECT_EQ(1, WordsCount(word).at("qwerty5"));
}

TEST(WordsCountTests, TakeTwoEqualWords_ReturnTwoOccurForIt)
{
    const std::string phrase = "qwerty qwerty";
    MyMap myMap;
    myMap["qwerty"] = 2;
    EXPECT_EQ(myMap, WordsCount(phrase));
}

TEST(WordsCountTests, AcceptanceTest)
{
    const std::string phrase = "olly olly in come free";
    MyMap myMap;
    myMap["olly"] = 2;
    myMap["in"] = 1;
    myMap["come"] = 1;
    myMap["free"] = 1;

    EXPECT_EQ(myMap, WordsCount(phrase));
}

TEST(WordsCountTests, TakeTwoWordsWithManuSpaces_ReturnTwoOccurForIt)
{
    const std::string phrase = "   qwerty       qwerty   ";
    MyMap myMap;
    myMap["qwerty"] = 2;
    EXPECT_EQ(myMap, WordsCount(phrase));
}
