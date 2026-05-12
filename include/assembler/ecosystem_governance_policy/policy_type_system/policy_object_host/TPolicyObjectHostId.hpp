#pragma once

#include <string>
#include <utility>

namespace assembler::ecosystem_governance::policy_type_system::policy_object_host
{
/*
 * Wave: EG-POL-W38_Policy_Object_Host_Surface
 * Domain: ecosystem_governance / policy_type_system / policy_object_host
 * File: TPolicyObjectHostId.hpp
 *
 * Architectural role:
 *   Defines the primitive identity of a target-owned policy object host surface. The host identity belongs to the functional target composition boundary, not to the policy object itself.
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

struct TPolicyObjectHostId
{
    std::string value;

    TPolicyObjectHostId() = default;
    explicit TPolicyObjectHostId(std::string v) : value(std::move(v)) {}

    [[nodiscard]] bool empty() const noexcept { return value.empty(); }
    [[nodiscard]] explicit operator bool() const noexcept { return !empty(); }

    friend bool operator==(const TPolicyObjectHostId& a, const TPolicyObjectHostId& b) noexcept
    { return a.value == b.value; }
    friend bool operator!=(const TPolicyObjectHostId& a, const TPolicyObjectHostId& b) noexcept
    { return !(a == b); }
};
}
