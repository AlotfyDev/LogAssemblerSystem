#pragma once
#include "assembler/communication_context/facade_layer/managerial/TAsccObligationReadinessView.hpp"
#include "assembler/communication_context/obligations/reports/TObligationReport.hpp"
#include "assembler/communication_context/obligations/runtime/TObligationRuntimeView.hpp"

/**
 * @file TObligationFacadeEvidenceAdapter.hpp
 * @brief Common facade adapter for obligation readiness evidence.
 */
namespace assembler::communication_context {
    struct TObligationFacadeEvidenceAdapter final {
        [[nodiscard]] static constexpr TAsccObligationReadinessView to_readiness_view(TObligationReport report, TObligationRuntimeView view) noexcept {
            const bool ok = report.is_satisfied() && view.ready();
            return TAsccObligationReadinessView{ok ? TAsccComponentReadinessStatus::ready : TAsccComponentReadinessStatus::blocked, report, view, "obligation readiness"};
        }
    };
}
