/*
Write a function, that is given a string and a length limit, splits provided string into sequence of string,
where length of each string is not more, than provided limit. If there are spaces under provided limit -
last space should be used to wrapp this line. If there are no spaces - wrapp it on provided length limit.
*/

/*
  - return passed string if its length less then limit
  - pass a string without spaces with length more than limit
  - pass a string with spaces with length more than limit
  - pass a long string that contains intervals without spaces of size > limit
*/


#include <gtest/gtest.h>
#include <cctype>

using WrappedWords = std::vector<std::string>;

WrappedWords WordWrap(const std::string& stringToWrapp, size_t limit)
{
    WrappedWords result;
    for (size_t pos = 0; pos < stringToWrapp.size();)
    {
        if (pos + limit < stringToWrapp.size())
        {
            std::string limitedString(stringToWrapp.substr(pos, limit));
            size_t space_pos = limitedString.find_last_of(' ');

            if (space_pos != std::string::npos)
            {
                result.push_back(stringToWrapp.substr(pos, space_pos));
                pos += space_pos + 1;
            }
            else
            {
                result.push_back(limitedString);
                pos += limit;
            }
        }
        else
        {
            result.push_back(stringToWrapp.substr(pos, limit));
            pos += limit;
        }
    }
    return result;
}

TEST(WordWrapTest, PassStringShorterThanLimit)
{
    const std::string shortString("123");
    EXPECT_EQ(WrappedWords{shortString}, WordWrap(shortString, 20));
}

TEST(WordWrapTest, PassStringWithoutSpacesLongerThanLimit)
{
    EXPECT_EQ(WrappedWords({"12345", "67"}),
              WordWrap("1234567", 5));
}

TEST(WordWrapTest, PassStringWithSpacesLongerThanLimit)
{
    EXPECT_EQ(WrappedWords({"123", "45"}),
              WordWrap("123 45", 5));
}
