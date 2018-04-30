#include <gtest/gtest.h>
#include <sstream>
#include <string>

std::string BobAnswer(const std::string& tellBob)
{
    return "Sure.";
}

TEST(Bobtest, BobAnswer_input_single_question_mark_return_shure)
{
    EXPECT_EQ("Sure.", BobAnswer("?"));
}

TEST(Bobtest, BobAnswer_input_exclamation_mark_return_Whoa_chill_out)
{
    EXPECT_EQ("Whoa, chill out!", BobAnswer("!"));
}
