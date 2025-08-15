#pragma once
#include <cstdint>

///
/// A component to represent the health point of an entity.
///
class HealthPoint final {
public:
    ///
    /// Argument Constructor.
    ///
    /// \param hp Starting hp
    ///
    HealthPoint(const uint8_t) noexcept;

public:
    ///
    ///  health point can only be positive.
    ///
    uint8_t m_hp;
};
