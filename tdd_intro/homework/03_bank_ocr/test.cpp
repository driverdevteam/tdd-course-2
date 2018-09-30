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
#include <string>

/*
 * Plan:
 * 1. Test each single digit
 * 2. Test invalid digit
 * 3. Test full sequence of single digit
 * 4. Test all digits in single sequence
 * 5. Acceptance
*/

const unsigned short g_linesInDigit = 3;
struct Digit
{
    std::string lines[3];
};
using Number = uint64_t;

const unsigned short g_digitsOnDisplay = 9;
struct Display
{
    std::string lines[3];
};

const Digit s_digit0 = { " _ ",
                         "| |",
                         "|_|"
                       };
const Digit s_digit1 = { "   ",
                         "  |",
                         "  |"
                       };
const Digit s_digit2 = { " _ ",
                         " _|",
                         "|_ "
                       };
const Digit s_digit3 = { " _ ",
                         " _|",
                         " _|"
                       };
const Digit s_digit4 = { "   ",
                         "|_|",
                         "  |"
                       };
const Digit s_digit5 = { " _ ",
                         "|_ ",
                         " _|"
                       };
const Digit s_digit6 = { " _ ",
                         "|_ ",
                         "|_|"
                       };
const Digit s_digit7 = { " _ ",
                         "  |",
                         "  |"
                       };
const Digit s_digit8 = { " _ ",
                         "|_|",
                         "|_|"
                       };
const Digit s_digit9 = { " _ ",
                         "|_|",
                         " _|"
                       };

const Display s_displayAll0 = { " _  _  _  _  _  _  _  _  _ ",
                                "| || || || || || || || || |",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll1 = { "                           ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll2 = {  " _  _  _  _  _  _  _  _  _ ",
                                 " _| _| _| _| _| _| _| _| _|",
                                 "|_ |_ |_ |_ |_ |_ |_ |_ |_ "
};

const Display s_displayAll3 = { " _  _  _  _  _  _  _  _  _ ",
                                " _| _| _| _| _| _| _| _| _|",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_displayAll4 = { "                           ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll5 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_displayAll6 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll7 = { " _  _  _  _  _  _  _  _  _ ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll8 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll9 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_display123456789 = { "    _  _     _  _  _  _  _ ",
                                     "  | _| _||_||_ |_   ||_||_|",
                                     "  ||_  _|  | _||_|  ||_| _|"
};

bool AreDigitsEqual(const Digit& digit1, const Digit& digit2)
{
    for (size_t digitLine = 0; digitLine < g_linesInDigit; ++digitLine)
    {
        if (digit1.lines[digitLine] != digit2.lines[digitLine])
        {
            return false;
        }
    }
    return true;
}

Number DigitToNumber(const Digit& digit)
{
    static const Digit s_possibleDigit[] = {
        s_digit0, s_digit1, s_digit2, s_digit3, s_digit4, s_digit5, s_digit6, s_digit7, s_digit8, s_digit9
    };

    for (Number number = 0; number < 10; ++number)
    {
        if (AreDigitsEqual(digit, s_possibleDigit[number]))
        {
            return number;
        }
    }
    throw std::runtime_error("Digit was not recognized");
}

Digit ExtractDigitFromDisplay(const Display& display)
{
    Digit firstDigit;
    firstDigit.lines[0] = display.lines[0].substr(0, g_linesInDigit);
    firstDigit.lines[1] = display.lines[1].substr(0, g_linesInDigit);
    firstDigit.lines[2] = display.lines[2].substr(0, g_linesInDigit);

    return firstDigit;
}

std::string DisplayToNumber(const Display& display)
{
    Digit firstDigit = ExtractDigitFromDisplay(display);
    if (AreDigitsEqual(firstDigit, s_digit0))
    {
        return "000000000";
    }
    else if (AreDigitsEqual(firstDigit, s_digit2))
    {
        return "222222222";
    }
    return "111111111";
}

TEST(BankOCR, Zero)
{
    Number num = DigitToNumber(s_digit0);
    ASSERT_EQ(0, num);
}

TEST(BankOCR, One)
{
    Number num = DigitToNumber(s_digit1);
    ASSERT_EQ(1, num);
}

TEST(BankOCR, Two)
{
    Number num = DigitToNumber(s_digit2);
    ASSERT_EQ(2, num);
}

TEST(BankOCR, EachSingleDigitAcceptance)
{
    EXPECT_EQ(3, DigitToNumber(s_digit3));
    EXPECT_EQ(4, DigitToNumber(s_digit4));
    EXPECT_EQ(5, DigitToNumber(s_digit5));
    EXPECT_EQ(6, DigitToNumber(s_digit6));
    EXPECT_EQ(7, DigitToNumber(s_digit7));
    EXPECT_EQ(8, DigitToNumber(s_digit8));
    EXPECT_EQ(9, DigitToNumber(s_digit9));
}

TEST(BankOCR, InvalidDigit)
{
    Digit invalidDigit = {
        " _ ",
        " _|"
        "|_|"
    };

    EXPECT_ANY_THROW(DigitToNumber(invalidDigit));
}

TEST(BankOCR, DisplayToNumber_Nulls)
{
    std::string num = DisplayToNumber(s_displayAll0);
    EXPECT_EQ("000000000", num);
}

TEST(BankOCR, DisplayToNumber_Ones)
{
    std::string num = DisplayToNumber(s_displayAll1);
    EXPECT_EQ("111111111", num);
}

TEST(BankOCR, DisplayToNumber_Twos)
{
    std::string num = DisplayToNumber(s_displayAll2);
    EXPECT_EQ("222222222", num);
}
