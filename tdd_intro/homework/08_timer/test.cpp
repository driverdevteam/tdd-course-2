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
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef Clock::duration Duration;
typedef std::chrono::time_point<Clock> TimePoint;

class ITimer {
public:
  virtual ~ITimer() {}

  virtual void Start(int64_t millis) = 0;
  virtual bool IsExpired() const = 0;
  virtual Duration TimeLeft() const = 0;
};

class ICurrentTime {
public:
    virtual ~ICurrentTime() {}

    virtual void Reset() = 0;
    virtual void AddTime(int64_t millis) = 0;
};

class CurrentTime : public ICurrentTime {
public:
    void Reset() override;
    void AddTime(int64_t millis) override;
private:
    TimePoint m_time;
};

class Timer : public ITimer
{
public:
    Timer(CurrentTime& currentTime)
        : m_currentTime(currentTime)
    {
    }

    void Start(int64_t millis) override;
    bool IsExpired() const override;
    Duration TimeLeft() const override;
private:
    CurrentTime& m_currentTime;
};

void Timer::Start(int64_t millis)
{
}

bool Timer::IsExpired() const
{
    return false;
}

Duration Timer::TimeLeft() const
{
    return Duration();
}

TEST(Timer, IsExpired_NotExpired)
{
    CurrentTime currentTime;
    Timer timer(currentTime);

    const int64_t aLotOfTime = 5000;

    timer.Start(aLotOfTime);
    EXPECT_FALSE(timer.IsExpired());
}

TEST(Timer, IsExpired_Expired)
{
    CurrentTime currentTime;
    Timer timer(currentTime);

    const int64_t timeForTimer = 2000;
    const int64_t timeToGo = 3000;

    timer.Start(timeForTimer);
    currentTime.AddTime(timeToGo);

    EXPECT_TRUE(timer.IsExpired());
}
