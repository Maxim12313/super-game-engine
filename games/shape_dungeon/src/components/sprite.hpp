#pragma once
#include "graphics/color.hpp"
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
    /// \param col The color you want the sprite to be (RBG 0.0-1.0)
    ///
    Sprite(const float w, const float h, graphics::Color color) noexcept;

    ///
    /// Circle Constructor.
    ///
    /// \param radius Radius of the circle to draw.
    /// \param col The color you want the sprite to be (RGB 0.0-1.0)
    ///
    Sprite(const float radius, graphics::Color color) noexcept;

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
    graphics::Color m_color;
};
