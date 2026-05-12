#pragma once

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyFamilyKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyScopePath.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyFamilyId.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyFamilyProfile.hpp

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
 *   TPolicyFamilyProfile is the family-level descriptor that states what a
 *   policy family is allowed to govern. It collects identity, semantic family
 *   kind, default scope, allowed scopes, and basic expectations for replacement,
 *   observation, and future realization. It is not a policy instance and does
 *   not execute behavior.
 */
struct TPolicyFamilyProfile final
{
    TPolicyFamilyId family_id{};
    TPolicyFamilyKind kind{TPolicyFamilyKind::unspecified};
    std::string canonical_name{};
    TPolicyScope default_scope{TPolicyScope::unspecified};
    std::vector<TPolicyScope> allowed_scopes{};
    bool safe_replacement_expected{false};
    bool observation_expected{true};
    bool runtime_realization_expected{false};
    bool experimental{false};

    [[nodiscard]] bool IsValid() const noexcept
    {
        return family_id.IsValid() && IsKnownPolicyFamilyKind(kind) && !canonical_name.empty();
    }

    [[nodiscard]] bool AllowsScope(TPolicyScope scope) const noexcept
    {
        return std::find(allowed_scopes.begin(), allowed_scopes.end(), scope) != allowed_scopes.end();
    }

    void AddAllowedScope(TPolicyScope scope)
    {
        if (scope == TPolicyScope::unspecified || AllowsScope(scope)) return;
        allowed_scopes.push_back(scope);
    }

    [[nodiscard]] bool IsRuntimeSensitive() const noexcept
    {
        return runtime_realization_expected || IsRuntimeSensitivePolicyFamilyKind(kind);
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
