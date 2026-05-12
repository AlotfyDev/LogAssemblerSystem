#pragma once

#include <string>
#include <vector>
#include <utility>

namespace assembler::ecosystem_governance::policy_type_system::target_realization
{
/*
 * Wave: EG-POL-W36_Target_Realization_Map_And_Capability_Declaration
 * Domain: ecosystem_governance / policy_type_system / target_realization
 * File: TPolicySemanticToTargetMappingRule.hpp
 *
 * Architectural role:
 *   This header defines a mapping rule from one governance semantic part to one target-declared capability. It is the bridge between W35 DTO semantics and target-side realization definitions.
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

struct TPolicySemanticToTargetMappingRule
{
    std::string semantic_part_name;
    std::string target_capability_name;
    std::string realization_contract_ref;
    std::string target_realization_note;
    bool mandatory{false};
    bool safe_point_sensitive{false};
    std::vector<std::string> constraints;

    [[nodiscard]] bool is_well_formed() const noexcept
    {
        return !semantic_part_name.empty() && !target_capability_name.empty();
    }

    void add_constraint(std::string constraint)
    {
        if (!constraint.empty()) constraints.push_back(std::move(constraint));
    }
};
}
