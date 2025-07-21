#pragma once

#include "graphics/stat_window.hpp"
#include <chrono>
class Clock {
public:
    // if target_fps == -1, then ignore adjust_fps
    Clock(int target_fps);

    // updates and returns dt in sec, todo at start of game loop
    double update_dt();

    // returns dt in sec prev frame to now
    double get_dt_now() const;

    // sleeps to get target_fps as cap, ignore if target_fps==-1
    void adjust_fps(double accuracy = 0.001) const;

    // more recent fps
    double last_fps() const;

    // avg fps of last
    double avg_fps() const;

private:
    int m_target_fps;
    StatWindow<double> m_fps_stats;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_prev_frame;
};
