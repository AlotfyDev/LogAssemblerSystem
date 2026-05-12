#pragma once

#include <algorithm>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilityDescriptor.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyTargetCapabilitySet.hpp
 * Wave: EG-POL-W13_Target_Capability_Contracts
 * Domain: ecosystem_governance / policy_type_system / target_capability
 *
 * Architectural boundary:
 *   W13 implements the first target-capability contract layer derived from
 *   EG-POL-ARCH-002_Policy_Target_Kind_And_Capability_Model. It follows W12
 *   Policy Family And Scope and prepares W14 compatibility-matrix work. The
 *   wave is descriptive and non-executing: it describes target capabilities,
 *   capability sets, and compatibility reports without invoking targets or
 *   realizing policies.
 *
 * Relationship to prior waves:
 *   - W01 supplies primitive policy identity and result vocabulary used by
 *     later policy layers.
 *   - W06 supplies TPolicyTargetKind and target-kind descriptors; W13 refines
 *     the capability side of that target model without changing W06's
 *     descriptor-only boundary.
 *   - W09 supplies TPolicy as a semantic governing aggregate, not an executor.
 *   - W10 supplies non-executing assignment basics; W13 does not activate or
 *     run assignments.
 *   - W11 supplies registry basics; W13 does not become a registry.
 *   - W12 supplies family/scope descriptors that future compatibility waves
 *     will join with these capability descriptors.
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-002 states that Target Kind is not Target Instance, Target
 *   Capability is not runtime execution, Capability Descriptor is not a C++
 *   method, and Realization Binding is not a realizer. This file preserves that
 *   doctrine. W13 provides the smallest C++ vocabulary required before the
 *   Policy Family Compatibility Matrix, assignment lifecycle implementation,
 *   realization contracts, runtime readiness, or TPolicyRealizer.
 *
 * Explicit non-responsibilities:
 *   This file does not implement TPolicyRealizer, TPolicyExecutor, target
 *   invocation, target ownership, communication binding, material circulation
 *   behavior, add-on execution, telemetry, persistence, runtime scheduling, or
 *   policy execution.
 *
 * Current implementation posture:
 *   The current code is a conservative C++17 header-only foundation. The
 *   opening documentation describes the complete architectural responsibility,
 *   while the code intentionally remains a small set of value carriers and
 *   structural helpers.
 *
 * File responsibility:
 *   TPolicyTargetCapabilitySet groups target capability descriptors for compatibility checks. It can answer whether a target kind declares specific capability kinds, but it does not execute or expose target methods.
 */
struct TPolicyTargetCapabilitySet final
{
    std::vector<TPolicyTargetCapabilityDescriptor> capabilities{};

    [[nodiscard]] bool IsEmpty() const noexcept
    {
        return capabilities.empty();
    }

    [[nodiscard]] bool Contains(TPolicyTargetCapabilityKind kind) const noexcept
    {
        return std::any_of(capabilities.begin(), capabilities.end(), [kind](const auto& item) {
            return item.kind == kind && !item.IsForbidden();
        });
    }

    [[nodiscard]] bool ContainsValid(TPolicyTargetCapabilityKind kind) const noexcept
    {
        return std::any_of(capabilities.begin(), capabilities.end(), [kind](const auto& item) {
            return item.kind == kind && item.IsValid() && !item.IsForbidden();
        });
    }

    void Add(TPolicyTargetCapabilityDescriptor descriptor)
    {
        if (!IsKnownTargetCapabilityKind(descriptor.kind)) return;
        auto it = std::find_if(capabilities.begin(), capabilities.end(), [&](const auto& item) {
            return item.kind == descriptor.kind && item.target_kind == descriptor.target_kind;
        });
        if (it == capabilities.end()) capabilities.push_back(std::move(descriptor));
        else *it = std::move(descriptor);
    }

    [[nodiscard]] bool Satisfies(const std::vector<TPolicyTargetCapabilityKind>& required) const noexcept
    {
        return std::all_of(required.begin(), required.end(), [&](auto kind) {
            return Contains(kind);
        });
    }

    [[nodiscard]] std::vector<TPolicyTargetCapabilityKind> Missing(const std::vector<TPolicyTargetCapabilityKind>& required) const
    {
        std::vector<TPolicyTargetCapabilityKind> missing;
        for (auto kind : required)
        {
            if (!Contains(kind)) missing.push_back(kind);
        }
        return missing;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
