#pragma once

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "assembler/ecosystem_governance/policy_type_system/semantic_delivery/TPolicyBundleDtoId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/semantic_delivery/TPolicySemanticDeliveryIssue.hpp"
#include "assembler/ecosystem_governance/policy_type_system/semantic_delivery/TPolicySemanticDeliveryStatus.hpp"

namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery
{
/*
 * Wave: EG-POL-W35_Policy_Bundle_DTO_And_Semantic_Delivery
 * Domain: ecosystem_governance / policy_type_system / semantic_delivery
 *
 * Architectural role:
 *   This header defines a report over semantic bundle delivery. It records status, issues, accepted target-domain scope, and evidence references without becoming an audit exporter or persistence engine.
 *
 * Relationship to prior waves and ARCH-009:
 *   W31 introduced audit export boundaries, W33 introduced compliance suite concepts, and ARCH-009 requires transparent semantic delivery before target completion. This report records that boundary evidence.
 *
 * Full intended picture:
 *   Future catalog and compliance tools may use this report to prove that a governance semantic DTO was delivered to the correct domain intake before completion and host assignment.
 *
 * Explicit non-responsibilities:
 *   This file does not export audits, persist reports, activate assignments, mutate targets, or execute policies.
 */
struct TPolicySemanticDeliveryReport
{
    TPolicyBundleDtoId bundle_id;
    TPolicySemanticDeliveryStatus status = TPolicySemanticDeliveryStatus::draft;
    std::string target_domain;
    std::string evidence_ref;
    std::vector<TPolicySemanticDeliveryIssue> issues;

    void add_issue(TPolicySemanticDeliveryIssue issue)
    {
        issues.push_back(std::move(issue));
    }

    [[nodiscard]] std::size_t issue_count() const noexcept { return issues.size(); }

    [[nodiscard]] bool has_blockers() const noexcept
    {
        for (const auto& issue : issues)
        {
            if (issue.is_blocking()) return true;
        }
        return false;
    }
};

} // namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery
