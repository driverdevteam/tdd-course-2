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

using DigitSequence = std::vector<std::string>;

namespace
{
size_t s_digitWidth = 3;
size_t s_digitHeight = 3;
size_t s_digitSequenceWidth = 9 * s_digitWidth;

std::vector<DigitSequence> s_digits({{" _ ",
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
}

bool CheckDigitSequenceDimension(const DigitSequence& digitSequence, size_t digitsWidth = 3)
{

    if (digitSequence.size() != s_digitWidth)
    {
        return false;
    }

    for (const std::string& line : digitSequence)
    {
        if (line.size() != digitsWidth)
        {
            return false;
        }
    }

    return true;
}

std::string ParseDigit(const DigitSequence& d)
{
    for (size_t i = 0; i < s_digits.size(); ++i)
    {
        if (d == s_digits[i])
        {
            return std::to_string(i);
        }
    }

    return "*";
}

std::string ParseDigits(const DigitSequence& digits)
{
    std::string res;

    for (size_t i = 0; i < s_digitSequenceWidth; i += s_digitWidth)
    {
        DigitSequence digit;

        for (size_t j = 0; j < s_digitHeight; ++j)
        {
            digit.push_back(digits[j].substr(i, s_digitWidth));
        }

        if (CheckDigitSequenceDimension(digit))
        {
            res += ParseDigit(digit);
        }
    }

    return res;
}

TEST(BankOCRTests, CheckDigitSequenceDimension_true)
{
    DigitSequence digit = {"   ", "   ", "   "};
    EXPECT_TRUE(CheckDigitSequenceDimension(digit));
}

TEST(BankOCRTests, CheckDigitSequenceDimension_false)
{
    DigitSequence digit = {"  ", "!   ", " "};
    EXPECT_FALSE(CheckDigitSequenceDimension(digit));
}

TEST(BankOCRTests, ParseDigit_1)
{
    DigitSequence digit = {"   ",
                           "  |",
                           "  |"};
    EXPECT_EQ("1", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigit_2)
{
    DigitSequence digit = {" _ ",
                           " _|",
                           "|_ "};
    EXPECT_EQ("2", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigit_8)
{
    DigitSequence digit = {" _ ",
                           "|_|",
                           "|_|"};
    EXPECT_EQ("8", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigit_wrong_4)
{
    DigitSequence wrongDigit = {"|@|",
                                "  |"
                               };
    EXPECT_EQ("*", ParseDigit(wrongDigit));
}

TEST(BankOCRTests, Parse_all_digitis)
{
    DigitSequence digits = {"    _  _     _  _  _  _  _ ",
                            "  | _| _||_||_ |_   ||_||_|",
                            "  ||_  _|  | _||_|  ||_| _|"};
    EXPECT_EQ("123456789", ParseDigits(digits));
}

TEST(BankOCRTests, CheckDigitSequenceDimension_with_param_true)
{
    DigitSequence digits = {"    _  _     _  _  _  _  _ ",
                            "  | _| _||_||_ |_   ||_||_|",
                            "  ||_  _|  | _||_|  ||_| _|"};
    EXPECT_TRUE(CheckDigitSequenceDimension(digits, s_digitSequenceWidth));
}


