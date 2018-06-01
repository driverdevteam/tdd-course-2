/*
Given a person's allergy score, determine whether or not they're allergic to a given item, and their full list of allergies.
An allergy test produces a single numeric score which contains the information about all the allergies the person has (that they were tested for).
The list of items (and their value) that were tested are:

eggs (1) peanuts (2) shellfish (4) strawberries (8) tomatoes (16)
chocolate (32) pollen (64) cats (128)

So if Tom is allergic to peanuts and chocolate, he gets a score of 34.

Now, given just that score of 34, your program should be able:

To say have Tom allergic to specific product or not.
To give list of all allergens Tom is allergic to.
Note: a given score may include allergens not listed above (i.e. allergens that score 256, 512, 1024, etc.). Your program should ignore those components of the score. For example, if the allergy score is 257, your program should only report the eggs (1) allergy.
*/
#include <gtest/gtest.h>

//tests list
/*
  1.Check no allergy
  2.Check eggs alergy
  3.Check peanuts alergy
  4.Check shellfish alergy
  5.Check tomatoes alergy
  6.Check chocolate alergy
  7.Check pollen alergy
  8.Check cats alergy
  9.Check eggs and peanuts
  10.Check eggs and strawberries and pollen
  11.Check random alergy
 */

std::string GetAlergy(size_t score)
{
    return "You don't have any alergy";
}

TEST(GetAlergy, Check_no_allergy)
{
    EXPECT_EQ("You don't have any alergy", GetAlergy(0));
}

TEST(GetAlergy, Check_eggs_alergy)
{
    EXPECT_EQ("You have alergy:eggs", GetAlergy(1));
}

