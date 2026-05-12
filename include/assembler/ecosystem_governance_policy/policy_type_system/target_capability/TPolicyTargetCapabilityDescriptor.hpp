#pragma once

#include <cstdint>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyTargetKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilityId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilityKind.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyTargetCapabilityDescriptor.hpp
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
 *   TPolicyTargetCapabilityDescriptor describes one capability promised or required by a target kind. It stores identity, capability kind, target-kind owner, strength, mutability, and human-readable notes. It is not a callable and not a method signature.
 */
enum class TPolicyTargetCapabilityStrength : std::uint8_t
{
    unknown = 0,
    required = 1,
    recommended = 2,
    optional = 3,
    forbidden = 4,
    deferred = 5
};

enum class TPolicyTargetCapabilityMutability : std::uint8_t
{
    unknown = 0,
    read_only = 1,
    controlled_mutation = 2,
    replacement_sensitive = 3,
    lifecycle_sensitive = 4,
    runtime_forbidden = 5
};

struct TPolicyTargetCapabilityDescriptor final
{
    TPolicyTargetCapabilityId capability_id{};
    TPolicyTargetCapabilityKind kind{TPolicyTargetCapabilityKind::unknown};
    TPolicyTargetKind target_kind{TPolicyTargetKind::unknown};
    TPolicyTargetCapabilityStrength strength{TPolicyTargetCapabilityStrength::unknown};
    TPolicyTargetCapabilityMutability mutability{TPolicyTargetCapabilityMutability::unknown};
    std::string canonical_name{};
    std::string notes{};

    [[nodiscard]] bool IsValid() const noexcept
    {
        return capability_id.IsValid() &&
               IsKnownTargetCapabilityKind(kind) &&
               IsKnown(target_kind) &&
               strength != TPolicyTargetCapabilityStrength::unknown &&
               mutability != TPolicyTargetCapabilityMutability::unknown &&
               !canonical_name.empty();
    }

    [[nodiscard]] constexpr bool IsRequired() const noexcept
    {
        return strength == TPolicyTargetCapabilityStrength::required;
    }

    [[nodiscard]] constexpr bool IsForbidden() const noexcept
    {
        return strength == TPolicyTargetCapabilityStrength::forbidden;
    }

    [[nodiscard]] constexpr bool AllowsRuntimeMutation() const noexcept
    {
        return mutability == TPolicyTargetCapabilityMutability::controlled_mutation ||
               mutability == TPolicyTargetCapabilityMutability::replacement_sensitive ||
               mutability == TPolicyTargetCapabilityMutability::lifecycle_sensitive;
    }

    [[nodiscard]] constexpr bool IsDescriptorOnly() const noexcept
    {
        return true;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
