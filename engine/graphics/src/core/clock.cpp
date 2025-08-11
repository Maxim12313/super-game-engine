#include "clock.hpp"
#include <chrono>
#include <thread>

// helpers **********

// where dt in sec
double to_fps(double dt) {
    return 1 / dt;
}

// where fps in sec
double to_dt(double fps) {
    return 1 / fps;
}

// class public **********
Clock::Clock(int target_fps)
    : m_prev_frame(std::chrono::high_resolution_clock::now()),
      m_target_fps(target_fps) {
}

double Clock::update_dt() {
    auto curr_frame = std::chrono::high_resolution_clock::now();
    auto duration = curr_frame - m_prev_frame;
    int ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    double sec = ms / 1000.0;
    m_fps_stats.push(to_fps(sec));
    m_prev_frame = curr_frame;
    return sec;
}

double Clock::get_dt_now() const {
    auto curr_frame = std::chrono::high_resolution_clock::now();
    auto duration = curr_frame - m_prev_frame;
    int ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    return ms / 1000.0;
}

void Clock::adjust_fps(double accuracy) const {
    if (m_target_fps == -1)
        return;
    double dt = get_dt_now();
    double target_dt = to_dt(m_target_fps);
    double to_wait = target_dt - dt;
    if (to_wait > accuracy) {
        std::this_thread::sleep_for(std::chrono::duration<double>(to_wait));
    }
}

double Clock::last_fps() const {
    return m_fps_stats.last();
}

double Clock::avg_fps() const {
    return m_fps_stats.avg();
}
