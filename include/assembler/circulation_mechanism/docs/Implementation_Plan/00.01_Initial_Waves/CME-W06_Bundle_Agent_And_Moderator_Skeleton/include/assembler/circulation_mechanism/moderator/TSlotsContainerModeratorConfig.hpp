#pragma once

#include "assembler/circulation_mechanism/capacity/TCapacityProfileId.hpp"

/*
    TSlotsContainerModeratorConfig.hpp

    Responsibility:
        Configuration surface for moderator skeleton.

    Does not own:
        - Concrete reset algorithm.
*/

namespace assembler {
namespace circulation_mechanism {

struct TSlotsContainerModeratorConfig final
{
    TCapacityProfileId default_empty_capacity_profile_id{};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return default_empty_capacity_profile_id.is_valid();
    }
};
} // namespace circulation_mechanism
} // namespace assembler
