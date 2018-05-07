#include <gtest/gtest.h>
#include <string>

std::string AskBob(const std::string& question)
{
    if (question.empty())
    {
        return "Fine. Be that way!";
    }
    else
    {
        if (question.back() == '?')
        {
            return "Sure.";
        }
        else if (question.back() == '!')
        {
            return "Whoa, chill out!";
        }
    }
    return "Whatever.";
}

TEST(Bob, AskNothing)
{
    std::string answer = AskBob("");
    EXPECT_EQ("Fine. Be that way!", answer);
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

TEST(Bob, ShoutAtHim)
{
    std::string answer = AskBob("Gerrarahere!");
    EXPECT_EQ("Whoa, chill out!", answer);
}

TEST(Bob, BlaBlaBla)
{
    std::string answer = AskBob("Bla-bla-bla");
    EXPECT_EQ("Whatever.", answer);
}
