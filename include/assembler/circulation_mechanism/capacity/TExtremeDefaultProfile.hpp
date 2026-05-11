#pragma once
#include "TCirculationCapacityProfile.hpp"

/*
    TExtremeDefaultProfile.hpp

    Responsibility:
        Wraps a circulation capacity profile as an extreme/default pre-sized profile.
*/
namespace assembler {
namespace circulation_mechanism {

struct TExtremeDefaultProfile final
{
    TCirculationCapacityProfile capacity{};
    std::uint32_t safety_margin_percent{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return capacity.is_valid() && capacity.extreme_default_enabled;
    }

    [[nodiscard]] constexpr bool has_safety_margin() const noexcept
    {
        return safety_margin_percent > 0U;
    }
};
} // namespace circulation_mechanism
} // namespace assembler
