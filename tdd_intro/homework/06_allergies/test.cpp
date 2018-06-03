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
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
using StringSet = std::set<std::string>;

//List of tests:
//    1. Input 1 and get set with "eggs"
//    2. Input 0 and get empty set
//    3. Input 3 and get "eggs" and "peanuts"
//    4. Input 87 and get "polen", "chocolate" and "eggs"
//    5. Input 256 and get all list of allergies
//    6. Input 260 and "eggs" and "peanuts"


StringSet CalculateAllergents(int scores)
{
    static const std::vector<std::pair<int, std::string>> allergentsScores = {{128, "cats"},
                                                                              {64, "pollen"},
                                                                              {32, "chocolate"},
                                                                              {16, "tomatoes"},
                                                                              {8, "strawberries"},
                                                                              {4, "shellfish"},
                                                                              {2, "peanuts"},
                                                                              {1, "eggs"}};
    StringSet results;
    for (auto val = allergentsScores.begin(); val != allergentsScores.end(); ++val)
    {
        if (scores - val->first >= 0)
        {
            results.insert(val->second);
            scores-=val->first;
        }
    }

    return results;
}


TEST(AllergentsTests, Input_0_get_emptyList)
{
    StringSet allergentsList = CalculateAllergents(0);
    auto findedElement = std::find(allergentsList.begin(), allergentsList.end(), "");

    EXPECT_TRUE(allergentsList.empty());
    EXPECT_FALSE(findedElement != allergentsList.end());
}
TEST(AllergentsTests, Input_1_get_eggs)
{
    const std::string checkString = "eggs";
    StringSet allergentsList = CalculateAllergents(1);
    auto findedElement = std::find(allergentsList.begin(), allergentsList.end(), checkString);

    EXPECT_EQ(StringSet{checkString}, allergentsList);
    EXPECT_TRUE(findedElement != allergentsList.end());
}
TEST(AllergentsTests, Input_2_get_peanuts)
{
    const std::string checkString = "peanuts";
    StringSet allergentsList = CalculateAllergents(2);
    auto findedElement = std::find(allergentsList.begin(), allergentsList.end(), checkString);

    EXPECT_EQ(StringSet{checkString}, allergentsList);
    EXPECT_TRUE(findedElement != allergentsList.end());
}
TEST(AllergentsTests, Input_3_get_eggs_peanuts_check_peanuts)
{
    StringSet checkList = {"eggs", "peanuts"};
    StringSet allergentsList = CalculateAllergents(3);
    auto findedElement = std::find(allergentsList.begin(), allergentsList.end(), "peanuts");

    EXPECT_TRUE(allergentsList == checkList);
    EXPECT_TRUE(findedElement != allergentsList.end());
}
