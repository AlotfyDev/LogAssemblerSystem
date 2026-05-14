#pragma once
#include <cstddef>
#include <string_view>
#include "assembler/communication_context/bridge_carriers/correlation/TCorrelationToken.hpp"
namespace assembler::communication_context
{
    struct TCarrierFlowReport final
    {
        std::size_t recorded_events{0u};
        std::uint64_t rejected_events{0u};
        TCorrelationToken correlation{TCorrelationToken::invalid()};
        std::string_view report_name{"carrier_flow_report"};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return !report_name.empty(); }
        [[nodiscard]] constexpr bool clean() const noexcept { return is_valid() && rejected_events == 0u; }
    };
}
