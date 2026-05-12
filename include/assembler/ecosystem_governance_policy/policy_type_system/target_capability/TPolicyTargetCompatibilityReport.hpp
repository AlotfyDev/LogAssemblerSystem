#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/realization_binding/TPolicyTargetKind.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_capability/TPolicyTargetCapabilityKind.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyTargetCompatibilityReport.hpp
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
 *   TPolicyTargetCompatibilityReport records the descriptive result of comparing a required capability set against a target kind and its declared capabilities. It is a report carrier only and does not perform assignment activation, realization, or target invocation.
 */
enum class TPolicyTargetCompatibilityStatus : std::uint8_t
{
    unknown = 0,
    compatible = 1,
    compatible_with_warnings = 2,
    conditionally_compatible = 3,
    deferred = 4,
    incompatible = 5,
    forbidden = 6,
    unknown_target_kind = 7,
    insufficient_capabilities = 8,
    boundary_violation = 9
};

struct TPolicyTargetCompatibilityReport final
{
    TPolicyTargetKind target_kind{TPolicyTargetKind::unknown};
    TPolicyTargetCompatibilityStatus status{TPolicyTargetCompatibilityStatus::unknown};
    std::vector<TPolicyTargetCapabilityKind> missing_capabilities{};
    std::vector<TPolicyTargetCapabilityKind> satisfied_capabilities{};
    std::string note{};

    [[nodiscard]] bool IsPositive() const noexcept
    {
        return status == TPolicyTargetCompatibilityStatus::compatible ||
               status == TPolicyTargetCompatibilityStatus::compatible_with_warnings ||
               status == TPolicyTargetCompatibilityStatus::conditionally_compatible;
    }

    [[nodiscard]] bool IsBlocking() const noexcept
    {
        return status == TPolicyTargetCompatibilityStatus::incompatible ||
               status == TPolicyTargetCompatibilityStatus::forbidden ||
               status == TPolicyTargetCompatibilityStatus::unknown_target_kind ||
               status == TPolicyTargetCompatibilityStatus::insufficient_capabilities ||
               status == TPolicyTargetCompatibilityStatus::boundary_violation;
    }

    [[nodiscard]] bool HasMissingCapabilities() const noexcept
    {
        return !missing_capabilities.empty();
    }

    [[nodiscard]] static TPolicyTargetCompatibilityReport Compatible(TPolicyTargetKind kind)
    {
        TPolicyTargetCompatibilityReport r;
        r.target_kind = kind;
        r.status = TPolicyTargetCompatibilityStatus::compatible;
        return r;
    }

    [[nodiscard]] static TPolicyTargetCompatibilityReport Missing(
        TPolicyTargetKind kind,
        std::vector<TPolicyTargetCapabilityKind> missing)
    {
        TPolicyTargetCompatibilityReport r;
        r.target_kind = kind;
        r.status = TPolicyTargetCompatibilityStatus::insufficient_capabilities;
        r.missing_capabilities = std::move(missing);
        return r;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system
