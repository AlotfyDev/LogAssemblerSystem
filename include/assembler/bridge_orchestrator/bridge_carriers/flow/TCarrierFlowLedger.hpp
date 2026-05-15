#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowDirection.hpp"
#include "assembler/communication_context/bridge_carriers/flow/TCarrierFlowRecord.hpp"

/**
 * @file TCarrierFlowLedger.hpp
 * @brief Bounded runtime ledger for ASCC carrier-flow events.
 *
 * This is the runtime container that records produced/consumed/observed/relayed
 * carrier events during one ASCC operation or operation slice.
 *
 * It is not telemetry, persistence, or an event bus. It is bounded local
 * evidence used by carrier runtime, diagnostics, and facade projections.
 */

namespace assembler::communication_context
{
    template <std::size_t Capacity>
    struct TCarrierFlowLedger final
    {
        std::array<TCarrierFlowRecord, Capacity> records{};
        std::size_t count{0u};
        std::uint64_t rejected_records{0u};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return count <= Capacity;
        }

        [[nodiscard]] constexpr bool empty() const noexcept
        {
            return count == 0u;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return count >= Capacity;
        }

        constexpr bool record(TCarrierFlowRecord flow_record) noexcept
        {
            if (!is_valid() || full() || !flow_record.is_valid())
            {
                ++rejected_records;
                return false;
            }

            records[count++] = flow_record;
            return true;
        }

        [[nodiscard]] constexpr std::size_t count_direction(
            TCarrierFlowDirection direction) const noexcept
        {
            std::size_t total = 0u;

            for (std::size_t index = 0u; index < count; ++index)
            {
                if (records[index].direction == direction)
                {
                    ++total;
                }
            }

            return total;
        }

        [[nodiscard]] constexpr std::size_t produced_count() const noexcept
        {
            return count_direction(TCarrierFlowDirection::produced);
        }

        [[nodiscard]] constexpr std::size_t consumed_count() const noexcept
        {
            return count_direction(TCarrierFlowDirection::consumed);
        }

        [[nodiscard]] constexpr bool has_rejections() const noexcept
        {
            return rejected_records > 0u;
        }
    };
}
