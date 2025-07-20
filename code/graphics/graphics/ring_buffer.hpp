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

    void push(T &&val) {
        T res;
        // just pass it on without ret
        push(std::move(val), res);
    }

    // returns true if it overwrote and puts popped in vres
    bool push(T &&val, T &res) {
        // overwrites if max capacity
        if (full())
            res = pop();

        // perfect forwarding: moved if rvalue, copied if lvalue
        m_data[m_head] = std::forward<T>(val);
        m_head = iterate(m_head);
        m_sz++;
    }

    // fails if empty
    T pop() {
        ASSERT(!empty() && "is empty");
        T &val = m_data[m_tail];
        m_tail = iterate(m_tail);
        m_sz--;
        return val;
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
