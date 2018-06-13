/*
We have several coffee machines. We have to create class which makes a coffee.
class ICoffeCore
{
public:
    ~ICoffeCore(){}
    virtual void SetCupSize(int gram) = 0;
    virtual void AddWater(int gram, int temperature) = 0;
    virtual void AddSugar(int gram) = 0;
    virtual void AddCoffee(int gram) = 0;
    virtual void AddMilk(int gram) = 0;
    virtual void AddMilkFoam(int gram) = 0;
    virtual void AddChocolate(int gram) = 0;
    virtual void AddCream(int gram) = 0;
};

We produce:
- americano: water & coffee 1:2 or 1:3. Water temp 60C
- cappuccino - milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
- latte - milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
- marochino - chocolate & coffee & milk foam, 1:4, 1:4, 1:4 and 1:4 is empty

We have 2 size of cup, it is:
- little 100 gram
- big 140 gram
*/

// 1. test cup creation of the certain size
// 2. test adding the water (weight and temperature)
// 3. test americano
// 4. test cappuccino
// 5. test latte
// (optional) 6. test marochino

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class ICoffeCore
{
public:
    ~ICoffeCore(){}
    virtual void AddWater(int gram, int temperature) = 0;
    virtual void AddSugar(int gram) = 0;
    virtual void AddCoffee(int gram) = 0;
    virtual void AddMilk(int gram) = 0;
    virtual void AddMilkFoam(int gram) = 0;
    virtual void AddChocolate(int gram) = 0;
    virtual void AddCream(int gram) = 0;
};

class CoffeeCoreMock : public ICoffeCore
{
public:
    MOCK_METHOD2(AddWater, void(int, int));
    MOCK_METHOD1(AddSugar, void(int));
    MOCK_METHOD1(AddCoffee, void(int));
    MOCK_METHOD1(AddMilk, void(int));
    MOCK_METHOD1(AddMilkFoam, void(int));
    MOCK_METHOD1(AddChocolate, void(int));
    MOCK_METHOD1(AddCream, void(int));
};

enum CupSize
{
    CupSizeInvalid = 0,
    CupSizeLittle = 100,
    CupSizeBig = 140
};

enum Component
{
    Watter,
    Sugar,
    Coffee,
    Milk,
    MilkFloam,
    Chocolate,
    Cream
};

class CoffeeMachine
{
public:
    CoffeeMachine(ICoffeCore& core);

    void CreateLittleCup();
    void CreateBigCup();
    void CreateHotWaterCup();
    void CreateAmericano();
    void CreateCappuccino();

private:
    void CheckCup();
    void AddComponent(Component component, int size);

private:
    ICoffeCore& m_core;
    CupSize m_size;
    int m_freeSpaceInCup;
    int m_waterTemperature;
};

CoffeeMachine::CoffeeMachine(ICoffeCore& core)
    : m_core(core),
      m_freeSpaceInCup(CupSizeInvalid),
      m_size(CupSizeInvalid)
{
}

void CoffeeMachine::CreateLittleCup()
{
    m_size = CupSizeLittle;
    m_freeSpaceInCup = m_size;
}

void CoffeeMachine::CreateBigCup()
{
    m_size = CupSizeBig;
    m_freeSpaceInCup = m_size;
}

void CoffeeMachine::CreateHotWaterCup()
{
    CheckCup();

    m_waterTemperature = 95;
    AddComponent(Watter, m_size);
}

void CoffeeMachine::CreateAmericano()
{
    CheckCup();

    m_waterTemperature = 60;
    AddComponent(Watter, m_size / 2);
    AddComponent(Coffee, m_size / 2);
}

void CoffeeMachine::CreateCappuccino()
{
    CheckCup();

    m_waterTemperature = 80;
    AddComponent(Watter, m_freeSpaceInCup / 4);
    AddComponent(Milk, m_freeSpaceInCup / 4);
    AddComponent(Coffee, m_freeSpaceInCup / 4);
    AddComponent(MilkFloam, m_freeSpaceInCup / 4);
}

void CoffeeMachine::CheckCup()
{
    if(m_freeSpaceInCup == CupSizeInvalid)
    {
        throw std::runtime_error("cap is empty");
    }
}

void CoffeeMachine::AddComponent(Component component, int size)
{
    if (m_freeSpaceInCup < size)
    {
        throw std::runtime_error("overflow");
    }

    switch (component)
    {
    case Watter:
        m_core.AddWater(size, m_waterTemperature);
        break;

    case Coffee:
        m_core.AddCoffee(size);
        break;

    case Milk:
        m_core.AddMilk(size);
        break;

    case MilkFloam:
        m_core.AddMilkFoam(size);
        break;

    default:
        throw std::runtime_error("unexpected component");
    }

    m_freeSpaceInCup -= size;
}

TEST(CoffeCoretest, CreateHotWater)
{
    CoffeeCoreMock mock;
    CoffeeMachine machine(mock);

    EXPECT_CALL(mock, AddWater(CupSizeBig, 95)).Times(1);
    machine.CreateBigCup();
    machine.CreateHotWaterCup();
}

// FIX: sequence
//- americano: water & coffee 1:2 or 1:3. Water temp 60C
TEST(CoffeCoretest, CreateAmericanoBig)
{
    CoffeeCoreMock mock;
    CoffeeMachine machine(mock);

    testing::InSequence seq;
    EXPECT_CALL(mock, AddWater(CupSizeBig / 2, 60)).Times(1);
    EXPECT_CALL(mock, AddCoffee(CupSizeBig / 2)).Times(1);
    machine.CreateBigCup();
    machine.CreateAmericano();
}

TEST(CoffeCoretest, CreateAmericanoLittle)
{
    CoffeeCoreMock mock;
    CoffeeMachine machine(mock);

    EXPECT_CALL(mock, AddWater(CupSizeLittle / 2, 60)).Times(1);
    EXPECT_CALL(mock, AddCoffee(CupSizeLittle / 2)).Times(1);
    machine.CreateLittleCup();
    machine.CreateAmericano();
}

TEST(CoffeCoretest, CreateAmericanoLittle_NoCup)
{
    CoffeeCoreMock mock;
    CoffeeMachine machine(mock);

    EXPECT_CALL(mock, AddWater(testing::_, testing::_)).Times(0);
    EXPECT_CALL(mock, AddCoffee(testing::_)).Times(0);

    EXPECT_THROW(machine.CreateAmericano(), std::runtime_error);
}

TEST(CoffeCoretest, CreateCappuccinooLittle)
{
    CoffeeCoreMock mock;
    CoffeeMachine machine(mock);

    testing::InSequence seq;
    EXPECT_CALL(mock, AddWater(CupSizeLittle / 4, 80)).Times(1);
    EXPECT_CALL(mock, AddMilk(CupSizeLittle / 4)).Times(1);
    EXPECT_CALL(mock, AddCoffee(CupSizeLittle / 4)).Times(1);
    EXPECT_CALL(mock, AddMilkFoam(CupSizeLittle / 4)).Times(1);
    machine.CreateLittleCup();
    machine.CreateCappuccino();
}

TEST(CoffeCoretest, CreateCappuccinoo_NoCup)
{
    CoffeeCoreMock mock;
    CoffeeMachine machine(mock);

    testing::InSequence seq;
    EXPECT_CALL(mock, AddWater(testing::_, testing::_)).Times(0);
    EXPECT_CALL(mock, AddMilk(testing::_)).Times(0);
    EXPECT_CALL(mock, AddCoffee(testing::_)).Times(0);
    EXPECT_CALL(mock, AddMilkFoam(testing::_)).Times(0);

    EXPECT_THROW(machine.CreateCappuccino(), std::runtime_error);
}

TEST(CoffeCoretest, Overflow)
{
    CoffeeCoreMock mock;
    CoffeeMachine machine(mock);

    machine.CreateBigCup();
    machine.CreateAmericano();
    EXPECT_THROW(machine.CreateAmericano(), std::runtime_error);
}
// add other tests
