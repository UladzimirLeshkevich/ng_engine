//#pragma once
#include <chrono>

class timer
{
public:
    timer();
    void   reset();
    double elapsed() const;
//=======================================================
void start_timer()
{
    start = clock_t::now();
}

void frame_begin()
{
    end_last_frame = clock_t::now();
}

void frame_end()
{
    start = end_last_frame;
}

float get_delta_time()
{
    return  (std::chrono::duration_cast<milli_sec>(end_last_frame - start)).count();
} 

std::chrono::milliseconds calc_delta_time_duration()
{
    return  (std::chrono::duration_cast<milli_sec>(end_last_frame - start));
    //return frame_delta.count();
    //return std::chrono::duration_cast<second_f>(end_last_frame - start).count();
} 

private:
    using clock_t  = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1>>;
    using second_f = std::chrono::duration<float, std::ratio<1>>;

    std::chrono::time_point<clock_t> m_beg;

    // from OM
    using clock_timer = std::chrono::high_resolution_clock;
    using nano_sec    = std::chrono::nanoseconds;
    using milli_sec   = std::chrono::milliseconds;
    using time_point  = std::chrono::time_point<clock_timer, nano_sec>;

    time_point  start;
    time_point end_last_frame;
};
