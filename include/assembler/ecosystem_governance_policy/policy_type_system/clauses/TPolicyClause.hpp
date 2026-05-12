#pragma once

#include <cstdint>
#include <assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp>
#include "TPolicyClauseId.hpp"
#include "TPolicyClauseKind.hpp"
#include "TPolicyClauseRole.hpp"
#include "TPolicyClauseStatus.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyClause.hpp
 * Wave: EG-POL-W02_Policy_Clauses
 * Domain: ecosystem_governance / policy_type_system / clauses
 *
 * Full architectural responsibility:
 *   TPolicyClause is the primitive structural carrier for one policy-local
 *   clause. It represents governing content at the clause level, but it does
 *   not become a full policy object. The complete policy aggregate will later
 *   compose one or more clauses together with identity, replacement, lifecycle,
 *   observation, realization binding, graph structure, and optional traversal
 *   foundation views.
 *
 * Why this file exists in W02:
 *   The Policy Object taxonomy requires clause presence as a mandatory
 *   structural element. W02 introduces a minimal clause value object so later
 *   waves can reason about safe-point participation, lifecycle diagnostics,
 *   graph clause nodes, TPolicy validation, assignment, and registry cataloging
 *   without inventing clause structure repeatedly.
 *
 * Relationship to other files in this wave:
 *   - TPolicyClauseId identifies the clause.
 *   - TPolicyClauseKind classifies clause content family.
 *   - TPolicyClauseRole describes policy-local participation.
 *   - TPolicyClauseStatus reports primitive clause structural status.
 *   - TPolicyClauseView exposes read-only access to this carrier.
 *   - TPolicyClauseSet groups multiple clauses without creating TPolicy.
 *
 * Relationship to future waves:
 *   - W03 replacement structures may bind safe points to clause identities.
 *   - W07 graph structure may wrap this carrier in clause nodes.
 *   - W08 traversal foundation must not treat a clause as a sequence channel.
 *   - W09 TPolicy will aggregate clauses and apply graph invariants over them.
 *
 * Explicit non-responsibilities:
 *   TPolicyClause does not evaluate truth, does not choose applicability, does
 *   not execute a realization mechanism, does not own a target object, does not
 *   define traversal order, and does not represent the full policy object.
 *
 * Current implementation note:
 *   W02 intentionally stores only structural metadata and a small payload token.
 *   Later family-specific clause payloads may be represented by descriptors,
 *   typed extensions, or graph-backed nodes without changing this file's basic
 *   role.
 */
struct TPolicyClause final
{
    using payload_token_type = std::uint64_t;
    using order_type = std::uint32_t;

    TPolicyClauseId id{};
    TPolicyId owner_policy_id{};
    TPolicyClauseKind kind{TPolicyClauseKind::unknown};
    TPolicyClauseRole role{TPolicyClauseRole::unspecified};
    TPolicyClauseStatus status{TPolicyClauseStatus::unknown};
    order_type order{0};
    payload_token_type payload_token{0};

    constexpr TPolicyClause() noexcept = default;

    constexpr TPolicyClause(
        TPolicyClauseId clauseId,
        TPolicyId ownerPolicyId,
        TPolicyClauseKind clauseKind,
        TPolicyClauseRole clauseRole,
        order_type clauseOrder = 0,
        payload_token_type payloadToken = 0) noexcept
        : id(clauseId),
          owner_policy_id(ownerPolicyId),
          kind(clauseKind),
          role(clauseRole),
          status(TPolicyClauseStatus::valid),
          order(clauseOrder),
          payload_token(payloadToken)
    {
    }

    [[nodiscard]] constexpr bool HasIdentity() const noexcept { return id.IsValid(); }
    [[nodiscard]] constexpr bool HasOwnerPolicy() const noexcept { return owner_policy_id.IsValid(); }
    [[nodiscard]] constexpr bool HasPayloadToken() const noexcept { return payload_token != 0; }
    [[nodiscard]] constexpr bool IsStructurallyUsable() const noexcept
    {
        return HasIdentity() && HasOwnerPolicy() && IsSpecified(kind) && IsSpecified(role) && IsUsable(status);
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
