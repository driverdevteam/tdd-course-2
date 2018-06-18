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

class ICurrentTime
{
public:
    virtual ~ICurrentTime() {}

    virtual TimePoint GetCurrentTime() const = 0;
};

class ITimer {
public:
  virtual ~ITimer(){}
  virtual void Start() = 0;
  virtual bool IsExpired() const = 0;
  virtual Duration TimeLeft() const = 0;

};


class MockCurrentTime: public ICurrentTime
{
public:
    MOCK_CONST_METHOD0(GetCurrentTime, TimePoint(void));
};

class Timer: public ITimer
{
public:
        Timer(ICurrentTime& currentTime, Duration& duration);
        void Start();
        bool IsExpired()const ;
        Duration TimeLeft()const;
private:
    Duration m_duration;
    ICurrentTime& m_currentTime;
    TimePoint m_endTime;
};

Timer::Timer(ICurrentTime &currentTime, Duration &duration)
    :m_duration(duration)
    , m_currentTime(currentTime)
    , m_endTime(Duration(0))
{

}

void Timer::Start()
{
     m_endTime = m_currentTime.GetCurrentTime() + m_duration;
}

bool Timer::IsExpired() const
{
    if (m_endTime < m_currentTime.GetCurrentTime())
    {
        return true;
    }

    return false;
}

Duration Timer::TimeLeft() const
{
    TimePoint currentTime(m_currentTime.GetCurrentTime());
    if (m_endTime < currentTime)
    {
        return Duration(0);
    }
    return Duration(m_endTime - currentTime);
}

TEST(TimerTests, Start)
{
    MockCurrentTime currentTime;
    EXPECT_CALL(currentTime, GetCurrentTime()).WillRepeatedly(testing::Return(TimePoint(Duration(100))));

    Timer timer(currentTime, Duration(0));

    timer.Start();
    EXPECT_FALSE(timer.IsExpired());
}

TEST(TimerTests, TimeLeft)
{
     MockCurrentTime currentTime;
     EXPECT_CALL(currentTime, GetCurrentTime()).WillRepeatedly(testing::Return(TimePoint(Duration(1000))));
     Timer timer(currentTime, Duration(0));
     timer.Start();
     EXPECT_EQ(Duration(0), timer.TimeLeft());
}

TEST(TimerTests, Restart)
{
    MockCurrentTime currentTime;
    EXPECT_CALL(currentTime, GetCurrentTime())
                .WillOnce(testing::Return(TimePoint(Duration(12))))
                .WillOnce(testing::Return(TimePoint(Duration(40))));

    Timer timer(currentTime, Duration(100));
    timer.Start();
    timer.Start();

    EXPECT_CALL(currentTime, GetCurrentTime())
            .WillOnce(testing::Return(TimePoint(Duration(100))));

    EXPECT_FALSE(timer.IsExpired());
}

