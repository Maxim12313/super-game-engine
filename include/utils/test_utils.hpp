/**
 * @file
 * @brief utils for testing / debugging
 */

#pragma once
#include <iostream>
#include <spdlog/spdlog.h>
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
inline vector<string> split(const string &s, char delimiter) {
    vector<string> res;
    res.push_back("");
    for (char c : s) {
        if (c == delimiter && !res.back().empty()) {
            res.push_back("");
        } else {
            res.back() += c;
        }
    }
    if (res.back().empty())
        res.pop_back();
    return res;
}

/// More verbose ASSERT
#define ASSERT(cond)                                                           \
    do {                                                                       \
        if (!(cond)) {                                                         \
            SPDLOG_CRITICAL("Assertion failed: {}", #cond);                    \
            exit(1);                                                           \
        }                                                                      \
    } while (0);

/// More verbose ASSERT on equality
#define ASSERT_EQUAL(actual, expected)                                         \
    do {                                                                       \
        if (!((actual) == (expected))) {                                       \
            SPDLOG_CRITICAL("Assertion failed: {} == {}", #actual, #expected); \
            SPDLOG_CRITICAL("  Actual:  {}", (actual));                        \
            SPDLOG_CRITICAL("  Expected:  {}", (expected));                    \
            exit(1);                                                           \
        }                                                                      \
    } while (0)

/// For iterables (auto val : data) loopable
/// More verbose ASSERT on equality of iterables
#define ASSERT_ITERABLE_EQUAL(actual, expected)                                \
    do {                                                                       \
        if (!((actual) == (expected))) {                                       \
            SPDLOG_CRITICAL("Assertion failed: {} == {}", #actual, #expected); \
            SPDLOG_CRITICAL("  Actual:  {}", iter_to_string(actual));          \
            SPDLOG_CRITICAL("  Expected:  {}", iter_to_str(expected));         \
            exit(1);                                                           \
        }                                                                      \
    } while (0)

}; // namespace debug
