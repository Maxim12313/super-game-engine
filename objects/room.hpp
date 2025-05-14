#pragma once
#include "../include/globals.hpp"
#include <stack>

struct Room {
    // [begin, end)
    int begin_idx, end_idx;
    stack<int> unused;

    Room() {
        for (int i = begin_idx; i < end_idx; i++) {
            unused.push(i);
        }
    }

    void set_unused(int idx) { unused.push(idx); }

    int get_unused() {
        // NOTE:: could either replace or keep old
        if (unused.empty())
            return -1;
        int res = unused.top();
        unused.pop();
        return res;
    }
};
