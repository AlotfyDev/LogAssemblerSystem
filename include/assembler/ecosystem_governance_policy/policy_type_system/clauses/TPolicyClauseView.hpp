#pragma once

#include "TPolicyClause.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyClauseView.hpp
 * Wave: EG-POL-W02_Policy_Clauses
 * Domain: ecosystem_governance / policy_type_system / clauses
 *
 * Full architectural responsibility:
 *   TPolicyClauseView is the read-only observation surface for a primitive
 *   policy clause. It allows later diagnostics, graph invariant checks,
 *   aggregate policy views, and registry descriptors to inspect clause
 *   structure without receiving mutation authority over the clause carrier.
 *
 * Why this file exists in W02:
 *   The Policy Type System requires early separation between carriers and
 *   views. A clause view lets W02 provide safe read access before W05
 *   observation/audit, W07 graph views, and W09 TPolicyView are introduced.
 *
 * Relationship to other files in this wave:
 *   - TPolicyClauseView references TPolicyClause.
 *   - TPolicyClauseSet may produce views over stored clauses.
 *   - TPolicyClauseKind, Role, Status, and Id remain visible through this view
 *     without exposing mutable storage.
 *
 * Relationship to future waves:
 *   - W07 PolicyGraphView may embed or translate TPolicyClauseView.
 *   - W09 TPolicyView may expose clause views to callers.
 *   - W05 observation records may reference clause views when describing
 *     evidence, but this file is not an audit model.
 *
 * Explicit non-responsibilities:
 *   TPolicyClauseView does not own a clause, does not extend clause lifetime,
 *   does not mutate clause state, does not evaluate clause truth, and does not
 *   perform traversal.
 */
class TPolicyClauseView final
{
public:
    constexpr TPolicyClauseView() noexcept = default;
    explicit constexpr TPolicyClauseView(const TPolicyClause* clause) noexcept : clause_(clause) {}

    [[nodiscard]] constexpr bool IsBound() const noexcept { return clause_ != nullptr; }
    [[nodiscard]] constexpr const TPolicyClause* Get() const noexcept { return clause_; }

    [[nodiscard]] constexpr TPolicyClauseId Id() const noexcept { return clause_ ? clause_->id : TPolicyClauseId{}; }
    [[nodiscard]] constexpr TPolicyId OwnerPolicyId() const noexcept { return clause_ ? clause_->owner_policy_id : TPolicyId{}; }
    [[nodiscard]] constexpr TPolicyClauseKind Kind() const noexcept { return clause_ ? clause_->kind : TPolicyClauseKind::unknown; }
    [[nodiscard]] constexpr TPolicyClauseRole Role() const noexcept { return clause_ ? clause_->role : TPolicyClauseRole::unspecified; }
    [[nodiscard]] constexpr TPolicyClauseStatus Status() const noexcept { return clause_ ? clause_->status : TPolicyClauseStatus::unknown; }
    [[nodiscard]] constexpr bool IsStructurallyUsable() const noexcept { return clause_ && clause_->IsStructurallyUsable(); }

private:
    const TPolicyClause* clause_{nullptr};
};

} // namespace assembler::ecosystem_governance::policy_type_system
