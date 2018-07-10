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

using DigitView = std::vector<std::string>;
class Digit
{
public:
    Digit(const std::initializer_list<std::string>& lst)
    {
        DigitView view;
        for (const auto& line : lst) { view.push_back(line); }
        Init(view);
    }
    Digit(const DigitView& view)
    {
        Init(view);
    }

    const DigitView& View() const { return m_view; }

    static constexpr unsigned char Height() { return 3; }
    static constexpr unsigned char Width() { return 3; }

private:
    void Init(const DigitView& view)
    {
        if (view.size() != Height())
        {
            throw std::runtime_error("Invalid digit view height");
        }

        for (const auto& line : view)
        {
            if (line.size() != Width())
            {
                throw std::runtime_error("Invalid digit view width");
            }
        }
        m_view = view;
    }

private:
    DigitView m_view;
};

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

bool DigitsAreEqual(const Digit& left, const Digit& right)
{
    for (unsigned char line = 0; line < Digit::Height(); ++line)
    {
        if (left.View().at(line) != right.View().at(line))
        {
            return false;
        }
    }
    return true;
}

using Number = unsigned char;
Number DigitToNumber(const Digit& digit)
{
    static const std::vector<const Digit*> s_possibleDigits = { &s_0, &s_1, &s_2, &s_3, &s_4, &s_5, &s_6, &s_7, &s_8, &s_9 };
    for (Number n = 0; s_possibleDigits.size(); ++n)
    {
        if (DigitsAreEqual(digit, *s_possibleDigits.at(n)))
        {
            return n;
        }
    }
    throw std::runtime_error("Digit could not be parsed");
}

using DigitsDisplayView = std::vector<std::string>;
class DigitsDisplay
{
public:
    DigitsDisplay(const std::initializer_list<std::string>& lst)
    {
        if (lst.size() != Digit::Height())
        {
            throw std::runtime_error("Invalid digit display view height");
        }

        for (const auto& line : lst)
        {
            if (line.size() != Width())
            {
                throw std::runtime_error("Invalid digit display view width");
            }
            m_view.push_back(line);
        }
    }

    const DigitsDisplayView& View() const { return m_view; }

    static constexpr unsigned char NumbersCount() { return 9; }
    static constexpr unsigned char Height() { return Digit::Height(); }
    static constexpr unsigned char Width() { return Digit::Width() * NumbersCount(); }

private:
    DigitsDisplayView m_view;
};

std::string ParseDisplay(const DigitsDisplay& display)
{
    DigitView digitView(display.Height());
    std::string res;
    for (unsigned char digitPos = 0; digitPos < display.Width(); digitPos += Digit::Width())
    {
        for (unsigned char height = 0; height < display.Height(); ++height)
        {
            digitView.at(height) = display.View().at(height).substr(digitPos, Digit::Width());
        }
        res += std::to_string(DigitToNumber(Digit(digitView)));
    }
    return res;
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

TEST(BankOCRTests, DigitToNumber_Acceptance)
{
    EXPECT_EQ(3, DigitToNumber(Digit { " _ ",
                                       " _|",
                                       " _|"
                                     }
                               ));
    EXPECT_EQ(4, DigitToNumber(Digit { "   ",
                                       "|_|",
                                       "  |"
                                     }
                               ));
    EXPECT_EQ(5, DigitToNumber(Digit { " _ ",
                                       "|_ ",
                                       " _|"
                                     }
                               ));
    EXPECT_EQ(6, DigitToNumber(Digit { " _ ",
                                       "|_ ",
                                       "|_|"
                                     }
                               ));
    EXPECT_EQ(7, DigitToNumber(Digit { " _ ",
                                       "  |",
                                       "  |"
                                     }
                               ));
    EXPECT_EQ(8, DigitToNumber(Digit { " _ ",
                                       "|_|",
                                       "|_|"
                                     }
                               ));
    EXPECT_EQ(9, DigitToNumber(Digit { " _ ",
                                       "|_|",
                                       " _|"
                                     }
                               ));
}

TEST(BankOCRTests, ParseDigits_000000000)
{
    DigitsDisplay nulls = { " _  _  _  _  _  _  _  _  _ ",
                            "| || || || || || || || || |",
                            "|_||_||_||_||_||_||_||_||_|"
    };
    EXPECT_STREQ("000000000", ParseDisplay(nulls).c_str());
}

TEST(BankOCRTests, ParseDigits_111111111)
{
    DigitsDisplay ones =  { "                           ",
                            "  |  |  |  |  |  |  |  |  |",
                            "  |  |  |  |  |  |  |  |  |"
    };
    EXPECT_STREQ("111111111", ParseDisplay(ones).c_str());
}
