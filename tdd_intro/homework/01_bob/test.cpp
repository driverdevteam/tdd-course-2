/*
Bob answers 'Sure.' if you ask him a question. (? in the end)

He answers 'Whoa, chill out!' if you yell at him. (! in the end)

He says 'Fine. Be that way!' if you address him without actually saying anything.

He answers 'Whatever.' to anything else.
*/
#include <gtest/gtest.h>

const std::string s_answerWhatever("Whatever.");
const std::string s_answerSure("Sure.");
const std::string s_answerChillOut("Whoa, chill out!");

std::string GetBobAnswer(const std::string& speech)
{
    if (!speech.empty())
    {
        if (speech.back() == '?')
        {
            return s_answerSure;
        }
        else if (speech.back() == '!')
        {
            return s_answerChillOut;
        }
    }

    return s_answerWhatever;
}

TEST(BOB, GetBobAnswer_TellNothing)
{
    EXPECT_EQ(GetBobAnswer(""), s_answerWhatever);
}

TEST(BOB, GetBobAnswer_TellQuestionMark)
{
    EXPECT_EQ(GetBobAnswer("?"), s_answerSure);
}

TEST(BOB, GetBobAnswer_AskQuestion)
{
    EXPECT_EQ(GetBobAnswer("How are you?"), s_answerSure);
}

TEST(BOB, GetBobAnswer_QuestionMarkNotLast)
{
    EXPECT_EQ(GetBobAnswer("What?What"), s_answerWhatever);
}

TEST(BOB, GetBobAnswer_TellExclamationMark)
{
    EXPECT_EQ(GetBobAnswer("!"), s_answerChillOut);
}
