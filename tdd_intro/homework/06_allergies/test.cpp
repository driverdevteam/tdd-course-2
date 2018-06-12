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
//8. List score 255

#include <gtest/gtest.h>
#include <map>
#include <vector>

enum Allergy
{
    allergiesFirst = 0,
    eggs = allergiesFirst,
    peanuts,
    shellfish,
    strawberries,
    tomatoes,
    chocolate,
    pollen,
    cats,
    allergiesLast = cats
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

using Allergies_vt = std::set<std::string>;

bool IsAllergicTo(const std::string& allergy, int score)
{
    auto it = allergies.find(allergy);
    if (it != allergies.end())
    {
        int degreeOfAllergy = it->second;
        return (score & 1 << degreeOfAllergy) != 0;
    }
    return false;
}

Allergies_vt List(int score)
{
    Allergies_vt result;
    for (const auto& allergy : allergies)
    {
        if (IsAllergicTo(allergy.first, score))
        {
            result.insert(allergy.first);
        }
    }

    return result;
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

TEST(IsAllergicToTest, Takes_eggs_score_257_return_true)
{
    EXPECT_TRUE(IsAllergicTo("eggs", 257));
}

TEST(IsAllergicToTest, Takes_eggs_score_0_return_false)
{
    EXPECT_FALSE(IsAllergicTo("eggs", 0));
}

TEST(IsAllergicToTest, Takes_peanuts_score_2_return_true)
{
    EXPECT_TRUE(IsAllergicTo("peanuts", 2));
}

TEST(IsAllergicToTest, Takes_shellfish_score_4_return_true)
{
    EXPECT_TRUE(IsAllergicTo("shellfish", 4));
}

TEST(IsAllergicToTest, Takes_strawberries_score_8_return_true)
{
    EXPECT_TRUE(IsAllergicTo("strawberries", 8));
}

TEST(IsAllergicToTest, Takes_tomatoes_score_16_return_true)
{
    EXPECT_TRUE(IsAllergicTo("tomatoes", 16));
}

TEST(IsAllergicToTest, Takes_chocolate_score_32_return_true)
{
    EXPECT_TRUE(IsAllergicTo("chocolate", 32));
}

TEST(IsAllergicToTest, Takes_pollen_score_64_return_true)
{
    EXPECT_TRUE(IsAllergicTo("pollen", 64));
}

TEST(IsAllergicToTest, Takes_cats_score_128_return_true)
{
    EXPECT_TRUE(IsAllergicTo("cats", 128));
}

TEST(IsAllergicToTest, Takes_pollen_score_128_return_false)
{
    EXPECT_FALSE(IsAllergicTo("pollen", 128));
}

TEST(IsAllergicToTest, Takes_empty_string_score_128_return_false)
{
    EXPECT_FALSE(IsAllergicTo("", 128));
}

TEST(ListTest, Takes_0_return_empty_list)
{
    EXPECT_TRUE(List(0).empty());
}

TEST(ListTest, Takes_1_return_eggs)
{
    Allergies_vt allergiesList = List(1);
    ASSERT_EQ(1, allergiesList.size());
    EXPECT_TRUE("eggs", allergiesList[0]);
}

TEST(ListTest, Takes_256_return_all)
{
    Allergies_vt allergiesList = List(255);
    Allergies_vt expected {"eggs", "peanuts", "shellfish", "strawberries", "tomatoes", "chocolate", "pollen", "cats"};
    ASSERT_EQ(expected.size(), allergiesList.size());
    EXPECT_EQ(expected, allergiesList);
}
