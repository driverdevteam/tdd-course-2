#include <gtest/gtest.h>
#include <string>

/*
Convert arabic numbers to Roman
*/

void ChoosePrefixAndSuffix(unsigned short num, char five, char ten, std::string& prefix, std::string& suffix)
{
    if (num <= 5)
    {
        suffix = five;
    }
    else if (num <= 10)
    {
        prefix = five;
        suffix = ten;
    }
}

std::string GetRomanDecimalToken(unsigned short num, char one, char five, char ten)
{
    std::string prefix;
    std::string suffix;
    ChoosePrefixAndSuffix(num, five, ten, prefix, suffix);

    std::string result;
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
            result += one;
        }
    }
    else
    {
        result = one + suffix;
    }

    return result;
}

std::string ArabicToRoman(unsigned short num)
{
    std::string result;
    if (num / 10 <= 3)
    {
        while (num >= 10)
        {
            result += GetRomanDecimalToken(10, 'I', 'V', 'X');
            num -= 10;
        }
    }
    else
    {
        if (num != 50)
        {
            result += GetRomanDecimalToken(10, 'I', 'V', 'X');
        }
        result += "L";
    }
    num %= 10;
    result += GetRomanDecimalToken(num, 'I', 'V', 'X');

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

TEST(Roman, AcceptanceFrom12To19)
{
    EXPECT_EQ("XII", ArabicToRoman(12));
    EXPECT_EQ("XIII", ArabicToRoman(13));
    EXPECT_EQ("XIV", ArabicToRoman(14));
    EXPECT_EQ("XV", ArabicToRoman(15));
    EXPECT_EQ("XVI", ArabicToRoman(16));
    EXPECT_EQ("XVII", ArabicToRoman(17));
    EXPECT_EQ("XVIII", ArabicToRoman(18));
    EXPECT_EQ("XIX", ArabicToRoman(19));
}

TEST(Roman, Arabic20_RomanXX)
{
    EXPECT_EQ("XX", ArabicToRoman(20));
}

TEST(Roman, Arabic21_RomanXX)
{
    EXPECT_EQ("XXI", ArabicToRoman(21));
}

TEST(Roman, Arabic40_RomanXL)
{
    EXPECT_EQ("XL", ArabicToRoman(40));
}

TEST(Roman, Arabic50_RomanXL)
{
    EXPECT_EQ("L", ArabicToRoman(50));
}

