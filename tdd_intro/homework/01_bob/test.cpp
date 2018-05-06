/*
Bob answers 'Sure.' if you ask him a question. (? in the end)

He answers 'Whoa, chill out!' if you yell at him. (! in the end)

He says 'Fine. Be that way!' if you address him without actually saying anything.

He answers 'Whatever.' to anything else.
*/
#include <gtest/gtest.h>

std::string BobAnswer(const std::string& phrase)
{
    if(phrase == "")
    {
        return "Fine. Be that way!";
    }
    else
    {
        return "Whatever";
    }
}

TEST(BOB_ANSWER, ASK_NOTHIN_ANSWER_FINE)
{
    EXPECT_EQ("Fine. Be that way!", BobAnswer(""));
}

TEST(BOB_ANSWER, ASK_TEST_ANSWER_Whatever)
{
    EXPECT_EQ("Whatever", BobAnswer("TEST"));
}

TEST(BOB_ANSWER, ASK_TEST1_ANSWER_Whatever)
{
    EXPECT_EQ("Whatever", BobAnswer("TEST1"));
}
