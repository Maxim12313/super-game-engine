#pragma once
#include <utility>

template <typename each_iterator>
class EachRange {
public:
    EachRange(each_iterator &begin_it, each_iterator &end_it)
        : m_begin(std::move(begin_it)), m_end(std::move(end_it)) {
    }

    each_iterator begin() {
        return m_begin;
    }
    each_iterator end() {
        return m_end;
    }

private:
    each_iterator m_begin;
    each_iterator m_end;
};
