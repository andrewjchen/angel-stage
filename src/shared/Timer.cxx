#include "Timer.hxx"
Timer::Timer () {
    _start = boost::chrono::high_resolution_clock::now();
    _delta_start = boost::chrono::high_resolution_clock::now();
    _delta_end = boost::chrono::high_resolution_clock::now();
    _wall = (_start - boost::chrono::high_resolution_clock::now());
    _delta = (_delta_end - _delta_start);
}

void Timer::reset_delta() {
    // _wall = boost::chrono::duration_cast<ms>(_start - boost::chrono::high_resolution_clock::now())
    _wall = (boost::chrono::high_resolution_clock::now() - _start);
    _delta_start = _delta_end;
    _delta_end = boost::chrono::high_resolution_clock::now();
    _delta = (_delta_end - _delta_start);
}

double Timer::wall() {
    return _wall.count();
}

double Timer::delta() {
    return _delta.count();
}
