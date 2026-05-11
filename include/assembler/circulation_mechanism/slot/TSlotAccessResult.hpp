#pragma once

#include "TSlotAccessStatus.hpp"
#include "assembler/circulation_mechanism/state/TSlotState.hpp"

/*
    TSlotAccessResult.hpp

    Responsibility:
        Result carrier for slot residency/access operations.
*/

namespace assembler {
namespace circulation_mechanism {


struct TSlotAccessResult final
{
    TSlotAccessStatus status{TSlotAccessStatus::not_attempted};
    TSlotState before{TSlotState::empty};
    TSlotState after{TSlotState::empty};

    [[nodiscard]] constexpr bool accepted() const noexcept
    {
        return status == TSlotAccessStatus::accepted;
    }

    [[nodiscard]] constexpr bool rejected() const noexcept
    {
        return !accepted();
    }

    [[nodiscard]] constexpr bool changed() const noexcept
    {
        return before != after;
    }
};

} // namespace circulation_mechanism
} // namespace assembler
