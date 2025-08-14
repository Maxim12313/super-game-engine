// position.hpp

#ifndef SHAPE_DUNGEON_COMPONENTS_POSITION_HPP_
#define SHAPE_DUNGEON_COMPONENTS_POSITION_HPP_

namespace Component {
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
    Position(const double x, const double y) noexcept;

    ///
    /// Move constructor.
    ///
    Position(Position &&) noexcept;

    ///
    /// Default destructor.
    ///
    ~Position() noexcept = default;

    ///
    /// Move assignment overload.
    ///
    Position &operator=(Position &&) noexcept;

public:
    ///
    /// x pos on screen.
    ///
    double m_x;

    ///
    /// y pos on screen.
    ///
    double m_y;
};
} // namespace Component

#endif
