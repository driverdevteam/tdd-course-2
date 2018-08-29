/*
Write a function, that is given a string and a length limit, splits provided string into sequence of string,
where length of each string is not more, than provided limit. If there are spaces under provided limit -
last space should be used to Wrappp this line. If there are no spaces - Wrappp it on provided length limit.

When pos is specified, the search only includes sequences of characters that begin at or before position pos, ignoring any possible match beginning after pos.

"When pos is specified, the",
"search only includes sequences",
"of characters that begin at or",
"before position pos, ignoring",
"any possible match beginning",
"after pos."
*/

#include <gtest/gtest.h>
#include <cctype>
#include <sstream>
//1. Empty test.
//2. Short word and big limit.
//3. Big word and short limit.
//4. Input string with all spaces.
//5. String with 2 words and space before limit.
//6. String with 2 words and space after limit.
//7. String with 2 words and space on limit.
//8. String with 2 words and  several spaces before limit.
//9. String with words and different count of spaces.
//10.

using Strings_vt = std::vector<std::string>;

bool ClearPart(std::string& outPart)
{
    if(outPart == " ")
    {
        return false;
    }

    if(outPart.back() == ' ')
    {
        outPart.pop_back();
    }

    if(outPart[0] == ' ')
    {
        outPart = outPart.substr(1);
    }

    return true;
}
std::vector<std::string> WordWrapp(std::string data, unsigned int limit)
{

    Strings_vt result;

    if(data == "")
    {
        return result;
    }

    if(limit > data.size())
    {
        result.push_back(data);
        return result;
    }

    for(int i=0; i< data.size(); i+=limit)
    {
        std::string part = data.substr(i,limit);

        if(!ClearPart(part))
        {
            continue;
        }

        result.push_back(part);
    }

    return result;
}

TEST(WordWrappTests, Put_empty_get_empty)
{
    EXPECT_EQ(Strings_vt{}, WordWrapp("", 5));
}

TEST(WordWrappTests, Put_ShortWord_with_BigLimit)
{
    EXPECT_EQ(Strings_vt{"Word"}, WordWrapp("Word", 5));
}

TEST(WordWrappTests, Put_ShortWord_with_space)
{
    EXPECT_EQ(Strings_vt{"Word"}, WordWrapp("Word ", 4));
}

TEST(WordWrappTests, BigWord_ShortLimit)
{
    EXPECT_EQ(Strings_vt({"01234", "56789"}), WordWrapp("0123456789", 5));
}

TEST(WordWrappTests, BigWord_ShortLimit_ThreeWords)
{
    EXPECT_EQ(Strings_vt({"01234", "56789", "01234"}), WordWrapp("012345678901234", 5));
}

TEST(WordWrappTests, TwoWordWithSpace)
{
    EXPECT_EQ(Strings_vt({"0123", "4567"}), WordWrapp("0123 4567", 5));
}

TEST(WordWrappTests, ThreeWordWithSingleSpaces)
{
    EXPECT_EQ(Strings_vt({"012 3", "4567", "8"}), WordWrapp("012 3 45678", 5));
}

TEST(WordWrappTests, ClearPartWithOutSpaces)
{
    std::string str = "test";
    std::string expect = "test";
    EXPECT_TRUE(ClearPart(std::string(str)));
    EXPECT_STREQ(expect.c_str(), str.c_str());
}

TEST(WordWrappTests, ClearPartWithSpaceAfter)
{
    std::string str = "test ";
    std::string expect = "test";
    EXPECT_TRUE(ClearPart(str));
    EXPECT_STREQ(expect.c_str(), str.c_str());
}

TEST(WordWrappTests, ClearPartWithSpaceBefore)
{
    std::string str = " test";
    std::string expect = "test";
    EXPECT_TRUE(ClearPart(str));
    EXPECT_STREQ(expect.c_str(), str.c_str());
}

TEST(WordWrappTests, TakeNumberStringWithSpaces_GetRightSplitted)
{
    const std::string txt = "12345 6 123456789 123456789";
    Strings_vt res = {"12345", "6 1234", "56789", "123456", "789"};
    EXPECT_EQ(res, WordWrapp(txt, 6));
}

