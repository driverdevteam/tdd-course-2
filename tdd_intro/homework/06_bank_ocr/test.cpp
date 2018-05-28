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
using Digits = std::vector<Digit>;
using DigitsLine = std::vector<std::string>;

const Digits s_digits({{" _ ",
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

const size_t s_digitHeight(3);
const size_t s_digitWidth(3);
const size_t s_digitsLineWidth(9 * s_digitWidth);

bool CheckMatrixDimension(const Digit& digit)
{
    if (digit.size() != s_digitHeight)
    {
        return false;
    }

    for (const std::string& line : digit)
    {
        if (line.size() != s_digitWidth)
        {
            return false;
        }
    }

    return true;
}

bool CheckDigitsLineDimension(const DigitsLine& digitsLine)
{
    if (digitsLine.size() != s_digitHeight)
    {
        return false;
    }

    for (const std::string& line : digitsLine)
    {
        if (line.size() != s_digitsLineWidth)
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

std::string ParseDigitsLine(const DigitsLine& digitsLine)
{
    std::string result;

    for (size_t i = 0; i < s_digitsLineWidth; i += s_digitWidth)
    {
        Digit digit;

        for (size_t j = 0; j < s_digitHeight; ++j)
        {
            digit.push_back(digitsLine[j].substr(i, s_digitWidth));
        }

        if (CheckMatrixDimension(digit))
        {
            result += ParseDigit(digit);
        }
    }

    return result;
}

std::vector<std::string> ParseDigitsLines(const DigitsLine& digitsLines)
{
    std::vector<std::string> result;
    const size_t linesCount = digitsLines.size() - s_digitHeight;

    for (size_t i = 0; i <= linesCount; i += s_digitHeight)
    {
        DigitsLine lineOfDigits;

        for (size_t j = 0; j < s_digitHeight; ++j)
        {
            lineOfDigits.push_back(digitsLines[i + j]);
        }

        if (CheckDigitsLineDimension(lineOfDigits))
        {
            result.push_back(ParseDigitsLine(lineOfDigits));
        }
    }

    return result;
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

TEST(BankOCRTests, ParseDigit_8)
{
    Digit digit = {" _ ",
                   "|_|",
                   "|_|"};
    EXPECT_EQ("8", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigit_WrongDigit)
{
    Digit digit = {"|_ ",
                   "|_|",
                   "|_|"};
    EXPECT_EQ("?", ParseDigit(digit));
}

TEST(BankOCRTests, ParseDigitsLine_ParseAllDigits)
{
    DigitsLine digitsLine = {"    _  _     _  _  _  _  _ ",
                             "  | _| _||_||_ |_   ||_||_|",
                             "  ||_  _|  | _||_|  ||_| _|"};
    EXPECT_EQ("123456789", ParseDigitsLine(digitsLine));
}

TEST(BankOCRTests, CheckDigitsLineDimension_true)
{
    DigitsLine digitsLine = {"    _  _     _  _  _  _  _ ",
                             "  | _| _||_||_ |_   ||_||_|",
                             "  ||_  _|  | _||_|  ||_| _|"};
    EXPECT_TRUE(CheckDigitsLineDimension(digitsLine));
}

TEST(BankOCRTests, CheckDigitsLineDimension_false)
{
    DigitsLine digitsLine = {"    _  _     _  _  _  _  _ ",
                             "  | _|  _||_||_ |_   ||_||_|",
                             "  ||_  |  | _||_|  ||_| _|"};
    EXPECT_FALSE(CheckDigitsLineDimension(digitsLine));
}

TEST(BankOCRTests, ParseDigitsLines_Parse2Lines)
{
    DigitsLine digitsLines = {"    _  _     _  _  _  _  _ ",
                              "  | _| _||_||_ |_   ||_||_|",
                              "  ||_  _|  | _||_|  ||_| _|",
                              "    _  _     _  _  _  _  _ ",
                              "  | _| _|  ||_ |_|  ||_ |_|",
                              "  ||_  _|  | _||_|  ||_| _|"};
    EXPECT_EQ(std::vector<std::string>({"123456789", "123158769"}),
              ParseDigitsLines(digitsLines));
}

TEST(BankOCRTests, ParseDigitsLines_Parse1LineAndSkipHalf)
{
    DigitsLine digitsLines = {"    _  _     _  _  _  _  _ ",
                              "  | _| _||_||_ |_   ||_||_|",
                              "  ||_  _|  | _||_|  ||_| _|",
                              "    _  _     _  _  _  _  _ ",
                              "  | _| _|  ||_ |_|  ||_ |_|"};
    EXPECT_EQ(std::vector<std::string>({"123456789"}),
              ParseDigitsLines(digitsLines));
}
