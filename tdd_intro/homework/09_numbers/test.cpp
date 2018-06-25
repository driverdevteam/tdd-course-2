#include <gtest/gtest.h>

/*
    - 0-99 out of bounds
    - 0-19
    - 20,30,40...
    - 21,42...
    - 0-99999 out of bounds
    - 100,200
    - 123,321
    - 1000, 10000
    - 12345
*/

std::string GetZeroNumberString()
{
    return "zero";
}

std::string GetOneNumberString()
{
    return "one";
}

std::string GetTwoNumberString()
{
    return "two";
}

std::string GetThreeNumberString()
{
    return "three";
}

std::string GetFourNumberString()
{
    return "four";
}

std::string GetFiveNumberString()
{
    return "five";
}

std::string GetSixNumberString()
{
    return "six";
}

std::string GetSevenNumberString()
{
    return "seven";
}

std::string GetEightNumberString()
{
    return "eight";
}

std::string GetNineNumberString()
{
    return "nine";
}

std::string GetTenNumberString()
{
    return "ten";
}

std::string GetElevenNumberString()
{
    return "eleven";
}

std::string GetTwelveNumberString()
{
    return "twelve";
}

std::string GetThirteenNumberString()
{
    return "thirteen";
}

std::string GetFourteenNumberString()
{
    return "fourteen";
}

std::string GetFifteenNumberString()
{
    return "fifteen";
}

std::string GetSixteenNumberString()
{
    return "sixteen";
}

std::string GetSeventeenNumberString()
{
    return "seventeen";
}

std::string GetEighteenNumberString()
{
    return "eighteen";
}

std::string GetNineteenNumberString()
{
    return "nineteen";
}

std::string GetTwentyNumberString()
{
    return "twenty";
}

std::string GetThirtyNumberString()
{
    return "thirty";
}

std::string GetFourtyNumberString()
{
    return "fourty";
}

std::string GetFiftyNumberString()
{
    return "fifty";
}

std::string GetSixtyNumberString()
{
    return "sixty";
}

std::string GetSeventyNumberString()
{
    return "seventy";
}

std::string GetEightyNumberString()
{
    return "eighty";
}

std::string GetNinetyNumberString()
{
    return "ninety";
}

std::string GetSpacerString()
{
    return " ";
}

std::string GetHundredString()
{
    return "hundred";
}

const std::vector<std::string> s_numbersStrings({
                                    GetZeroNumberString(),
                                    GetOneNumberString(),
                                    GetTwoNumberString(),
                                    GetThreeNumberString(),
                                    GetFourNumberString(),
                                    GetFiveNumberString(),
                                    GetSixNumberString(),
                                    GetSevenNumberString(),
                                    GetEightNumberString(),
                                    GetNineNumberString(),
                                    GetTenNumberString(),
                                    GetElevenNumberString(),
                                    GetTwelveNumberString(),
                                    GetThirteenNumberString(),
                                    GetFourteenNumberString(),
                                    GetFifteenNumberString(),
                                    GetSixteenNumberString(),
                                    GetSeventeenNumberString(),
                                    GetEighteenNumberString(),
                                    GetNineteenNumberString()
                                });


const std::vector<std::string> s_tensNumbersStrings({
                                    "",
                                    "",
                                    GetTwentyNumberString(),
                                    GetThirtyNumberString(),
                                    GetFourtyNumberString(),
                                    GetFiftyNumberString(),
                                    GetSixtyNumberString(),
                                    GetSeventyNumberString(),
                                    GetEightyNumberString(),
                                    GetNinetyNumberString()
                                });

std::string Number0_99ToString(int num)
{
    if (num < 0 || 99 < num)
    {
        throw std::out_of_range("Only numbers 0..99 are acceptable.");
    }

    std::string result;

    int tensNum = num / 10;
    bool addNumber = true;

    if (tensNum >= 2 && tensNum < s_tensNumbersStrings.size())
    {
        result = s_tensNumbersStrings[tensNum];

        num %= 10;
        addNumber = num != 0;

        if (addNumber)
        {
            result += "-";
        }
    }

    if (addNumber && num < s_numbersStrings.size())
    {
        result += s_numbersStrings[num];
    }

    return result;
}

std::string NumberToString(int num)
{
    if (num < 0 || 99999 < num)
    {
        throw std::out_of_range("Only numbers 0..99999 are acceptable.");
    }

    std::string result;
    bool addNumber = true;

    if (num >= 100)
    {
        result += Number0_99ToString(num / 100) + GetSpacerString() + GetHundredString();
        num %= 100;
        addNumber = num != 0;
    }

    if (addNumber)
    {
        result += Number0_99ToString(num);
    }

    return result;
}

TEST(NumbersTests, Number0_99ToString_OutOfBounds)
{
    EXPECT_THROW(Number0_99ToString(-1), std::out_of_range);
    EXPECT_THROW(Number0_99ToString(100), std::out_of_range);
}

TEST(NumbersTests, Number0_99ToString_0)
{
    EXPECT_EQ(GetZeroNumberString(), Number0_99ToString(0));
}

TEST(NumbersTests, Number0_99ToString_1)
{
    EXPECT_EQ(GetOneNumberString(), Number0_99ToString(1));
}

TEST(NumbersTests, Number0_99ToString_2)
{
    EXPECT_EQ(GetTwoNumberString(), Number0_99ToString(2));
}

TEST(NumbersTests, Number0_99ToString_3)
{
    EXPECT_EQ(GetThreeNumberString(), Number0_99ToString(3));
}

TEST(NumbersTests, Number0_99ToString_4)
{
    EXPECT_EQ(GetFourNumberString(), Number0_99ToString(4));
}

TEST(NumbersTests, Number0_99ToString_5)
{
    EXPECT_EQ(GetFiveNumberString(), Number0_99ToString(5));
}

TEST(NumbersTests, Number0_99ToString_6)
{
    EXPECT_EQ(GetSixNumberString(), Number0_99ToString(6));
}

TEST(NumbersTests, Number0_99ToString_7)
{
    EXPECT_EQ(GetSevenNumberString(), Number0_99ToString(7));
}

TEST(NumbersTests, Number0_99ToString_8)
{
    EXPECT_EQ(GetEightNumberString(), Number0_99ToString(8));
}

TEST(NumbersTests, Number0_99ToString_9)
{
    EXPECT_EQ(GetNineNumberString(), Number0_99ToString(9));
}

TEST(NumbersTests, Number0_99ToString_10)
{
    EXPECT_EQ(GetTenNumberString(), Number0_99ToString(10));
}

TEST(NumbersTests, Number0_99ToString_11)
{
    EXPECT_EQ(GetElevenNumberString(), Number0_99ToString(11));
}

TEST(NumbersTests, Number0_99ToString_12)
{
    EXPECT_EQ(GetTwelveNumberString(), Number0_99ToString(12));
}

TEST(NumbersTests, Number0_99ToString_13)
{
    EXPECT_EQ(GetThirteenNumberString(), Number0_99ToString(13));
}

TEST(NumbersTests, Number0_99ToString_14)
{
    EXPECT_EQ(GetFourteenNumberString(), Number0_99ToString(14));
}

TEST(NumbersTests, Number0_99ToString_15)
{
    EXPECT_EQ(GetFifteenNumberString(), Number0_99ToString(15));
}

TEST(NumbersTests, Number0_99ToString_16)
{
    EXPECT_EQ(GetSixteenNumberString(), Number0_99ToString(16));
}

TEST(NumbersTests, Number0_99ToString_17)
{
    EXPECT_EQ(GetSeventeenNumberString(), Number0_99ToString(17));
}

TEST(NumbersTests, Number0_99ToString_18)
{
    EXPECT_EQ(GetEighteenNumberString(), Number0_99ToString(18));
}

TEST(NumbersTests, Number0_99ToString_19)
{
    EXPECT_EQ(GetNineteenNumberString(), Number0_99ToString(19));
}

TEST(NumbersTests, Number0_99ToString_20)
{
    EXPECT_EQ(GetTwentyNumberString(), Number0_99ToString(20));
}

TEST(NumbersTests, Number0_99ToString_30)
{
    EXPECT_EQ(GetThirtyNumberString(), Number0_99ToString(30));
}

TEST(NumbersTests, Number0_99ToString_40)
{
    EXPECT_EQ(GetFourtyNumberString(), Number0_99ToString(40));
}

TEST(NumbersTests, Number0_99ToString_50)
{
    EXPECT_EQ(GetFiftyNumberString(), Number0_99ToString(50));
}

TEST(NumbersTests, Number0_99ToString_60)
{
    EXPECT_EQ(GetSixtyNumberString(), Number0_99ToString(60));
}

TEST(NumbersTests, Number0_99ToString_70)
{
    EXPECT_EQ(GetSeventyNumberString(), Number0_99ToString(70));
}

TEST(NumbersTests, Number0_99ToString_80)
{
    EXPECT_EQ(GetEightyNumberString(), Number0_99ToString(80));
}

TEST(NumbersTests, Number0_99ToString_90)
{
    EXPECT_EQ(GetNinetyNumberString(), Number0_99ToString(90));
}

TEST(NumbersTests, Number0_99ToString_21)
{
    EXPECT_EQ(GetTwentyNumberString() + "-" + GetOneNumberString(), Number0_99ToString(21));
}

TEST(NumbersTests, NumberToString_OutOfBounds)
{
    EXPECT_THROW(NumberToString(-1), std::out_of_range);
    EXPECT_THROW(NumberToString(100000), std::out_of_range);
}

TEST(NumbersTests, NumberToString_42)
{
    EXPECT_EQ(GetFourtyNumberString() + "-" + GetTwoNumberString(), NumberToString(42));
}

TEST(NumbersTests, NumberToString_100)
{
    EXPECT_EQ(GetOneNumberString() + GetSpacerString() + GetHundredString(),
              NumberToString(100));
}
