// sprite.cpp

#include "sprite.hpp"
#include <glm/glm.hpp>

namespace Component {
Sprite::Sprite(const int w, const int h, glm::vec4 color) noexcept
    : m_width{w}, m_height{h}, m_color{color}, m_radius{0} {
}

Sprite::Sprite(const int radius, glm::vec4 color) noexcept
    : m_radius{radius}, m_color{color}, m_width{0}, m_height{0} {
}

Sprite::Sprite(Sprite &&s) noexcept {
    this->m_color = s.m_color;
    this->m_height = s.m_height;
    this->m_radius = s.m_radius;
    this->m_width = s.m_width;
}

Sprite &Sprite::operator=(Sprite &&s) noexcept {
    if (this != &s) {
        this->m_color = s.m_color;
        this->m_height = s.m_height;
        this->m_radius = s.m_radius;
        this->m_width = s.m_width;
    }

    return *this;
}
} // namespace Component
