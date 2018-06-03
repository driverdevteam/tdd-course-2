/*
Given a person's allergy score, determine whether or not they're allergic to a given item, and their full list of allergies.
An allergy test produces a single numeric score which contains the information about all the allergies the person has (that they were tested for).
The list of items (and their value) that were tested are:
    eggs (1)
    peanuts (2)
    shellfish (4)
    strawberries (8)
    tomatoes (16)
    chocolate (32)
    pollen (64)
    cats (128)
So if Tom is allergic to peanuts and chocolate, he gets a score of 34.

Now, given just that score of 34, your program should be able:
    To say have Tom allergic to specific product or not.
    To give list of all allergens Tom is allergic to.

E.g. it can be class with methods IsAllergicTo(string), List() and receiving allergyScore in constructor

Note: a given score may include allergens not listed above (i.e. allergens that score 256, 512, 1024, etc.).
Your program should ignore those components of the score.
For example, if the allergy score is 257, your program should only report the eggs (1) allergy.
*/

//List of tests:
//    1. Input 1 and get set with "eggs"
//    2. Input 0 and get empty set
//    3. Input 3 and get "eggs" and "peanuts"
//    4. Input 97 and get "polen", "chocolate" and "eggs"
//    5. Input 255 and get all list of allergies
//    6. Input 259 and "eggs" and "peanuts"


#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
using StringSet = std::set<std::string>;

namespace
{
    static const std::vector<std::pair<int, std::string>> allergentsScores = {{128, "cats"},
                                                                              {64, "pollen"},
                                                                              {32, "chocolate"},
                                                                              {16, "tomatoes"},
                                                                              {8, "strawberries"},
                                                                              {4, "shellfish"},
                                                                              {2, "peanuts"},
                                                                              {1, "eggs"}};
    const int TOMS_ALLERGENTS_END_VALUE = 256;
}

void CalculateAllergents(int scores, StringSet& results)
{
    if (scores / TOMS_ALLERGENTS_END_VALUE >= 1)
    {
        scores = scores % TOMS_ALLERGENTS_END_VALUE;
    }
    for (auto val = allergentsScores.begin(); val != allergentsScores.end(); ++val)
    {
        if (scores - val->first >= 0)
        {
            results.insert(val->second);
            scores-=val->first;
        }
    }
}


TEST(AllergentsTests, Input_0_get_emptyList)
{
    StringSet allergentsList;
    CalculateAllergents(0, allergentsList);
    auto findedElement = std::find(allergentsList.begin(), allergentsList.end(), "");

    EXPECT_TRUE(allergentsList.empty());
    EXPECT_FALSE(findedElement != allergentsList.end());
}
TEST(AllergentsTests, Input_1_get_eggs)
{
    StringSet allergentsList;
    const std::string checkString = allergentsScores[7].second;
    CalculateAllergents(1, allergentsList);
    auto findedElement = std::find(allergentsList.begin(), allergentsList.end(), checkString);

    EXPECT_EQ(StringSet{checkString}, allergentsList);
    EXPECT_TRUE(findedElement != allergentsList.end());
}
TEST(AllergentsTests, Input_2_get_peanuts)
{
    StringSet allergentsList;
    const std::string checkString = allergentsScores[6].second;
    CalculateAllergents(2, allergentsList);
    auto findedElement = std::find(allergentsList.begin(), allergentsList.end(), checkString);

    EXPECT_EQ(StringSet{checkString}, allergentsList);
    EXPECT_TRUE(findedElement != allergentsList.end());
}
TEST(AllergentsTests, Input_3_get_eggs_peanuts_check_peanuts)
{
    StringSet allergentsList;
    StringSet checkList = {allergentsScores[7].second, allergentsScores[6].second};
    CalculateAllergents(3, allergentsList);
    auto findedElement = std::find(allergentsList.begin(), allergentsList.end(), allergentsScores[6].second);

    EXPECT_TRUE(allergentsList == checkList);
    EXPECT_TRUE(findedElement != allergentsList.end());
}
TEST(AllergentsTests, Input_87_get_eggs_chocolate_polen_check_chocolate)
{
    StringSet allergentsList;
    StringSet checkList = {allergentsScores[1].second, allergentsScores[2].second, allergentsScores[7].second};
    CalculateAllergents(97, allergentsList);
    auto findedElement = std::find(allergentsList.begin(), allergentsList.end(), allergentsScores[1].second);

    EXPECT_TRUE(allergentsList == checkList);
    EXPECT_TRUE(findedElement != allergentsList.end());
}
TEST(AllergentsTests, Input_255_get_all_alergents_list)
{
    StringSet allergentsList;
    CalculateAllergents(255, allergentsList);
    auto findedElement = std::find(allergentsList.begin(), allergentsList.end(), allergentsScores[0].second);

    EXPECT_TRUE(allergentsList.size() == allergentsScores.size());
    EXPECT_TRUE(findedElement != allergentsList.end());
}

TEST(AllergentsTests, Input_259_get_eggs_peanuts_check_eggs)
{
    StringSet allergentsList;
    StringSet checkList = {allergentsScores[7].second, allergentsScores[6].second};
    CalculateAllergents(259, allergentsList);
    auto findedElement = std::find(allergentsList.begin(), allergentsList.end(), allergentsScores[7].second);

    EXPECT_TRUE(allergentsList == checkList);
    EXPECT_TRUE(findedElement != allergentsList.end());
}
