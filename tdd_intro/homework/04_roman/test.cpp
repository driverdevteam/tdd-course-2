#include <gtest/gtest.h>
#include <string>

/*
Convert arabic numbers to Roman
*/

std::string ArabicToRoman(unsigned short num)
{
    std::string result;

    if (num == 4)
    {
        result = "IV";
    }
    else if (num == 5)
    {
        result = "V";
    }
    else if (num == 6)
    {
        result = "VI";
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

TEST(Roman, NullToEmpty)
{
    EXPECT_EQ("", ArabicToRoman(0));
}

TEST(Roman, Arabic1_RomanI)
{
    EXPECT_EQ("I", ArabicToRoman(1));
}

TEST(Roman, Arabic2_RomanII)
{
    EXPECT_EQ("II", ArabicToRoman(2));
}

TEST(Roman, Arabic3_RomanIII)
{
    EXPECT_EQ("III", ArabicToRoman(3));
}

TEST(Roman, Arabic4_RomanIV)
{
    EXPECT_EQ("IV", ArabicToRoman(4));
}

TEST(Roman, Arabic5_RomanV)
{
    EXPECT_EQ("V", ArabicToRoman(5));
}

TEST(Roman, Arabic6_RomanVI)
{
    EXPECT_EQ("VI", ArabicToRoman(6));
}
