/*### Bank OCR

Your manager has recently purchased a machine that assists in reading letters and faxes sent in by branch offices. The machine scans the paper documents, and produces a file with a number of entries. You will write a program to parse this file.

#### Specification
#### User Story 1

The following format is created by the machine:
```
    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|
```
Each entry is 3 lines long, and each line has 27 characters. 3 lines of each entry contain an account number written using pipes and underscores.

Each account number should have 9 digits, all of which should be in the range 0-9. A normal file contains around 500 entries.

Write a program that can take this file and parse it into actual account numbers.

Example input and output
```
 _  _  _  _  _  _  _  _  _
| || || || || || || || || |
|_||_||_||_||_||_||_||_||_|

=> 000000000

  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 111111111

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
|_ |_ |_ |_ |_ |_ |_ |_ |_

=> 222222222

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
 _| _| _| _| _| _| _| _| _|

=> 333333333

|_||_||_||_||_||_||_||_||_|
  |  |  |  |  |  |  |  |  |

=> 444444444

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
 _| _| _| _| _| _| _| _| _|

=> 555555555

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
|_||_||_||_||_||_||_||_||_|

=> 666666666

 _  _  _  _  _  _  _  _  _
  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 777777777

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
|_||_||_||_||_||_||_||_||_|

=> 888888888

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
 _| _| _| _| _| _| _| _| _|

=> 999999999

    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|

=> 123456789
```
*/
#include <gtest/gtest.h>

// check matrix for one digit 3x3
// parse one digit
   // - parse 1
   // - parse 2
   // - parse 0-9
   // - check invalid one digit
// parse several digits (27x3)
// parse 27x3 (9 digits)
   // - check matrix 27x3
   // - parse
// parse several lines

using Digit = std::vector<std::string>;
using Number = std::vector<std::string>;

const size_t matrixWidth = 27;
const size_t digitWidth = 3;
const size_t digitHeight = 3;

std::map<Digit, std::string> s_digits({
                              {{"   ",
                                "  |",
                                "  |"}, "1"},

                              {{" _ ",
                                " _|",
                                "|_ "}, "2"},

                               {{" _ ",
                                 " _|",
                                 " _|"}, "3"},

                              {{"   ",
                                "|_|",
                                "  |"}, "4"},

                              {{" _ ",
                                "|_ ",
                                " _|"}, "5"},

                              {{" _ ",
                                "|_ ",
                                "|_|"}, "6"},

                               {{" _ ",
                                 "  |",
                                 "  |"}, "7"},

                              {{" _ ",
                                "|_|",
                                "|_|"}, "8"},

                              {{" _ ",
                                "|_|",
                                " _|"}, "9"},

                              {{" _ ",
                                "| |",
                                "|_|"}, "0"}

});

std::string ParseDigit(const Digit& digit)
{
    const auto it = s_digits.find(digit);
    if (it != s_digits.end())
    {
        return it->second;
    }

    return "?";
}

bool CheckMatrix(const Number& number)
{
    if (number.size() == digitHeight)
    {
        for (const auto line : number)
        {
            if (line.size() != matrixWidth)
            {
                return false;
            }
        }

        return true;
    }

}

std::string ParseNumber(const Number& number)
{
    if (!CheckMatrix(number))
    {
        return "";
    }

    std::string result;
    for (int i = 0; i < matrixWidth; i+=3)
    {
        Digit digit{std::string(number[0].begin() + i, number[0].begin() + i + 3),
                    std::string(number[1].begin() + i, number[1].begin() + i + 3),
                    std::string(number[2].begin() + i, number[2].begin() + i + 3)};
        result += ParseDigit(digit);
    }
    return result;
}

TEST(BankOCRTests, ParseDigit_1)
{
    Digit digit = {"   ",
                   "  |",
                   "  |"};
    EXPECT_EQ("1", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigit_2)
{
    Digit digit = {" _ ",
                   " _|",
                   "|_ "};
    EXPECT_EQ("2", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigit_3)
{
    Digit digit = {" _ ",
                   " _|",
                   " _|"};
    EXPECT_EQ("3", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigit_4)
{
    Digit digit = {"   ",
                   "|_|",
                   "  |"};
    EXPECT_EQ("4", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigit_5)
{
    Digit digit = {" _ ",
                   "|_ ",
                   " _|"};
    EXPECT_EQ("5", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigit_6)
{
    Digit digit = {" _ ",
                   "|_ ",
                   "|_|"};
    EXPECT_EQ("6", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigit_7)
{
    Digit digit = {" _ ",
                   "  |",
                   "  |"};
    EXPECT_EQ("7", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigit_8)
{
    Digit digit = {" _ ",
                   "|_|",
                   "|_|"};
    EXPECT_EQ("8", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigit_9)
{
    Digit digit = {" _ ",
                   "|_|",
                   " _|"};
    EXPECT_EQ("9", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigit_0)
{
    Digit digit = {" _ ",
                   "| |",
                   "|_|"};
    EXPECT_EQ("0", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigit_corrupted)
{
    Digit digit = {" _ ",
                   " | ",
                   " | "};
    EXPECT_EQ("?", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigit_invalid_matrix)
{
    Digit digit = {"",
                   "!   ",
                   "!   "};
    EXPECT_EQ("?", ParseDigit(digit));
}

TEST(BankOCRTests, ParseNumber_123456789)
{
    Number number = {"    _  _     _  _  _  _  _ ",
                     "  | _| _||_||_ |_   ||_||_|",
                     "  ||_  _|  | _||_|  ||_| _|"};
    EXPECT_EQ("123456789", ParseNumber(number));
}

TEST(BankOCRTests, ParseNumber_invalid_matrix_width)
{
    Number number = {"    _  _     _  _  _  _ ",
                     "  | _| _||_||_ |_   ||_|",
                     "  ||_  _|  | _||_|  ||_|"};
    EXPECT_EQ("", ParseNumber(number));
}

TEST(BankOCRTests, ParseNumber_invalid_matrix_height)
{
    Number number = {"  | _| _||_||_ |_   ||_|",
                     "  ||_  _|  | _||_|  ||_|"};
    EXPECT_EQ("", ParseNumber(number));
}
