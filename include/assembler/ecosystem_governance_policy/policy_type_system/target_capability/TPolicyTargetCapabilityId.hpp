#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyTargetCapabilityId.hpp
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
 *   TPolicyTargetCapabilityId is the primitive identity token for a described target capability. It allows capability descriptors and capability sets to reference capabilities without depending on runtime targets, methods, adapters, or realization engines.
 */
struct TPolicyTargetCapabilityId final
{
    using value_type = std::uint64_t;

    value_type value{0};

    constexpr TPolicyTargetCapabilityId() noexcept = default;
    explicit constexpr TPolicyTargetCapabilityId(value_type v) noexcept : value(v) {}

    [[nodiscard]] static constexpr TPolicyTargetCapabilityId Invalid() noexcept { return TPolicyTargetCapabilityId{}; }
    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    friend constexpr bool operator==(TPolicyTargetCapabilityId lhs, TPolicyTargetCapabilityId rhs) noexcept { return lhs.value == rhs.value; }
    friend constexpr bool operator!=(TPolicyTargetCapabilityId lhs, TPolicyTargetCapabilityId rhs) noexcept { return !(lhs == rhs); }
    friend constexpr bool operator<(TPolicyTargetCapabilityId lhs, TPolicyTargetCapabilityId rhs) noexcept { return lhs.value < rhs.value; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
