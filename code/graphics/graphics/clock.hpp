#pragma once

#include <chrono>
class Clock {
public:
    // if target_fps == -1, then ignore adjust_fps
    Clock(int target_fps, int stat_window = 1);

    // updates and returns dt in sec, todo at start of game loop
    double update_dt();

    // returns dt in sec but does not change prev frame
    double get_dt() const;

    // sleeps to get target_fps as cap, ignore if target_fps==-1
    void adjust_fps() const;

    // avg fps of last
    double get_fps() const;

private:
    int m_target_fps;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_prev_frame;
};
