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

std::vector<Digit> s_digits({{" _ ",
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
                              " _|"}

});

Digit GetDigitFromList(Digit& bigDigits, const size_t index)
{
    Digit result = {{bigDigits[0].substr(0,3)},bigDigits[1].substr(0,3),bigDigits[2].substr(0,3) };
    return result;
}
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

    for(size_t i=0; i <s_digits.size(); ++i)
    {
        if(digit == s_digits[i])
        {
            return std::to_string(i);
        }
    }
   throw std::exception("Digit is unknown");
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

TEST(BankOCRTests, ParseAllDigits)
{
    for(int i=0;i< 10; i++)
    {
        EXPECT_EQ(std::to_string(i), ParseDigit(s_digits[i]));
    }
}

TEST(BankOCRTests, CheckInvalidOneDigit)
{
    Digit wrongDigit= {"$$$",
                       "$$$",
                       "$$$"};

    EXPECT_THROW(ParseDigit(wrongDigit), std::exception);
}
//--------------------------------------------------------------
TEST(GetDigitFromList, ParseOneDigit)
{
    EXPECT_EQ(s_digits[0], GetDigitFromList(s_digits[0], 0));
}

TEST(GetDigitFromList, ParseOneDigitFromManyNumbers)
{
    Digit severalDigit ={{"    _  _     _  _  _  _  _",
                          "  | _| _||_||_ |_   ||_||_|",
                          "  ||_  _|  | _||_|  ||_| _|"}};
    EXPECT_EQ(s_digits[1], GetDigitFromList(severalDigit, 0));
}
