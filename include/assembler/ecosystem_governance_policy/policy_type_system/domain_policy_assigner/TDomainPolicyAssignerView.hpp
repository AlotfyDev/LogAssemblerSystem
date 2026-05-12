#pragma once

#include <cstddef>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TDomainPolicyAssignerId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TDomainPolicyAssignerStatus.hpp"
#include "assembler/ecosystem_governance/policy_type_system/domain_policy_assigner/TDomainPolicyAssignerReport.hpp"

namespace assembler::ecosystem_governance::policy_type_system::domain_policy_assigner
{
/*
 * Wave: EG-POL-W39_Domain_PolicyAssigner_And_SafePoint_Switch
 * Domain: ecosystem_governance / policy_type_system / domain_policy_assigner
 * File: TDomainPolicyAssignerView.hpp
 *
 * Architectural role:
 *   Defines a read-only view over a domain assigner and its report for diagnostics, catalog, and compliance use.
 *
 * Relationship to prior waves and EG-POL-ARCH-009:
 *   W35 delivers governance semantics as DTOs. W36 lets the target declare realization capabilities and semantic-to-target mappings. W37 defines completed policy objects. W38 defines the target-owned Policy Object Host Surface and its assignment port. W39 introduces the domain-local PolicyAssigner and safe-point switch model that coordinates completed-policy-object switching only through host-declared safe points.
 *
 * Full intended picture:
 *   Governance provides semantics, the target completes the policy object, the target-owned host stages it, and the domain-local assigner decides whether a safe-point switch is allowed. The assigner writes only assignment-port metadata in this foundation wave; it does not execute runtime behavior.
 *
 * Explicit non-responsibilities:
 *   This file does not invoke targets, mutate functional object behavior, execute policy logic, call a realizer, persist assignment state, export audit, or bypass host safe-point rules. 
 */

struct TDomainPolicyAssignerView
{
    const TDomainPolicyAssignerId* assigner_id{nullptr};
    const std::string* domain_ref{nullptr};
    TDomainPolicyAssignerStatus status{TDomainPolicyAssignerStatus::unknown};
    const TDomainPolicyAssignerReport* report{nullptr};

    [[nodiscard]] bool valid() const noexcept { return assigner_id != nullptr && domain_ref != nullptr; }
    [[nodiscard]] bool can_evaluate() const noexcept { return assigner_can_evaluate(status); }
    [[nodiscard]] bool healthy() const noexcept { return report ? report->healthy() : can_evaluate(); }
    [[nodiscard]] std::size_t evidence_count() const noexcept { return report ? report->evidence_refs.size() : 0U; }
    [[nodiscard]] const std::string& domain() const { static const std::string empty; return domain_ref ? *domain_ref : empty; }
};
}
