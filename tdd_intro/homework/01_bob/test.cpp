/*
Bob answers 'Sure.' if you ask him a question. (? in the end)

He answers 'Whoa, chill out!' if you yell at him. (! in the end)

He says 'Fine. Be that way!' if you address him without actually saying anything.

He answers 'Whatever.' to anything else.
*/
#include <gtest/gtest.h>

const std::string s_answerWhatever("Whatever");

std::string GetBobAnswer(const std::string& speech)
{
    if (speech == "?")
    {
        return "Sure.";
    }

    return s_answerWhatever;
}

TEST(BOB, GetBobAnswer_TellNothing)
{
    EXPECT_EQ(GetBobAnswer(""), s_answerWhatever);
}

TEST(BOB, GetBobAnswer_TellQuestionMark)
{
    EXPECT_EQ(GetBobAnswer("?"), "Sure.");
}
