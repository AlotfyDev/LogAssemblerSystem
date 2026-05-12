#pragma once

namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery
{
/*
 * Wave: EG-POL-W35_Policy_Bundle_DTO_And_Semantic_Delivery
 * Domain: ecosystem_governance / policy_type_system / semantic_delivery
 *
 * Architectural role:
 *   This header defines the coarse status of a policy semantic delivery flow. It tells whether a governance semantic bundle is draft, prepared, admitted, rejected, delivered, deferred, expired, or invalid at the DTO boundary.
 *
 * Relationship to prior waves and ARCH-009:
 *   W16/W17 describe publication and registry visibility; W18-W20 describe pre-execution readiness. ARCH-009 inserts a semantic-delivery stage before target completion and host assignment. This status enum belongs to that stage.
 *
 * Full intended picture:
 *   Future implementations may use these statuses to coordinate governance bundle creation, domain intake, target completion, and catalog reporting before any assignment lifecycle state changes.
 *
 * Explicit non-responsibilities:
 *   This file does not activate assignments, complete policy objects, invoke target hosts, switch safe points, or execute realization.
 */
enum class TPolicySemanticDeliveryStatus
{
    draft,
    prepared,
    admission_pending,
    admitted,
    delivered,
    rejected,
    deferred,
    expired,
    invalid
};

} // namespace assembler::ecosystem_governance::policy_type_system::semantic_delivery
