#pragma once

/*
    LOGAPI-W22 — Timestamp Stabilization Policies Optional

    Responsibility:
        Define optional policy-sensitive timestamp stabilization descriptors,
        timestamp stabilization rule profiles, change/switch requests, readiness
        reports, and policy-reference carriers.

    Boundary:
        This wave does not implement ecosystem governance, policy assignment,
        TPolicyObjectHost, realizer behavior, clock acquisition, calendar conversion,
        envelope assembly, circulation handoff, or persistence.

    Doctrine:
        Timestamp stabilization can run as configuration.
        Changing timestamp semantics may be policy-sensitive.
        This wave only models optional governance hooks for timestamp profiles.
*/

#include "TLogApiTimestampProfileSwitchKind.hpp"
#include "TLogApiTimestampSafePointFlag.hpp"
#include "TLogApiTimestampStabilizationRuleDescriptor.hpp"

namespace assembler::log_level_api::timestamp_stabilizer::optional_policies {

/*
    Timestamp profile switch request.

    This request only models readiness to switch. It does not perform policy
    assignment and does not mutate a live timestamp stabilizer.
*/
struct TLogApiTimestampProfileSwitchRequest final {
    TLogApiTimestampProfileSwitchKind switch_kind{TLogApiTimestampProfileSwitchKind::Unknown};
    TLogApiTimestampStabilizationRuleDescriptor current_rule{};
    TLogApiTimestampStabilizationRuleDescriptor target_rule{};
    TLogApiTimestampSafePointFlag safe_point{};

    [[nodiscard]] bool IsReady() const noexcept {
        if (switch_kind == TLogApiTimestampProfileSwitchKind::Unknown) return false;
        if (!current_rule.IsDeclared()) return false;
        if (!target_rule.IsDeclared()) return false;

        if (switch_kind == TLogApiTimestampProfileSwitchKind::SafePointReplacement) {
            return safe_point.IsRaised(TLogApiTimestampSafePointKind::BeforeProfileReplacement);
        }

        if (switch_kind == TLogApiTimestampProfileSwitchKind::PolicySensitiveReplacement) {
            return target_rule.policy_ref.IsPresent();
        }

        return true;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::optional_policies
