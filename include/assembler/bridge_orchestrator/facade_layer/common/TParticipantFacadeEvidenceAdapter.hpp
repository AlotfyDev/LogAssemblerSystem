#pragma once
#include "assembler/communication_context/facade_layer/managerial/TAsccParticipantReadinessView.hpp"
#include "assembler/communication_context/participants/reports/TParticipantRuntimeReport.hpp"

/**
 * @file TParticipantFacadeEvidenceAdapter.hpp
 * @brief Common facade adapter for participant runtime evidence.
 */
namespace assembler::communication_context {
    struct TParticipantFacadeEvidenceAdapter final {
        [[nodiscard]] static constexpr TAsccParticipantReadinessView to_readiness_view(TParticipantRuntimeReport report) noexcept {
            return TAsccParticipantReadinessView::from_report(report);
        }
    };
}
