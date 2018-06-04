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

int DegreeOfTwo(unsigned int number)
{
    int degree = 0;

    unsigned int power;

    while ((power = static_cast<unsigned int>(pow(2, degree))) <= number)
    {
        if (power == number)
        {
            return degree;
        }

        ++degree;
    }

    return -1;
}

AllergiesList GetAllergiesList(unsigned int score)
{
    AllergiesList result;

    unsigned int commonDegree = 0;
    unsigned int commonPow;
    unsigned int foundDegree;

    while (score != 0)
    {
        if ((foundDegree = DegreeOfTwo(score)) != -1)
        {
            if (foundDegree < allergies_mp.size())
            {
                result.push_back(allergies_mp.find(static_cast<unsigned int>(pow(2, foundDegree)))->second);
            }
            break;
        }
        else
        {
            commonPow = static_cast<unsigned int>(pow(2, commonDegree));
            result.push_back(allergies_mp.find(commonPow)->second);
            score -= commonPow;
        }
    }

    return result;
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

TEST(Allergies, GetAllergiesList_EggsAndPeanutsAllergy)
{
    unsigned int score = 3;
    EXPECT_EQ(AllergiesList({"eggs", "peanuts"}), GetAllergiesList(score));
}

TEST(AllergiesList, GetAllergiesList_EggsAndShellfishAllergy)
{
    unsigned int score = 5;
    EXPECT_EQ(AllergiesList({"eggs", "shellfish"}), GetAllergiesList(score));
}

TEST(AllergiesList, GetAllergiesList_MoreThan256)
{
    unsigned int score = 257;
    EXPECT_EQ(AllergiesList({"eggs"}), GetAllergiesList(score));
}

TEST(AllergiesList, DegreeOfTwo_DegreeOne)
{
    unsigned int number = 2;
    unsigned int degree = 1;
    EXPECT_EQ(degree, DegreeOfTwo(number));
}

TEST(AllergiesList, DegreeOfTwo_DegreeThree)
{
    unsigned int number = 8;
    unsigned int degree = 3;
    EXPECT_EQ(degree, DegreeOfTwo(number));
}
