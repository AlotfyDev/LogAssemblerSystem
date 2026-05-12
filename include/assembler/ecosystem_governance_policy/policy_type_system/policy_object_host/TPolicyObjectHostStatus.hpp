#pragma once

namespace assembler::ecosystem_governance::policy_type_system::policy_object_host
{
/*
 * Wave: EG-POL-W38_Policy_Object_Host_Surface
 * Domain: ecosystem_governance / policy_type_system / policy_object_host
 * File: TPolicyObjectHostStatus.hpp
 *
 * Architectural role:
 *   Defines host surface status values used to indicate whether a target-owned host can admit completed policy objects and whether a safe-point-sensitive assignment slot is available.
 *
 * Relationship to prior waves and EG-POL-ARCH-009:
 *   W35 delivers governance semantics as DTOs. W36 lets a target declare capability and semantic-to-target realization mapping. W37 completes a policy object by joining governance semantics with target realization evidence. W38 introduces the target-owned host surface that can later receive a completed policy object for safe-point-aware assignment.
 *
 * Full intended picture:
 *   A functional target composes a TPolicyObjectHost-like surface. The host declares safe-point visibility, admissible completed-policy criteria, current assignment slot metadata, and host evidence. Later W39 Domain PolicyAssigner will use this host surface to switch completed policy objects only at host-declared safe points.
 *
 * Explicit non-responsibilities:
 *   This file does not perform assignment switching, choose a policy, invoke a realizer, mutate target behavior, execute runtime policy logic, persist host state, or export audit records. 
 */

enum class TPolicyObjectHostStatus
{
    unknown = 0,
    declared,
    available,
    blocked,
    safe_point_open,
    assignment_slot_occupied,
    replacement_pending,
    retired,
    forbidden
};

[[nodiscard]] constexpr bool host_accepts_assignment(TPolicyObjectHostStatus status) noexcept
{
    return status == TPolicyObjectHostStatus::available ||
           status == TPolicyObjectHostStatus::safe_point_open ||
           status == TPolicyObjectHostStatus::assignment_slot_occupied;
}

[[nodiscard]] constexpr bool host_is_terminal(TPolicyObjectHostStatus status) noexcept
{
    return status == TPolicyObjectHostStatus::retired || status == TPolicyObjectHostStatus::forbidden;
}
}
