#pragma once
#include <print>
#include <string.h>

// log levels
#define LOG_LEVEL_ERROR 0
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_DEBUG 2
#define LOG_LEVEL_TRACE 3

// Reset
#define COLOR_RESET "\033[0m"
#define COLOR_GRAY "\033[90m"
#define COLOR_CYAN "\033[36m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"

// HELPERS
#define __FILENAME__                                                           \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG(prefix, color, fmt, ...)                                           \
    std::println("{}[{}]{} [{} {}:{}]: " fmt, color, prefix, COLOR_RESET,      \
                 __FILENAME__, __func__, __LINE__, ##__VA_ARGS__)

// log ../macros
#if LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOG_ERROR(fmt, ...) LOG("ERROR", COLOR_RED, fmt, ##__VA_ARGS__)
#else
#define LOG_ERROR(fmt, ...) ((void)0)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
#define LOG_INFO(fmt, ...) LOG("INFO ", COLOR_GREEN, fmt, ##__VA_ARGS__)
#else
#define LOG_INFO(fmt, ...) ((void)0)
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#define LOG_DEBUG(fmt, ...) LOG("DEBUG", COLOR_CYAN, fmt, ##__VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...) ((void)0)
#endif

#if LOG_LEVEL >= LOG_LEVEL_TRACE
#define LOG_TRACE(fmt, ...) LOG("TRACE", COLOR_GRAY, fmt, ##__VA_ARGS__)
#else
#define LOG_TRACE(fmt, ...) ((void)0)
#endif

// assert helper
template <typename Iterable>
std::string iter_to_string(Iterable data) {
    std::string res = "{ ";
    for (auto val : data) {
        res += to_string(val) + ",";
    }
    res += " }";
    return res;
}
template <typename Iterable>
bool iter_equal(Iterable a, Iterable b) {
    return std::equal(std::begin(a), std::end(a), std::begin(b), std::end(b));
}

// assert ../macros
#ifdef DEBUG
#define ASSERT(cond)                                                           \
    do {                                                                       \
        if (!(cond)) {                                                         \
            LOG_ERROR("Assertion failed: {}", #cond);                          \
            exit(1);                                                           \
        }                                                                      \
    } while (0);
#else
#define ASSERT(cond) ((void)(0))
#endif

#ifdef DEBUG
#define ASSERT_EQUAL(actual, expected)                                         \
    do {                                                                       \
        if (!((actual) == (expected))) {                                       \
            LOG_ERROR("Assertion failed: {} == {}", #actual, #expected);       \
            std::print("  Actual:  {}\n", (actual));                           \
            std::print("  Expected:  {}\n", (expected));                       \
            exit(1);                                                           \
        }                                                                      \
    } while (0)
#else
#define ASSERT_EQUAL(actual, expected) ((void)0)
#endif
