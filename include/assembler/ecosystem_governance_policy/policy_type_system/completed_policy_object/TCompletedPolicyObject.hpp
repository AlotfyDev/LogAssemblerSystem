#pragma once

#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObjectEvidenceRef.hpp"
#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObjectId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObjectIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/completed_policy_object/TCompletedPolicyObjectStatus.hpp"
#include "assembler/ecosystem_governance/policy_type_system/semantic_delivery/TPolicyBundleDtoId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/semantic_delivery/TPolicySemanticPayloadRef.hpp"
#include "assembler/ecosystem_governance/policy_type_system/target_realization/TPolicyTargetRealizationMapId.hpp"

namespace assembler::ecosystem_governance::policy_type_system::completed_policy_object
{
/*
 * Wave: EG-POL-W37_Completed_Policy_Object_And_Domain_View
 * Domain: ecosystem_governance / policy_type_system / completed_policy_object
 * File: TCompletedPolicyObject.hpp
 *
 * Architectural role:
 *   Defines the completed policy object aggregate: governance semantic bundle reference, target realization map reference, family/domain/target identity, status, evidence, and issues.
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

struct TCompletedPolicyObject
{
    TCompletedPolicyObjectId id;
    semantic_delivery::TPolicyBundleDtoId governance_bundle_id;
    semantic_delivery::TPolicySemanticPayloadRef semantic_payload_ref;
    target_realization::TPolicyTargetRealizationMapId target_realization_map_id;
    std::string policy_family_ref;
    std::string target_kind_ref;
    std::string domain_ref;
    TCompletedPolicyObjectStatus status{TCompletedPolicyObjectStatus::draft};
    std::vector<TCompletedPolicyObjectEvidenceRef> evidence_refs;
    std::vector<TCompletedPolicyObjectIssue> issues;

    [[nodiscard]] bool has_identity() const noexcept
    {
        return !id.empty() && !governance_bundle_id.empty() && !target_realization_map_id.empty();
    }

    [[nodiscard]] bool has_domain_binding() const noexcept
    {
        return !domain_ref.empty() && !target_kind_ref.empty() && !policy_family_ref.empty();
    }

    [[nodiscard]] bool has_blocking_issue() const noexcept
    {
        for (const auto& issue : issues) if (issue.blocking) return true;
        return false;
    }

    [[nodiscard]] bool ready_for_host_assignment() const noexcept
    {
        return has_identity() && has_domain_binding() && is_completed_status(status) && !has_blocking_issue();
    }

    void add_evidence_ref(TCompletedPolicyObjectEvidenceRef ref)
    {
        if (!ref.empty()) evidence_refs.push_back(std::move(ref));
    }

    void add_issue(TCompletedPolicyObjectIssue issue)
    {
        if (!issue.empty()) issues.push_back(std::move(issue));
    }
};
}
