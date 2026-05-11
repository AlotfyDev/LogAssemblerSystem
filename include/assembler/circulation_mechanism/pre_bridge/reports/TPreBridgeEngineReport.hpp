#pragma once
#include "TPreBridgeEngineReportId.hpp"
#include "TPreBridgeEngineIssueKind.hpp"
#include "../TPreBridgeEngineId.hpp"
#include "../runtime/TPreBridgeRuntimeState.hpp"

/*
    TPreBridgeEngineReport.hpp

    Current responsibility:
        Evidence report for PreBridge engine configuration/lifecycle.

    Non-ownership:
        Report does not execute runtime.
*/
namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

struct TPreBridgeEngineReport final {
    TPreBridgeEngineReportId report_id{};
    TPreBridgeEngineId engine_id{};
    TPreBridgeRuntimeState before{TPreBridgeRuntimeState::unconfigured};
    TPreBridgeRuntimeState after{TPreBridgeRuntimeState::unconfigured};
    TPreBridgeEngineIssueKind issue{TPreBridgeEngineIssueKind::none};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return report_id.is_valid() && engine_id.is_valid(); }
    [[nodiscard]] constexpr bool passed() const noexcept { return is_valid() && issue == TPreBridgeEngineIssueKind::none; }
};
} // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler
