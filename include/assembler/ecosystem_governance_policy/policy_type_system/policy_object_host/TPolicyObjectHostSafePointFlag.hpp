#pragma once

#include <string>
#include <utility>

namespace assembler::ecosystem_governance::policy_type_system::policy_object_host
{
/*
 * Wave: EG-POL-W38_Policy_Object_Host_Surface
 * Domain: ecosystem_governance / policy_type_system / policy_object_host
 * File: TPolicyObjectHostSafePointFlag.hpp
 *
 * Architectural role:
 *   Defines the target-owned safe-point declaration flag used by later assigners to determine whether a staged policy switch may occur.
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

struct TPolicyObjectHostSafePointFlag
{
    bool declared{false};
    bool currently_open{false};
    std::string safe_point_ref;
    std::string reason;

    [[nodiscard]] bool usable() const noexcept
    {
        return declared && currently_open && !safe_point_ref.empty();
    }

    static TPolicyObjectHostSafePointFlag closed(std::string ref, std::string why = {})
    {
        TPolicyObjectHostSafePointFlag flag;
        flag.declared = !ref.empty();
        flag.currently_open = false;
        flag.safe_point_ref = std::move(ref);
        flag.reason = std::move(why);
        return flag;
    }

    static TPolicyObjectHostSafePointFlag open(std::string ref, std::string why = {})
    {
        TPolicyObjectHostSafePointFlag flag;
        flag.declared = !ref.empty();
        flag.currently_open = !ref.empty();
        flag.safe_point_ref = std::move(ref);
        flag.reason = std::move(why);
        return flag;
    }
};
}
