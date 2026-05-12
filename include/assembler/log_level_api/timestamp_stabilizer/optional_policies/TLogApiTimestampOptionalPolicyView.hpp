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

#include "TLogApiTimestampStabilizationRuleDescriptor.hpp"

namespace assembler::log_level_api::timestamp_stabilizer::optional_policies {

struct TLogApiTimestampOptionalPolicyView final {
    std::string rule_id{};
    std::string rule_name{};
    std::string sensitivity{};
    std::string policy_id{};
    bool declared{false};

    [[nodiscard]] static TLogApiTimestampOptionalPolicyView From(const TLogApiTimestampStabilizationRuleDescriptor& rule) {
        TLogApiTimestampOptionalPolicyView view{};
        view.rule_id = rule.id.ToString();
        view.rule_name = rule.rule_name;
        view.policy_id = rule.policy_ref.policy_id;
        view.declared = rule.IsDeclared();

        switch (rule.sensitivity) {
            case TLogApiTimestampPolicySensitivityKind::ConfigurationOnly: view.sensitivity = "configuration_only"; break;
            case TLogApiTimestampPolicySensitivityKind::PolicySensitive: view.sensitivity = "policy_sensitive"; break;
            case TLogApiTimestampPolicySensitivityKind::RequiresSafePoint: view.sensitivity = "requires_safe_point"; break;
            default: view.sensitivity = "unknown"; break;
        }

        return view;
    }
};

} // namespace assembler::log_level_api::timestamp_stabilizer::optional_policies
