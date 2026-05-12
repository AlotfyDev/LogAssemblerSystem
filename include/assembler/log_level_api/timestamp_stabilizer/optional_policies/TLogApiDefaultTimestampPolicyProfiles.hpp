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

#include "assembler/log_level_api/timestamp_stabilizer/TLogApiDefaultTimestampProfile.hpp"

#include "TLogApiTimestampStabilizationRuleDescriptor.hpp"

namespace assembler::log_level_api::timestamp_stabilizer::optional_policies {

struct TLogApiDefaultTimestampPolicyProfiles final {
    [[nodiscard]] static TLogApiTimestampStabilizationRuleDescriptor MakeConfigurationOnlyRule() {
        TLogApiTimestampStabilizationRuleDescriptor rule{};
        rule.id = TLogApiTimestampStabilizationRuleId{1};
        rule.status = TLogApiTimestampStabilizationRuleStatus::Active;
        rule.rule_name = "default.timestamp.configuration_only.rule";
        rule.sensitivity = TLogApiTimestampPolicySensitivityKind::ConfigurationOnly;
        rule.config = assembler::log_level_api::timestamp_stabilizer::TLogApiDefaultTimestampProfile::Make();
        return rule;
    }

    [[nodiscard]] static TLogApiTimestampStabilizationRuleDescriptor MakePolicySensitiveRule() {
        auto rule = MakeConfigurationOnlyRule();
        rule.id = TLogApiTimestampStabilizationRuleId{2};
        rule.rule_name = "default.timestamp.policy_sensitive.rule";
        rule.sensitivity = TLogApiTimestampPolicySensitivityKind::PolicySensitive;
        rule.policy_ref = {"timestamp-policy-default", "timestamp_stabilization", "v1"};
        return rule;
    }

    [[nodiscard]] static TLogApiTimestampStabilizationRuleDescriptor MakeSafePointReplacementRule() {
        auto rule = MakePolicySensitiveRule();
        rule.id = TLogApiTimestampStabilizationRuleId{3};
        rule.rule_name = "default.timestamp.safe_point_replacement.rule";
        rule.sensitivity = TLogApiTimestampPolicySensitivityKind::RequiresSafePoint;
        rule.policy_ref = {"timestamp-policy-safe-point", "timestamp_stabilization", "v1"};
        return rule;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::optional_policies
