#pragma once

#include <algorithm>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/compatibility_matrix/TPolicyFamilyCompatibilityEvaluator.hpp"
#include "assembler/ecosystem_governance/policy_type_system/compatibility_matrix/TPolicyFamilyCompatibilityRule.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyFamilyCompatibilityMatrix.hpp

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
 *   TPolicyFamilyCompatibilityMatrix owns a bounded list of compatibility rows
 *   and delegates structural evaluation to TPolicyFamilyCompatibilityEvaluator.
 *   It is an in-memory rule collection and lookup helper only. It is not a
 *   policy registry, assignment lifecycle engine, authority system, realizer,
 *   target locator, or runtime execution engine.
 */
struct TPolicyFamilyCompatibilityMatrix final
{
    std::vector<TPolicyFamilyCompatibilityRule> rules{};

    void AddRule(TPolicyFamilyCompatibilityRule rule)
    {
        if (!rule.IsValid()) return;
        auto it = std::find_if(rules.begin(), rules.end(), [&](const auto& current) {
            return current.rule_id == rule.rule_id;
        });
        if (it == rules.end()) rules.push_back(std::move(rule));
        else *it = std::move(rule);
    }

    [[nodiscard]] const TPolicyFamilyCompatibilityRule* FindRule(
        TPolicyFamilyKind family,
        TPolicyTargetKind target) const noexcept
    {
        auto it = std::find_if(rules.begin(), rules.end(), [&](const auto& rule) {
            return rule.Matches(family, target);
        });
        return it == rules.end() ? nullptr : &(*it);
    }

    [[nodiscard]] bool HasRule(TPolicyFamilyKind family, TPolicyTargetKind target) const noexcept
    {
        return FindRule(family, target) != nullptr;
    }

    [[nodiscard]] TPolicyFamilyCompatibilityReport Evaluate(
        const TPolicyFamilyProfile& family_profile,
        TPolicyTargetKind candidate_target_kind,
        const TPolicyScopePath& target_scope,
        const TPolicyTargetCapabilitySet& target_capabilities) const
    {
        const auto* rule = FindRule(family_profile.kind, candidate_target_kind);
        if (rule == nullptr)
        {
            TPolicyFamilyCompatibilityReport report;
            report.policy_family_kind = family_profile.kind;
            report.target_kind = candidate_target_kind;
            report.status = TPolicyFamilyCompatibilityStatus::deferred;
            report.AddIssue(TPolicyFamilyCompatibilityIssue::Warning(
                TPolicyFamilyCompatibilityIssueKind::custom,
                "no compatibility matrix row exists for this policy family and target kind"));
            return report;
        }
        return TPolicyFamilyCompatibilityEvaluator::Evaluate(
            *rule,
            family_profile,
            candidate_target_kind,
            target_scope,
            target_capabilities);
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
