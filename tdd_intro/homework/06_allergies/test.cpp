/*
Given a person's allergy score, determine whether or not they're allergic to a given item, and their full list of allergies.
An allergy test produces a single numeric score which contains the information about all the allergies the person has (that they were tested for).
The list of items (and their value) that were tested are: eggs (1) peanuts (2) shellfish (4) strawberries (8) tomatoes (16) chocolate (32) pollen (64) cats (128)
So if Tom is allergic to peanuts and chocolate, he gets a score of 34.

Now, given just that score of 34, your program should be able:

To say have Tom allergic to specific product or not.
To give list of all allergens Tom is allergic to.
Note: a given score may include allergens not listed above (i.e. allergens that score 256, 512, 1024, etc.).
Your program should ignore those components of the score. For example, if the allergy score is 257, your program should only report the eggs (1) allergy.
*/

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <map>

using AllergiesList = std::vector<std::string>;

std::map<unsigned int, std::string> allergies_mp = {{1, "eggs"},
                                                    {2, "peanuts"},
                                                    {4, "shellfish"},
                                                    {8, "strawberries"},
                                                    {16, "tomatoes"},
                                                    {32, "chocolate"},
                                                    {64, "pollen"},
                                                    {128, "cats"}};

AllergiesList GetAllergiesList(unsigned int score)
{
    return {allergies_mp.find(score)->second};
}

TEST(Allergies, GetAllergiesList_EggsAllergy)
{
    unsigned int score = 1;
    EXPECT_EQ(AllergiesList({"eggs"}), GetAllergiesList(score));
}

TEST(Allergies, GetAllergiesList_PeanutsAllergy)
{
    unsigned int score = 2;
    EXPECT_EQ(AllergiesList({"peanuts"}), GetAllergiesList(score));
}

TEST(Allergies, GetAllergiesList_NoAllergy)
{
    unsigned int score = 0;
    EXPECT_EQ(AllergiesList(), GetAllergiesList(score));
}
