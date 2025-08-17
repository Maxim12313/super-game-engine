#pragma once

///
/// A component to represents the reload time of a weapon
///
class WeaponCooldown final {
public:
    ///
    /// Argument Constructor.
    ///
    /// \param amount of time in second for weapon to reload
    ///
    WeaponCooldown(const float) noexcept;

public:
    ///
    ///  time in second to reload the weapon
    ///
    float m_weaponCooldown;
};
