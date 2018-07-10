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

using Digit = char[3][4]; // 4 is 3 + 1 for the null terminator

const Digit s_0 = { " _ ",
                    "| |",
                    "|_|"
                  };
const Digit s_1 = { "   ",
                    "  |",
                    "  |"
                  };
const Digit s_2 = { " _ ",
                    " _|",
                    "|_ "
                  };
const Digit s_3 = { " _ ",
                    " _|",
                    " _|"
                  };
const Digit s_4 = { "   ",
                    "|_|",
                    "  |"
                  };
const Digit s_5 = { " _ ",
                    "|_ ",
                    " _|"
                  };
const Digit s_6 = { " _ ",
                    "|_ ",
                    "|_|"
                  };
const Digit s_7 = { " _ ",
                    "  |",
                    "  |"
                  };
const Digit s_8 = { " _ ",
                    "|_|",
                    "|_|"
                  };
const Digit s_9 = { " _ ",
                    "|_|",
                    " _|"
                  };

const std::vector<const Digit*> s_possibleDigits = { &s_0, &s_1, &s_2, &s_3, &s_4, &s_5, &s_6, &s_7, &s_8, &s_9 };

bool DigitsAreEqual(const Digit& left, const Digit& right)
{
    return strcmp(left[0], right[0]) == 0 &&
           strcmp(left[1], right[1]) == 0 &&
           strcmp(left[2], right[2]) == 0;
}

using Number = unsigned char;
Number DigitToNumber(const Digit& digit)
{
    for (Number n = 0; s_possibleDigits.size(); ++n)
    {
        if (DigitsAreEqual(digit, *s_possibleDigits.at(n)))
        {
            return n;
        }
    }
    throw std::runtime_error("Digit could not be parsed");
}

TEST(BankOCRTests, DigitToNumber_0)
{
    EXPECT_EQ(0, DigitToNumber(Digit { " _ ",
                                       "| |",
                                       "|_|"
                                     }
                               ));
}

TEST(BankOCRTests, DigitToNumber_1)
{
    EXPECT_EQ(1, DigitToNumber(Digit { "   ",
                                       "  |",
                                       "  |"
                                     }
                               ));
}

TEST(BankOCRTests, DigitToNumber_2)
{
    EXPECT_EQ(2, DigitToNumber(Digit { " _ ",
                                       " _|",
                                       "|_ "
                                     }
                               ));
}
