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

  virtual void Start(int64_t nanos) = 0;
  virtual bool IsExpired() const = 0;
  virtual Duration TimeLeft() const = 0;
};

class ICurrentTime {
public:
    virtual ~ICurrentTime() {}

    virtual void Reset() = 0;
    virtual void AddTime(int64_t nanos) = 0;
    virtual TimePoint GetTime() const = 0;
};

class CurrentTime : public ICurrentTime {
public:
    void Reset() override;
    void AddTime(int64_t nanos) override;
    TimePoint GetTime() const override;
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

    void Start(int64_t nanos) override;
    bool IsExpired() const override;
    Duration TimeLeft() const override;
private:
    CurrentTime& m_currentTime;
    TimePoint m_expirationTime;
};

void Timer::Start(int64_t nanos)
{
    m_currentTime.Reset();
    m_expirationTime = m_currentTime.GetTime() + Duration(nanos);
}

bool Timer::IsExpired() const
{
    return m_currentTime.GetTime() > m_expirationTime;
}

Duration Timer::TimeLeft() const
{
    if (IsExpired())
    {
        return Duration(0);
    }

    return m_expirationTime - m_currentTime.GetTime();
}

void CurrentTime::Reset()
{
    m_time = Clock::now();
}

void CurrentTime::AddTime(int64_t nanos)
{
    m_time += Duration(nanos);
}

TimePoint CurrentTime::GetTime() const
{
    return m_time;
}

TEST(Timer, IsExpired_TimeNotChanged)
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

TEST(Timer, IsExpired_NotExpired)
{
    CurrentTime currentTime;
    Timer timer(currentTime);

    const int64_t timeForTimer = 2000;
    const int64_t timeToGo = 1000;

    timer.Start(timeForTimer);
    currentTime.AddTime(timeToGo);

    EXPECT_FALSE(timer.IsExpired());
}

TEST(Timer, AtLimit_NotExpired)
{
    CurrentTime currentTime;
    Timer timer(currentTime);

    const int64_t timeForTimer = 2000;
    const int64_t timeToGo = 2000;

    timer.Start(timeForTimer);
    currentTime.AddTime(timeToGo);

    EXPECT_FALSE(timer.IsExpired());
}

TEST(Timer, TimeLeft_WholeTimeLeft)
{
    CurrentTime currentTime;
    Timer timer(currentTime);

    const int64_t timeForTimer = 2000;

    timer.Start(timeForTimer);

    EXPECT_EQ(Duration(timeForTimer), timer.TimeLeft());
}

TEST(Timer, TimeLeft_SomeTimeLeft)
{
    CurrentTime currentTime;
    Timer timer(currentTime);

    const int64_t timeForTimer = 2000;
    const int64_t timeToGo = 1000;

    timer.Start(timeForTimer);
    currentTime.AddTime(timeToGo);

    EXPECT_EQ(Duration(timeForTimer - timeToGo), timer.TimeLeft());
}

TEST(Timer, TimeLeft_Expired)
{
    CurrentTime currentTime;
    Timer timer(currentTime);

    const int64_t timeForTimer = 1000;
    const int64_t timeToGo = 2000;

    timer.Start(timeForTimer);
    currentTime.AddTime(timeToGo);

    EXPECT_EQ(Duration(0), timer.TimeLeft());
}

TEST(Timer, TimeLeft_NoTimeLeft)
{
    CurrentTime currentTime;
    Timer timer(currentTime);

    const int64_t timeForTimer = 2000;
    const int64_t timeToGo = 2000;

    timer.Start(timeForTimer);
    currentTime.AddTime(timeToGo);

    EXPECT_EQ(Duration(0), timer.TimeLeft());
}
