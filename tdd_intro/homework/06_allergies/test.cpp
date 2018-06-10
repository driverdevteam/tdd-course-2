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
#include <map>

/*
  - AllergyIndexTests
    - Compare allergy index with correct number
    - Compare allergy index with incorrect number
    - Compare with complex number
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

enum AllergyIndex : uint64_t
{
    AllergyIndexFirst = 0,
    AllergyIndexEggs = AllergyIndexFirst,
    AllergyIndexPeanuts,
    AllergyIndexShellfish,
    AllergyIndexStrawberries,
    AllergyIndexTomatoes,
    AllergyIndexChocolate,
    AllergyIndexPollen,
    AllergyIndexCats,
    AllergyIndexLast = AllergyIndexCats
};

static const std::map<std::string, AllergyIndex> s_allergies({
                         {"eggs", AllergyIndexEggs},
                         {"peanuts", AllergyIndexPeanuts},
                         {"shellfish", AllergyIndexShellfish},
                         {"strawberries", AllergyIndexStrawberries},
                         {"tomatoes", AllergyIndexTomatoes},
                         {"chocolate", AllergyIndexChocolate},
                         {"pollen", AllergyIndexPollen},
                         {"cats", AllergyIndexCats} });

bool HaveAllergy(uint64_t allergyScore, AllergyIndex alergyIndex)
{
    return (allergyScore & uint64_t(1) << alergyIndex) != 0;
}

using AllergiesList = std::set<std::string>;

AllergyIndex GetAllergyIndex(const std::string& allergyName)
{
    auto allergy = s_allergies.find(allergyName);

    if (allergy == s_allergies.end())
    {
        throw std::out_of_range("Allergy has no index.");
    }

    return allergy->second;
}

class PersonAllergies
{
public:
    explicit PersonAllergies(uint64_t allergyScore)
        : m_allergyScore(allergyScore)
    {}

    AllergiesList List()
    {
        AllergiesList allergiesList;

        for (auto allergy : s_allergies)
        {
            if (HaveAllergy(m_allergyScore, allergy.second))
            {
                allergiesList.insert(allergy.first);
            }
        }

        return allergiesList;
    }

    bool IsAllergicTo(const std::string& allergyName)
    {
        return HaveAllergy(m_allergyScore, GetAllergyIndex(allergyName));
    }

private:
    uint64_t m_allergyScore;
};

const uint64_t s_unexistentAllergyIndex(256);
const std::string s_tomatoes("tomatoes");
const std::string s_eggs("eggs");
const uint64_t s_tomatoesIndex(16);

TEST(HaveAllergyTests, CompareWithCorrectNumber)
{
    EXPECT_TRUE(HaveAllergy(1, AllergyIndexEggs));
}

TEST(HaveAllergyTests, CompareWithIncorrectNumber)
{
    EXPECT_FALSE(HaveAllergy(2, AllergyIndexEggs));
}

TEST(HaveAllergyTests, CompareWithComplexNumber)
{
    EXPECT_TRUE(HaveAllergy(5, AllergyIndexEggs));
    EXPECT_TRUE(HaveAllergy(5, AllergyIndexShellfish));
}

TEST(GetAllergyIndexTests, WithCorrectName)
{
    EXPECT_EQ(AllergyIndexEggs, GetAllergyIndex(s_eggs));
}

TEST(GetAllergyIndexTests, WithIncorrectName)
{
    EXPECT_THROW(GetAllergyIndex(""), std::out_of_range);
}

TEST(GetAllergyIndexTests, WithCorrectName_tomatoes)
{
    EXPECT_EQ(AllergyIndexTomatoes, GetAllergyIndex(s_tomatoes));
}

TEST(PersonAllergiesTests, UnexistentAllergy_EmptyList)
{
    PersonAllergies personAllergies(s_unexistentAllergyIndex);
    EXPECT_EQ(AllergiesList(), personAllergies.List());
}

TEST(PersonAllergiesTests, IsAllergicTo_UnexistentAllergy)
{
    PersonAllergies personAllergies(s_unexistentAllergyIndex);
    EXPECT_FALSE(personAllergies.IsAllergicTo(s_tomatoes));
}

TEST(PersonAllergiesTests, List_OneAllergy)
{
    PersonAllergies personAllergies(s_tomatoesIndex);
    EXPECT_EQ(AllergiesList({s_tomatoes}), personAllergies.List());
}

TEST(PersonAllergiesTests, List_TwoAllergy)
{
    PersonAllergies personAllergies(s_tomatoesIndex + 1);
    EXPECT_EQ(AllergiesList({s_tomatoes, s_eggs}), personAllergies.List());
}

TEST(PersonAllergiesTests, IsAllergicTo_ExistentAllergy)
{
    PersonAllergies personAllergies(s_tomatoesIndex);
    EXPECT_TRUE(personAllergies.IsAllergicTo(s_tomatoes));
}

TEST(PersonAllergiesTests, IsAllergicTo_ExistentAllergy_WrongIndex)
{
    PersonAllergies personAllergies(s_tomatoesIndex);
    EXPECT_FALSE(personAllergies.IsAllergicTo(s_eggs));
}

TEST(PersonAllergiesTests, IsAllergicTo_TwoAllergy)
{
    PersonAllergies personAllergies(s_tomatoesIndex + 1);
    EXPECT_TRUE(personAllergies.IsAllergicTo(s_tomatoes));
    EXPECT_TRUE(personAllergies.IsAllergicTo(s_eggs));
}

TEST(PersonAllergiesTests, List_ExistentAndUnexistentAllergy)
{
    PersonAllergies personAllergies(s_tomatoesIndex + s_unexistentAllergyIndex);
    EXPECT_EQ(AllergiesList({s_tomatoes}), personAllergies.List());
}
