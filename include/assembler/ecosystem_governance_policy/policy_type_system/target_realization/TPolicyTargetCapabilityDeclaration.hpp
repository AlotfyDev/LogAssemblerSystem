#pragma once

#include <string>
#include <vector>
#include <utility>

#include "assembler/ecosystem_governance/policy_type_system/target_realization/TPolicyTargetCapabilityDeclarationId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_realization/TPolicyTargetRealizationCapabilityKind.hpp"

namespace assembler::ecosystem_governance::policy_type_system::target_realization
{
/*
 * Wave: EG-POL-W36_Target_Realization_Map_And_Capability_Declaration
 * Domain: ecosystem_governance / policy_type_system / target_realization
 * File: TPolicyTargetCapabilityDeclaration.hpp
 *
 * Architectural role:
 *   This header defines the target-side declaration of a capability that may participate in completing a policy object for a specific target kind.
 *
 * Relationship to prior waves and ARCH-009:
 *   W35 delivers governance semantic bundles as DTOs. W36 starts the target-side half of ARCH-009 by describing what the target declares it can realize and how governance semantics are mapped to target-owned capabilities. It builds on W13 target capability contracts, W14 compatibility rules, W18 realization contracts, and W21-W24 realization skeletons, while staying before completed policy object creation and host assignment.
 *
 * Full intended picture:
 *   A policy-aware domain object will eventually declare capabilities, bind governance semantic parts to target realization mappings, and produce a target-side declaration report. Later waves will use these declarations to create a completed policy object, then assign it through a TPolicyObjectHost at a safe point.
 *
 * Explicit non-responsibilities:
 *   This file does not create a completed policy object, assign a policy to a host, switch policies at a safe point, invoke target behavior, mutate target state, or perform runtime execution. 
 */

struct TPolicyTargetCapabilityDeclaration
{
    TPolicyTargetCapabilityDeclarationId id;
    std::string target_kind_ref;
    std::string capability_name;
    TPolicyTargetRealizationCapabilityKind capability_kind{TPolicyTargetRealizationCapabilityKind::unknown};
    bool required_for_completion{false};
    bool safe_point_required{false};
    bool runtime_mutation_forbidden{true};
    std::vector<std::string> evidence_refs;

    [[nodiscard]] bool is_well_formed() const noexcept
    {
        return !id.empty() && !target_kind_ref.empty() && !capability_name.empty() &&
               capability_kind != TPolicyTargetRealizationCapabilityKind::unknown;
    }

    [[nodiscard]] bool can_participate_in_completion() const noexcept
    {
        return is_well_formed() && (!may_mutate_target(capability_kind) || !runtime_mutation_forbidden);
    }

    void add_evidence_ref(std::string ref) { if (!ref.empty()) evidence_refs.push_back(std::move(ref)); }
};
}
