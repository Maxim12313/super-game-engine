#pragma once

///
/// A component that describes the position of something on the screen.
///
class Position final {
public:
    ///
    /// Argument Constructor.
    ///
    /// \param x The starting x-pos on screen.
    /// \param y The starting y-pos on screen.
    ///
    Position(const float x, const float y) noexcept;

    ///
    /// Move constructor.
    ///
    Position(Position &&) noexcept;

    ///
    /// Move assignment overload.
    ///
    Position &operator=(Position &&) noexcept;

public:
    ///
    /// x pos on screen.
    ///
    float m_x;

    ///
    /// y pos on screen.
    ///
    float m_y;
};
