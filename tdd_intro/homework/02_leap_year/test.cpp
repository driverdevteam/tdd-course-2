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


bool IsLeapYear(unsigned int year)
{

    return year % 4 == 0 && year % 100 != 0 || year % 400 == 0 ? true : false;
}

TEST(LeapYearTests, IsLeapYear_1997)
{
    EXPECT_EQ(false, IsLeapYear(1997));
}

TEST(LeapYearTests, IsLeapYear_1900)
{
    EXPECT_EQ(false, IsLeapYear(1900));
}

TEST(LeapYearTests, IsLeapYear_2100)
{
    EXPECT_EQ(false, IsLeapYear(2100));
}

TEST(LeapYearTests, IsLeapYear_2000)
{
    EXPECT_EQ(true, IsLeapYear(2000));
}
