#pragma once
#include <cstdint>

///
/// A component to represents the reload time of a weapon
///
class Ammo final {
public:
    ///
    /// Argument Constructor.
    ///
    /// \param amount of time in second for weapon to reload
    ///
    Ammo(const uint8_t) noexcept;

public:
    ///
    ///  time in second to reload the weapon
    ///
    uint8_t m_ammo;
};
