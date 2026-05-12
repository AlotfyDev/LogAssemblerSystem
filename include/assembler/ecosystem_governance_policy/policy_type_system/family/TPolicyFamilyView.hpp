#pragma once

#include "assembler/ecosystem_governance/policy_type_system/family/TPolicyFamilyProfile.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyFamilyView.hpp

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
 *   TPolicyFamilyView is a read-only facade over a TPolicyFamilyProfile. It is
 *   intended for later registry views, compatibility checks, assignment review,
 *   and compliance reports. It does not own the family profile and does not
 *   mutate any policy or target state.
 */
class TPolicyFamilyView final
{
public:
    TPolicyFamilyView() noexcept = default;
    explicit TPolicyFamilyView(const TPolicyFamilyProfile* profile) noexcept : profile_(profile) {}

    [[nodiscard]] bool IsBound() const noexcept { return profile_ != nullptr; }
    [[nodiscard]] bool IsValid() const noexcept { return profile_ != nullptr && profile_->IsValid(); }

    [[nodiscard]] TPolicyFamilyId FamilyId() const noexcept
    {
        return profile_ ? profile_->family_id : TPolicyFamilyId::Invalid();
    }

    [[nodiscard]] TPolicyFamilyKind Kind() const noexcept
    {
        return profile_ ? profile_->kind : TPolicyFamilyKind::unspecified;
    }

    [[nodiscard]] TPolicyScope DefaultScope() const noexcept
    {
        return profile_ ? profile_->default_scope : TPolicyScope::unspecified;
    }

    [[nodiscard]] bool AllowsScope(TPolicyScope scope) const noexcept
    {
        return profile_ && profile_->AllowsScope(scope);
    }

    [[nodiscard]] bool RequiresSafeReplacement() const noexcept
    {
        return profile_ && profile_->safe_replacement_expected;
    }

    [[nodiscard]] bool RequiresObservation() const noexcept
    {
        return profile_ && profile_->observation_expected;
    }

    [[nodiscard]] bool ExpectsRuntimeRealization() const noexcept
    {
        return profile_ && profile_->runtime_realization_expected;
    }

private:
    const TPolicyFamilyProfile* profile_{nullptr};
};

} // namespace assembler::ecosystem_governance::policy_type_system
