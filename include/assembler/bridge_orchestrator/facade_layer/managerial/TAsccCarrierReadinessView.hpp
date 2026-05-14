#pragma once
#include <string_view>
#include "assembler/communication_context/bridge_carriers/requirements/TCarrierRequirementSatisfactionReport.hpp"
#include "assembler/communication_context/bridge_carriers/validation/TCarrierValidationReport.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccComponentReadinessStatus.hpp"
namespace assembler::communication_context
{
    struct TAsccCarrierReadinessView final
    {
        TAsccComponentReadinessStatus status{TAsccComponentReadinessStatus::unknown};
        TCarrierValidationReport validation_report{};
        TCarrierRequirementSatisfactionReport requirement_report{};
        std::string_view readiness_note{};
        [[nodiscard]] constexpr bool is_valid() const noexcept { return status != TAsccComponentReadinessStatus::unknown; }
        [[nodiscard]] constexpr bool ready() const noexcept
        {
            return is_valid() && status == TAsccComponentReadinessStatus::ready && validation_report.passed() && requirement_report.satisfied();
        }
        [[nodiscard]] static constexpr TAsccCarrierReadinessView from_reports(TCarrierValidationReport validation, TCarrierRequirementSatisfactionReport requirement, std::string_view note = {}) noexcept
        {
            const bool ok = validation.passed() && requirement.satisfied();
            return {ok ? TAsccComponentReadinessStatus::ready : TAsccComponentReadinessStatus::blocked, validation, requirement, note};
        }
    };
}
