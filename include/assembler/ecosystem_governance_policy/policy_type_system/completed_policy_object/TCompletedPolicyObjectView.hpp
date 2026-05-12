#pragma once

#include <cstddef>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObject.hpp"

namespace assembler::ecosystem_governance::policy_type_system::completed_policy_object
{
/*
 * Wave: EG-POL-W37_Completed_Policy_Object_And_Domain_View
 * Domain: ecosystem_governance / policy_type_system / completed_policy_object
 * File: TCompletedPolicyObjectView.hpp
 *
 * Architectural role:
 *   Defines a read-only view over a completed policy object for consumers that must inspect completion readiness without mutation or ownership.
 *
 * Relationship to prior waves and EG-POL-ARCH-009:
 *   W35 delivers governance semantic bundles as DTOs. W36 lets a target declare realization capabilities and semantic-to-target mapping rules. W37 introduces the completed policy object as the first carrier that combines governance semantic identity with target realization-map evidence. This follows ARCH-009: Policy Object completion precedes assignment, and assignment later occurs through a target-owned host at a declared safe point.
 *
 * Full intended picture:
 *   A domain will receive a governance semantic bundle, validate it against target capability declarations and target realization maps, then produce a completed policy object. Domain-facing views can then expose completed policy objects for later host assignment, safe-point switching, audit, and readiness reporting.
 *
 * Explicit non-responsibilities:
 *   This file does not assign a policy to a target, host a policy object, perform safe-point switching, invoke a realizer, mutate target state, persist policy records, or run production execution. 
 */

struct TCompletedPolicyObjectView
{
    const TCompletedPolicyObject* object{nullptr};

    [[nodiscard]] bool valid() const noexcept { return object != nullptr; }
    [[nodiscard]] const std::string& policy_family_ref() const { static const std::string empty; return object ? object->policy_family_ref : empty; }
    [[nodiscard]] const std::string& target_kind_ref() const { static const std::string empty; return object ? object->target_kind_ref : empty; }
    [[nodiscard]] const std::string& domain_ref() const { static const std::string empty; return object ? object->domain_ref : empty; }
    [[nodiscard]] TCompletedPolicyObjectStatus status() const noexcept { return object ? object->status : TCompletedPolicyObjectStatus::unknown; }
    [[nodiscard]] bool ready_for_host_assignment() const noexcept { return object && object->ready_for_host_assignment(); }
    [[nodiscard]] std::size_t issue_count() const noexcept { return object ? object->issues.size() : 0U; }
    [[nodiscard]] std::size_t evidence_count() const noexcept { return object ? object->evidence_refs.size() : 0U; }
};
}
