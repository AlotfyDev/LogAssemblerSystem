#pragma once

#include "TPolicyIssue.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyResult.hpp
 * Wave: EG-POL-W01_Primitive_Policy_Identity
 * Domain: ecosystem_governance / policy_type_system / identity
 *
 * Full architectural responsibility:
 *   TPolicyResult is the primitive result carrier for identity-layer policy
 *   operations. It exists so early construction or validation steps can return
 *   a status and issue without creating exceptions, registry records, audit
 *   trails, lifecycle states, or aggregate policy objects.
 *
 * Why this file exists in W01:
 *   The identity layer needs a consistent way to represent success, invalidity,
 *   incompleteness, unsupported values, and conflicts. This result carrier
 *   keeps reporting local to the primitive policy identity wave.
 *
 * Relationship to other files:
 *   - TPolicyStatus supplies the primary result status.
 *   - TPolicyIssue supplies the optional issue detail.
 *   - Identity primitives may use TPolicyResult in future helper functions or
 *     construction routines.
 *
 * Relationship to future waves:
 *   - Later waves may introduce richer result families for clauses,
 *     replacement, lifecycle, observation, graph invariants, traversal
 *     foundations, assignment, and registry. Those result types may compose or
 *     translate this primitive result, but should not erase it.
 *
 * Explicit non-responsibilities:
 *   TPolicyResult is not a full validation report, not an audit record, not a
 *   registry lookup result, not a lifecycle snapshot, and not an execution
 *   result. It only reports primitive identity-layer operation status.
 */
struct TPolicyResult final
{
    TPolicyStatus status{TPolicyStatus::unknown};
    TPolicyIssue issue{};

    constexpr TPolicyResult() noexcept = default;
    constexpr TPolicyResult(TPolicyStatus s, TPolicyIssue i = {}) noexcept : status(s), issue(i) {}

    [[nodiscard]] static constexpr TPolicyResult Success() noexcept
    {
        return TPolicyResult{TPolicyStatus::valid, TPolicyIssue{TPolicyStatus::valid, 0}};
    }

    [[nodiscard]] static constexpr TPolicyResult Failure(TPolicyStatus status, TPolicyIssue::code_type code = 0) noexcept
    {
        return TPolicyResult{status, TPolicyIssue{status, code}};
    }

    [[nodiscard]] constexpr bool Ok() const noexcept { return IsSuccess(status); }
};

} // namespace assembler::ecosystem_governance::policy_type_system
