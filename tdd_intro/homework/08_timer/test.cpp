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

    virtual TimePoint Get() const;
};

class Timer : ITimer
{
public:
    Timer()
    {}

    virtual void Start() override
    {

    }

    virtual bool IsExpired() const override
    {
        return true;
    }

    virtual Duration TimeLeft() const override
    {
      return Duration();
    }
};

class CurrentTime : ICurrentTime
{
public:
    MOCK_CONST_METHOD0(Get, TimePoint());
};

TEST(TimerTests, IsExpired_NotStarted)
{
    Timer timer;
    EXPECT_TRUE(timer.IsExpired());
}

TEST(TimerTests, IsExpired_StartedLong)
{
    Timer timer(Duration(10000000));
    timer.Start();
    EXPECT_FALSE(timer.IsExpired());
}
