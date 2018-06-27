/*
Say in C++
Given a number from 0 to 99,999, spell out that number in English.

Step 1
Handle the basic case of 0 through 99.

If the input to the program is 22, then the output should be 'twenty-two'.

Your program should complain loudly if given a number outside the blessed range.

Some good test cases for this program are:

0
14
50
98
-1
100
Step 2
Put it all together to get nothing but plain English.

12345 should give twelve thousand three hundred forty-five.

The program must also report any values that are out of range.

Extensions
Use and (correctly) when spelling out the number in English:

14 becomes "fourteen".
100 becomes "one hundred".
120 becomes "one hundred and twenty".
1002 becomes "one thousand and two".
1323 becomes "one thousand three hundred and twenty-three".
*/

#include <gtest/gtest.h>
