#pragma once

#include <chrono>
class Clock {
public:
    Clock(int target_fps);

    // updates and returns dt in sec, todo at start of game loop
    double update_dt();

    // returns in sec
    double get_dt() const;

private:
    int m_target_fps;
    double m_dt;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_prev_frame;
};
