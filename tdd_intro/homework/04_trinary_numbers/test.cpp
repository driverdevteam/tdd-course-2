#include <gtest/gtest.h>

/*
Convert a trinary number, represented as a string (e.g. '102012'), to its decimal equivalent using first principles.

The program should consider strings specifying an invalid trinary as the value 0.

Trinary numbers contain three symbols: 0, 1, and 2.

The last place in a trinary number is the 1's place. The second to last is the 3's place, the third to last is the 9's place, etc.

# "102012"
    1       0       2       0       1       2    # the number
1*3^5   + 0*3^4 + 2*3^3 + 0*3^2 + 1*3^1 + 2*3^0    # the value
  243   +   0 +    54 +     0 +     3 +     2 =  302

If your language provides a method in the standard library to perform the conversion, pretend it doesn't exist and implement it yourself.
*/

int s_charNumberPos = 48;
int s_zero = 0;
int s_first = 1;
int s_second = 2;
int s_thirt = 3;

std::vector<int> GetNumbersListFromString(const std::string& numbers)
{
    std::vector<int> result;
    for(char symb: numbers)
    {
        int numeral = static_cast<int>(symb) - s_charNumberPos;
        result.push_back(numeral);
    }
    return result;
}

int GetIntFromTrynaryNumb(const int numb, int index)
{
    return numb * static_cast<int>(pow(s_thirt, index));
}

int GetTrynaryFromString(std::string& strNumbs)
{
    std::vector<int> numbers = GetNumbersListFromString(strNumbs);
    int result =0;
    for(int i= numbers.size() -1, j=0; i>=0; --i, ++j)
    {
        if(numbers[j] > s_second ||  numbers[j]< s_zero)
        {
           return s_zero;
        }
        result += GetIntFromTrynaryNumb(numbers[j], i);
    }

    return result;
}

TEST(GetTrynaryFromString, INPUT_0_RETURN_0)
{
    std::string input = "0";
    EXPECT_EQ(0, GetTrynaryFromString(input));
}

TEST(GetTrynaryFromString, INPUT_3_RETURN_0)
{
    std::string input = "3";
    EXPECT_EQ(0, GetTrynaryFromString(input));
}

TEST(GetTrynaryFromString, INPUT_1_RETURN_1)
{
    std::string input = "1";
    EXPECT_EQ(1, GetTrynaryFromString(input));
}

TEST(GetTrynaryFromString, INPUT_2_RETURN_2)
{
    std::string input = "2";
    EXPECT_EQ(2, GetTrynaryFromString(input));
}

TEST(GetTrynaryFromString, INPUT_9_RETURN_0)
{
    std::string input = "9";
    EXPECT_EQ(0, GetTrynaryFromString(input));
}

TEST(GetTrynaryFromString, INPUT_11_RETURN_2)
{
    std::string input = "11";
    EXPECT_EQ(4, GetTrynaryFromString(input));
}

TEST(GetTrynaryFromString, INPUT_102012_RETURN_302)
{
    std::string input = "102012";
    EXPECT_EQ(302, GetTrynaryFromString(input));
}

//------------------------------------------------------------
TEST(GetIntFromTrynaryNumb, INPUT_0_0_return_0)
{
    EXPECT_EQ(s_zero, GetIntFromTrynaryNumb(0, 0));
}

TEST(GetIntFromTrynaryNumb, INPUT_1_0_return_1)
{
    EXPECT_EQ(s_first, GetIntFromTrynaryNumb(1, 0));
}

TEST(GetIntFromTrynaryNumb, INPUT_2_2_return_18)
{
    EXPECT_EQ(18, GetIntFromTrynaryNumb(2, 2));
}

//-----------------------------------------------------------
TEST(GetNumbersListFromString, INPUT_0_RETURN_0)
{
    std::string input = "0";
    std::vector<int> expect;
    expect.push_back(0);
    EXPECT_EQ(expect, GetNumbersListFromString(input));
}
TEST(GetNumbersListFromString, INPUT_1_RETURN_1)
{
    std::string input = "1";
    std::vector<int> expect;
    expect.push_back(1);
    EXPECT_EQ(expect, GetNumbersListFromString(input));
}
TEST(GetNumbersListFromString, INPUT_12_RETURN_12)
{
    std::string input = "12";
    std::vector<int> expect;
    expect.push_back(s_first);
    expect.push_back(s_second);
    EXPECT_EQ(expect, GetNumbersListFromString(input));
}
TEST(GetNumbersListFromString, INPUT_12345_RETURN_12345)
{
    std::string input = "12345";
    std::vector<int> expect;
    expect.push_back(1);
    expect.push_back(2);
    expect.push_back(3);
    expect.push_back(4);
    expect.push_back(5);
    EXPECT_EQ(expect, GetNumbersListFromString(input));
}




