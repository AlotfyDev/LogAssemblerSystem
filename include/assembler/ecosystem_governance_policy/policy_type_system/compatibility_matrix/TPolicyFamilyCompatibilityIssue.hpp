#pragma once

#include <cstdint>
#include <string>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyFamilyCompatibilityIssue.hpp

 * Wave: EG-POL-W14_Family_Target_Compatibility_Matrix
 * Domain: ecosystem_governance / policy_type_system / compatibility_matrix
 *
 * Architectural boundary:
 *   W14 implements the first policy-family-to-target-kind compatibility matrix
 *   layer derived from EG-POL-ARCH-003_Policy_Family_Compatibility_Matrix. It
 *   follows W12 Policy Family And Scope and W13 Target Capability Contracts.
 *   The wave remains descriptive and non-executing: it defines compatibility
 *   rules, reports, and evaluation helpers without activating assignments,
 *   invoking targets, realizing policies, or mutating runtime components.
 *
 * Relationship to prior waves:
 *   - W01 supplies primitive identity and policy scope vocabulary.
 *   - W06 supplies target-kind descriptors and preserves the descriptor-only
 *     boundary for realization binding.
 *   - W09 supplies TPolicy as a semantic governing aggregate, not an executor.
 *   - W10 supplies non-executing assignment basics; W14 does not activate
 *     assignments.
 *   - W11 supplies registry basics; W14 does not become a registry or service
 *     locator.
 *   - W12 supplies family and scope profiles consumed by compatibility rules.
 *   - W13 supplies target capability descriptors and capability sets consumed
 *     by compatibility rules.
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-003 states that compatibility is distinct from assignment, that
 *   assignment is distinct from realization, that target capability is not a
 *   method call, and that the matrix must not become a runtime engine. This
 *   wave implements that matrix vocabulary at code level while preserving those
 *   boundaries.
 *
 * Explicit non-responsibilities:
 *   This file does not implement assignment lifecycle activation, authority
 *   roles, source publication, registry persistence, realization contracts,
 *   runtime readiness, TPolicyRealizer, TPolicyExecutor, target invocation,
 *   material circulation behavior, communication binding, add-on execution,
 *   telemetry, logging, or persistence.
 *
 * Current implementation posture:
 *   The current code is a conservative C++17 header-only foundation. The
 *   opening documentation describes the complete architectural responsibility,
 *   while the code intentionally remains a small set of value carriers and
 *   structural helpers.
 * File responsibility:
 *   TPolicyFamilyCompatibilityIssue records why a policy-family-to-target-kind
 *   relation is positive, conditional, deferred, incompatible, or forbidden. It
 *   is a diagnostic carrier for compatibility evaluation only and cannot
 *   activate assignments or execute policy behavior.
 */
enum class TPolicyFamilyCompatibilitySeverity : std::uint8_t
{
    info = 0,
    notice = 1,
    warning = 2,
    blocking = 3,
    critical = 4,
    forbidden = 5
};

enum class TPolicyFamilyCompatibilityIssueKind : std::uint8_t
{
    none = 0,
    unknown_family = 1,
    unknown_target_kind = 2,
    scope_mismatch = 3,
    missing_required_capability = 4,
    lifecycle_mismatch = 5,
    replacement_unsafe = 6,
    observation_missing = 7,
    realization_not_supported = 8,
    authority_required = 9,
    registry_required = 10,
    boundary_violation = 11,
    anti_collapse_violation = 12,
    custom = 255
};

struct TPolicyFamilyCompatibilityIssue final
{
    TPolicyFamilyCompatibilityIssueKind kind{TPolicyFamilyCompatibilityIssueKind::none};
    TPolicyFamilyCompatibilitySeverity severity{TPolicyFamilyCompatibilitySeverity::info};
    std::string message{};

    [[nodiscard]] bool IsBlocking() const noexcept
    {
        return severity == TPolicyFamilyCompatibilitySeverity::blocking ||
               severity == TPolicyFamilyCompatibilitySeverity::critical ||
               severity == TPolicyFamilyCompatibilitySeverity::forbidden;
    }

    [[nodiscard]] static TPolicyFamilyCompatibilityIssue Blocking(
        TPolicyFamilyCompatibilityIssueKind issue_kind,
        std::string note)
    {
        return TPolicyFamilyCompatibilityIssue{
            issue_kind,
            TPolicyFamilyCompatibilitySeverity::blocking,
            std::move(note)
        };
    }

    [[nodiscard]] static TPolicyFamilyCompatibilityIssue Warning(
        TPolicyFamilyCompatibilityIssueKind issue_kind,
        std::string note)
    {
        return TPolicyFamilyCompatibilityIssue{
            issue_kind,
            TPolicyFamilyCompatibilitySeverity::warning,
            std::move(note)
        };
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
