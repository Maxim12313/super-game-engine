#include "clock.hpp"
#include <chrono>
#include <thread>

Clock::Clock(int target_fps, int stat_window)
    : m_prev_frame(std::chrono::high_resolution_clock::now()) {
}

double Clock::update_dt() {
    auto curr_frame = std::chrono::high_resolution_clock::now();
    auto duration = curr_frame - m_prev_frame;
    int ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    m_prev_frame = curr_frame;
    return ms / 1000.0;
}

double Clock::get_dt() const {
    auto curr_frame = std::chrono::high_resolution_clock::now();
    auto duration = curr_frame - m_prev_frame;
    int ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    return ms / 1000.0;
}

void Clock::adjust_fps() const {
    if (m_target_fps == -1)
        return;
    double dt = get_dt();
    double target_dt = 1.0 / m_target_fps;
    double to_wait = target_dt - dt;
    if (to_wait > 0.0) {
        std::this_thread::sleep_for(std::chrono::duration<double>(to_wait));
    }
}
