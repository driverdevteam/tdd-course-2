# WorkShops

Workshop sessions is one of the core parts of the "Practicing TDD" course. This kind of sessions is implemented in specific way:

Group of people sit in a room with PC and projector. Two men from group peek a task from provided list and implement it in _live_ mode using ping-pong technique. Rest of group observes this process and corrects their actions if they choose a wrong path, or avoiding TDD practicies.

Pairs of programmers switch from task to task.

All workshops sessions tasks are listed below in corresponding order

## FizzBuzz

Nothing but classics. FizzBuzz is a most common kata in the world.

### Task

Write a program that prints the numbers from 1 to 100. But for multiples of three print “Fizz” instead of the number and for the multiples of five print “Buzz”. For numbers which are multiples of both three and five print “FizzBuzz “.

## Words Count

### Task

Given a phrase -> count the occurrences of each word in that phrase.

For example for the input "olly olly in come free"

```
olly: 2
in: 1
come: 1
free: 1
```

Example declaration of function required can be something like this:

```
std::map<std::string, int> WordsCount(std::string)
```

### Armstrong number 

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

### Roman numerals

Write a function to convert from normal numbers to Roman Numerals.

The Romans wrote numbers using letters - I, V, X, L, C, D, M. (converter http://www.novaroma.org/via_romana/numbers.html)

There is no need to be able to convert numbers larger than about 3000. (The Romans themselves didn't tend to go any higher)

Wikipedia says: Modern Roman numerals ... are written by expressing each digit separately starting with the left most digit and skipping any digit with a value of zero.

To see this in practice, consider the example of 1990.
In Roman numerals 1990 is MCMXC:
1000=M 900=CM 90=XC

2008 is written as MMVIII:
2000=MM 8=VIII

1998 is written as MCMXCVIII.

### Word Wrapp

Write a function, that is given a string and a length limit, splits provided string into sequence of string, where length of each string is not more, than provided limit. If there are spaces under provided limit - last space should be used to wrapp this line. If there are no spaces - wrapp it on provided length limit.

As an acceptance test you can use this input:
```
When pos is specified, the search only includes sequences of characters that begin at or before position pos, ignoring any possible match beginning after pos.
```
It should be wrapped by length of 30 into this sequence of lines (ommiting quotes):
```
"When pos is specified, the",
"search only includes sequences",
"of characters that begin at or",
"before position pos, ignoring",
"any possible match beginning",
"after pos."
```

