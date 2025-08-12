#include "../src/core/stat_window.hpp"

using namespace graphics;

int main() {
    StatWindow<int, 20> stat_window;
    for (int r = 0; r < 100; r++) {
        stat_window.push(r);
        int l = std::max(r - 20 + 1, 0);
        int expected_sum = (l + r) * (r - l + 1) / 2;
        double expected_avg = (l + r) / 2.0;
        ASSERT_EQUAL(expected_sum, stat_window.sum());
        ASSERT_EQUAL(expected_avg, stat_window.avg());
    }
}
