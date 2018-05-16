#include <gtest/gtest.h>
#include <string>
/*
Write a function to convert from normal numbers to Roman Numerals.

The Romans wrote numbers using letters - I, V, X, L, C, D, M. (converter http://www.novaroma.org/via_romana/numbers.html)

There is no need to be able to convert numbers larger than about 3000. (The Romans themselves didn't tend to go any higher)

Wikipedia says: Modern Roman numerals ... are written by expressing each digit separately starting with the left most digit and skipping any digit with a value of zero.

To see this in practice, consider the example of 1990.
In Roman numerals 1990 is MCMXC:
1000=M 900=CM 90=XC

2008 is written as MMVIII:
2000=MM 8=VIII

1998 is written as MCMXCVIII.
*/

std::string Co

std::string ConvertToRoman(unsigned short num)
{
    if(num == 10)
    {
        return std::string("X");
    }
    else if (num == 0)
    {
        return std::string();
    }

    std::string result;
    if (num / 5 > 0)
    {
        result = "V";
        num -= 5;
    }

    if (num == 4)
    {
        result = "IV";
    }
    else if (num == 9)
    {
        result = "IX";
    }
    else
    {
        while (num--)
        {
            result += "I";
        }
    }
    return result;
}

TEST(ConvertToRomanTest, insert_zero_return_empty_string)
{
    EXPECT_EQ("", ConvertToRoman(0));
}

TEST(ConvertToRomanTest, insert_one_return_I)
{
    EXPECT_EQ("I", ConvertToRoman(1));
}

TEST(ConvertToRomanTest, insert_2_return_II)
{
    EXPECT_EQ("II", ConvertToRoman(2));
}

TEST(ConvertToRomanTest, insert_5_return_V)
{
    EXPECT_EQ("V", ConvertToRoman(5));
}

TEST(ConvertToRomanTest, insert_4_return_IV)
{
     EXPECT_EQ("IV", ConvertToRoman(4));
}

TEST(ConvertToRomanTest, insert_10_return_X)
{
     EXPECT_EQ("X", ConvertToRoman(10));
}

TEST(ConvertToRomanTest, AcceptanceLess10)
{
    EXPECT_EQ("III", ConvertToRoman(3));
    EXPECT_EQ("VI", ConvertToRoman(6));
    EXPECT_EQ("VII", ConvertToRoman(7));
    EXPECT_EQ("VIII", ConvertToRoman(8));
}
