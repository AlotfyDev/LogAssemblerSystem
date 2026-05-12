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

#include <string>

#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampStabilizerConfig.hpp"
#include "TLogApiTimestampPolicyRef.hpp"
#include "TLogApiTimestampPolicySensitivityKind.hpp"
#include "TLogApiTimestampStabilizationRuleId.hpp"
#include "TLogApiTimestampStabilizationRuleStatus.hpp"

namespace assembler::log_level_api::timestamp_stabilizer::optional_policies {

/*
    Policy-sensitive timestamp rule descriptor.

    It wraps a timestamp stabilizer configuration and classifies whether changes
    to that configuration are plain configuration changes or policy-sensitive.
*/
struct TLogApiTimestampStabilizationRuleDescriptor final {
    TLogApiTimestampStabilizationRuleId id{};
    TLogApiTimestampStabilizationRuleStatus status{TLogApiTimestampStabilizationRuleStatus::Unknown};

    std::string rule_name{};
    TLogApiTimestampPolicySensitivityKind sensitivity{TLogApiTimestampPolicySensitivityKind::Unknown};
    TLogApiTimestampPolicyRef policy_ref{};
    assembler::log_level_api::timestamp_stabilizer::TLogApiTimestampStabilizerConfig config{};

    [[nodiscard]] bool IsDeclared() const noexcept {
        if (!id.IsValid()) return false;
        if (status == TLogApiTimestampStabilizationRuleStatus::Unknown
            || status == TLogApiTimestampStabilizationRuleStatus::Rejected) return false;
        if (rule_name.empty()) return false;
        if (sensitivity == TLogApiTimestampPolicySensitivityKind::Unknown) return false;
        if (!config.IsResolved()) return false;

        if (sensitivity != TLogApiTimestampPolicySensitivityKind::ConfigurationOnly
            && !policy_ref.IsPresent()) return false;

        return true;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::optional_policies
