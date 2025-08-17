#pragma once
#include <cstdint>

///
/// A component to represents the amount of ammo the weapon have
///
class Ammo final {
public:
    ///
    /// Argument Constructor.
    ///
    /// \param amount of starting ammo
    ///
    Ammo(const uint8_t) noexcept;

public:
    ///
    ///  amount of ammo
    ///
    uint8_t m_ammo;
};
