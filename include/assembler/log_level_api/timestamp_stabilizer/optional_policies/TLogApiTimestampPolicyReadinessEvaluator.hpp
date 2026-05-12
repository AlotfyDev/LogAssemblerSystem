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

#include "TLogApiTimestampPolicyReadinessReport.hpp"

namespace assembler::log_level_api::timestamp_stabilizer::optional_policies {

class TLogApiTimestampPolicyReadinessEvaluator final {
public:
    [[nodiscard]] static TLogApiTimestampPolicyReadinessReport Evaluate(
        const TLogApiTimestampStabilizationRuleDescriptor& rule
    ) {
        TLogApiTimestampPolicyReadinessReport report{};
        report.rule = rule;

        if (!rule.IsDeclared()) {
            report.issues.push_back({
                "LOGAPI_TIMESTAMP_RULE_NOT_DECLARED",
                "Timestamp stabilization rule is not declared.",
                true
            });
            return report;
        }

        if (rule.sensitivity != TLogApiTimestampPolicySensitivityKind::ConfigurationOnly
            && !rule.policy_ref.IsPresent()) {
            report.issues.push_back({
                "LOGAPI_TIMESTAMP_POLICY_REF_MISSING",
                "Policy-sensitive timestamp rule requires a policy reference.",
                true
            });
        }

        return report;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::optional_policies
