#include "utils/macros.hpp"
#include <queue>
#include <graphics/ring_buffer.hpp>

int main() {
    RingBuffer<int, 10> actual;
    std::queue<int> expected;
    for (int i = 0; i < 100; i++) {
        int val = rand();
        ASSERT_EQUAL(actual.size(), expected.size());
        if (expected.size() == 10) {
            expected.pop();
            actual.pop();
        }
        actual.push(val);
        expected.push(val);
        ASSERT_EQUAL(actual.front(), expected.front());
    }
}
