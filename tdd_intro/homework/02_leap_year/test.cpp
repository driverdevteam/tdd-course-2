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

bool IsDivisibleBy4(int year)
{
    return (year % 4) == 0;
}

bool IsDivisibleBy100(int year)
{
    return (year % 100) == 0;
}

bool IsLeapYear(int year)
{
    bool result = true;
    result &= IsDivisibleBy4(year);
    result &= !IsDivisibleBy100(year);
    return result;
}

TEST(IsLeapYear, check_LeapYear)
{
    EXPECT_TRUE(IsLeapYear(2016));
}

TEST(IsLeapYear, check_NotLeapYear)
{
    EXPECT_FALSE(IsLeapYear(2017));
}

TEST(IsLeapYear, check_NotLeapYear_ForDivisibleBy100)
{
    EXPECT_FALSE(IsLeapYear(1900));
}

TEST(IsLeapYear, check_LeapYear_ForDivisibleBy400)
{
    EXPECT_TRUE(IsLeapYear(2000));
}
