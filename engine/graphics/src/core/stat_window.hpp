#pragma once

#include "ring_buffer.hpp"
#include <cstddef>

namespace graphics {
// T must be a numeric type, we expect to take sum,avg
template <typename T, size_t capacity = 32>
class StatWindow {
public:
    StatWindow() : m_sum(0) {
    }
    void push(T val) {
        if (m_window.size() == capacity) {
            m_sum -= m_window.front();
            m_window.pop();
        }
        m_window.push(val);
        m_sum += val;
        m_last = val;
    }

    double sum() const {
        return m_sum;
    }

    double avg() const {
        return m_sum / m_window.size();
    }

    // undefined if before any push
    T last() const {
        return m_last;
    }

private:
    T m_last;
    long double m_sum;
    RingBuffer<T, capacity> m_window;
};
} // namespace graphics
