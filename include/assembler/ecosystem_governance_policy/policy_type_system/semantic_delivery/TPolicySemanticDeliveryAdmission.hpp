#pragma once

#include <string>
#include <utility>
#include <vector>

namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery
{
/*
 * Wave: EG-POL-W35_Policy_Bundle_DTO_And_Semantic_Delivery
 * Domain: ecosystem_governance / policy_type_system / semantic_delivery
 *
 * Architectural role:
 *   This header defines a pre-completion admission decision for a governance semantic bundle. It tells whether a target domain may inspect the bundle for completion, without assigning it to a host or realizing it.
 *
 * Relationship to prior waves and ARCH-009:
 *   ARCH-009 requires policy object completion before assignment. Admission is therefore a guard before completion, not a replacement for assignment lifecycle or realization readiness.
 *
 * Full intended picture:
 *   Future domain-local admission checks may validate publication state, family, target kind, scope, and required semantic parts. This type records the outcome and missing requirements.
 *
 * Explicit non-responsibilities:
 *   This file does not complete policies, declare target capabilities, switch host assignments, or invoke a target.
 */
struct TPolicySemanticDeliveryAdmission
{
    bool accepted = false;
    std::string reason;
    std::vector<std::string> missing_requirements;

    [[nodiscard]] bool is_admitted() const noexcept
    {
        return accepted && missing_requirements.empty();
    }

    void reject(std::string why)
    {
        accepted = false;
        reason = std::move(why);
    }

    void require(std::string requirement)
    {
        missing_requirements.push_back(std::move(requirement));
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery
