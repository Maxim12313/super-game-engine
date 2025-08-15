#pragma once
#include <glm/ext/vector_float2.hpp>

///
/// A component that describes the velocity using direction and speed
///
class Velocity2D final {
public:
    ///
    /// Argument Constructor.
    ///
    /// \param dir The starting direction
    /// \param sp The starting speed
    ///
    Velocity2D(const glm::vec2 dir, const float sp) noexcept;

    ///
    /// Move constructor.
    ///
    Velocity2D(Velocity2D &&) noexcept;

    ///
    /// Move assignment overload.
    ///
    Velocity2D &operator=(Velocity2D &&) noexcept;

public:
    ///
    /// direction entity is moving in
    ///
    glm::vec2 m_direction;

    ///
    /// speed entity is moving at
    ///
    float m_speed;
};
