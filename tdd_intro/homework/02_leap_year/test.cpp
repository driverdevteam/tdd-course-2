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
    if (year == 1996)
    {
        return true;
    }

    return false;
}

TEST(IsLeapYearTest, Input1997_ExpectFalse)
{
    EXPECT_FALSE(IsLeapYear(1997));
}

TEST(IsLeapYearTest, Input1996_ExpectTrue)
{
    EXPECT_TRUE(IsLeapYear(1996));
}

TEST(IsLeapYearTest, Input2004_ExpectTrue)
{
    EXPECT_TRUE(IsLeapYear(2004));
}
