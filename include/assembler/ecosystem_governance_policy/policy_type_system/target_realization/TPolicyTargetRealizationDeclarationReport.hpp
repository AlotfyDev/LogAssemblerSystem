#pragma once

#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/target_realization/TPolicyTargetRealizationMapId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_realization/TPolicyTargetRealizationMapStatus.hpp"

namespace assembler::ecosystem_governance::policy_type_system::target_realization
{
/*
 * Wave: EG-POL-W36_Target_Realization_Map_And_Capability_Declaration
 * Domain: ecosystem_governance / policy_type_system / target_realization
 * File: TPolicyTargetRealizationDeclarationReport.hpp
 *
 * Architectural role:
 *   This header defines the diagnostic report produced when a target realization map is checked for completeness and readiness for future completed-policy-object creation.
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

struct TPolicyTargetRealizationDeclarationReport
{
    TPolicyTargetRealizationMapId map_id;
    TPolicyTargetRealizationMapStatus status{TPolicyTargetRealizationMapStatus::unknown};
    std::vector<std::string> missing_capabilities;
    std::vector<std::string> missing_mappings;
    std::vector<std::string> issues;

    [[nodiscard]] bool passed() const noexcept
    {
        return is_positive(status) && missing_capabilities.empty() && missing_mappings.empty() && issues.empty();
    }

    void add_issue(std::string issue)
    {
        if (!issue.empty()) issues.push_back(std::move(issue));
    }

    void add_missing_capability(std::string capability)
    {
        if (!capability.empty()) missing_capabilities.push_back(std::move(capability));
    }

    void add_missing_mapping(std::string mapping)
    {
        if (!mapping.empty()) missing_mappings.push_back(std::move(mapping));
    }
};
}
