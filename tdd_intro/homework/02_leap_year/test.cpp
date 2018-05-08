/*
Given a year, report if it is a leap year.

The tricky thing here is that a leap year in the Gregorian calendar occurs:

on every year that is evenly divisible by 4
  except every year that is evenly divisible by 100
    unless the year is also evenly divisible by 400

For example, 1997 is not a leap year, but 1996 is. 1900 is not a leap year, but 2000 is.

If your language provides a method in the standard library that does this look-up, pretend it doesn't exist and implement it yourself.
*/

#include <gtest/gtest.h>

bool IsLeapYear(int year)
{
    if (year > 1582)
    {
        return year % 400 == 0 || year % 100 != 0 && year % 4 == 0;
    }

    return year % 4 == 0;
}

TEST(IsLeapYear, take_4444_return_true)
{
    EXPECT_TRUE(IsLeapYear(4444));
}

TEST(IsLeapYear, take_4441_return_false)
{
    EXPECT_FALSE(IsLeapYear(4441));
}

TEST(IsLeapYear, take_1111_return_false)
{
    EXPECT_FALSE(IsLeapYear(1111));
}

TEST(IsLeapYear, take_2100_return_false)
{
    EXPECT_FALSE(IsLeapYear(2100));
}

TEST(IsLeapYear, take_4100_return_false)
{
    EXPECT_FALSE(IsLeapYear(4100));
}

TEST(IsLeapYear, take_2000_return_true)
{
    EXPECT_TRUE(IsLeapYear(2000));
}

TEST(IsLeapYear, take_4000_return_true)
{
    EXPECT_TRUE(IsLeapYear(4000));
}

TEST(IsLeapYear, take_1500_return_true)
{
    EXPECT_TRUE(IsLeapYear(1500));
}

TEST(IsLeapYear, take_1000_return_true)
{
    EXPECT_TRUE(IsLeapYear(1000));
}

TEST(IsLeapYear, take_999_return_false)
{
    EXPECT_FALSE(IsLeapYear(999));
}


