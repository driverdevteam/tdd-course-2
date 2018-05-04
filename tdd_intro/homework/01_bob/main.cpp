#include <gtest/gtest.h>
#include <string>

std::string AskBob(const std::string& question)
{
    return "Whatever.";
}

TEST(Bob, AskNothing)
{
    std::string answer = AskBob("");
    EXPECT_EQ("Whatever.", answer);
}
