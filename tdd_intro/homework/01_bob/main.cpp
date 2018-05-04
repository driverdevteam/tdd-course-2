#include <gtest/gtest.h>
#include <string>

std::string AskBob(const std::string& question)
{
    if (!question.empty() && question.back() == '?')
    {
        return "Sure.";
    }
    return "Whatever.";
}

TEST(Bob, AskNothing)
{
    std::string answer = AskBob("");
    EXPECT_EQ("Whatever.", answer);
}

TEST(Bob, AskQuestion_English)
{
    std::string answer = AskBob("English, Bob, do you speak it?");
    EXPECT_EQ("Sure.", answer);
}

TEST(Bob, AskQuestion_German)
{
    std::string answer = AskBob("German, Bob, do you speak it?");
    EXPECT_EQ("Sure.", answer);
}

TEST(Bob, ThrowAnAngryLook)
{
    std::string answer = AskBob("!");
    EXPECT_EQ("Whoa, chill out!", answer);
}
