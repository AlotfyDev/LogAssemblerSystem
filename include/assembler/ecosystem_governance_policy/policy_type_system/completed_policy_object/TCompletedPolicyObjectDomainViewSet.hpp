#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TDomainCompletedPolicyObjectView.hpp"

namespace assembler::ecosystem_governance::policy_type_system::completed_policy_object
{
/*
 * Wave: EG-POL-W37_Completed_Policy_Object_And_Domain_View
 * Domain: ecosystem_governance / policy_type_system / completed_policy_object
 * File: TCompletedPolicyObjectDomainViewSet.hpp
 *
 * Architectural role:
 *   Defines an aggregate set of domain views for cataloging completed policy objects across domains without acting as a runtime registry.
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

struct TCompletedPolicyObjectDomainViewSet
{
    std::vector<TDomainCompletedPolicyObjectView> domain_views;

    [[nodiscard]] bool empty() const noexcept { return domain_views.empty(); }
    [[nodiscard]] std::size_t size() const noexcept { return domain_views.size(); }

    [[nodiscard]] std::size_t total_ready_count() const noexcept
    {
        std::size_t count = 0;
        for (const auto& view : domain_views) count += view.ready_count();
        return count;
    }

    void add(TDomainCompletedPolicyObjectView view)
    {
        if (!view.domain_ref.empty()) domain_views.push_back(std::move(view));
    }
};
}
