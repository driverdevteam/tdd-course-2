#include <gtest/gtest.h>
#include <string>

/*
Convert arabic numbers to Roman
*/

std::string ArabicToRoman(unsigned short num)
{
    return "";
}

TEST(Roman, NullToEmpty)
{
    EXPECT_EQ("", ArabicToRoman(0));
}

TEST(Roman, Arabic1_RomanI)
{
    EXPECT_EQ("I", ArabicToRoman(1));
}
