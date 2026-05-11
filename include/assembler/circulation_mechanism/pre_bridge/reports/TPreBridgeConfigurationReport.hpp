#pragma once
#include "TPreBridgeEngineReportId.hpp"
#include "TPreBridgeConfigurationIssueKind.hpp"
#include "assembler/circulation_mechanism/pre_bridge/default_profile/TPreBridgeDefaultProfileId.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

struct TPreBridgeConfigurationReport final {
    TPreBridgeEngineReportId report_id{};
    TPreBridgeDefaultProfileId default_profile_id{};
    TPreBridgeConfigurationIssueKind issue{TPreBridgeConfigurationIssueKind::none};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return report_id.is_valid() && default_profile_id.is_valid();
    }

    [[nodiscard]] constexpr bool passed() const noexcept {
        return is_valid() && issue == TPreBridgeConfigurationIssueKind::none;
    }
};
} // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler
