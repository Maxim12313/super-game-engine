#include "../include/utils/test_utils.hpp"

vector<string> debug::split(const string &s, char delimiter) {
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
