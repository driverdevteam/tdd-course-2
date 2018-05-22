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
