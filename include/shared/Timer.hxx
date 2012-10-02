#ifndef TIMER_HXX
#define TIMER_HXX
#include <boost/chrono.hpp>

typedef boost::chrono::duration<double, boost::milli> ms;
typedef boost::chrono::high_resolution_clock::time_point time_point;

class Timer {
public:
    Timer();
    virtual ~Timer() {};
    virtual void reset_delta();
    virtual double wall();
    virtual double delta();
private:
    time_point _start;
    time_point _delta_start; //lastTime;
    time_point _delta_end; // thisTime
    ms _wall;
    ms _delta;

};

#endif /* TIMER_HXX */
