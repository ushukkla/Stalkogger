#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <chrono>

class Timer
{   
    std::thread Thread; 
    bool Alive = false;
    long CallNumber = -1L;  
    long repeat_count = -1L;    
    std::chrono::milliseconds interval = std::chrono::milliseconds(0);  
    std::function<void(void)> funct = nullptr;

    void SleepAndRun()
    {
        std::this_thread::sleep_for(interval);  
        if(Alive)
            Function()(); 
    }
    
    void ThreadFunc()
    {
        if(CallNumber == Infinite)
            while(Alive) SleepAndRun();
        else
            while(repeat_count--) SleepAndRun();
    }

public:
    static const long Infinite = -1L;
    // our constructors
    Timer(){}
    // this constructors accepts a reference to a constant function object
    Timer(const std::function<void(void)> &f) : funct(f) {}
    // this one will have more parameters
    Timer(const std::function<void(void)> &f, const unsigned long &i, const long repeat = Timer::Infinite) : funct(f), interval(std::chrono::milliseconds(i)), CallNumber(repeat) {}
    // method for starting the timer
    void Start(bool Async = true)
    {
        if(IsAlive())
            return;
        Alive = true;
        repeat_count = CallNumber;
        if(Async)
            Thread = std::thread(ThreadFunc, this); 
        else
            ThreadFunc();   // he has this->ThreadFunct();
    }
    // method for stopping the timer
    void Stop()
    {
        Alive = false;
        Thread.join();
    }
    // setters and getters
    void SetFunction(const std::function<void(void)> &f)  // for when we use the empty constructor
    {
        funct = f;
    }
    bool IsAlive() const
    {
        return Alive;
    }
    void RepeatCount(const long r)
    {
        if(Alive)
            return;
        CallNumber = r;
    }
    long GetLeftCount() const   // to know how many iterations are left
    {
        return repeat_count;
    }
    long RepeatCount() const    // get the total number of repeatances
    {
        return CallNumber;
    }
    void SetInterval(const unsigned long &i)
    {
        if(Alive)
            return;
        interval = std::chrono::milliseconds(i);
    }
    unsigned long Interval() const
    {
        return interval.count();     }
    const std::function<void(void)> &Function() const
    {
        return funct;
    }
};

#endif 
