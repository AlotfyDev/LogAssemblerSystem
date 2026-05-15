#pragma once
#include "assembler/communication_context/channels/reports/TChannelRuntimeReport.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccChannelReadinessView.hpp"

/**
 * @file TChannelFacadeEvidenceAdapter.hpp
 * @brief Common facade adapter for ASCC channel runtime evidence.
 */
namespace assembler::communication_context {
    struct TChannelFacadeEvidenceAdapter final {
        [[nodiscard]] static constexpr TAsccChannelReadinessView to_readiness_view(TChannelRuntimeReport report) noexcept {
            return TAsccChannelReadinessView::from_report(report);
        }
    };
}
