#include <gtest/gtest.h>
#include <string>

/*
Convert arabic numbers to Roman
*/

std::string ArabicToRoman(unsigned short num)
{
    std::string result;
    std::string prefix;
    std::string suffix;

    if (num <= 5)
    {
        suffix = "V";
    }
    else if (num <= 10)
    {
        prefix = "V";
        suffix = "X";
    }
    else
    {
        prefix = "X";
    }

    unsigned short onesLeft = num % 5;
    if (onesLeft == 0 && num > 0)
    {
        return suffix;
    }
    else if (onesLeft <= 3)
    {
        result = prefix;
        while(onesLeft--)
        {
            result += "I";
        }
    }
    else
    {
        result = "I" + suffix;
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

TEST(Roman, Arabic10_RomanX)
{
    EXPECT_EQ("X", ArabicToRoman(10));
}

TEST(Roman, Arabic11_RomanXI)
{
    EXPECT_EQ("XI", ArabicToRoman(11));
}

TEST(Roman, Arabic15_RomanXV)
{
    EXPECT_EQ("XV", ArabicToRoman(15));
}
