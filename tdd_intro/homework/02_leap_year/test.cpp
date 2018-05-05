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

bool isLeapYear(int year)
{
    const int firstProvingDivider = 4;
    const int unprovingDivider = 100;
    const int totalProvingDivider = 400;

    if ((year % firstProvingDivider == 0 && year % unprovingDivider != 0)
        || year % totalProvingDivider == 0)
    {
        return true;
    }

    return false;
}

TEST(isLeapYear, isLeapYear_FirstLeapYear)
{
    const int year = 4;
    EXPECT_EQ(isLeapYear(year), true);
}

TEST(isLeapYear, isLeapYear_OtherSimpleLeapYear)
{
    const int year = 8;
    EXPECT_EQ(isLeapYear(year), true);
}

TEST(isLeapYear, isLeapYear_HundredYear)
{
    const int year = 100;
    EXPECT_EQ(isLeapYear(year), false);
}

TEST(isLeapYear, isLeapYear_ThoursandYear)
{
    const int year = 1000;
    EXPECT_EQ(isLeapYear(year), false);
}

TEST(isLeapYear, isLeapYear_TwoThoursandYear)
{
    const int year = 2000;
    EXPECT_EQ(isLeapYear(year), true);
}

TEST(isLeapYear, isLeapYear_FourThoursandYear)
{
    const int year = 4000;
    EXPECT_EQ(isLeapYear(year), true);
}

TEST(isLeapYear, isLeapYear_ZeroYear)
{
    const int year = 0;
    EXPECT_EQ(isLeapYear(year), false);
}
