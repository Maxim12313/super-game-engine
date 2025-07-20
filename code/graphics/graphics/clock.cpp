#include "clock.hpp"
#include <chrono>

Clock::Clock(int target_fps)
    : m_prev_frame(std::chrono::high_resolution_clock::now()), m_dt(0) {
}

double Clock::update_dt() {
    auto curr_frame = std::chrono::high_resolution_clock::now();
    auto duration = curr_frame - m_prev_frame;
    int ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    m_dt = ms / 1000.0;
    m_prev_frame = curr_frame;
    return m_dt;
}

double Clock::get_dt() const {
    return m_dt;
}
