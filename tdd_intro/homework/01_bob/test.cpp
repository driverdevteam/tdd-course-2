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
    const std::string sureAnswerString = "Sure.";
    const std::string whoaAnsertString = "Whoa, chill out!";
    const std::string fineBeThatWayAnswerString = "Fine. Be that way!";
    const std::string whateverAnswerString = "Whatever.";
}

std::string GetAnswerFromBob(std::string&& str)
{
    if (str.empty())
    {
        return fineBeThatWayAnswerString;
    }
    switch(str.back())
    {
    case '?':
        return sureAnswerString;
        break;
    case '!':
        return whoaAnsertString;
        break;
    default:
        break;
    }

    return whateverAnswerString;
}

TEST(BobTaskTests, GetAnswerFromBob_IsSure)
{
    EXPECT_EQ(sureAnswerString, GetAnswerFromBob("Bobby?"));
}

TEST(BobTaskTests, GetAnswerFromBob_IsWhoaChillOut)
{
    EXPECT_EQ(whoaAnsertString, GetAnswerFromBob("Bobby!"));
}

TEST(BobTaskTests, GetAnswerFromBob_IsFineBeThatWay)
{
    EXPECT_EQ(fineBeThatWayAnswerString, GetAnswerFromBob(""));
}

TEST(BobTaskTests, GetAnswerFromBob_IsWhatever)
{
    EXPECT_EQ(whateverAnswerString, GetAnswerFromBob("Bobby.Hey.Bobby.Go.go.Go."));
}

TEST(BobTaskTests, GetAnswerFromBob_IsQuestionInTheStartAndExclamationInTheEnd)
{
    EXPECT_EQ(whoaAnsertString, GetAnswerFromBob("Bobby?Hey.Bobby.Bobbo.Bibbif.Go!"));
}
