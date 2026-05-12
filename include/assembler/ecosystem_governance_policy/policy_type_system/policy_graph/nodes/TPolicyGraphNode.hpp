#pragma once

#include <cstdint>
#include "TPolicyGraphNodeId.hpp"
#include "TPolicyGraphNodeKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_graph/TPolicyGraphId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/clauses/TPolicyClauseId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/replacement/TPolicySafePointId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyRealizationBindingId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/observation/TPolicyObservationId.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyGraphNode.hpp
 * Wave: EG-POL-W07_Policy_Graph_Structure
 * Domain: ecosystem_governance / policy_type_system / policy_graph / nodes
 *
 * Full architectural responsibility:
 *   TPolicyGraphNode is the compact structural node carrier for the policy graph. It stores graph identity, node identity, node kind, owner policy identity, and optional references to semantic primitives from earlier waves.
 *
 * Why this file exists in W07:
 *   W07 introduces policy graph structure after identity, clauses, replacement, lifecycle, observation, and realization binding exist. This node lets those prior semantic elements appear as graph structure without becoming a final TPolicy aggregate.
 *
 * Relationship to previous waves:
 *   W01 supplies TPolicyId; W02 supplies TPolicyClauseId; W03 supplies TPolicySafePointId; W05 supplies TPolicyObservationId; W06 supplies TPolicyRealizationBindingId. TPolicyGraphNode may reference those primitives without owning or executing them.
 *
 * Relationship to other files in this wave:
 *   TPolicyGraphEdge connects node identities. TPolicyGraphInvariant checks whether sufficient node kinds exist. TPolicyGraphView exposes nodes without mutation.
 *
 * Relationship to future waves:
 *   W08 traversal may later build channel foundations that refer to graph structure, but this node is not a traversal channel. W09 TPolicy may aggregate nodes through TPolicyGraph.
 *
 * Explicit non-responsibilities:
 *   TPolicyGraphNode is not a policy aggregate, not a clause body, not a safe-point algorithm, not lifecycle transition logic, not realization binding execution, not observation storage, not a traversal step, and not a target object.
 *
 * Current implementation note:
 *   W07 intentionally provides compact structural carriers and invariant helpers only. The opening documentation records the complete intended architectural picture even where the current code is a minimal foundation block.
 */
struct TPolicyGraphNode final
{
    TPolicyGraphId graph_id{};
    TPolicyGraphNodeId node_id{};
    TPolicyGraphNodeKind kind{TPolicyGraphNodeKind::unknown};
    TPolicyId owner_policy_id{};
    TPolicyClauseId clause_ref{};
    TPolicySafePointId safe_point_ref{};
    TPolicyRealizationBindingId realization_binding_ref{};
    TPolicyObservationId observation_ref{};
    std::uint64_t auxiliary_ref{0};
    std::uint32_t flags{0};

    constexpr TPolicyGraphNode() noexcept = default;

    constexpr TPolicyGraphNode(
        TPolicyGraphId graph,
        TPolicyGraphNodeId node,
        TPolicyGraphNodeKind node_kind,
        TPolicyId owner = {},
        std::uint64_t aux = 0,
        std::uint32_t node_flags = 0) noexcept
        : graph_id(graph), node_id(node), kind(node_kind), owner_policy_id(owner), auxiliary_ref(aux), flags(node_flags) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept
    {
        return graph_id.IsValid() && node_id.IsValid() && IsKnownPolicyGraphNodeKind(kind);
    }

    [[nodiscard]] constexpr bool IsRoot() const noexcept { return kind == TPolicyGraphNodeKind::policy_root; }
    [[nodiscard]] constexpr bool IsMandatoryKind() const noexcept { return IsMandatoryPolicyGraphNodeKind(kind); }
    [[nodiscard]] constexpr bool HasOwnerPolicy() const noexcept { return owner_policy_id.IsValid(); }
    [[nodiscard]] constexpr bool HasClauseRef() const noexcept { return clause_ref.IsValid(); }
    [[nodiscard]] constexpr bool HasSafePointRef() const noexcept { return safe_point_ref.IsValid(); }
    [[nodiscard]] constexpr bool HasRealizationBindingRef() const noexcept { return realization_binding_ref.IsValid(); }
    [[nodiscard]] constexpr bool HasObservationRef() const noexcept { return observation_ref.IsValid(); }
};

} // namespace assembler::ecosystem_governance::policy_type_system
