#pragma once
#include <utility>
#include <vector>

namespace ecs {

// Declaration ********
// WARNING: these are lightweight and store the begin/end iterators directly
// If those iterators are invalidated, so too is this range
template <typename each_iterator>
class EachRange {
public:
    EachRange(each_iterator begin_it, each_iterator end_it);

    each_iterator begin() const;
    each_iterator end() const;

private:
    each_iterator m_begin;
    each_iterator m_end;
};

}; // namespace ecs

namespace ecs {
// Class public ********
template <typename each_iterator>
EachRange<each_iterator>::EachRange(each_iterator begin_it,
                                    each_iterator end_it)
    : m_begin(begin_it), m_end(end_it) {
}

template <typename each_iterator>
each_iterator EachRange<each_iterator>::begin() const {
    return m_begin;
}

template <typename each_iterator>
each_iterator EachRange<each_iterator>::end() const {
    return m_end;
}
}; // namespace ecs
