#pragma once
#include <sstream>
#include <string>
#include <ostream>
#include <tuple>

template <typename Iterable>
std::string str_list(Iterable data) {
    std::ostringstream res;
    res << "[ ";
    for (auto val : data)
        res << val << ", ";
    res << "] ";
    return res.str();
}

template <typename... Ts>
std::string str_tuple(std::tuple<Ts...> data) {
    std::ostringstream res;
    res << "[ ";
    ((res << std::get<Ts>(data) << " "), ...);
    res << "] ";
    return res.str();
}

// tuple
template <typename... Ts>
std::ostream &operator<<(std::ostream &os, const std::tuple<Ts...> tuple) {
    os << str_tuple<Ts...>(tuple);
    return os;
}
