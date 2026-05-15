#pragma once
#include "assembler/communication_context/facade_layer/managerial/TAsccProtocolReadinessView.hpp"
#include "assembler/communication_context/protocols/requirements/TProtocolRequirementReport.hpp"

/**
 * @file TProtocolRequirementFacadeAdapter.hpp
 * @brief Adapter that converts protocol requirement reports into facade readiness input.
 */
namespace assembler::communication_context {
    struct TProtocolRequirementFacadeAdapter final {
        [[nodiscard]] static constexpr TAsccProtocolReadinessView to_readiness_view(
            TBridgeProtocolKind protocol,
            TProtocolRequirementReport report,
            bool protocol_known,
            bool plan_valid,
            bool binding_compatible,
            bool participant_capabilities_satisfied) noexcept
        {
            const bool ok = protocol_known && plan_valid && report.passed() && binding_compatible && participant_capabilities_satisfied;
            return {protocol, ok ? TAsccComponentReadinessStatus::ready : TAsccComponentReadinessStatus::blocked, report, protocol_known, plan_valid, report.passed(), binding_compatible, participant_capabilities_satisfied, ok ? "protocol ready" : "protocol not ready"};
        }
    };
}
