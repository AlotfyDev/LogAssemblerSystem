#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicySafePointKind.hpp
 * Wave: EG-POL-W03_Safe_Point_And_Replacement
 * Domain: ecosystem_governance / policy_type_system / replacement
 *
 * Full architectural responsibility:
 *   TPolicySafePointKind classifies the semantic role of a safe point in the
 *   policy replacement model. It captures whether the anchor represents an
 *   activation boundary, suspension boundary, replacement eligibility anchor,
 *   retirement boundary, clause-sensitive replacement point, or a generic
 *   structural boundary.
 *
 * Why this file exists in W03:
 *   Safe replacement semantics are not optional decoration. They are a
 *   foundational part of policy-object meaning. W03 needs an explicit kind
 *   vocabulary before safe point carriers, replacement boundaries, replacement
 *   rules, and replacement plans can be represented.
 *
 * Relationship to other files in this wave:
 *   - TPolicySafePoint uses this enum to classify safe point instances.
 *   - TPolicyReplacementBoundary may constrain which safe point kinds can act
 *     as replacement boundaries.
 *   - TPolicyReplacementRule may require a specific safe point kind before a
 *     replacement plan is considered structurally eligible.
 *
 * Relationship to future waves:
 *   - W04 lifecycle may map lifecycle transition phases to specific safe point
 *     kinds.
 *   - W07 graph structure may expose safe point node kind through this enum.
 *   - W08 traversal foundation may reference safe point kinds only as metadata;
 *     it must not convert them into traversal behavior.
 *
 * Explicit non-responsibilities:
 *   This enum does not decide whether replacement is currently allowed, does
 *   not execute a swap, does not encode synchronization semantics, and does not
 *   own target object state.
 *
 * Current implementation note:
 *   The kind list is intentionally conservative and can grow in later waves as
 *   concrete policy families introduce richer replacement surfaces.
 */
enum class TPolicySafePointKind : std::uint8_t
{
    unknown = 0,
    structural_boundary = 1,
    activation_boundary = 2,
    suspension_boundary = 3,
    replacement_eligibility_anchor = 4,
    clause_sensitive_anchor = 5,
    retirement_boundary = 6,
    manual_review_anchor = 7
};

[[nodiscard]] constexpr bool IsKnown(TPolicySafePointKind kind) noexcept
{
    return kind != TPolicySafePointKind::unknown;
}

} // namespace assembler::ecosystem_governance::policy_type_system
