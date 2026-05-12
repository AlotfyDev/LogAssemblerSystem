#pragma once

#include <cstddef>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/target_realization/TPolicyTargetRealizationMap.hpp"

namespace assembler::ecosystem_governance::policy_type_system::target_realization
{
/*
 * Wave: EG-POL-W36_Target_Realization_Map_And_Capability_Declaration
 * Domain: ecosystem_governance / policy_type_system / target_realization
 * File: TPolicyTargetRealizationMapView.hpp
 *
 * Architectural role:
 *   This header defines a read-only view over a target realization map for consumers that need summary access without mutation or ownership.
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

struct TPolicyTargetRealizationMapView
{
    const TPolicyTargetRealizationMap* map{nullptr};

    [[nodiscard]] bool valid() const noexcept { return map != nullptr; }
    [[nodiscard]] const std::string& target_kind_ref() const { static const std::string empty; return map ? map->target_kind_ref : empty; }
    [[nodiscard]] const std::string& policy_family_ref() const { static const std::string empty; return map ? map->policy_family_ref : empty; }
    [[nodiscard]] std::size_t capability_count() const noexcept { return map ? map->capabilities.size() : 0U; }
    [[nodiscard]] std::size_t mapping_rule_count() const noexcept { return map ? map->mapping_rules.size() : 0U; }
    [[nodiscard]] bool ready_for_completion() const { return map && map->is_ready_for_completion(); }
};
}
