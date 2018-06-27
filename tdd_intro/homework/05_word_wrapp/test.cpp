/*
Write a function, that is given a string and a length limit, splits provided string into sequence of string,
where length of each string is not more, than provided limit. If there are spaces under provided limit -
last space should be used to wrapp this line. If there are no spaces - wrapp it on provided length limit.
*/

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <list>

//List of tests:
//    1. Check zero string.
//    2. Check string splitting before limit
//    3. Check string splitting without spaces by limit.
//    4. Check string splitting with one space in the end.
//    5. Check string splitting with one space at start.
//    6. Check string splitting with multiple spaces at start.
//    7. Check string splitting with multiple spaces in the end of string.

namespace
{
    using StringList = std::list<std::string>;

    StringList wrapp(const std::string& str, unsigned int limit)
    {
        StringList result;
        if (str.empty())
        {
            return StringList{""};
        }
        std::string tmp;
        size_t length = str.length();
        for (auto startPos = 0; startPos < length; startPos += limit)
        {
            tmp = str.substr(startPos,limit);
            result.push_back(tmp);
        }
        return result;
    }
}


TEST(WordWrapTests, TakeZeroString_GetZeroString)
{
    EXPECT_EQ(StringList{""}, wrapp("", 0));
}

TEST(WordWrapTests, TakeStringBeforeLimit_GetString)
{
    const std::string txt = "Hello world!";
    EXPECT_EQ(StringList{txt}, wrapp(txt, 30));
}

TEST(WordWrapTests, TakeStringUnderLimit_GetStringList)
{
    const std::string txt = "Hello!I_said_hello!_Hey!";
    StringList res = {"Hello!I_sa", "id_hello!_", "Hey!"};
    EXPECT_EQ(res, wrapp(txt, 10));
}


