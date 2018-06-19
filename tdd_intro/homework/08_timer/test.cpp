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
//    virtual Duration TimeLeft() const = 0;
};

template <typename TClock>
class Timer : public ITimer {
public:
    Timer(TClock clock);

    virtual void Start(int periodSec) override;
    virtual bool IsExpired() const override;
//    virtual Duration TimeLeft() override;

private:
    TClock m_clock;
    int m_periodSec;
    TimePoint m_startPoint;
};

template<typename TClock>
Timer<TClock>::Timer(TClock clock)
{

}

template<typename TClock>
void Timer<TClock>::Start(int periodSec)
{

}

template<typename TClock>
bool Timer<TClock>::IsExpired() const
{
    return false;
}

//template<typename TClock>
//Duration Timer<TClock>::TimeLeft()
//{

//}

class MocClock
{
public:
    MocClock();

    TimePoint now();

private:
    TimePoint m_timePoint;
};

MocClock::MocClock()
{

}

TimePoint MocClock::now()
{
    return m_timePoint;
}


TEST (TimerTest, IsExpired_return_false)
{
    MocClock moc;
    Timer<MocClock> timer = Timer<MocClock>(moc);
    timer.Start(10);

    EXPECT_FALSE(timer.IsExpired());
}





