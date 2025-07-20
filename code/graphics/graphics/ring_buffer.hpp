#pragma once

#include "utils/macros.hpp"
#include <cstddef>
#include <utility>

template <typename T, size_t capacity>
class RingBuffer {
private:
    size_t iterate(size_t idx) {
        return (idx + 1) % capacity;
    }

public:
    RingBuffer() : m_sz(0), m_head(0), m_tail(0) {};

    // TODO: perfect forwarding: moved if rvalue, copied if lvalue
    void push(T val) {
        ASSERT(!full() && "is full");
        m_data[m_head] = val;
        m_head = iterate(m_head);
        m_sz++;
    }

    // fails if empty
    void pop() {
        ASSERT(!empty() && "is empty");
        m_tail = iterate(m_tail);
        m_sz--;
    }

    T &front() {
        ASSERT(!empty() && "is empty");
        return m_data[m_tail];
    }

    bool full() const {
        return m_sz == capacity;
    }

    bool empty() const {
        return m_sz == 0;
    }

    size_t size() const {
        return m_sz;
    }

private:
    T m_data[capacity];
    size_t m_sz;
    size_t m_head;
    size_t m_tail;
};
