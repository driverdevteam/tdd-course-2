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
    {}

    virtual void Start() override
    {

    }

    virtual bool IsExpired() const override
    {
        if (m_duration.count() != 0)
        {
            return false;
        }
        return true;
    }

    virtual Duration TimeLeft() const override
    {
      return Duration();
    }

private:
    Duration m_duration;
    ICurrentTime* m_currentTime;
};

class MockCurrentTime : public ICurrentTime
{
public:
    MOCK_CONST_METHOD0(Get, TimePoint());
};

TEST(TimerTests, IsExpired_NotStarted)
{
    MockCurrentTime currentTime;
    Timer timer(&currentTime, Duration(0));
    EXPECT_TRUE(timer.IsExpired());
}

TEST(TimerTests, IsExpired_StartedLong)
{
    MockCurrentTime currentTime;
    Timer timer(&currentTime, Duration(10000000));
    timer.Start();
    EXPECT_FALSE(timer.IsExpired());
}

TEST(TimerTests, IsExpired_Expired)
{
    MockCurrentTime currentTime;

    EXPECT_CALL(currentTime, Get())
            .WillOnce(testing::Return(TimePoint(Duration(123))))
            .WillOnce(testing::Return(TimePoint(Duration(321))));

    Timer timer(&currentTime, Duration(100));
    timer.Start();
    EXPECT_TRUE(timer.IsExpired());
}
