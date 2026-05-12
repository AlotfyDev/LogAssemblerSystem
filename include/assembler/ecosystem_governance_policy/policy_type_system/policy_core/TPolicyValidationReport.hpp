#pragma once

#include <cstdint>
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyStatus.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyIssue.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyValidationReport.hpp
 * Wave: EG-POL-W09_TPolicy_Aggregate_And_View
 * Domain: ecosystem_governance / policy_type_system / policy_core
 *
 * Full architectural responsibility:
 *   TPolicyValidationReport is the W09 aggregate-level validation evidence
 *   carrier for a composed TPolicy. It reports whether the mandatory semantic
 *   and structural slots of a policy object are present without becoming a
 *   policy graph invariant engine, traversal validator, registry validator,
 *   realization executor, or persistence diagnostic.
 *
 * Why this file exists in W09:
 *   W09 is the first wave allowed to introduce TPolicy as an aggregate over
 *   prior foundations. That aggregate requires a local, compact report that can
 *   say whether identity, clauses, safe replacement, lifecycle, observation,
 *   realization binding, and graph structure are sufficiently present for the
 *   object to be treated as a structurally usable policy. This report keeps
 *   validation at the aggregate surface and prevents callers from confusing
 *   validation with execution.
 *
 * Relationship to previous waves:
 *   - W01 provides primitive status and issue vocabulary reused here.
 *   - W02 provides clause presence and usability information.
 *   - W03 provides safe replacement and safe-point semantics.
 *   - W04 provides lifecycle/state capability.
 *   - W05 provides observation/audit capability.
 *   - W06 provides realization binding descriptors.
 *   - W07 provides policy graph structural validity.
 *   - W08 provides optional traversal foundation types.
 *
 * Relationship to other files in this wave:
 *   - TPolicy uses this report to express aggregate validation.
 *   - TPolicyBuildResult carries this report with a primitive result.
 *   - TPolicyView may expose high-level completeness booleans derived from this
 *     report rather than exposing mutable internals.
 *
 * Relationship to future waves:
 *   - W10 assignment may consume this report to refuse assignment of incomplete
 *     policies.
 *   - W11 registry basics may use this report to classify registry entries.
 *   - Future diagnostics may translate this report into observation evidence,
 *     but this file is not itself a logging, telemetry, or audit exporter.
 *
 * Explicit non-responsibilities:
 *   TPolicyValidationReport does not build a policy, mutate a policy, execute a
 *   policy, traverse a policy graph, assign a policy, register a policy, invoke
 *   a realization mechanism, own a target object, or persist audit evidence.
 *
 * Current implementation note:
 *   W09 intentionally provides a compact value type with boolean flags and a
 *   primitive issue code. Later waves may introduce richer diagnostics while
 *   preserving this report's role as aggregate-level validation evidence.
 */
struct TPolicyValidationReport final
{
    bool identity_present{false};
    bool clauses_present{false};
    bool replacement_present{false};
    bool lifecycle_present{false};
    bool observation_present{false};
    bool realization_binding_present{false};
    bool graph_present{false};
    bool graph_minimum_valid{false};
    bool traversal_foundation_present{false};
    TPolicyIssue issue{};

    [[nodiscard]] constexpr bool HasMandatorySemanticBase() const noexcept
    {
        return identity_present &&
               clauses_present &&
               replacement_present &&
               lifecycle_present &&
               observation_present &&
               realization_binding_present;
    }

    [[nodiscard]] constexpr bool HasMandatoryStructuralBase() const noexcept
    {
        return graph_present && graph_minimum_valid;
    }

    [[nodiscard]] constexpr bool IsStructurallyComplete() const noexcept
    {
        return HasMandatorySemanticBase() && HasMandatoryStructuralBase();
    }

    [[nodiscard]] constexpr TPolicyStatus Status() const noexcept
    {
        return IsStructurallyComplete() ? TPolicyStatus::valid : TPolicyStatus::incomplete;
    }

    [[nodiscard]] constexpr TPolicyIssue::code_type MissingMask() const noexcept
    {
        return (identity_present ? 0u : 1u) |
               (clauses_present ? 0u : 2u) |
               (replacement_present ? 0u : 4u) |
               (lifecycle_present ? 0u : 8u) |
               (observation_present ? 0u : 16u) |
               (realization_binding_present ? 0u : 32u) |
               (graph_present ? 0u : 64u) |
               (graph_minimum_valid ? 0u : 128u);
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
