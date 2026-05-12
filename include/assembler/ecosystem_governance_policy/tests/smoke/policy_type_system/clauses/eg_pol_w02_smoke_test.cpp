#include <cassert>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp>
#include <assembler/ecosystem_governance/policy_type_system/clauses/TPolicyClauseId.hpp>
#include <assembler/ecosystem_governance/policy_type_system/clauses/TPolicyClauseKind.hpp>
#include <assembler/ecosystem_governance/policy_type_system/clauses/TPolicyClauseRole.hpp>
#include <assembler/ecosystem_governance/policy_type_system/clauses/TPolicyClauseStatus.hpp>
#include <assembler/ecosystem_governance/policy_type_system/clauses/TPolicyClause.hpp>
#include <assembler/ecosystem_governance/policy_type_system/clauses/TPolicyClauseView.hpp>
#include <assembler/ecosystem_governance/policy_type_system/clauses/TPolicyClauseSet.hpp>

int main()
{
    using namespace assembler::ecosystem_governance::policy_type_system;

    constexpr TPolicyId policyId{100};
    constexpr TPolicyClauseId clauseId{1};
    constexpr TPolicyClause clause{
        clauseId,
        policyId,
        TPolicyClauseKind::directive,
        TPolicyClauseRole::primary,
        0,
        999
    };

    static_assert(clauseId.IsValid(), "clause id should be valid");
    static_assert(IsSpecified(TPolicyClauseKind::directive), "clause kind should be specified");
    static_assert(IsSpecified(TPolicyClauseRole::primary), "clause role should be specified");
    static_assert(IsUsable(TPolicyClauseStatus::valid), "valid clause status should be usable");
    static_assert(!IsFailure(TPolicyClauseStatus::dormant), "dormant is not a failure");
    static_assert(clause.IsStructurallyUsable(), "clause should be structurally usable");
    static_assert(clause.HasPayloadToken(), "payload token should be present");

    TPolicyClauseSet<4> set;
    assert(set.Empty());
    assert(set.Add(clause));
    assert(set.Size() == 1);
    assert(set.Contains(clauseId));
    assert(set.HasUsableClause());

    const TPolicyClauseView view = set.At(0);
    assert(view.IsBound());
    assert(view.Id() == clauseId);
    assert(view.OwnerPolicyId() == policyId);
    assert(view.Kind() == TPolicyClauseKind::directive);
    assert(view.Role() == TPolicyClauseRole::primary);
    assert(view.IsStructurallyUsable());

    const TPolicyClauseView missing = set.At(100);
    assert(!missing.IsBound());

    return 0;
}
