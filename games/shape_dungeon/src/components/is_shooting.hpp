#pragma once

///
/// A component to represent whether a weapon is triggered to fire
///
class IsShooting final {
public:
    ///
    /// Argument Constructor.
    ///
    /// \param shooting if firing is triggered
    ///
    IsShooting(const bool shooting) noexcept;

public:
    ///
    /// whether the weapon is shooting
    ///
    bool m_isShooting;
};
