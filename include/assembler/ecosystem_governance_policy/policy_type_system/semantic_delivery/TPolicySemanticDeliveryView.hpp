#pragma once

#include <cstddef>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/semantic_delivery/TPolicyBundleDtoId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/semantic_delivery/TPolicySemanticDeliveryStatus.hpp"

namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery
{
/*
 * Wave: EG-POL-W35_Policy_Bundle_DTO_And_Semantic_Delivery
 * Domain: ecosystem_governance / policy_type_system / semantic_delivery
 *
 * Architectural role:
 *   This header defines a read-only summary of semantic delivery state for cataloging, diagnostics, and compliance review. The view exists so callers can inspect delivery without reaching into DTO internals or domain host internals.
 *
 * Relationship to prior waves and ARCH-009:
 *   W34 introduced production readiness views and ARCH-009 adds semantic delivery as an explicit pre-host stage. This view summarizes that stage without exposing execution capability.
 *
 * Full intended picture:
 *   Future dashboards and catalog documents may display bundle id, status, target domain, issue count, and blocker state.
 *
 * Explicit non-responsibilities:
 *   This file does not modify DTOs, admit bundles, complete policies, assign hosts, or run recovery.
 */
struct TPolicySemanticDeliveryView
{
    TPolicyBundleDtoId bundle_id;
    TPolicySemanticDeliveryStatus status = TPolicySemanticDeliveryStatus::draft;
    std::string target_domain;
    std::size_t semantic_part_count = 0;
    std::size_t issue_count = 0;
    bool has_blockers = false;
};

} // namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery
