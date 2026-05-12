#pragma once

#include <cstddef>
#include "TPolicySnapshot.hpp"
#include "TPolicyValidationReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/lifecycle/TPolicyLifecycleView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/replacement/TPolicyReplacementView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyRealizationBindingView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_graph/views/TPolicyGraphView.hpp"
#include "assembler/ecosystem_governance/policy_type_system/traversal_foundation/TPolicyTraversalFoundationView.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyView.hpp
 * Wave: EG-POL-W09_TPolicy_Aggregate_And_View
 * Domain: ecosystem_governance / policy_type_system / policy_core
 *
 * Full architectural responsibility:
 *   TPolicyView is the read-only aggregate projection over a TPolicy. It exposes
 *   high-level identity, lifecycle, replacement, realization binding, structural
 *   graph, traversal foundation, and validation information without granting
 *   mutation authority over the policy aggregate or any lower-layer carrier.
 *
 * Why this file exists in W09:
 *   W09 introduces TPolicy as the first aggregate over the earlier foundation
 *   waves. A view is required so callers can inspect the aggregate while the
 *   implementation continues to preserve strict separation between policy data,
 *   realization execution, target ownership, assignment, and registry behavior.
 *
 * Relationship to previous waves:
 *   - W04 lifecycle view is included as a lifecycle-only projection.
 *   - W03 replacement view is included as a descriptive safe replacement view.
 *   - W06 realization binding view is included as a non-executable descriptor.
 *   - W07 graph view remains structural and not traversal.
 *   - W08 traversal foundation view remains vocabulary and not engine.
 *
 * Relationship to other files in this wave:
 *   - TPolicy produces TPolicyView.
 *   - TPolicySnapshot supplies copy-safe summary information.
 *   - TPolicyValidationReport supplies aggregate completeness evidence.
 *
 * Relationship to future waves:
 *   - W10 assignment can consume this view to decide whether assignment may be
 *     represented.
 *   - W11 registry basics can expose a subset of this view through registry
 *     descriptors.
 *
 * Explicit non-responsibilities:
 *   TPolicyView does not mutate, build, assign, register, execute, traverse,
 *   schedule, invoke a target, own a target, export telemetry, write audit
 *   storage, or communicate with other domains.
 *
 * Current implementation note:
 *   W09 uses value and pointer-free subviews where possible. Any lower-level
 *   view that itself references external data remains read-only by contract.
 */
struct TPolicyView final
{
    TPolicySnapshot snapshot{};
    TPolicyValidationReport validation{};
    TPolicyLifecycleView lifecycle{};
    TPolicyReplacementView replacement{};
    TPolicyRealizationBindingView realization{};
    TPolicyGraphView graph{};
    TPolicyTraversalFoundationView traversal{};

    [[nodiscard]] constexpr bool IsPresent() const noexcept
    {
        return snapshot.HasIdentity();
    }

    [[nodiscard]] constexpr bool IsStructurallyComplete() const noexcept
    {
        return validation.IsStructurallyComplete();
    }

    [[nodiscard]] constexpr bool HasTraversalFoundation() const noexcept
    {
        return traversal.IsNonEmpty();
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
