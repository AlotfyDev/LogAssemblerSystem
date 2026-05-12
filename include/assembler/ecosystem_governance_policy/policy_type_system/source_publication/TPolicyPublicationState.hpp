#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyPublicationState.hpp
 * Wave: EG-POL-W16_Policy_Source_And_Publication
 * Domain: ecosystem_governance / policy_type_system / source_publication
 *
 * Architectural boundary:
 *   W16 implements the first policy source and publication vocabulary derived
 *   from EG-POL-ARCH-006_Policy_Source_Publication_And_Registry_Versioning.
 *   It follows W12 Policy Family And Scope, W13 Target Capability Contracts,
 *   W14 Family Target Compatibility Matrix, and W15 Assignment Lifecycle And
 *   Conflict. The wave is descriptive and non-executing: it classifies policy
 *   source descriptors, publication states, publication records, version
 *   lineage, and publication views without publishing to a real registry,
 *   assigning policies, realizing policies, or invoking targets.
 *
 * Relationship to prior waves:
 *   - W01 supplies TPolicyId, TPolicyVersion, and primitive source vocabulary.
 *   - W09 supplies TPolicy as semantic aggregate, not executor.
 *   - W10 supplies non-executing assignment basics; W16 does not activate
 *     assignments.
 *   - W11 supplies registry basics; W16 prepares publication/registry-version
 *     semantics but does not become registry persistence.
 *   - W12, W13, W14, and W15 supply family/scope, target capability,
 *     compatibility, and assignment lifecycle foundations that later workflows
 *     will consume.
 *
 * Relationship to Phase A architecture:
 *   EG-POL-ARCH-006 states that source is not validity, ingestion is not
 *   publication, publication is not assignment, assignment is not realization,
 *   registry is not a storage engine, and rollback readiness is not rollback
 *   execution. This file preserves those non-collapse rules.
 *
 * Explicit non-responsibilities:
 *   This file does not implement source parsing, persistent registry storage,
 *   database registry, authority roles, assignment activation, realization
 *   contracts, runtime readiness, TPolicyRealizer, target invocation, material
 *   circulation behavior, communication binding, telemetry, logging, or
 *   persistence.
 *
 * Current implementation posture:
 *   The code is a conservative C++17 header-only foundation. The opening
 *   documentation describes the complete architectural responsibility, while
 *   the implementation intentionally remains a small set of value carriers and
 *   structural helpers.
 *
 * File responsibility:
 *   TPolicyPublicationState classifies publication lifecycle posture for a policy version. It identifies whether a policy is unpublished, requested, approved, published, withdrawn, deprecated, retired, superseded, rollback candidate, or forbidden. It does not assign or execute the policy.
 */

enum class TPolicyPublicationState : std::uint8_t
{
    unknown = 0,
    unpublished = 1,
    publication_requested = 2,
    publication_review_pending = 3,
    publication_approved = 4,
    published = 5,
    publication_rejected = 6,
    publication_deferred = 7,
    publication_withdrawn = 8,
    deprecated = 9,
    retired = 10,
    superseded = 11,
    rollback_candidate = 12,
    forbidden = 13
};

[[nodiscard]] constexpr bool IsPublished(TPolicyPublicationState state) noexcept
{
    return state == TPolicyPublicationState::published ||
           state == TPolicyPublicationState::deprecated ||
           state == TPolicyPublicationState::superseded ||
           state == TPolicyPublicationState::rollback_candidate;
}

[[nodiscard]] constexpr bool IsAssignmentVisible(TPolicyPublicationState state) noexcept
{
    return state == TPolicyPublicationState::publication_approved ||
           state == TPolicyPublicationState::published ||
           state == TPolicyPublicationState::deprecated ||
           state == TPolicyPublicationState::rollback_candidate;
}

[[nodiscard]] constexpr bool IsForbiddenForNewAssignment(TPolicyPublicationState state) noexcept
{
    return state == TPolicyPublicationState::unpublished ||
           state == TPolicyPublicationState::publication_requested ||
           state == TPolicyPublicationState::publication_review_pending ||
           state == TPolicyPublicationState::publication_rejected ||
           state == TPolicyPublicationState::publication_deferred ||
           state == TPolicyPublicationState::publication_withdrawn ||
           state == TPolicyPublicationState::retired ||
           state == TPolicyPublicationState::forbidden ||
           state == TPolicyPublicationState::unknown;
}

[[nodiscard]] constexpr bool RequiresRevalidationOnAssignment(TPolicyPublicationState state) noexcept
{
    return state == TPolicyPublicationState::deprecated ||
           state == TPolicyPublicationState::superseded ||
           state == TPolicyPublicationState::rollback_candidate;
}

} // namespace assembler::ecosystem_governance::policy_type_system
