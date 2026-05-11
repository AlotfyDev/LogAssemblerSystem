#pragma once

#include "assembler/circulation_mechanism/ids/TSlotIndex.hpp"
#include "assembler/circulation_mechanism/state/TSlotState.hpp"

#include <cstdint>

/*
    TSlotOccupancyView.hpp

    Delivery:
        CME-SLOT-PROD-W01 — Production Residency And Access Contract

    Current responsibility:
        Read-only projection of slot occupancy and payload residency.

    Production capabilities:
        - exposes slot index,
        - exposes slot state,
        - exposes whether a payload is resident,
        - exposes payload byte size,
        - classifies empty/dispatch-candidate state.

    Explicit non-ownership:
        - Does not expose mutable payload memory.
        - Does not own envelope lifecycle after dispatch exposure.
        - Does not perform dispatch.
*/

namespace assembler {
namespace circulation_mechanism {


struct TSlotOccupancyView final
{
    TSlotIndex slot_index{};
    TSlotState state{TSlotState::empty};
    bool occupied{false};
    std::uint32_t payload_size{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return slot_index.is_valid();
    }

    [[nodiscard]] constexpr bool is_empty() const noexcept
    {
        return !occupied && payload_size == 0U && state == TSlotState::empty;
    }

    [[nodiscard]] constexpr bool is_dispatch_candidate() const noexcept
    {
        return occupied && payload_size > 0U && is_dispatch_ready(state);
    }
};

} // namespace circulation_mechanism
} // namespace assembler
