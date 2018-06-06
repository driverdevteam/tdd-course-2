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
  9.Check eggs and peanuts
  10.Check eggs and strawberries and pollen
  11.Check random alergy
 */


const std::string s_notAlergy = "You don't have any alergy";
const std::string s_alergyOn = "You have alergy:";
std::map<int, std::string> s_alergyList = {
                                         {1, "eggs"},
                                         {2, "peanuts"},
                                         {4, "shellfish"},
                                         {8, "strawberries"},
                                         {16, "tomatoes"},
                                         {32, "chocolate"},
                                         {64, "pollen"},
                                         {128, "cats"}
                                         };


int GetDegreeCount(int number)
{
    int degree = 0;

    unsigned int power;

    while (static_cast<unsigned int>(pow(2, degree)) <= number)
    {

        ++degree;
    }
    return --degree;
}

std::string GetAlergy(size_t score)
{
    if(!score)
    {
        return s_notAlergy;
    }

    std::string result = s_alergyOn;
    unsigned int maxDegree  = s_alergyList.size() - 1;;
    unsigned int foundPow;
    unsigned int foundDegree;

    while (score != 0)
    {
        foundDegree = GetDegreeCount(score);
        foundPow = static_cast<unsigned int>(pow(2, foundDegree));

        if (foundDegree < maxDegree)
        {
            result += s_alergyList.find(foundPow)->second + ",";
        }

        score -= foundPow;
    }
    result.pop_back();
    return result;
}

TEST(GetAlergy, Check_no_allergy)
{
    EXPECT_EQ(s_notAlergy, GetAlergy(0));
}

TEST(GetAlergy, Check_eggs_alergy)
{
    EXPECT_EQ(s_alergyOn + s_alergyList[1], GetAlergy(1));
}

TEST(GetAlergy, Check_peanuts_alergy)
{
    EXPECT_EQ(s_alergyOn + s_alergyList[2], GetAlergy(2));
}

TEST(GetAlergy, Check_shellfish_alergy)
{
    EXPECT_EQ(s_alergyOn + s_alergyList[4], GetAlergy(4));
}

TEST(GetAlergy, Check_tomatoes_alergy)
{
    EXPECT_EQ(s_alergyOn + s_alergyList[16], GetAlergy(16));
}

TEST(GetAlergy, Check_two_alergies)
{
    EXPECT_EQ(s_alergyOn + "shellfish,eggs", GetAlergy(5));
}

TEST(GetAlergy, AcceptanceTest)
{
    EXPECT_EQ(s_alergyOn + "chocolate,peanuts", GetAlergy(34));
}
//----------------------------------------------------------------------
TEST(GetAlergy, GetDegreeCount)
{
    EXPECT_EQ(1, GetDegreeCount(2));
}

TEST(GetAlergy, GetDegreeCountFrom4)
{
    EXPECT_EQ(2, GetDegreeCount(4));
}

TEST(GetAlergy, GetDegreeCountFrom8)
{
    EXPECT_EQ(3, GetDegreeCount(8));
}

