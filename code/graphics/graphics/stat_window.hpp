#pragma once

#include "graphics/ring_buffer.hpp"
#include <cstddef>
template <typename T, std::size_t capacity>
class StatWindow {
public:
    StatWindow() : m_sum(0) {
    }
    void push(T val) {
        if (m_window.size() == capacity) {
            m_sum -= m_window.front();
            m_window.pop();
        }
        m_sum += val;
        m_window.push(val);
    }

    double get_sum() const {
        return m_sum;
    }

    double get_avg() const {
        return m_sum / m_window.size();
    }

private:
    long double m_sum;
    RingBuffer<T, capacity> m_window;
};
