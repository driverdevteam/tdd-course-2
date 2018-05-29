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

std::vector<Digit> s_digits({
                            {" _ ",
                             "| |",
                             "|_|"},

                            {"   ",
                             "  |",
                             "  |"},

                            {" _ ",
                             " _|",
                             "|_ "},

                            {" _ ",
                             " _|",
                             " _|"},

                            {"   ",
                             "|_|",
                             "  |"},

                            {" _ ",
                             "|_ ",
                             " _|"},

                            {" _ ",
                             "|_ ",
                             "|_|"},

                            {" _ ",
                             "  |",
                             "  |"},

                            {" _ ",
                             "|_|",
                             "|_|"},

                            {" _ ",
                             "|_|",
                             " _|"}});

bool CheckMatrixDimension(const Digit& digit)
{
    const size_t prefferedSize = 3;

    if (digit.size() != prefferedSize)
    {
        return false;
    }

    for (const std::string& line : digit)
    {
        if (line.size() != prefferedSize)
        {
            return false;
        }
    }

    return true;
}

std::string ParseDigit(const Digit& digit)
{
    for (size_t i = 0; i < s_digits.size(); ++i)
    {
        if (digit == s_digits[i])
        {
            return std::to_string(i);
        }
    }

    return "?";
}

std::string ParseSeveralDigits(const std::vector<Digit>& digits)
{
    return "000";
}

TEST(BankOCRTests, Check_Matrix_dimension_true)
{
    Digit digit = {"   ", "   ", "   "};
    EXPECT_TRUE(CheckMatrixDimension(digit));
}

TEST(BankOCRTests, Check_Matrix_dimension_false)
{
    Digit digit = {"  ", "!   ", " "};
    EXPECT_FALSE(CheckMatrixDimension(digit));
}

TEST(BankOCRTests, ParseDigit_1)
{
    EXPECT_EQ("1", ParseDigit(s_digits[1]));
}

TEST(BankOCRTests, ParseDigit_2)
{
    EXPECT_EQ("2", ParseDigit(s_digits[2]));
}

TEST(BankOCRTests, ParseDigit_8)
{
    EXPECT_EQ("8", ParseDigit(s_digits[8]));
}

TEST(BankOCRTests, ParseDigit_0_9)
{
    for (size_t i = 0; i < s_digits.size(); ++i)
    {
        EXPECT_EQ(std::to_string(i), ParseDigit(s_digits[i]));
    }
}

TEST(BankOCRTests, ParseDigit_InvalidDigit)
{
    Digit digit = {" __",
                   "|_ ",
                   " _|"};
    EXPECT_EQ("?", ParseDigit(digit));
}

TEST(BankOCRTests, ParseSeveralDigits_ThreeZeros)
{
    std::vector<Digit> digits;

    digits.push_back(s_digits[0]);
    digits.push_back(s_digits[0]);
    digits.push_back(s_digits[0]);

    EXPECT_EQ("000", ParseSeveralDigits(digits));
}

TEST(BankOCRTests, ParseSeveralDigits_TwoThrees)
{
    std::vector<Digit> digits;

    digits.push_back(s_digits[3]);
    digits.push_back(s_digits[3]);

    EXPECT_EQ("33", ParseSeveralDigits(digits));
}
