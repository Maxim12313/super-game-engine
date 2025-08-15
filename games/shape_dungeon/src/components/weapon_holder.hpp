#pragma once

#include "ecs/common.hpp"
#include "optional"

///
/// A component for storing what weapon is held
///
class WeaponHolder final {
public:
    ///
    /// Argument Constructor.
    ///
    /// \param main, first equiped weapon
    /// \param secondary, second equiped weapon which could be optional
    ///
    WeaponHolder(const ecs::Entity main,
                 const std::optional<ecs::Entity> secondary) noexcept;

    ///
    /// Move constructor.
    ///
    WeaponHolder(WeaponHolder &&) noexcept;

    ///
    /// Default destructor. Will not be responsible for cleaning up weapons held
    ///
    ~WeaponHolder() noexcept = default;

    ///
    /// Move assignment overload.
    ///
    WeaponHolder &operator=(WeaponHolder &&) noexcept;

public:
    ///
    /// first slot for weapon
    ///
    ecs::Entity m_mainHand;

    ///
    /// second slot for weapon
    ///
    std::optional<ecs::Entity> m_offHand;

    ///
    /// which weapon is being used
    ///
    ecs::Entity m_activeHand;
};
