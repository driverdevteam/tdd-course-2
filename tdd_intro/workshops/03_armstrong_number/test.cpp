/*
An Armstrong number is a number that is the sum of its own digits each raised to the power of the number of digits.

For example:

9 is an Armstrong number, because 9 = 9^1 = 9
10 is not an Armstrong number, because 10 != 1^2 + 0^2 = 1
153 is an Armstrong number, because: 153 = 1^3 + 5^3 + 3^3 = 1 + 125 + 27 = 153
154 is not an Armstrong number, because: 154 != 1^3 + 5^3 + 4^3 = 1 + 125 + 64 = 190
9474 is an Armstrong number

Write some code to determine whether a number is an Armstrong number.

Acceptance test
5 - true
100 - false
9475 - false
9926315 - true
9926314 - false

_from http://exercism.io/_
*/
#include <gtest/gtest.h>
