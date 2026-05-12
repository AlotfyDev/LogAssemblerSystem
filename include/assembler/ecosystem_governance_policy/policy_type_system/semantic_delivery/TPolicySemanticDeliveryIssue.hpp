#pragma once

#include <string>
#include <utility>

namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery
{
/*
 * Wave: EG-POL-W35_Policy_Bundle_DTO_And_Semantic_Delivery
 * Domain: ecosystem_governance / policy_type_system / semantic_delivery
 *
 * Architectural role:
 *   This header defines a non-executing issue record for semantic bundle delivery. It reports missing identity, missing family semantics, unsupported target scope, stale publication snapshot, or any other DTO-level problem.
 *
 * Relationship to prior waves and ARCH-009:
 *   W33 introduced compliance-style issue vocabulary and W34 introduced readiness evidence style. ARCH-009 requires semantic delivery to be validated before target-side completion. This issue type records that validation without performing completion.
 *
 * Full intended picture:
 *   Future delivery and catalog reports may collect these issues to block malformed policy semantic bundles before they are handed to a domain-local completion process.
 *
 * Explicit non-responsibilities:
 *   This file does not remediate issues, mutate policies, persist reports, assign a completed policy object, or invoke a policy host.
 */
enum class TPolicySemanticDeliveryIssueSeverity
{
    info,
    warning,
    blocking,
    critical
};

struct TPolicySemanticDeliveryIssue
{
    std::string code;
    std::string message;
    TPolicySemanticDeliveryIssueSeverity severity = TPolicySemanticDeliveryIssueSeverity::info;

    TPolicySemanticDeliveryIssue() = default;
    TPolicySemanticDeliveryIssue(std::string c, std::string m, TPolicySemanticDeliveryIssueSeverity s)
        : code(std::move(c)), message(std::move(m)), severity(s) {}

    [[nodiscard]] bool is_blocking() const noexcept
    {
        return severity == TPolicySemanticDeliveryIssueSeverity::blocking ||
               severity == TPolicySemanticDeliveryIssueSeverity::critical;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery
