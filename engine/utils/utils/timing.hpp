#include <chrono>

static std::chrono::time_point<std::chrono::high_resolution_clock> curr;

inline int get_micro_since() {
    auto now = std::chrono::high_resolution_clock::now();
    int time = std::chrono::duration_cast<std::chrono::microseconds>(now - curr)
                   .count();
    curr = now;
    return time;
}

inline int get_ms_since() {
    auto now = std::chrono::high_resolution_clock::now();
    int time = std::chrono::duration_cast<std::chrono::microseconds>(now - curr)
                   .count();
    curr = now;
    return time;
}
