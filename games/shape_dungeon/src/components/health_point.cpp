#include "health_point.hpp"

Health_Point::Health_Point(const int hp) noexcept : m_hp(hp) {
}

Health_Point::Health_Point(Health_Point &&hp) noexcept {
    this->m_hp = hp.m_hp;
}

Health_Point &Health_Point::operator=(Health_Point &&hp) noexcept {
    if (this != &hp) {
        this->m_hp = hp.m_hp;
    }

    return *this;
}
