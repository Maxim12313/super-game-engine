#include "position.hpp"

namespace Component {
Position::Position(const float x, const float y) noexcept : m_x{x}, m_y{y} {
}

Position::Position(Position &&p) noexcept {
    this->m_x = p.m_x;
    this->m_y = p.m_y;
}

Position &Position::operator=(Position &&p) noexcept {
    if (this != &p) {
        this->m_x = p.m_x;
        this->m_y = p.m_y;
    }

    return *this;
}
} // namespace Component
