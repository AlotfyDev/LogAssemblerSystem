#pragma once
#include <string_view>
#include "assembler/communication_context/bridge_carriers/admission/TAdmissionResult.hpp"
#include "assembler/communication_context/bridge_carriers/readiness/TReadinessView.hpp"
#include "assembler/communication_context/bridge_carriers/views/TCarrierView.hpp"
#include "assembler/communication_context/bridge_core/results/TBridgeResult.hpp"
#include "assembler/communication_context/obligations/reports/TObligationReport.hpp"

/**
 * @file TObligationInvocationResult.hpp
 * @brief Unified result of an ASCC obligation invocation.
 */
namespace assembler::communication_context {
    struct TObligationInvocationResult final {
        TObligationStatus status{TObligationStatus::unknown};
        TCarrierView carrier{};
        TReadinessView readiness{};
        TAdmissionResult admission{};
        TBridgeResult bridge_result{};
        std::string_view note{};
        [[nodiscard]] constexpr bool succeeded() const noexcept { return status == TObligationStatus::satisfied; }
        [[nodiscard]] constexpr bool failed() const noexcept { return status == TObligationStatus::failed || status == TObligationStatus::unsupported || status == TObligationStatus::incomplete; }
    };
}
