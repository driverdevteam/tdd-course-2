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

Digit s_severalDigit ={{"    _  _     _  _  _  _  _ ",
                        "  | _| _||_||_ |_   ||_||_|",
                        "  ||_  _|  | _||_|  ||_| _|"}};

const size_t s_numberStep = 3;
const size_t s_countNumbers = 9;
Digit GetDigitFromList(const Digit& bigDigits, const size_t index)
{
    size_t startPos = index * s_numberStep;

    Digit result = { bigDigits[0].substr(startPos, s_numberStep),
                     bigDigits[1].substr(startPos, s_numberStep),
                     bigDigits[2].substr(startPos, s_numberStep)};
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
    std::string result = "";
    for(size_t i=0; i <s_countNumbers; ++i)
    {
        Digit indexDigit = GetDigitFromList(digit, i);
        for(size_t j =0; j<s_digits.size(); ++j)
        {

            if(indexDigit == s_digits[j])
            {
                result += std::to_string(j);
            }
        }
    }

   if(result.empty())
   {
       throw std::exception("Digit is unknown");
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

TEST(BankOCRTests, CheckInvalidOneDigit)
{
    Digit wrongDigit= {"$$$",
                       "$$$",
                       "$$$"};

    EXPECT_THROW(ParseDigit(wrongDigit), std::exception);
}

TEST(BankOCRTests, ParseManyDigits)
{
    EXPECT_EQ("123456789", ParseDigit(s_severalDigit));
}
//--------------------------------------------------------------
TEST(GetDigitFromList, ParseOneDigit)
{
    EXPECT_EQ(s_digits[0], GetDigitFromList(s_digits[0], 0));
}

TEST(GetDigitFromList, ParseDigitFromManyNumbers)
{

    EXPECT_EQ(s_digits[1], GetDigitFromList(s_severalDigit, 0));
}

TEST(GetDigitFromList, ParseDigitFromManyNumbersWithIndex_2)
{
    EXPECT_EQ(s_digits[3], GetDigitFromList(s_severalDigit, 2));
}

TEST(GetDigitFromList, ParseRandomDigitWithIndex_2)
{
    Digit randomDigit ={{"    _  _  _     _  _  _  _ ",
                            " _||_   | _||_||_   ||_||_|",
                            "|_  _|  | _|  ||_|  ||_| _|"}};

    EXPECT_EQ(s_digits[3], GetDigitFromList(s_severalDigit, 2));
}
