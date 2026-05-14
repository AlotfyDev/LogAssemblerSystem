#pragma once
#include "assembler/communication_context/bridge_carriers/requirements/TCarrierRequirementSatisfactionReport.hpp"
#include "assembler/communication_context/bridge_carriers/validation/TCarrierValidationReport.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccCarrierReadinessView.hpp"
namespace assembler::communication_context
{
    struct TCarrierFacadeEvidenceAdapter final
    {
        [[nodiscard]] static constexpr TAsccCarrierReadinessView to_readiness_view(TCarrierValidationReport validation, TCarrierRequirementSatisfactionReport requirement) noexcept
        {
            return TAsccCarrierReadinessView::from_reports(validation, requirement);
        }
    };
}
