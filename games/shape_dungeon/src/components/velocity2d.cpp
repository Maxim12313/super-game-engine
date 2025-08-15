#include <glm/glm.hpp>
#include "velocity2d.hpp"

Velocity2D::Velocity2D(const glm::vec2 dir, const float sp) noexcept
    : m_direction{dir}, m_speed{sp} {
}

Velocity2D::Velocity2D(Velocity2D &&v) noexcept {
    this->m_direction = v.m_direction;
    this->m_speed = v.m_speed;
}

Velocity2D &Velocity2D::operator=(Velocity2D &&v) noexcept {
    if (this != &v) {
        this->m_direction = v.m_direction;
        this->m_speed = v.m_speed;
    }

    return *this;
}
