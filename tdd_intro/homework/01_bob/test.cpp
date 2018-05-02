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
    const std::string sureString = "Sure";
}

std::string GetAnswerFromBob(std::string&& str)
{
    return sureString;
}

TEST(BobTaskTests, GetAnswerFromBob_IsSure)
{
    EXPECT_EQ(sureString, GetAnswerFromBob("Bobby?"));
}
