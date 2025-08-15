#include "weapon_holder.hpp"
#include "ecs/common.hpp"
#include <optional>

WeaponHolder::WeaponHolder(const ecs::Entity main,
                           const std::optional<ecs::Entity> secondary) noexcept
    : m_mainHand{main}, m_offHand{secondary} {
}

WeaponHolder::WeaponHolder(WeaponHolder &&wh) noexcept {
    this->m_mainHand = wh.m_mainHand;
    this->m_offHand = wh.m_offHand;
    this->m_activeHand = wh.m_activeHand;
}

WeaponHolder &WeaponHolder::operator=(WeaponHolder &&wh) noexcept {
    if (this != &wh) {
        this->m_mainHand = wh.m_mainHand;
        this->m_offHand = wh.m_offHand;
        this->m_activeHand = wh.m_activeHand;
    }

    return *this;
}
