#pragma once

#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/semantic_delivery/TPolicyGovernanceSemanticBundleDto.hpp"
#include "assembler/ecosystem_governance/policy_type_system/semantic_delivery/TPolicySemanticDeliveryAdmission.hpp"
#include "assembler/ecosystem_governance/policy_type_system/semantic_delivery/TPolicySemanticDeliveryReport.hpp"
#include "assembler/ecosystem_governance/policy_type_system/semantic_delivery/TPolicySemanticDeliveryStatus.hpp"

namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery
{
/*
 * Wave: EG-POL-W35_Policy_Bundle_DTO_And_Semantic_Delivery
 * Domain: ecosystem_governance / policy_type_system / semantic_delivery
 *
 * Architectural role:
 *   This header defines the non-executing boundary that carries a governance semantic bundle DTO into a target domain for later completion. It is the first architectural bridge introduced after ARCH-009, but it is not a runtime bridge or a host.
 *
 * Relationship to prior waves and ARCH-009:
 *   ARCH-009 clarifies that governance semantics are delivered first; target capabilities and realization definitions complete the policy object later; assignment happens only through a target-owned host at safe points. This boundary represents only the semantic delivery step.
 *
 * Full intended picture:
 *   Future domain waves may implement local receivers of this boundary, then produce completed policy object records and host assignment requests. This boundary remains explicit so delivery is not confused with completion or assignment.
 *
 * Explicit non-responsibilities:
 *   This file does not complete policy objects, own target capabilities, host policies, switch assignments, persist DTOs, or invoke realizers.
 */
struct TPolicySemanticDeliveryBoundary
{
    std::string boundary_name;
    std::string source_governance_scope;
    std::string target_domain;
    TPolicySemanticDeliveryStatus status = TPolicySemanticDeliveryStatus::draft;
    TPolicySemanticDeliveryAdmission admission;
    TPolicySemanticDeliveryReport report;

    [[nodiscard]] bool can_deliver(const TPolicyGovernanceSemanticBundleDto& dto) const noexcept
    {
        return admission.is_admitted() && dto.has_identity() && dto.semantic_part_count() > 0U;
    }

    TPolicySemanticDeliveryReport deliver_descriptor_only(const TPolicyGovernanceSemanticBundleDto& dto) const
    {
        TPolicySemanticDeliveryReport out = report;
        out.bundle_id = dto.id;
        out.target_domain = target_domain;
        out.status = can_deliver(dto) ? TPolicySemanticDeliveryStatus::delivered : TPolicySemanticDeliveryStatus::rejected;
        return out;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery
