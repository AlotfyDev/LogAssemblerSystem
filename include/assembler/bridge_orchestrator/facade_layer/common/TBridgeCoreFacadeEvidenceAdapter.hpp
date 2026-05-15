#pragma once
#include "assembler/communication_context/bridge_core/issues/TBridgeCoreIssue.hpp"
#include "assembler/communication_context/bridge_core/views/TBridgeCoreView.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccBridgeReadinessView.hpp"

namespace assembler::communication_context
{
    struct TBridgeCoreFacadeEvidenceAdapter final
    {
        [[nodiscard]] static constexpr TAsccBridgeReadinessView to_readiness_view(
            TBridgeCoreView view,
            TBridgeCoreIssue issue,
            std::string_view note = {}) noexcept
        {
            return {
                view.is_valid() && !issue.is_present()
                    ? TAsccComponentReadinessStatus::ready
                    : TAsccComponentReadinessStatus::blocked,
                view,
                issue,
                note
            };
        }
    };
}
