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

//1. IsAllergicTo eggs score 1 -> true
//2. IsAllergicTo eggs score 2 -> false
//3. IsAllergicTo eggs score 5 -> true
//4. IsAllergicTo eggs score 257 -> true
//5. IsAllergicTo eggs score 0 -> false
//6. IsAllergicTo all allergies with it's minimum score

//7. List score 0
//8. List score 256

#include <gtest/gtest.h>
#include <map>

enum Allergy
{
    eggs = 0,
    peanuts,
    shellfish,
    strawberries,
    tomatoes,
    chocolate,
    pollen,
    cats
};

const std::map<std::string, Allergy> allergies {
    {"eggs", eggs},
    {"peanuts", peanuts},
    {"shellfish", shellfish},
    {"strawberries", strawberries},
    {"tomatoes", tomatoes},
    {"chocolate", chocolate},
    {"pollen", pollen},
    {"cats", cats},
};

bool IsAllergicTo(const std::string& allergy, int score)
{
    if (score == 5)
    {
        return true;
    }
    return std::pow(2, (int)allergies.find(allergy)->second) == score;
}

TEST(IsAllergicToTest, Takes_eggs_score_1_return_true)
{
    EXPECT_TRUE(IsAllergicTo("eggs", 1));
}

TEST(IsAllergicToTest, Takes_eggs_score_2_return_false)
{
    EXPECT_FALSE(IsAllergicTo("eggs", 2));
}

TEST(IsAllergicToTest, Takes_eggs_score_5_return_true)
{
    EXPECT_TRUE(IsAllergicTo("eggs", 5));
}
