/*
Bob answers 'Sure.' if you ask him a question. (? in the end)

He answers 'Whoa, chill out!' if you yell at him. (! in the end)

He says 'Fine. Be that way!' if you address him without actually saying anything.

He answers 'Whatever.' to anything else.
*/
#include <gtest/gtest.h>

const std::string whatever = "Whatever";
const std::string fine = "Fine. Be that way!";
const std::string sure = "Sure.";
const std::string whoa = "Whoa, chill out!";

std::string BobAnswer(const std::string& phrase)
{
    if(phrase == "")
    {
        return fine;
    }
    else if(phrase.back() == '?')
    {
        return sure;
    }
    else if (phrase.back() == '!')
    {
        return whoa;
    }
    else
    {
        return whatever;
    }
}

TEST(BOB_ANSWER, ASK_NOTHIN_ANSWER_FINE)
{
    EXPECT_EQ(fine, BobAnswer(""));
}

TEST(BOB_ANSWER, ASK_TEST_ANSWER_Whatever)
{
    EXPECT_EQ(whatever, BobAnswer("TEST"));
}

TEST(BOB_ANSWER, ASK_TEST1_ANSWER_Whatever)
{
    EXPECT_EQ(whatever, BobAnswer("TEST1"));
}

TEST(BOB_ANSWER, ASK_With_Yell_ANSWER_Whoa)
{
    EXPECT_EQ(whoa, BobAnswer("!"));
}

TEST(BOB_ANSWER, ASK_WITH_YELL_AND_WORDS_ANSWER_WHOA)
{
    EXPECT_EQ(whoa, BobAnswer("HELLO!"));
}

TEST(BOB_ANSWER, ASK_WITH_QUESTION_ANSWER_Sure)
{
    EXPECT_EQ(sure, BobAnswer("?"));
}

TEST(BOB_ANSWER, ASK_WITH_QUESTION_WITH_WORDS_ANSWER_Sure)
{
    EXPECT_EQ(sure, BobAnswer("HELLO?"));
}

