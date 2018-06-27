/*
Say in C++
Given a number from 0 to 99,999, spell out that number in English.

Step 1
Handle the basic case of 0 through 99.

If the input to the program is 22, then the output should be 'twenty-two'.

Your program should complain loudly if given a number outside the blessed range.

Some good test cases for this program are:

0
14
50
98
-1
100
Step 2
Put it all together to get nothing but plain English.

12345 should give twelve thousand three hundred forty-five.

The program must also report any values that are out of range.

Extensions
Use and (correctly) when spelling out the number in English:

14 becomes "fourteen".
100 becomes "one hundred".
120 becomes "one hundred and twenty".
1002 becomes "one thousand and two".
1323 becomes "one thousand three hundred and twenty-three".
*/

#include <gtest/gtest.h>
#include <string>
#include <map>

std::map<int, std::string> s_0To19Numbers = {
    {0, "zero"},
    {1, "one"},
    {2, "two"},
    {3, "three"},
    {4, "four"},
    {5, "five"},
    {6, "six"},
    {7, "seven"},
    {8, "eight"},
    {9, "nine"},
    {10, "ten"},
    {11, "eleven"},
    {12, "twelve"},
    {13, "thirteen"},
    {14, "fourteen"},
    {15, "fifteen"},
    {16, "sixteen"},
    {17, "seventeen"},
    {18, "eighteen"},
    {19, "nineteen"}
};

std::map<int, std::string> s_20To90Numbers = {
    {20, "twenty"},
    {30, "thirty"},
    {40, "fourty"},
    {50, "fifty"},
    {60, "sixty"},
    {70, "seventy"},
    {80, "eighty"},
    {90, "ninety"}
};


std::string GetSpelling(int number)
{
    if (number < 0 || number > 99999)
    {
        throw std::out_of_range("Out of bounds value!");
    }

    int tens = number / 10;

    if (tens > 1)
    {
        std::string tenPart = s_20To90Numbers.find(tens * 10)->second;

        int ones = number % 10;
        if (ones != 0)
        {
            return tenPart + "-" + s_0To19Numbers.find(ones)->second;
        }
        else
        {
            return tenPart;
        }
    }
    else
    {
        return s_0To19Numbers.find(number)->second;
    }
}

TEST(GetSpelling, Input_0_Get_Zero)
{
    EXPECT_EQ("zero", GetSpelling(0));
}

TEST(GetSpelling, Input_1_Get_One)
{
    EXPECT_EQ("one", GetSpelling(1));
}

TEST(GetSpelling, OutOfBounds)
{
    EXPECT_THROW(GetSpelling(-1), std::out_of_range);
}

TEST(GetSpelling, Input_10_Get_Ten)
{
    EXPECT_EQ("ten", GetSpelling(10));
}

TEST(GetSpelling, Input_14_Get_Fourteen)
{
    EXPECT_EQ("fourteen", GetSpelling(14));
}

TEST(GetSpelling, Input_21_Get_TwentyOne)
{
    EXPECT_EQ("twenty-one", GetSpelling(21));
}

TEST(GetSpelling, Input_35_Get_ThirtyFive)
{
    EXPECT_EQ("thirty-five", GetSpelling(35));
}
