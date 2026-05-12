#pragma once

#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/target_realization/TPolicySemanticToTargetMappingRule.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_realization/TPolicyTargetCapabilityDeclaration.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_realization/TPolicyTargetRealizationMapId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_realization/TPolicyTargetRealizationMapStatus.hpp"

namespace assembler::ecosystem_governance::policy_type_system::target_realization
{
/*
 * Wave: EG-POL-W36_Target_Realization_Map_And_Capability_Declaration
 * Domain: ecosystem_governance / policy_type_system / target_realization
 * File: TPolicyTargetRealizationMap.hpp
 *
 * Architectural role:
 *   This header defines the aggregate target realization map: target kind, policy family, declared capabilities, and semantic-to-capability mapping rules.
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

struct TPolicyTargetRealizationMap
{
    TPolicyTargetRealizationMapId id;
    std::string target_kind_ref;
    std::string target_object_kind_ref;
    std::string policy_family_ref;
    TPolicyTargetRealizationMapStatus status{TPolicyTargetRealizationMapStatus::draft};
    std::vector<TPolicyTargetCapabilityDeclaration> capabilities;
    std::vector<TPolicySemanticToTargetMappingRule> mapping_rules;

    [[nodiscard]] bool has_identity() const noexcept
    {
        return !id.empty() && !target_kind_ref.empty() && !policy_family_ref.empty();
    }

    [[nodiscard]] bool has_capability(const std::string& name) const
    {
        for (const auto& cap : capabilities) if (cap.capability_name == name) return true;
        return false;
    }

    [[nodiscard]] bool mapping_rules_are_satisfied() const
    {
        for (const auto& rule : mapping_rules)
        {
            if (rule.mandatory && (!rule.is_well_formed() || !has_capability(rule.target_capability_name))) return false;
        }
        return true;
    }

    [[nodiscard]] bool is_ready_for_completion() const
    {
        return has_identity() && is_positive(status) && !mapping_rules.empty() && mapping_rules_are_satisfied();
    }

    void add_capability(TPolicyTargetCapabilityDeclaration capability)
    {
        capabilities.push_back(std::move(capability));
    }

    void add_mapping_rule(TPolicySemanticToTargetMappingRule rule)
    {
        mapping_rules.push_back(std::move(rule));
    }
};
}
