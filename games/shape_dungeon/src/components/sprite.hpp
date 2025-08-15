#pragma once
#include <glm/ext/vector_float4.hpp>

///
/// A component that describes a sprite or texture.
/// In this case our 'sprites' are colored rectangles and circles.
///
class Sprite final {
public:
    ///
    /// Rectangle Constructor.
    ///
    /// \param w Width of the sprite.
    /// \param h Height of the sprite.
    /// \param col The color you want the sprite to be (RGBA, 0 - 255).
    ///
    Sprite(const float w, const float h, glm::vec4 color) noexcept;

    ///
    /// Circle Constructor.
    ///
    /// \param radius Radius of the circle to draw.
    /// \param col The color you want the sprite to be (RGBA, 0 - 255).
    ///
    Sprite(const float radius, glm::vec4 color) noexcept;

    ///
    /// Move constructor.
    ///
    Sprite(Sprite &&) noexcept;

    ///
    /// Move assignment overload.
    ///
    Sprite &operator=(Sprite &&) noexcept;

public:
    ///
    /// Stores how wide the rectangle is.
    ///
    float m_width;

    ///
    /// Stores how high the rectangle is.
    ///
    float m_height;

    ///
    /// Stores the radius of a circle.
    ///
    float m_radius;

    ///
    /// Stores the color of the sprite.
    ///
    glm::vec4 m_color;
};
