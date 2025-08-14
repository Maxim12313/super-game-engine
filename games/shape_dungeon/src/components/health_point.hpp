#pragma once

///
/// A component to represent the health point of an entity.
///
class Health_Point final {
public:
    ///
    /// Argument Constructor.
    ///
    /// \param hp Starting hp
    ///
    Health_Point(const int hp) noexcept;

    ///
    /// Move constructor.
    ///
    Health_Point(Health_Point &&) noexcept;

    ///
    /// Default destructor.
    ///
    ~Health_Point() noexcept = default;

    ///
    /// Move assignment overload.
    ///
    Health_Point &operator=(Health_Point &&) noexcept;

public:
    ///
    ///  health point.
    ///
    int m_hp;
};
