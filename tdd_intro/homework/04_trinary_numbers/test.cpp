#include <gtest/gtest.h>
#include <stdexcept>

/*
Convert a trinary number, represented as a string (e.g. '102012'), to its decimal equivalent using first principles.

The program should consider strings specifying an invalid trinary as the value 0.

Trinary numbers contain three symbols: 0, 1, and 2.

The last place in a trinary number is the 1's place. The second to last is the 3's place, the third to last is the 9's place, etc.

# "102012"
    1       0       2       0       1       2    # the number
1*3^5   + 0*3^4 + 2*3^3 + 0*3^2 + 1*3^1 + 2*3^0    # the value
  243   +   0 +    54 +     0 +     3 +     2 =  302

If your language provides a method in the standard library to perform the conversion, pretend it doesn't exist and implement it yourself.
*/

char TrinaryCharToDigit(char trinaryChar)
{
    if (trinaryChar < '0' || '2' < trinaryChar)
    {
        throw std::out_of_range("Trinary char must be 0, 1 or 2.");
    }
    return trinaryChar - '0';
}

unsigned long TrinaryStringToNumber(const std::string& trinatyString)
{
    unsigned long result(0);
    unsigned long prevResult(0);

    try
    {
        const size_t lastIndex = trinatyString.size() - 1;
        for (size_t i = 0; i <= lastIndex; ++i)
        {
            result += TrinaryCharToDigit(trinatyString[i]) *
                    static_cast<unsigned long>(std::pow(3, lastIndex - i));

            if (result < prevResult)
            {
                result = 0;
                break;
            }

            prevResult = result;
        }
    }
    catch (const std::out_of_range&)
    {
        result = 0;
    }

    return result;
}

TEST(TrinaryCharToDigitTest, In0_Out0)
{
    EXPECT_EQ(0, TrinaryCharToDigit('0'));
}

TEST(TrinaryCharToDigitTest, In1_Out1)
{
    EXPECT_EQ(1, TrinaryCharToDigit('1'));
}

TEST(TrinaryCharToDigitTest, In2_Out2)
{
    EXPECT_EQ(2, TrinaryCharToDigit('2'));
}

TEST(TrinaryCharToDigitTest, In3_ThrowOutOfRange)
{
    EXPECT_THROW(TrinaryCharToDigit('3'), std::out_of_range);
}

TEST(TrinaryCharToDigitTest, InSymbol_ThrowOutOfRange)
{
    EXPECT_THROW(TrinaryCharToDigit('a'), std::out_of_range);
}

TEST(TrinaryStringToNumberTest, InEmptyString_Out0)
{
    EXPECT_EQ(0, TrinaryStringToNumber(""));
}

TEST(TrinaryStringToNumberTest, In1_Out1)
{
    EXPECT_EQ(1, TrinaryStringToNumber("1"));
}

TEST(TrinaryStringToNumberTest, InSymbol_Out0)
{
    EXPECT_EQ(0, TrinaryStringToNumber("a"));
}

TEST(TrinaryStringToNumberTest, In01_Out1)
{
    EXPECT_EQ(1, TrinaryStringToNumber("01"));
}

TEST(TrinaryStringToNumberTest, In1a_Out0)
{
    EXPECT_EQ(0, TrinaryStringToNumber("1a"));
}

TEST(TrinaryStringToNumberTest, In10_Out3)
{
    EXPECT_EQ(3, TrinaryStringToNumber("10"));
}

TEST(TrinaryStringToNumberTest, InHugeNumber_Out0)
{
    EXPECT_EQ(0, TrinaryStringToNumber("120021102002022201221111210"));
}

TEST(TrinaryStringToNumberTest, AcceptanceTest)
{
    EXPECT_EQ(302,        TrinaryStringToNumber("102012"));
    EXPECT_EQ(0,          TrinaryStringToNumber("-1"));
    EXPECT_EQ(4294967295, TrinaryStringToNumber("102002022201221111210"));
    EXPECT_EQ(0,          TrinaryStringToNumber("102002022201221111211"));
    EXPECT_EQ(1,          TrinaryStringToNumber("000000000000000000000000000000000000000000000000000000001"));
}
