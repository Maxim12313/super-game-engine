/**
 * @file
 * @brief utils for testing / debugging
 */

#pragma once
#include <iostream>
#include <vector>
using namespace std;

// more verbose ASSERT
// do while to ensure no nesting {} conflicts
namespace debug {
/**
 * @brief Converts iterable type into a string
 */
template <typename Iterable>
string iter_to_string(Iterable data) {
    string res = "{ ";
    for (auto val : data) {
        res += to_string(val) + ",";
    }
    res += " }";
    return res;
}

/**
 * @brief Split a string into a vector of strings over a delimiter
 */
vector<string> split(const string &s, char delimiter);

/// More verbose ASSERT
#define ASSERT(cond)                                                                                                   \
    do {                                                                                                               \
        if (!(cond)) {                                                                                                 \
            std::cerr << "Assertion failed: " << #cond << ", file " << __FILE__ << ", line " << __LINE__ << std::endl; \
            exit(1);                                                                                                   \
        }                                                                                                              \
    } while (0);

/// More verbose ASSERT on equality
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

/// For iterables (auto val : data) loopable
/// More verbose ASSERT on equality of iterables
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

}; // namespace debug
