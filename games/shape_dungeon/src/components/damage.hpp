#pragma once
#include <cstdint>

///
/// A component to represents the amount of damage an entity deals
///
class Damage final {
public:
    ///
    /// Argument Constructor.
    ///
    /// \param damage amount of hp that will be dealt
    ///
    Damage(const int16_t) noexcept;

public:
    ///
    ///  damage point, negative for healing
    ///
    int16_t m_dmg;
};
