#pragma once

#include "assembler/circulation_mechanism/ids/TSlotIndex.hpp"
#include "assembler/circulation_mechanism/state/TSlotState.hpp"
#include "TSlotAccessStatus.hpp"

/*
    TSlotTransitionReport.hpp

    Delivery:
        CME-SLOT-PROD-W01 — Production Residency And Access Contract

    Responsibility:
        Evidence carrier for slot state and residency changes.

    Non-ownership:
        Report does not execute transition or prove downstream delivery.
*/

namespace assembler {
namespace circulation_mechanism {


struct TSlotTransitionReport final
{
    TSlotIndex slot_index{};
    TSlotState before{TSlotState::empty};
    TSlotState after{TSlotState::empty};
    TSlotAccessStatus status{TSlotAccessStatus::not_attempted};
    std::uint32_t payload_size_before{0};
    std::uint32_t payload_size_after{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return slot_index.is_valid();
    }

    [[nodiscard]] constexpr bool accepted() const noexcept
    {
        return status == TSlotAccessStatus::accepted;
    }

    [[nodiscard]] constexpr bool changed() const noexcept
    {
        return before != after || payload_size_before != payload_size_after;
    }
};

} // namespace circulation_mechanism
} // namespace assembler
