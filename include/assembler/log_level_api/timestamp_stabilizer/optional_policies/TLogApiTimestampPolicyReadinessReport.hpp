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

#include <vector>

#include "TLogApiTimestampPolicyReadinessIssue.hpp"
#include "TLogApiTimestampStabilizationRuleDescriptor.hpp"

namespace assembler::log_level_api::timestamp_stabilizer::optional_policies {

struct TLogApiTimestampPolicyReadinessReport final {
    TLogApiTimestampStabilizationRuleDescriptor rule{};
    std::vector<TLogApiTimestampPolicyReadinessIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsReady() const noexcept {
        return rule.IsDeclared() && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::optional_policies
