#include <gtest/gtest.h>
#include <string>

/*
Convert arabic numbers to Roman. The upper limit is 3000, the lower limit is undefined,
but Romans doesn't speak with numbers zero and below.
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

std::string BuildRomanDecimalToken(unsigned short num, char one, const std::string& prefix, const std::string& suffix)
{
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

std::string GetRomanDecimalToken(unsigned short num, char one, char five, char ten)
{
    std::string prefix;
    std::string suffix;
    ChoosePrefixAndSuffix(num, five, ten, prefix, suffix);
    return BuildRomanDecimalToken(num, one, prefix, suffix);
}

std::string ArabicToRoman(unsigned short num)
{
    std::string result;
    if (num > 1000)
    {
        result += GetRomanDecimalToken(num / 1000, 'M', '\0', '\0');
        num %= 1000;
    }
    if (num > 100)
    {
        result += GetRomanDecimalToken(num / 100, 'C', 'D', 'M');
        num %= 100;
    }
    if (num > 10)
    {
        result += GetRomanDecimalToken(num / 10, 'X', 'L', 'C');
        num %= 10;
    }
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

TEST(Roman, Arabic50_RomanL)
{
    EXPECT_EQ("L", ArabicToRoman(50));
}

TEST(Roman, AcceptanceBefore100)
{
    EXPECT_EQ("XLII", ArabicToRoman(42));
    EXPECT_EQ("LXVII", ArabicToRoman(67));
    EXPECT_EQ("LXXXVIII", ArabicToRoman(88));
    EXPECT_EQ("XCV", ArabicToRoman(95));
    EXPECT_EQ("XCIX", ArabicToRoman(99));
}

TEST(Roman, Arabic200_RomanCC)
{
    EXPECT_EQ("CC", ArabicToRoman(200));
}

TEST(Roman, Arabic155_RomanCLV)
{
    EXPECT_EQ("CLV", ArabicToRoman(155));
}

TEST(Roman, AcceptanceBefore1000)
{
    EXPECT_EQ("CV", ArabicToRoman(105));
    EXPECT_EQ("CCLVI", ArabicToRoman(256));
    EXPECT_EQ("CCCLXVII", ArabicToRoman(367));
    EXPECT_EQ("DCCCLXXXVIII", ArabicToRoman(888));
    EXPECT_EQ("CMLXXXVII", ArabicToRoman(987));
    EXPECT_EQ("CMXCIX", ArabicToRoman(999));
}

TEST(Roman, Arabic1101_RomanMCI)
{
    EXPECT_EQ("MCI", ArabicToRoman(1101));
}

TEST(Roman, AcceptanceBefore3000)
{
    EXPECT_EQ("MCI", ArabicToRoman(1101));
    EXPECT_EQ("MDCCCXCVII", ArabicToRoman(1897));
    EXPECT_EQ("MMXVIII", ArabicToRoman(2018));
    EXPECT_EQ("MMDXXXVI", ArabicToRoman(2536));
    EXPECT_EQ("MMDCCCLXV", ArabicToRoman(2865));
    EXPECT_EQ("MMM", ArabicToRoman(3000));
}
