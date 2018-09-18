#include <gtest/gtest.h>

#include <string>

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

const unsigned int s_nonTrinaryErrorCode = 3;

unsigned int TrinaryCharToInt(char symbol)
{
    const char zeroChar = '0';
    const char threeChar = '3';

    if (symbol >= zeroChar && symbol < threeChar)
    {
        const unsigned int zero_value = 48;
        return static_cast<unsigned int>(symbol) - zero_value;
    }

    return s_nonTrinaryErrorCode;
}

std::string TrinaryToDecimal(std::string trinary)
{
    const std::string zeroStr = "0";
    const unsigned int trinarySystemBase = 3;

    if (trinary.empty())
    {
        return zeroStr;
    }
    else if (trinary.length())
    {
        reverse(trinary.begin(), trinary.end());
        unsigned int decimal = 0;
        unsigned int number;
        for (size_t i = 0; i < trinary.length(); ++i)
        {
            if ((number = TrinaryCharToInt(trinary[i])) != s_nonTrinaryErrorCode)
            {
                decimal += TrinaryCharToInt(trinary[i]) * static_cast<unsigned int>(pow(trinarySystemBase, i));
            }
            else
            {
                return zeroStr;
            }
        }
        return std::to_string(decimal);
    }

    return trinary;
}

TEST(TrinaryToDecimal, Get_0_Return_0)
{
    EXPECT_EQ(TrinaryToDecimal("0"), "0");
}

TEST(TrinaryToDecimal, Get_1_Return_1)
{
    EXPECT_EQ(TrinaryToDecimal("1"), "1");
}

TEST(TrinaryToDecimal, Get_10_Return_3)
{
    EXPECT_EQ(TrinaryToDecimal("10"), "3");
}

TEST(TrinaryToDecimal, Get_21_Return_7)
{
    EXPECT_EQ(TrinaryToDecimal("21"), "7");
}

TEST(TrinaryToDecimal, Get_NotTrinary_Return_0)
{
    EXPECT_EQ(TrinaryToDecimal("14"), "0");
}

TEST(TrinaryToDecimal, Get_Empty_Return_0)
{
    EXPECT_EQ(TrinaryToDecimal(""), "0");
}

TEST(TrinaryToDecimal, AcceptanceTest)
{
    EXPECT_EQ(TrinaryToDecimal("102012"), "302");
}

TEST(TrinaryCharToInt, Char_1_To_Number_1)
{
    EXPECT_EQ(TrinaryCharToInt('1'), 1);
}

TEST(TrinaryCharToInt, Char_2_To_Number_2)
{
    EXPECT_EQ(TrinaryCharToInt('2'), 2);
}

TEST(TrinaryCharToInt, Char_4_To_ErrorCode_3)
{
    EXPECT_EQ(TrinaryCharToInt('4'), 3);
}
