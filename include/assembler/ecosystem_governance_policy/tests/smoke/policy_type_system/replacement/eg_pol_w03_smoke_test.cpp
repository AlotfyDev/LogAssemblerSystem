#include <cassert>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp>
#include <assembler/ecosystem_governance/policy_type_system/clauses/TPolicyClauseId.hpp>
#include <assembler/ecosystem_governance/policy_type_system/replacement/TPolicySafePoint.hpp>
#include <assembler/ecosystem_governance/policy_type_system/replacement/TPolicyReplacementBoundary.hpp>
#include <assembler/ecosystem_governance/policy_type_system/replacement/TPolicyReplacementRule.hpp>
#include <assembler/ecosystem_governance/policy_type_system/replacement/TPolicyReplacementPlan.hpp>
#include <assembler/ecosystem_governance/policy_type_system/replacement/TPolicyReplacementView.hpp>

using namespace assembler::ecosystem_governance::policy_type_system;

int main()
{
    const TPolicyId policy{100};
    const TPolicyId replacement{101};
    const TPolicyClauseId clause{200};
    const TPolicySafePointId safePointId{300};

    const TPolicySafePoint safePoint{
        safePointId,
        policy,
        TPolicySafePointKind::replacement_eligibility_anchor,
        TPolicyReplacementEligibility::eligible,
        1,
        clause
    };

    assert(safePoint.HasIdentity());
    assert(safePoint.HasOwnerPolicy());
    assert(safePoint.IsClauseBound());
    assert(safePoint.IsStructurallyUsable());
    assert(safePoint.IsEligible());

    const TPolicyReplacementBoundary boundary{
        policy,
        safePointId,
        TPolicySafePointKind::replacement_eligibility_anchor,
        TPolicyReplacementEligibility::eligible,
        10
    };

    assert(boundary.IsStructurallyUsable());
    assert(boundary.IsEligible());

    const TPolicyReplacementRule rule{
        900,
        policy,
        TPolicySafePointKind::replacement_eligibility_anchor,
        TPolicyReplacementEligibility::eligible,
        false,
        true
    };

    assert(rule.IsStructurallyUsable());

    const TPolicyReplacementPlan plan{
        800,
        policy,
        replacement,
        safePointId,
        TPolicyReplacementEligibility::eligible,
        rule.rule_token
    };

    assert(plan.IsStructurallyUsable());
    assert(plan.IsEligible());
    assert(plan.HasRuleToken());

    const auto safeView = TPolicyReplacementView::FromSafePoint(safePoint);
    const auto boundaryView = TPolicyReplacementView::FromBoundary(boundary);
    const auto planView = TPolicyReplacementView::FromPlan(plan);

    assert(safeView.IsStructurallyUsable());
    assert(boundaryView.IsStructurallyUsable());
    assert(planView.IsStructurallyUsable());
    assert(safeView.IsEligible());
    assert(boundaryView.IsEligible());
    assert(planView.IsEligible());

    static_assert(IsKnown(TPolicySafePointKind::activation_boundary), "safe point kind helper should work");
    static_assert(IsReplacementAllowed(TPolicyReplacementEligibility::eligible), "eligibility helper should work");
    static_assert(!IsReplacementAllowed(TPolicyReplacementEligibility::blocked), "blocked is not allowed");

    return 0;
}
