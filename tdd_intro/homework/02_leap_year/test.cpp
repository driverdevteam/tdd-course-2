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

using Year = int;
bool IsLeapYear(Year year)
{
    if (year % 4 == 0)
    {
        if (year == 0 || year % 400 == 0 || year % 100 != 0)
        {
            return true;
        }
    }
    return false;
}

class Year_IsLeap: public ::testing::TestWithParam<Year> { };
class Year_IsNotLeap: public ::testing::TestWithParam<Year> { };

INSTANTIATE_TEST_CASE_P(IsLeapYear, Year_IsLeap,
    ::testing::Values(0, 4, 8, 20, 104, 400, 800, 1996, 2000));

INSTANTIATE_TEST_CASE_P(IsNotLeapYear, Year_IsNotLeap,
    ::testing::Values(1, 2, 3, 5, 7, 13, 99, 101, 200, 300, 900, 1900, 1997, 2001));

TEST_P(Year_IsLeap, Test)
{
    auto year = GetParam();
    EXPECT_TRUE(IsLeapYear(year)) << "Test failed for value " << year;
    EXPECT_TRUE(IsLeapYear(year * -1)) << "Test failed for negative value -" << year;
}

TEST_P(Year_IsNotLeap, Test)
{
    auto year = GetParam();
    EXPECT_FALSE(IsLeapYear(year)) << "Test failed for value " << year;
    EXPECT_FALSE(IsLeapYear(year * -1)) << "Test failed for negative value -" << year;
}
