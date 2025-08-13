#pragma once
#include <string>

// assert helper
template <typename Iterable>
std::string str_list(Iterable data) {
    std::string res = "[ ";
    for (auto val : data)
        res += std::to_string(val) + ", ";
    res += " ]";
    return res;
}
