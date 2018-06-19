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

//1. Check period expired
//2. Check period the period not expired
//3. Check time left
//4. Check previous items after Start while timer is running

#include <gtest/gtest.h>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef Clock::duration Duration;
typedef std::chrono::time_point<Clock> TimePoint;

class ITimer {
public:
    virtual ~ITimer() {}

    virtual void Start(int periodSec) = 0;
    virtual bool IsExpired() const = 0;
    virtual Duration TimeLeft() const = 0;
};

template <typename TClock>
class Timer : public ITimer {
public:
    Timer(TClock* clock);

    virtual void Start(int periodSec) override;
    virtual bool IsExpired() const override;
    virtual Duration TimeLeft() const override;

private:
    TClock* m_clock;
    Duration m_duration;
    TimePoint m_startPoint;
};

template<typename TClock>
Timer<TClock>::Timer(TClock* clock)
    : m_clock(clock)
{

}

template<typename TClock>
void Timer<TClock>::Start(int periodSec)
{
    m_duration = Duration(std::chrono::seconds(periodSec));
    m_startPoint = m_clock->now();
}

template<typename TClock>
bool Timer<TClock>::IsExpired() const
{
    return m_clock->now() - m_startPoint >= m_duration;
}

template<typename TClock>
Duration Timer<TClock>::TimeLeft() const
{
    return Duration(std::chrono::seconds(10));
}

class MocClock
{
public:
    MocClock();

    TimePoint now() const;
    void Rewind(int sec);

private:
    TimePoint m_timePoint;
};

MocClock::MocClock()
{
}

TimePoint MocClock::now() const
{
    return m_timePoint;
}

void MocClock::Rewind(int sec)
{
    m_timePoint += std::chrono::seconds(sec);
}


TEST (TimerTest, IsExpired_return_false)
{
    MocClock moc;
    Timer<MocClock> timer = Timer<MocClock>(&moc);
    timer.Start(10);

    EXPECT_FALSE(timer.IsExpired());
}

TEST (TimerTest, IsExpired_return_true)
{
    MocClock moc;
    Timer<MocClock> timer = Timer<MocClock>(&moc);
    timer.Start(10);

    moc.Rewind(10);
    EXPECT_TRUE(timer.IsExpired());
}

TEST (TimerTest, TimeLeft_return_10)
{
    MocClock moc;
    Timer<MocClock> timer = Timer<MocClock>(&moc);
    timer.Start(10);

    EXPECT_EQ(10, std::chrono::duration_cast<std::chrono::seconds>(timer.TimeLeft()).count());
}

TEST (TimerTest, TimeLeft_return_0)
{
    MocClock moc;
    Timer<MocClock> timer = Timer<MocClock>(&moc);
    timer.Start(10);

    moc.Rewind(10);
    EXPECT_EQ(0, std::chrono::duration_cast<std::chrono::seconds>(timer.TimeLeft()).count());
}

