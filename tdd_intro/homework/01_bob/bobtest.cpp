#include <gtest/gtest.h>
#include <sstream>
#include <string>

std::string BobAnswer(const std::string& tellBob)
{
    if (tellBob.empty())
    {
        return "Fine. Be that way!";
    }

    if (tellBob.back() == '?')
    {
        return "Sure.";
    }
    return "Whoa, chill out!";
}

TEST(Bobtest, BobAnswer_input_single_question_mark_return_shure)
{
    EXPECT_EQ("Sure.", BobAnswer("?"));
}

TEST(Bobtest, BobAnswer_input_text_with_question_mark_return_shure)
{
    EXPECT_EQ("Sure.", BobAnswer("How are you?"));
}

TEST(Bobtest, BobAnswer_input_exclamation_mark_return_Whoa_chill_out)
{
    EXPECT_EQ("Whoa, chill out!", BobAnswer("!"));
}

TEST(Bobtest, BobAnswer_input_text_with_exclamation_mark_return_Whoa_chill_out)
{
    EXPECT_EQ("Whoa, chill out!", BobAnswer("Shut up!"));
}

TEST(Bobtest, BobAnswer_input_empty_return_Fine_Be_that_way)
{
    EXPECT_EQ("Fine. Be that way!", BobAnswer(""));
}
