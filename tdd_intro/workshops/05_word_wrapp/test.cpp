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
std::vector<std::string> WordWrapp(std::string data, unsigned int limit)
{
    Strings_vt result;
    if (data.empty())
    {
        return result;
    }

    for (int pos = 0; pos < data.size();)
    {
        std::string word(data.substr(pos, limit));
        if (word.front() == ' ')
        {
            ++pos;
            continue;
        }

        while (word.back() == ' ')
        {
            word.pop_back();
        }
        result.push_back(word);

        pos += limit;
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
    EXPECT_EQ(Strings_vt({"012 3", "45678"}), WordWrapp("012 3 45678", 5));
}

TEST(WordWrappTests, TwoWordsWithAlotOfSpaces)
{
    EXPECT_EQ(Strings_vt({"12", "34567"}), WordWrapp("12    34567", 5));
}
