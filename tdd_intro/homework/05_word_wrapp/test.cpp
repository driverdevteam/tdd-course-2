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

    StringList wrapp(const std::string& str, size_t limit)
    {
        if (str.empty())
        {
            return StringList{""};
        }

        StringList result;
        std::string tmp;
        size_t space_pos = 0;
        const char DELIMITER = ' ';
        size_t length = str.length();
        for (size_t startPos = 0; startPos < length;)
        {
            tmp = str.substr(startPos, limit);
            space_pos = tmp.find_last_of(DELIMITER);
            auto spaces_count = std::count(tmp.begin(), tmp.end(), DELIMITER);
            if (spaces_count > 1  || tmp.back() == DELIMITER && space_pos != tmp.npos)
            {
                tmp = tmp.substr(0, space_pos);
                startPos += tmp.length() + 1;
            }
            else
            {
                startPos += limit;
            }
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
    EXPECT_EQ(StringList({txt}), wrapp(txt, 30));
}

TEST(WordWrapTests, TakeStringUnderLimit_GetStringList)
{
    const std::string txt = "Hello!I_said_hello!_Hey!";
    StringList res = {"Hello!I_sa", "id_hello!_", "Hey!"};
    EXPECT_EQ(res, wrapp(txt, 10));
}

TEST(WordWrapTests, TakeStringUnderLimitWithSpaces_GetSplittedString)
{
    const std::string txt = "Hello Man! Money!Monkey!Mikki!";
    StringList res = {"Hello Man!", "Money!Monkey!", "Mikki!"};
    EXPECT_EQ(res, wrapp(txt, 13));
}

TEST(WordWrapTests, TakeNumberStringWithSpaces_GetRightSplitted)
{
    const std::string txt = "12345 6 123456789 123456789";
    StringList res = {"12345", "6 1234", "56789", "123456", "789"};
    EXPECT_EQ(res, wrapp(txt, 6));
}
