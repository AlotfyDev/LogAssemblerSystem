#pragma once
#include <string_view>
#include "assembler/communication_context/participants/reports/TParticipantCapabilityMatchReport.hpp"
#include "assembler/communication_context/participants/runtime/TParticipantRuntimeContext.hpp"

/**
 * @file TParticipantRuntimeReport.hpp
 * @brief Evidence report for participant runtime admission and participation.
 */
namespace assembler::communication_context {
    struct TParticipantRuntimeReport final {
        TParticipantRuntimeContext context{};
        TParticipantCapabilityMatchReport capability_report{};
        bool carrier_participation_supported{false};
        std::string_view report_note{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return context.is_valid() && capability_report.is_valid(); }
        [[nodiscard]] constexpr bool ready() const noexcept { return is_valid() && context.ready() && capability_report.passed() && carrier_participation_supported; }
    };
}
