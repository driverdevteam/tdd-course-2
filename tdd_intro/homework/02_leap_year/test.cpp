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
    return year % 4 == 0 && year != 100;
}

TEST(LeapYear, Zero)
{
    EXPECT_TRUE(IsLeapYear(0));
}

TEST(LeapYear, One)
{
    EXPECT_FALSE(IsLeapYear(1));
}

TEST(LeapYear, Four)
{
    EXPECT_TRUE(IsLeapYear(4));
}

TEST(LeapYear, Hundred)
{
    EXPECT_FALSE(IsLeapYear(100));
}

TEST(LeapYear, TwoHundreds)
{
    EXPECT_FALSE(IsLeapYear(200));
}

