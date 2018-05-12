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
const std::string s_answerFine("Fine. Be that way!");
const std::string s_name("Bob");
const std::string s_nameWithDot = s_name + ".";

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
        else if (speech == s_name || speech == s_nameWithDot)
        {
            return s_answerFine;
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

TEST(BOB, GetBobAnswer_Yell)
{
    EXPECT_EQ(GetBobAnswer("HELLO!"), s_answerChillOut);
}

TEST(BOB, GetBobAnswer_ExclamationMarkNotLast)
{
    EXPECT_EQ(GetBobAnswer("HI!HI"), s_answerWhatever);
}

TEST(BOB, GetBobAnswer_AddressBobNotSayingAnything)
{
    EXPECT_EQ(GetBobAnswer("Bob"), s_answerFine);
}

TEST(BOB, GetBobAnswer_AddressBobWithDot)
{
    EXPECT_EQ(GetBobAnswer("Bob."), s_answerFine);
}

TEST(BOB, GetBobAnswer_AddressBobWithOtherWords)
{
    EXPECT_EQ(GetBobAnswer("Bob, wake up."), s_answerWhatever);
}
