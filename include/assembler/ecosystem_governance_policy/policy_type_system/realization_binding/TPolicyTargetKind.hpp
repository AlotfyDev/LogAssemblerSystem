#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyTargetKind.hpp
 * Wave: EG-POL-W06_Realization_Binding_And_Target_Kind
 * Domain: ecosystem_governance / policy_type_system / realization_binding
 *
 * Full architectural responsibility:
 *   TPolicyTargetKind describes the kind of external execution-bearing component
 *   a realization mechanism is expected to act upon. It names a target category,
 *   not a concrete runtime target instance and not a target-owned object.
 *
 * Why this file exists in W06:
 *   The Policy Object Graph Structure admits an optional Target-Kind Descriptor
 *   Node connected to a Realization Mechanism Binding Node. W06 introduces this
 *   vocabulary so policy binding can express expected target class without
 *   collapsing policy into target ownership or execution.
 *
 * Relationship to previous waves:
 *   - W01 policy identity names the policy that may be bound to a target kind.
 *   - W02 clauses may contain directives intended for a target kind.
 *   - W03 replacement may later ensure target-kind changes are safe.
 *   - W04 lifecycle may later constrain target-kind usage.
 *   - W05 observation may record target-kind selection evidence.
 *
 * Relationship to other files in this wave:
 *   - TPolicyTargetKindDescriptor wraps this enum with descriptor identity.
 *   - TPolicyRealizationBinding may include a target-kind descriptor.
 *
 * Relationship to future waves:
 *   - W07 graph may represent target-kind descriptor nodes.
 *   - W09 TPolicy may validate target-kind compatibility with policy family.
 *   - W10 assignment may point to actual consumers without changing this enum's
 *     non-ownership role.
 *
 * Explicit non-responsibilities:
 *   TPolicyTargetKind is not TPolicyTarget, not a pointer to a dispatcher,
 *   moderator, queue agent, material circulation component, communication port,
 *   or add-on. It does not own or invoke anything.
 *
 * Current implementation note:
 *   The enum includes common target categories known to the architecture and a
 *   custom category for future extension. It intentionally remains small.
 */
enum class TPolicyTargetKind : std::uint8_t
{
    unknown = 0,
    dispatcher = 1,
    moderator = 2,
    queue_bundle_agent = 3,
    slots_container = 4,
    round_manager = 5,
    material_circulation_component = 6,
    log_level_api_component = 7,
    communication_boundary_surface = 8,
    addon_adapter = 9,
    custom = 255
};

[[nodiscard]] constexpr bool IsKnown(TPolicyTargetKind kind) noexcept
{
    return kind != TPolicyTargetKind::unknown;
}

[[nodiscard]] constexpr bool IsConcreteRuntimeTargetKind(TPolicyTargetKind kind) noexcept
{
    return kind == TPolicyTargetKind::dispatcher ||
           kind == TPolicyTargetKind::moderator ||
           kind == TPolicyTargetKind::queue_bundle_agent ||
           kind == TPolicyTargetKind::slots_container ||
           kind == TPolicyTargetKind::round_manager ||
           kind == TPolicyTargetKind::material_circulation_component;
}

} // namespace assembler::ecosystem_governance::policy_type_system
