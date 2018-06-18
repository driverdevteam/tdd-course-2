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
    virtual void AddMilk(int gram, int temperature) = 0;
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
    MOCK_METHOD2(AddMilk, void(int, int));
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

class CoffeeMachine
{
public:
    CoffeeMachine(ICoffeCore& core);

    void CreateLittleCup();
    void CreateBigCup();
    void CreateHotWaterCup();
    void CreateAmericano();
    void CreateCappuccino();
    void CreateLatte();
private:
    ICoffeCore& m_core;
    CupSize m_size;
};

CoffeeMachine::CoffeeMachine(ICoffeCore& core)
    : m_core(core),
      m_size(CupSizeInvalid)
{
}

void CoffeeMachine::CreateLittleCup()
{
    m_size = CupSizeLittle;
}

void CoffeeMachine::CreateBigCup()
{
    m_size = CupSizeBig;
}

void CoffeeMachine::CreateHotWaterCup()
{
    m_core.AddWater(CupSizeBig, 95);
}

void CoffeeMachine::CreateAmericano()
{
    if(m_size == CupSizeInvalid)
    {
        throw std::runtime_error("cap is empty");
    }
    m_core.AddWater(m_size / 3, 60);
    m_core.AddCoffee((2*m_size) / 3);
}

void CoffeeMachine::CreateCappuccino()
{
    if(m_size == CupSizeInvalid)
    {
        throw std::runtime_error("cap is empty");
    }
    m_core.AddMilk(m_size / 3, 80);
    m_core.AddCoffee(m_size / 3);
    m_core.AddMilkFoam(m_size / 3);
}

void CoffeeMachine::CreateLatte()
{
    if(m_size == CupSizeInvalid)
    {
        throw std::runtime_error("cap is empty");
    }
    m_core.AddMilk(m_size / 4, 90);
    m_core.AddCoffee(m_size / 2);
    m_core.AddMilkFoam(m_size / 4);
}

TEST(CoffeCoretest, CreateHotWater)
{
    CoffeeCoreMock mock;
    CoffeeMachine machine(mock);

    EXPECT_CALL(mock, AddWater(CupSizeBig, 95)).Times(1);
    machine.CreateBigCup();
    machine.CreateHotWaterCup();
}

TEST(CoffeCoretest, CreateAmericanoBig)
{
    CoffeeCoreMock mock;
    CoffeeMachine machine(mock);

    EXPECT_CALL(mock, AddWater(CupSizeBig / 3, 60)).Times(1);
    EXPECT_CALL(mock, AddCoffee((2*CupSizeBig) / 3)).Times(1);
    machine.CreateBigCup();
    machine.CreateAmericano();
}

TEST(CoffeCoretest, CreateAmericanoLittle)
{
    CoffeeCoreMock mock;
    CoffeeMachine machine(mock);

    EXPECT_CALL(mock, AddWater(CupSizeLittle / 3, 60)).Times(1);
    EXPECT_CALL(mock, AddCoffee((2*CupSizeLittle) / 3)).Times(1);
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

TEST(CoffeCoretest, CreateCappuccinoBig)
{
    CoffeeCoreMock mock;
    CoffeeMachine machine(mock);

    EXPECT_CALL(mock, AddMilk(CupSizeBig / 3, 80)).Times(1);
    EXPECT_CALL(mock, AddCoffee(CupSizeBig / 3)).Times(1);
    EXPECT_CALL(mock, AddMilkFoam(CupSizeBig / 3)).Times(1);
    machine.CreateBigCup();
    machine.CreateCappuccino();
}

TEST(CoffeCoretest, CreateCappuccinoLittle)
{
    CoffeeCoreMock mock;
    CoffeeMachine machine(mock);

    EXPECT_CALL(mock, AddMilk(CupSizeLittle / 3, 80)).Times(1);
    EXPECT_CALL(mock, AddCoffee(CupSizeLittle / 3)).Times(1);
    EXPECT_CALL(mock, AddMilkFoam(CupSizeLittle / 3)).Times(1);
    machine.CreateLittleCup();
    machine.CreateCappuccino();
}

TEST(CoffeCoretest, CreateLatteBig)
{
    CoffeeCoreMock mock;
    CoffeeMachine machine(mock);

    EXPECT_CALL(mock, AddMilk(CupSizeBig / 4, 90)).Times(1);
    EXPECT_CALL(mock, AddCoffee(CupSizeBig / 2)).Times(1);
    EXPECT_CALL(mock, AddMilkFoam(CupSizeBig / 4)).Times(1);
    machine.CreateBigCup();
    machine.CreateLatte();
}
