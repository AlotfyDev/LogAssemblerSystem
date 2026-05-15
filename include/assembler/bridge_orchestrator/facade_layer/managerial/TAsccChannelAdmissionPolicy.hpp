#pragma once
#include "assembler/communication_context/channels/reports/TChannelRuntimeReport.hpp"
#include "assembler/communication_context/facade_layer/common/TChannelFacadeEvidenceAdapter.hpp"

/**
 * @file TAsccChannelAdmissionPolicy.hpp
 * @brief Managerial facade policy for ASCC channel admission.
 */
namespace assembler::communication_context {
    struct TAsccChannelAdmissionPolicy final {
        [[nodiscard]] static constexpr TAsccChannelReadinessView admit(TChannelRuntimeReport report) noexcept {
            return TChannelFacadeEvidenceAdapter::to_readiness_view(report);
        }
    };
}
