#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>

#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"

/**
 * @file TCarrierFlowReport.hpp
 * @brief Aggregate evidence report for one ASCC carrier-flow ledger.
 *
 * The report summarizes carrier-flow activity produced by `TCarrierFlowLedger`
 * or `TCarrierFlowRuntime`. It is bounded evidence, not telemetry or
 * persistence.
 */

namespace assembler::communication_context
{
    struct TCarrierFlowReport final
    {
        std::size_t recorded_events{0u};
        std::size_t produced_events{0u};
        std::size_t consumed_events{0u};
        std::size_t observed_events{0u};
        std::size_t relayed_events{0u};
        std::uint64_t rejected_events{0u};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view report_name{"carrier_flow_report"};

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return !report_name.empty();
        }

        [[nodiscard]] constexpr bool clean() const noexcept
        {
            return is_valid() && rejected_events == 0u;
        }

        [[nodiscard]] constexpr bool has_activity() const noexcept
        {
            return recorded_events > 0u;
        }

        [[nodiscard]] constexpr bool balanced_primary_exchange() const noexcept
        {
            return produced_events >= consumed_events;
        }
    };
}
