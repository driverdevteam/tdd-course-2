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

std::string Number0_99ToString(int num)
{
    if (num < 0 || 99 < num)
    {
        throw std::out_of_range("Only numbers 0..99 are acceptable.");
    }

    std::string result;

    switch (num)
    {
    case 0:
        result = GetZeroNumberString();
        break;
    case 1:
        result = "one";
        break;
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
    EXPECT_EQ("one", Number0_99ToString(1));
}
