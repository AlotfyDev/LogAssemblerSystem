#pragma once

#include <cstddef>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostAssignmentPort.hpp"
#include "assembler/ecosystem_governance/policy_type_system/policy_object_host/TPolicyObjectHostDescriptor.hpp"

namespace assembler::ecosystem_governance::policy_type_system::policy_object_host
{
/*
 * Wave: EG-POL-W38_Policy_Object_Host_Surface
 * Domain: ecosystem_governance / policy_type_system / policy_object_host
 * File: TPolicyObjectHostView.hpp
 *
 * Architectural role:
 *   Defines a read-only view over host descriptor and assignment-port state for assigners, diagnostics, catalog, and readiness checks.
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

struct TPolicyObjectHostView
{
    const TPolicyObjectHostDescriptor* descriptor{nullptr};
    const TPolicyObjectHostAssignmentPort* assignment_port{nullptr};

    [[nodiscard]] bool valid() const noexcept { return descriptor != nullptr; }
    [[nodiscard]] const std::string& domain_ref() const { static const std::string empty; return descriptor ? descriptor->domain_ref : empty; }
    [[nodiscard]] const std::string& target_ref() const { static const std::string empty; return descriptor ? descriptor->target_ref : empty; }
    [[nodiscard]] const std::string& target_kind_ref() const { static const std::string empty; return descriptor ? descriptor->target_kind_ref : empty; }
    [[nodiscard]] TPolicyObjectHostStatus status() const noexcept { return descriptor ? descriptor->status : TPolicyObjectHostStatus::unknown; }
    [[nodiscard]] bool safe_point_open() const noexcept { return descriptor && descriptor->safe_point_flag.usable(); }
    [[nodiscard]] bool has_current_assignment() const noexcept { return assignment_port && assignment_port->has_current_assignment(); }
    [[nodiscard]] bool has_pending_assignment() const noexcept { return assignment_port && assignment_port->has_pending_assignment(); }
    [[nodiscard]] bool can_switch_now() const noexcept { return assignment_port && assignment_port->can_switch_now(); }
    [[nodiscard]] std::size_t accepted_family_count() const noexcept { return descriptor ? descriptor->accepted_policy_families.size() : 0U; }
};
}
