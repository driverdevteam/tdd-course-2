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

using AllergyScore = unsigned int;
enum Allergy // Allergy corresponds to the score as the power of 2
{
    eggs = 0,
    peanuts,
    shellfish,
    strawberries,
    tomatoes,
    chocolate,
    pollen,
    cats,
    allergiesCount
};

using Allergies = std::set<Allergy>;

AllergyScore GetSingleAllergyScore(Allergy allergy)
{
    return 1 << allergy;
}

bool IsAlergyPresentInScore(Allergy allergy, AllergyScore score)
{
    return score & GetSingleAllergyScore(allergy);
}

Allergies GetAllergies(AllergyScore score)
{
    Allergies allergies;
    for (unsigned int i = 0; i < allergiesCount; ++i)
    {
        Allergy allergy = static_cast<Allergy>(i);
        if (IsAlergyPresentInScore(allergy, score))
        {
            allergies.insert(allergy);
        }
    }
    return allergies;
}

TEST(AllergiesTest, NotAllergic)
{
    EXPECT_EQ(Allergies{ }, GetAllergies(0));
}

TEST(AllergiesTest, Eggs)
{
    EXPECT_EQ(Allergies{ eggs }, GetAllergies(1));
}

TEST(AllergiesTest, Peanuts)
{
    EXPECT_EQ(Allergies{ peanuts }, GetAllergies(2));
}

TEST(AllergiesTest, EggsAndPeanuts)
{
    EXPECT_EQ((Allergies{ eggs, peanuts }), GetAllergies(3));
}

TEST(AllergiesTest, PeanutsAndShellfish)
{
    EXPECT_EQ((Allergies{ peanuts, shellfish }), GetAllergies(6));
}

TEST(AllergiesTest, GetSingleAllergyScore)
{
    EXPECT_EQ(1, GetSingleAllergyScore(eggs));
    EXPECT_EQ(2, GetSingleAllergyScore(peanuts));
    EXPECT_EQ(4, GetSingleAllergyScore(shellfish));
    EXPECT_EQ(8, GetSingleAllergyScore(strawberries));
    EXPECT_EQ(16, GetSingleAllergyScore(tomatoes));
    EXPECT_EQ(32, GetSingleAllergyScore(chocolate));
    EXPECT_EQ(64, GetSingleAllergyScore(pollen));
    EXPECT_EQ(128, GetSingleAllergyScore(cats));
}

TEST(AllergiesTest, IsAlergyPresentInScore)
{
    EXPECT_TRUE(IsAlergyPresentInScore(eggs, 1));
    EXPECT_TRUE(IsAlergyPresentInScore(peanuts, 2));
    EXPECT_TRUE(IsAlergyPresentInScore(shellfish, 4));
    EXPECT_TRUE(IsAlergyPresentInScore(strawberries, 8));
    EXPECT_TRUE(IsAlergyPresentInScore(tomatoes, 16));
    EXPECT_TRUE(IsAlergyPresentInScore(chocolate, 32));
    EXPECT_TRUE(IsAlergyPresentInScore(pollen, 64));
    EXPECT_TRUE(IsAlergyPresentInScore(cats, 128));
}
