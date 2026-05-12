#pragma once

#include <string>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyScopePath.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyScopeCompatibility.hpp

 * Wave: EG-POL-W12_Policy_Family_And_Scope
 * Domain: ecosystem_governance / policy_type_system / family
 *
 * Architectural boundary:
 *   W12 is the first implementation wave after Phase A architecture completion.
 *   It introduces the policy-family and policy-scope vocabulary needed before
 *   target capability contracts, compatibility evaluators, assignment lifecycle
 *   implementation, publication/versioning implementation, runtime readiness,
 *   or any future TPolicyRealizer. The wave remains descriptive and
 *   non-executing.
 *
 * Relationship to prior waves:
 *   - W01 provides primitive policy identity, including TPolicyFamilyId and
 *     TPolicyScope.
 *   - W09 provides the TPolicy aggregate, which may later contain or reference
 *     family profile information.
 *   - W10 provides assignment basics; W12 does not activate assignments.
 *   - W11 provides registry basics; W12 does not become a registry.
 *
 * Relationship to Phase A architecture:
 *   This wave implements the smallest code-level vocabulary derived from
 *   EG-POL-ARCH-001_Policy_Family_Taxonomy_And_Scope_Model and prepares later
 *   implementation of EG-POL-ARCH-002 and EG-POL-ARCH-003 without crossing into
 *   target invocation, policy realization, or runtime execution.
 *
 * Explicit non-responsibilities:
 *   This file does not implement target capability surfaces, target ownership,
 *   compatibility evaluation against concrete targets, assignment lifecycle,
 *   policy source ingestion, registry persistence, policy realization, runtime
 *   scheduling, telemetry, logging, or material circulation behavior.
 *
 * Current implementation posture:
 *   The current code is a C++17 header-only foundational block. The opening
 *   documentation describes the full architectural responsibility even when the
 *   code intentionally exposes only conservative value carriers and simple
 *   helper functions.

 * File responsibility:
 *   TPolicyScopeCompatibility provides the minimal status and report vocabulary
 *   for deciding whether a policy-family scope and a candidate target or
 *   assignment scope are compatible. It is not the full policy-family-to-target
 *   compatibility matrix; it is the scope-specific input needed by that later
 *   matrix.
 */
enum class TPolicyScopeCompatibilityStatus : std::uint8_t
{
    unknown = 0,
    compatible = 1,
    compatible_by_narrowing = 2,
    conditionally_compatible = 3,
    deferred = 4,
    incompatible = 5,
    forbidden = 6
};

struct TPolicyScopeCompatibilityIssue final
{
    std::string message{};
    bool blocking{false};
};

struct TPolicyScopeCompatibility final
{
    TPolicyScopeCompatibilityStatus status{TPolicyScopeCompatibilityStatus::unknown};
    std::vector<TPolicyScopeCompatibilityIssue> issues{};

    [[nodiscard]] bool IsPositive() const noexcept
    {
        return status == TPolicyScopeCompatibilityStatus::compatible ||
               status == TPolicyScopeCompatibilityStatus::compatible_by_narrowing ||
               status == TPolicyScopeCompatibilityStatus::conditionally_compatible;
    }

    [[nodiscard]] bool IsBlocking() const noexcept
    {
        if (status == TPolicyScopeCompatibilityStatus::incompatible ||
            status == TPolicyScopeCompatibilityStatus::forbidden)
        {
            return true;
        }
        for (const auto& issue : issues)
        {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] static TPolicyScopeCompatibility Compatible() noexcept
    {
        TPolicyScopeCompatibility result;
        result.status = TPolicyScopeCompatibilityStatus::compatible;
        return result;
    }

    [[nodiscard]] static TPolicyScopeCompatibility Incompatible(std::string reason)
    {
        TPolicyScopeCompatibility result;
        result.status = TPolicyScopeCompatibilityStatus::incompatible;
        result.issues.push_back(TPolicyScopeCompatibilityIssue{std::move(reason), true});
        return result;
    }
};

[[nodiscard]] inline TPolicyScopeCompatibility CheckScopePathCompatibility(
    const TPolicyScopePath& policy_scope,
    const TPolicyScopePath& target_scope)
{
    if (!policy_scope.IsSpecified())
    {
        return TPolicyScopeCompatibility::Incompatible("policy scope is unspecified");
    }
    if (!target_scope.IsSpecified())
    {
        return TPolicyScopeCompatibility::Incompatible("target scope is unspecified");
    }
    if (policy_scope.scope == TPolicyScope::global_governance)
    {
        return TPolicyScopeCompatibility::Compatible();
    }
    if (policy_scope.scope == target_scope.scope && HasPrefix(target_scope, policy_scope))
    {
        TPolicyScopeCompatibility result;
        result.status = policy_scope.segments.size() == target_scope.segments.size()
            ? TPolicyScopeCompatibilityStatus::compatible
            : TPolicyScopeCompatibilityStatus::compatible_by_narrowing;
        return result;
    }
    return TPolicyScopeCompatibility::Incompatible("policy scope path does not match target scope path");
}

} // namespace assembler::ecosystem_governance::policy_type_system
