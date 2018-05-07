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


bool CheckLeapYear(const int& year)
{
    if(!year)
    {
        return false;
    }

    if( year % 4 == 0)
    {
        if(year % 400 == 0 || year % 100)
        {
            return true;
        }
    }

    return false;
}

TEST(CHECK_LEAP_YEAR, CHECK_YEAR_INPUT_0_OUTPUT_false)
{
    EXPECT_EQ(false, CheckLeapYear(0));
}

TEST(CHECK_LEAP_YEAR, CHECK_YEAR_INPUT_4_OUTPUT_TRUE)
{
     EXPECT_EQ(true, CheckLeapYear(4));
}

TEST(CHECK_LEAP_YEAR, CHECK_YEAR_INPUT_8_OUTPUT_TRUE)
{
    EXPECT_EQ(true, CheckLeapYear(8));
}

TEST(CHECK_LEAP_YEAR, CHECK_YEAR_INPUT_100_OUTPUT_false)
{
    EXPECT_EQ(false, CheckLeapYear(100));
}

TEST(CHECK_LEAP_YEAR, CHECK_YEAR_INPUT_400_OUTPUT_true)
{
     EXPECT_EQ(true, CheckLeapYear(400));
}
