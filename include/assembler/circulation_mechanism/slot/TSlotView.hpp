#pragma once

#include "TSlotOccupancyView.hpp"

/*
    TSlotView.hpp

    Delivery:
        CME-SLOT-PROD-W01 — Production Residency And Access Contract

    Responsibility:
        Read-only projection of a production slot.

    Non-ownership:
        Does not expose mutable payload buffer.
*/

namespace assembler {
namespace circulation_mechanism {


struct TSlotView final
{
    TSlotOccupancyView occupancy{};

    [[nodiscard]] constexpr bool is_valid() const noexcept
    {
        return occupancy.is_valid();
    }

    [[nodiscard]] constexpr TSlotIndex index() const noexcept
    {
        return occupancy.slot_index;
    }

    [[nodiscard]] constexpr TSlotState state() const noexcept
    {
        return occupancy.state;
    }

    [[nodiscard]] constexpr bool occupied() const noexcept
    {
        return occupancy.occupied;
    }

    [[nodiscard]] constexpr std::uint32_t payload_size() const noexcept
    {
        return occupancy.payload_size;
    }

    [[nodiscard]] constexpr bool can_accept_ingress() const noexcept
    {
        return is_ingress_writable(occupancy.state);
    }

    [[nodiscard]] constexpr bool can_dispatch() const noexcept
    {
        return occupancy.is_dispatch_candidate();
    }
};

} // namespace circulation_mechanism
} // namespace assembler
