#pragma once

#include <cstdint>

///
/// A component to represents the reload time of a weapon
///
class ReloadTime final {
public:
    ///
    /// Argument Constructor.
    ///
    /// \param amount of time in second for weapon to reload
    ///
    ReloadTime(const float) noexcept;

public:
    ///
    ///  time in second to reload the weapon
    ///
    float m_reloadTime;
};
