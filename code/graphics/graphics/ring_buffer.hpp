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

    // TODO: learn about perfect forwarding
    void push(T val) {
        T res;
        // just pass it on without ret
        push(std::move(val), res);
    }

    // returns true if it overwrote and puts popped in vres
    bool push(T val, T &res) {
        // overwrites if max capacity
        bool popped = false;
        if (full()) {
            res = front();
            pop();
            popped = true;
        }

        // perfect forwarding: moved if rvalue, copied if lvalue
        m_data[m_head] = val;
        m_head = iterate(m_head);
        m_sz++;

        return popped;
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
