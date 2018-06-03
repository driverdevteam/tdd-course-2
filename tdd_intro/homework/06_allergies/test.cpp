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
using StringList = std::vector<std::string>;

//List of tests:
//    1. Input 1 and get set with "eggs"
//    2. Input 0 and get empty set
//    3. Input 3 and get "eggs" and "peanuts"
//    4. Input 87 and get "polen", "chocolate" and "eggs"
//    5. Input 256 and get all list of allergies
//    6. Input 260 and "eggs" and "peanuts"


StringList CalculateAllergents(unsigned int scores)
{
    static const std::map<unsigned int, std::string> allergentsScores = {{1, "eggs"},
                                                                   {2, "peanuts"},
                                                                   {4, "shellfish"},
                                                                   {8, "strawberries"},
                                                                   {16, "tomatoes"},
                                                                   {32, "chocolate"},
                                                                   {64, "pollen"},
                                                                   {128, "cats"}};
    if (scores > 0)
    {
        return StringList{"eggs"};
    }
    return StringList();
}


TEST(AllergentsTests, Input_0_get_emptyList)
{
    StringList allergentsList = CalculateAllergents(0);
    auto findedElement = std::find(allergentsList.begin(), allergentsList.end(), "");

    EXPECT_TRUE(allergentsList.empty());
    EXPECT_FALSE(findedElement != allergentsList.end());
}
TEST(AllergentsTests, Input_1_get_eggs)
{
    StringList allergentsList = CalculateAllergents(1);
    auto findedElement = std::find(allergentsList.begin(), allergentsList.end(), "eggs");

    EXPECT_EQ(StringList{"eggs"}, allergentsList);
    EXPECT_TRUE(findedElement != allergentsList.end());
}
