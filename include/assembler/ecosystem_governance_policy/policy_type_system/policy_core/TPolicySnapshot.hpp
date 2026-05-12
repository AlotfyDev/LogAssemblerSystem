#pragma once

#include <cstddef>
#include <cstdint>
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyFamilyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyVersion.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyScope.hpp"
#include "assembler/ecosystem_governance/policy_type_system/lifecycle/TPolicyLifecycleState.hpp"
#include "assembler/ecosystem_governance/policy_type_system/replacement/TPolicyReplacementEligibility.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicySnapshot.hpp
 * Wave: EG-POL-W09_TPolicy_Aggregate_And_View
 * Domain: ecosystem_governance / policy_type_system / policy_core
 *
 * Full architectural responsibility:
 *   TPolicySnapshot is an immutable-by-value summary of aggregate policy state.
 *   It captures policy identity, lifecycle state, replacement eligibility,
 *   component counts, and structural completeness flags without exposing the
 *   mutable clause set, graph arrays, audit trail storage, realization binding,
 *   or traversal foundation arrays.
 *
 * Why this file exists in W09:
 *   Once TPolicy is introduced, callers need a safe summary surface that can be
 *   copied, returned, logged by tests, or used by later assignment/registry
 *   layers without depending on aggregate internals. Snapshot is intentionally
 *   smaller than TPolicyView and does not expose pointers.
 *
 * Relationship to previous waves:
 *   - W01 identity fields anchor the snapshot.
 *   - W03 replacement eligibility communicates replacement readiness as data.
 *   - W04 lifecycle state communicates lifecycle position as data.
 *   - W07/W08 counts summarize graph and traversal material without owning or
 *     traversing either layer.
 *
 * Relationship to other files in this wave:
 *   - TPolicy produces TPolicySnapshot.
 *   - TPolicyView may include a TPolicySnapshot for compact public reporting.
 *   - TPolicyBuildResult may use snapshot-like fields later, but W09 keeps build
 *     result focused on validation.
 *
 * Relationship to future waves:
 *   - W10 assignment may store a snapshot when deciding whether an assignment is
 *     safe.
 *   - W11 registry entries may use snapshots as registry-facing descriptions.
 *
 * Explicit non-responsibilities:
 *   TPolicySnapshot is not a lifecycle engine, not an audit record, not a graph
 *   view, not a traversal view, not an assignment record, not a registry entry,
 *   not a realizer, and not a target reference.
 *
 * Current implementation note:
 *   W09 keeps the snapshot as a small value object. Later waves may extend it
 *   with additional version, graph, registry, or assignment descriptors while
 *   preserving its copy-safe summary role.
 */
struct TPolicySnapshot final
{
    TPolicyId policy_id{};
    TPolicyFamilyId family_id{};
    TPolicyVersion version{};
    TPolicyScope scope{TPolicyScope::unspecified};
    TPolicyLifecycleState lifecycle_state{TPolicyLifecycleState::unknown};
    TPolicyReplacementEligibility replacement_eligibility{TPolicyReplacementEligibility::unknown};
    std::size_t clause_count{0};
    std::size_t audit_marker_count{0};
    std::size_t graph_node_count{0};
    std::size_t graph_edge_count{0};
    std::size_t traversal_channel_count{0};
    bool structurally_complete{false};

    [[nodiscard]] constexpr bool HasIdentity() const noexcept
    {
        return policy_id.IsValid() && family_id.IsValid() && !version.IsZero() && IsSpecified(scope);
    }

    [[nodiscard]] constexpr bool HasClauses() const noexcept { return clause_count > 0; }
    [[nodiscard]] constexpr bool HasGraphMaterial() const noexcept { return graph_node_count > 0; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
