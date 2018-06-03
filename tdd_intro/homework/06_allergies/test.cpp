/*
Given a person's allergy score, determine whether or not they're allergic to a given item, and their full list of allergies.
An allergy test produces a single numeric score which contains the information about all the allergies the person has (that they were tested for).
The list of items (and their value) that were tested are:
    eggs (1)
    peanuts (2)
    shellfish (4)
    strawberries (8)
    tomatoes (16)
    chocolate (32)
    pollen (64)
    cats (128)
So if Tom is allergic to peanuts and chocolate, he gets a score of 34.

Now, given just that score of 34, your program should be able:
    To say have Tom allergic to specific product or not.
    To give list of all allergens Tom is allergic to.

E.g. it can be class with methods IsAllergicTo(string), List() and receiving allergyScore in constructor
	
Note: a given score may include allergens not listed above (i.e. allergens that score 256, 512, 1024, etc.).
Your program should ignore those components of the score.
For example, if the allergy score is 257, your program should only report the eggs (1) allergy.
*/
#include <gtest/gtest.h>

/*
  - AllergyIndexTests
    - Compare allergy index with correct number
    - Compare allergy index with incorrect number
  - AllergyNameTests
    - Find allergy index for correct name
    - Throw exceprion for incorrect name
  - PersonAllergiesTests
    - check with unexistent allergy
      - List() returns empty list
      - IsAllergicTo() returns false
    - check with one allergy
      - List() returns name of allergy
      - IsAllergicTo() returns true if allergy score = index of allergy name
      - IsAllergicTo() returns false if allergy score != index of allergy name
    - check with two allergies
      - List() returns names of allergies
      - IsAllergicTo() returns true if allergy score contains index of allergy name
      - IsAllergicTo() returns false if allergy score not contains index of allergy name
    - check with existent and unexistent allergies
      - List() returns name of existent allergy
*/
