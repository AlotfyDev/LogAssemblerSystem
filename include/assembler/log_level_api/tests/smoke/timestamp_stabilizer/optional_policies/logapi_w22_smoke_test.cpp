#include <cassert>
#include <iostream>

#include "assembler/log_level_api/timestamp_stabilizer/optional_policies/TLogApiTimestampOptionalPolicySurface.hpp"

int main() {
    using namespace assembler::log_level_api::timestamp_stabilizer::optional_policies;

    auto config_only = TLogApiDefaultTimestampPolicyProfiles::MakeConfigurationOnlyRule();
    assert(config_only.IsDeclared());

    auto policy_sensitive = TLogApiDefaultTimestampPolicyProfiles::MakePolicySensitiveRule();
    assert(policy_sensitive.IsDeclared());
    assert(policy_sensitive.policy_ref.IsPresent());

    auto readiness = TLogApiTimestampPolicyReadinessEvaluator::Evaluate(policy_sensitive);
    assert(readiness.IsReady());

    auto safe_point_rule = TLogApiDefaultTimestampPolicyProfiles::MakeSafePointReplacementRule();
    assert(safe_point_rule.IsDeclared());

    TLogApiTimestampProfileSwitchRequest not_ready{};
    not_ready.switch_kind = TLogApiTimestampProfileSwitchKind::SafePointReplacement;
    not_ready.current_rule = config_only;
    not_ready.target_rule = safe_point_rule;
    not_ready.safe_point = {TLogApiTimestampSafePointKind::BeforeTimestampStabilization, true};

    auto rejected = TLogApiTimestampProfileSwitchPlanner::Plan(not_ready);
    assert(!rejected.IsAccepted());

    TLogApiTimestampProfileSwitchRequest ready{};
    ready.switch_kind = TLogApiTimestampProfileSwitchKind::SafePointReplacement;
    ready.current_rule = config_only;
    ready.target_rule = safe_point_rule;
    ready.safe_point = {TLogApiTimestampSafePointKind::BeforeProfileReplacement, true};

    auto accepted = TLogApiTimestampProfileSwitchPlanner::Plan(ready);
    assert(accepted.IsAccepted());
    assert(accepted.effective_rule.rule_name == "default.timestamp.safe_point_replacement.rule");

    auto view = TLogApiTimestampOptionalPolicyView::From(safe_point_rule);
    assert(view.declared);
    assert(view.sensitivity == "requires_safe_point");
    assert(view.policy_id == "timestamp-policy-safe-point");

    std::cout << "LOGAPI-W22 smoke test passed\\n";
    return 0;
}
