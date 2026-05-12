#pragma once

#include <string>

namespace assembler::ecosystem_governance::policy_type_system::target_realization
{
/*
 * Wave: EG-POL-W36_Target_Realization_Map_And_Capability_Declaration
 * Domain: ecosystem_governance / policy_type_system / target_realization
 * File: TPolicyTargetRealizationMapId.hpp
 *
 * Architectural role:
 *   This header defines the primitive identity for a target realization map. The map is the target-owned declaration that links governance semantic parts to target capabilities.
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

struct TPolicyTargetRealizationMapId
{
    std::string value;

    TPolicyTargetRealizationMapId() = default;
    explicit TPolicyTargetRealizationMapId(std::string v) : value(std::move(v)) {}

    [[nodiscard]] bool empty() const noexcept { return value.empty(); }
    [[nodiscard]] explicit operator bool() const noexcept { return !empty(); }

    friend bool operator==(const TPolicyTargetRealizationMapId& a, const TPolicyTargetRealizationMapId& b) noexcept
    { return a.value == b.value; }
};
}
