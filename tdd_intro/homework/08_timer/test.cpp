/*
Timer
Implement a timer class that implements a following interface:

typedef std::chrono::high_resolution_clock Clock;
typedef Clock::duration Duration;
typedef std::chrono::time_point<Clock> TimePoint;

class ITimer {
public:
  virtual ~ITimer() {}

  virtual void Start() = 0;
  virtual bool IsExpired() const = 0;
  virtual Duration TimeLeft() const = 0;
};
Followed by this specification:

Timer allows to determine if specific period of time expired or not since Start was called last time
Timer allows to determine how much time left till period is expired
Timer can be started again any time, no metter in what state it is
*/

#include <gmock/gmock.h>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef Clock::duration Duration;
typedef std::chrono::time_point<Clock> TimePoint;

class ITimer
{
public:
  virtual ~ITimer() {}

  virtual void Start() = 0;
  virtual bool IsExpired() const = 0;
  virtual Duration TimeLeft() const = 0;
};

class ICurrentTime
{
public:
    virtual ~ICurrentTime() {}

    virtual TimePoint Get() const = 0;
};

class Timer : public ITimer
{
public:
    Timer(ICurrentTime* currentTime, const Duration& duration)
        : m_currentTime(currentTime)
        , m_duration(duration)
        , m_endTime(Duration(0))
    {}

    virtual void Start() override
    {
        m_endTime = m_currentTime->Get() + m_duration;
    }

    virtual bool IsExpired() const override
    {
        if (m_endTime < m_currentTime->Get())
        {
            return true;
        }

        return false;
    }

    virtual Duration TimeLeft() const override
    {
        return Duration(m_endTime - m_currentTime->Get());
    }

private:
    Duration m_duration;
    ICurrentTime* m_currentTime;
    TimePoint m_endTime;
};

class MockCurrentTime : public ICurrentTime
{
public:
    MOCK_CONST_METHOD0(Get, TimePoint());
};

void GetTimeCallForIsExpired(MockCurrentTime& currentTime)
{
    EXPECT_CALL(currentTime, Get())
            .WillOnce(testing::Return(TimePoint(Duration(123))))
            .WillOnce(testing::Return(TimePoint(Duration(321))));
}

TEST(TimerTests, IsExpired_NotStarted)
{
    MockCurrentTime currentTime;
    EXPECT_CALL(currentTime, Get())
            .WillOnce(testing::Return(TimePoint(Duration(123))));

    Timer timer(&currentTime, Duration(0));
    EXPECT_TRUE(timer.IsExpired());
}

TEST(TimerTests, IsExpired_StartedLong)
{
    MockCurrentTime currentTime;
    GetTimeCallForIsExpired(currentTime);

    Timer timer(&currentTime, Duration(10000000));
    timer.Start();
    EXPECT_FALSE(timer.IsExpired());
}

TEST(TimerTests, IsExpired_Expired)
{
    MockCurrentTime currentTime;
    GetTimeCallForIsExpired(currentTime);

    Timer timer(&currentTime, Duration(100));
    timer.Start();
    EXPECT_TRUE(timer.IsExpired());
}

TEST(TimerTests, TimeLeft_StartedNotExpired)
{
    MockCurrentTime currentTime;
    GetTimeCallForIsExpired(currentTime);

    Timer timer(&currentTime, Duration(1000));
    timer.Start();
    EXPECT_EQ(Duration(802), timer.TimeLeft());
}
