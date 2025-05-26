#pragma once
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// more verbose assert
// do while to ensure no nesting {} conflicts

template <typename Iterable>
string iter_to_string(Iterable data) {
    string res = "{ ";
    for (auto val : data) {
        res += to_string(val) + ",";
    }
    res += " }";
    return res;
}

#define ASSERT(cond)                                                                                                   \
    do {                                                                                                               \
        if (!(cond)) {                                                                                                 \
            std::cerr << "Assertion failed: " << #cond << ", file " << __FILE__ << ", line " << __LINE__ << std::endl; \
            exit(1);                                                                                                   \
        }                                                                                                              \
    } while (0);

#define ASSERT_EQUAL(actual, expected)                                                                                 \
    do {                                                                                                               \
        if (!((actual) == (expected))) {                                                                               \
            std::cerr << "Assertion failed: " << #actual << " == " << #expected << "\n"                                \
                      << "  Actual:   " << (actual) << "\n"                                                            \
                      << "  Expected: " << (expected) << "\n"                                                          \
                      << "  File: " << __FILE__ << ", line: " << __LINE__ << std::endl;                                \
            exit(1);                                                                                                   \
        }                                                                                                              \
    } while (0)

// for iterables (auto val : data) loopable
#define ASSERT_ITERABLE_EQUAL(actual, expected)                                                                        \
    do {                                                                                                               \
        if (!((actual) == (expected))) {                                                                               \
            std::cerr << "Assertion failed: " << #actual << " == " << #expected << "\n"                                \
                      << "  Actual:   " << to_string(actual) << "\n"                                                   \
                      << "  Expected: " << to_string(expected) << "\n"                                                 \
                      << "  File: " << __FILE__ << ", line: " << __LINE__ << std::endl;                                \
            exit(1);                                                                                                   \
        }                                                                                                              \
    } while (0)
