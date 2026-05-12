#pragma once

#include <cstdint>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyVersion.hpp"
#include "assembler/ecosystem_governance/policy_type_system/source_publication/TPolicyPublicationState.hpp"
#include "assembler/ecosystem_governance/policy_type_system/source_publication/TPolicySourceDescriptor.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyPublicationRecord.hpp
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
 *   TPolicyPublicationRecord captures the governance record that a policy version has a particular publication state, source descriptor, registry-facing visibility, and evidence reference. It does not publish by itself and does not imply assignment or realization.
 */

enum class TPolicyRegistryVisibility : std::uint8_t
{
    unknown = 0,
    hidden = 1,
    internal_review = 2,
    test_visible = 3,
    experimental_visible = 4,
    assignment_visible = 5,
    production_visible = 6,
    deprecated_visible = 7,
    retired_visible = 8,
    forbidden_visible = 9
};

struct TPolicyPublicationRecord final
{
    std::uint64_t publication_record_id{0};
    TPolicyId policy_id{};
    TPolicyVersion policy_version{};
    TPolicySourceDescriptor source_descriptor{};
    TPolicyPublicationState publication_state{TPolicyPublicationState::unknown};
    TPolicyRegistryVisibility visibility{TPolicyRegistryVisibility::unknown};
    std::uint64_t authority_evidence_id{0};
    std::string publication_note{};
    std::string audit_marker{};

    [[nodiscard]] bool IsValidRecord() const noexcept
    {
        return publication_record_id != 0 &&
               policy_id.IsValid() &&
               !policy_version.IsZero() &&
               source_descriptor.IsValidDescriptor() &&
               publication_state != TPolicyPublicationState::unknown &&
               visibility != TPolicyRegistryVisibility::unknown;
    }

    [[nodiscard]] constexpr bool IsPublishedRecord() const noexcept
    {
        return IsPublished(publication_state);
    }

    [[nodiscard]] constexpr bool HasAuthorityEvidence() const noexcept
    {
        return authority_evidence_id != 0;
    }

    [[nodiscard]] constexpr bool IsProductionVisible() const noexcept
    {
        return visibility == TPolicyRegistryVisibility::production_visible;
    }

    [[nodiscard]] constexpr bool IsRecordOnly() const noexcept { return true; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
