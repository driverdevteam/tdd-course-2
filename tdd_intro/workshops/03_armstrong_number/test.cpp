/*
An Armstrong number is a number that is the sum of its own digits each raised to the power of the number of digits.

For example:

9 is an Armstrong number, because 9 = 9^1 = 9
10 is not an Armstrong number, because 10 != 1^2 + 0^2 = 1
153 is an Armstrong number, because: 153 = 1^3 + 5^3 + 3^3 = 1 + 125 + 27 = 153
154 is not an Armstrong number, because: 154 != 1^3 + 5^3 + 4^3 = 1 + 125 + 64 = 190
9474 is an Armstrong number

Write some code to determine whether a number is an Armstrong number.

Acceptance test
5 - true
100 - false
9475 - false
9926315 - true
9926314 - false

_from http://exercism.io/_
*/
#include <gtest/gtest.h>
#include <set>

using Digits = std::multiset<unsigned int>;

Digits GetDidgitList(unsigned int num)
{
    Digits res;

    if (num == 0)
    {
        res.insert(0);
    }

    while (num > 0)
    {
        res.insert(num % 10);
        num /= 10;
    }

    return res;
}

bool IsArmstrongNumber(unsigned int num)
{
    Digits digits = GetDidgitList(num);
    unsigned int sum = 0;
    size_t digits_size = digits.size();

    for (auto digit : digits)
    {
        sum += static_cast<unsigned int>(std::pow(digit, digits_size ));
    }

    return num == sum;
}

TEST(IsArmstrongNumberTest, Input_9_Return_True)
{
    EXPECT_TRUE(IsArmstrongNumber(9));
}

TEST(IsArmstrongNumberTest, Input_10_Return_False)
{
    EXPECT_FALSE(IsArmstrongNumber(10));
}

TEST(IsArmstrongNumberTest, Input_7_Return_True)
{
    EXPECT_TRUE(IsArmstrongNumber(7));
}

TEST(IsArmstrongNumberTest, Input_153_Return_True)
{
    EXPECT_TRUE(IsArmstrongNumber(153));
}

TEST(IsArmstrongNumberTest, Input_370_Return_True)
{
    EXPECT_TRUE(IsArmstrongNumber(370));
}

TEST(IsArmstrongNumberTest, Input_1634_Return_True)
{
    EXPECT_TRUE(IsArmstrongNumber(1634));
}

TEST(IsArmstrongNumberTest, Input_9926315_Return_True)
{
    EXPECT_TRUE(IsArmstrongNumber(9926315));
}

TEST(IsArmstrongNumberTest, Input_9926314_Return_False)
{
    EXPECT_FALSE(IsArmstrongNumber(9926314));
}

TEST(IsArmstrongNumberTest, AcceptanceTest)
{
    EXPECT_TRUE(IsArmstrongNumber(5));
    EXPECT_TRUE(IsArmstrongNumber(9926315));
    EXPECT_FALSE(IsArmstrongNumber(100));
    EXPECT_FALSE(IsArmstrongNumber(9475));
    EXPECT_FALSE(IsArmstrongNumber(9926314));
}

TEST(GetDidgitListTest, Input_0)
{
    Digits res;
    res.insert(0);
    EXPECT_EQ(res, GetDidgitList(0));
}

TEST(GetDidgitListTest, Input_35)
{
    Digits res;
    res.insert(3);
    res.insert(5);
    EXPECT_EQ(res, GetDidgitList(35));
}

TEST(GetDidgitListTest, Input_945)
{
    Digits res;
    res.insert(9);
    res.insert(4);
    res.insert(5);
    EXPECT_EQ(res, GetDidgitList(945));
}



