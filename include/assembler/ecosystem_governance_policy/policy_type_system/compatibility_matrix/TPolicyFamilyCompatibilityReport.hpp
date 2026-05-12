#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/compatibility_matrix/TPolicyFamilyCompatibilityIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyFamilyKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyTargetKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilityKind.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyFamilyCompatibilityReport.hpp

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
 *   TPolicyFamilyCompatibilityReport is the structured output of W14
 *   compatibility evaluation. It records the status, missing capabilities,
 *   satisfied capabilities, and issues for a policy-family and target-kind
 *   relation. It is not an assignment, authority decision, registry entry,
 *   realization contract, or runtime execution result.
 */
enum class TPolicyFamilyCompatibilityStatus : std::uint8_t
{
    unknown = 0,
    compatible = 1,
    compatible_with_warnings = 2,
    conditionally_compatible = 3,
    deferred = 4,
    incompatible = 5,
    forbidden = 6,
    unknown_family = 7,
    unknown_target_kind = 8,
    insufficient_capabilities = 9,
    scope_mismatch = 10,
    boundary_violation = 11
};

struct TPolicyFamilyCompatibilityReport final
{
    TPolicyFamilyKind policy_family_kind{TPolicyFamilyKind::unspecified};
    TPolicyTargetKind target_kind{TPolicyTargetKind::unknown};
    TPolicyFamilyCompatibilityStatus status{TPolicyFamilyCompatibilityStatus::unknown};
    std::vector<TPolicyTargetCapabilityKind> required_capabilities{};
    std::vector<TPolicyTargetCapabilityKind> missing_capabilities{};
    std::vector<TPolicyTargetCapabilityKind> satisfied_capabilities{};
    std::vector<TPolicyFamilyCompatibilityIssue> issues{};
    std::string note{};

    [[nodiscard]] bool IsPositive() const noexcept
    {
        return status == TPolicyFamilyCompatibilityStatus::compatible ||
               status == TPolicyFamilyCompatibilityStatus::compatible_with_warnings ||
               status == TPolicyFamilyCompatibilityStatus::conditionally_compatible;
    }

    [[nodiscard]] bool IsBlocking() const noexcept
    {
        if (status == TPolicyFamilyCompatibilityStatus::incompatible ||
            status == TPolicyFamilyCompatibilityStatus::forbidden ||
            status == TPolicyFamilyCompatibilityStatus::unknown_family ||
            status == TPolicyFamilyCompatibilityStatus::unknown_target_kind ||
            status == TPolicyFamilyCompatibilityStatus::insufficient_capabilities ||
            status == TPolicyFamilyCompatibilityStatus::scope_mismatch ||
            status == TPolicyFamilyCompatibilityStatus::boundary_violation)
        {
            return true;
        }
        for (const auto& issue : issues)
        {
            if (issue.IsBlocking()) return true;
        }
        return false;
    }

    [[nodiscard]] bool HasMissingCapabilities() const noexcept
    {
        return !missing_capabilities.empty();
    }

    void AddIssue(TPolicyFamilyCompatibilityIssue issue)
    {
        if (issue.IsBlocking() && status == TPolicyFamilyCompatibilityStatus::compatible)
        {
            status = TPolicyFamilyCompatibilityStatus::incompatible;
        }
        issues.push_back(std::move(issue));
    }

    [[nodiscard]] static TPolicyFamilyCompatibilityReport Compatible(
        TPolicyFamilyKind family,
        TPolicyTargetKind target)
    {
        TPolicyFamilyCompatibilityReport report;
        report.policy_family_kind = family;
        report.target_kind = target;
        report.status = TPolicyFamilyCompatibilityStatus::compatible;
        return report;
    }

    [[nodiscard]] static TPolicyFamilyCompatibilityReport Incompatible(
        TPolicyFamilyKind family,
        TPolicyTargetKind target,
        std::string reason)
    {
        TPolicyFamilyCompatibilityReport report;
        report.policy_family_kind = family;
        report.target_kind = target;
        report.status = TPolicyFamilyCompatibilityStatus::incompatible;
        report.issues.push_back(TPolicyFamilyCompatibilityIssue::Blocking(
            TPolicyFamilyCompatibilityIssueKind::custom,
            std::move(reason)));
        return report;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
