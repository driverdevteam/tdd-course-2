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
    else if (num == 9)
    {
        result = "IX";
    }
    else if (num >= 5)
    {
        result = "V";
        num -= 5;
        while (num--)
        {
            result += "I";
        }
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

TEST(Roman, Arabic7_RomanVII)
{
    EXPECT_EQ("VII", ArabicToRoman(7));
}

TEST(Roman, Arabic8_RomanVIII)
{
    EXPECT_EQ("VIII", ArabicToRoman(8));
}

TEST(Roman, Arabic9_RomanIX)
{
    EXPECT_EQ("IX", ArabicToRoman(9));
}

