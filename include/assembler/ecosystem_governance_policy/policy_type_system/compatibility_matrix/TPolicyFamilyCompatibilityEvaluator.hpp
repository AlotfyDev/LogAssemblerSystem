#pragma once

#include <algorithm>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/compatibility_matrix/TPolicyFamilyCompatibilityReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/compatibility_matrix/TPolicyFamilyCompatibilityRule.hpp"
#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyFamilyProfile.hpp"
#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyScopePath.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilitySet.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyFamilyCompatibilityEvaluator.hpp

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
 *   TPolicyFamilyCompatibilityEvaluator performs a conservative structural
 *   evaluation of one compatibility rule against a policy family profile, target
 *   kind, scope path, and capability set. It returns a report only. It does not
 *   activate assignment, approve authority, create registry entries, realize a
 *   policy, or invoke a target.
 */
struct TPolicyFamilyCompatibilityEvaluator final
{
    [[nodiscard]] static TPolicyFamilyCompatibilityReport Evaluate(
        const TPolicyFamilyCompatibilityRule& rule,
        const TPolicyFamilyProfile& family_profile,
        TPolicyTargetKind candidate_target_kind,
        const TPolicyScopePath& target_scope,
        const TPolicyTargetCapabilitySet& target_capabilities)
    {
        if (!rule.IsValid())
        {
            return TPolicyFamilyCompatibilityReport::Incompatible(
                family_profile.kind,
                candidate_target_kind,
                "compatibility rule is invalid");
        }
        if (!family_profile.IsValid())
        {
            TPolicyFamilyCompatibilityReport report;
            report.policy_family_kind = family_profile.kind;
            report.target_kind = candidate_target_kind;
            report.status = TPolicyFamilyCompatibilityStatus::unknown_family;
            report.AddIssue(TPolicyFamilyCompatibilityIssue::Blocking(
                TPolicyFamilyCompatibilityIssueKind::unknown_family,
                "policy family profile is invalid or unknown"));
            return report;
        }
        if (!IsKnown(candidate_target_kind))
        {
            TPolicyFamilyCompatibilityReport report;
            report.policy_family_kind = family_profile.kind;
            report.target_kind = candidate_target_kind;
            report.status = TPolicyFamilyCompatibilityStatus::unknown_target_kind;
            report.AddIssue(TPolicyFamilyCompatibilityIssue::Blocking(
                TPolicyFamilyCompatibilityIssueKind::unknown_target_kind,
                "target kind is unknown"));
            return report;
        }
        if (!rule.Matches(family_profile.kind, candidate_target_kind))
        {
            return TPolicyFamilyCompatibilityReport::Incompatible(
                family_profile.kind,
                candidate_target_kind,
                "policy family kind and target kind do not match this matrix rule");
        }

        TPolicyFamilyCompatibilityReport report = TPolicyFamilyCompatibilityReport::Compatible(
            family_profile.kind,
            candidate_target_kind);
        report.required_capabilities = rule.required_capabilities;

        if (target_scope.IsSpecified() && !rule.AllowsScope(target_scope.scope))
        {
            report.status = TPolicyFamilyCompatibilityStatus::scope_mismatch;
            report.AddIssue(TPolicyFamilyCompatibilityIssue::Blocking(
                TPolicyFamilyCompatibilityIssueKind::scope_mismatch,
                "target scope is not allowed by this compatibility rule"));
        }

        auto missing = target_capabilities.Missing(rule.required_capabilities);
        if (!missing.empty())
        {
            report.status = TPolicyFamilyCompatibilityStatus::insufficient_capabilities;
            report.missing_capabilities = std::move(missing);
            report.AddIssue(TPolicyFamilyCompatibilityIssue::Blocking(
                TPolicyFamilyCompatibilityIssueKind::missing_required_capability,
                "target capability set does not satisfy the required compatibility rule capabilities"));
        }
        for (auto capability : rule.required_capabilities)
        {
            if (target_capabilities.Contains(capability)) report.satisfied_capabilities.push_back(capability);
        }

        if (rule.authority_required)
        {
            report.AddIssue(TPolicyFamilyCompatibilityIssue::Warning(
                TPolicyFamilyCompatibilityIssueKind::authority_required,
                "compatibility relation requires authority before assignment activation"));
            if (report.status == TPolicyFamilyCompatibilityStatus::compatible)
                report.status = TPolicyFamilyCompatibilityStatus::compatible_with_warnings;
        }
        if (rule.registry_required)
        {
            report.AddIssue(TPolicyFamilyCompatibilityIssue::Warning(
                TPolicyFamilyCompatibilityIssueKind::registry_required,
                "compatibility relation requires registry/publication satisfaction before activation"));
            if (report.status == TPolicyFamilyCompatibilityStatus::compatible)
                report.status = TPolicyFamilyCompatibilityStatus::compatible_with_warnings;
        }

        return report;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
