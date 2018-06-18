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

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <chrono>

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

class ICurrentTime
{
public:
    virtual ~ICurrentTime() {}

    virtual TimePoint Get() const = 0;
};

class MockCurrentTime: public ICurrentTime
{
public:
    MOCK_CONST_METHOD0(Get, TimePoint(void));
};

class Timer: public ITimer
{
public:
        ITimer(ICurrentTime& currentTime, Duration& duration);
        void Start();
        bool IsExpired();
        Duration TimeLeft();
private:
    Duration m_duration;
    ICurrentTime& m_currentTime;
    TimePoint m_endTime;
};

TEST(TimerTests, Start)
{
    MockCurrentTime currentTime;
    Timer timer(currentTime, 1);
    EXPECT_CALL(currentTime, GetCurrentTime()).WillOnce(testing::Return(TimePoint(Duration(123))));
    EXPECT_TRUE(timer.IsExpired());
}
