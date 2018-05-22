#include <gtest/gtest.h>
#include <string>

/*
Convert arabic numbers to Roman
*/

std::string ArabicToRoman(unsigned short num)
{
    std::string result;

    while (num--)
    {
        result += "I";
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

TEST(Roman, Arabic2_RomanIII)
{
    EXPECT_EQ("III", ArabicToRoman(3));
}
