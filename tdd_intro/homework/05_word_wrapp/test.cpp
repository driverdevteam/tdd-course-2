/*
Write a function, that is given a string and a length limit, splits provided string into sequence of string,
where length of each string is not more, than provided limit. If there are spaces under provided limit -
last space should be used to wrapp this line. If there are no spaces - wrapp it on provided length limit.
*/

#include <gtest/gtest.h>
#include <cctype>
#include <string>
#include <list>

//List of tests:
//    1. Check zero string.
//    2. Check string splitting without spaces by limit.
//    3. Check string splitting with one space in the end.
//    4. Check string splitting with one space at start.
//    5. Check string splitting with multiple spaces at start.
//    5. Check string splitting with multiple spaces in the end of string.

using StringList = std::list<std::string>;

TEST(WordWrapTests, TakeZeroString_GetZeroString)
{
    EXPECT_EQ(StringList{""}, wrapp(""));
}
