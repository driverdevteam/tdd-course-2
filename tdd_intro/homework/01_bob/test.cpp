/*
Bob answers 'Sure.' if you ask him a question. (? in the end)

He answers 'Whoa, chill out!' if you yell at him. (! in the end)

He says 'Fine. Be that way!' if you address him without actually saying anything.

He answers 'Whatever.' to anything else.
*/
#include <gtest/gtest.h>
#include <string>

namespace
{
    const std::string sureString = "Sure.";
    const std::string whoaString = "Whoa, chill out!";
    const std::string fineString = "Fine. Be that way!";
}

std::string GetAnswerFromBob(std::string&& str)
{
    if (str.find('?') != str.npos)
    {
        return sureString;
    }
    if (str.find('!') != str.npos)
    {
        return whoaString;
    }
    if (str.empty())
    {
        return fineString;
    }

    return "Whatever.";
}

TEST(BobTaskTests, GetAnswerFromBob_IsSure)
{
    EXPECT_EQ(sureString, GetAnswerFromBob("Bobby?"));
}

TEST(BobTaskTests, GetAnswerFromBob_IsWhoaChillOut)
{
    EXPECT_EQ(whoaString, GetAnswerFromBob("Bobby!"));
}

TEST(BobTaskTests, GetAnswerFromBob_IsFineBeThatWay)
{
    EXPECT_EQ(fineString, GetAnswerFromBob(""));
}

TEST(BobTaskTests, GetAnswerFromBob_IsWhatever)
{
    EXPECT_EQ("Whatever.", GetAnswerFromBob("Bobby.Hey.Bobby.Go.go.Go."));
}

