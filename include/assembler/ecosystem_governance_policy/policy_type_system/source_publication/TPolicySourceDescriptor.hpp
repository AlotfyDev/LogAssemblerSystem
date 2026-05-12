#pragma once

#include <cstdint>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicySource.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicySourceDescriptor.hpp
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
 *   TPolicySourceDescriptor records where a policy artifact came from, how trusted that source is, and what ingestion/validation posture is known. It is origin metadata, not proof of validity or publication.
 */

enum class TPolicySourceKind : std::uint8_t
{
    unknown = 0,
    authored_source = 1,
    imported_source = 2,
    generated_source = 3,
    template_source = 4,
    migration_source = 5,
    registry_export_source = 6,
    test_fixture_source = 7,
    synthetic_source = 8,
    forbidden_source = 9
};

enum class TPolicySourceTrustLevel : std::uint8_t
{
    unknown = 0,
    trusted = 1,
    review_required = 2,
    untrusted = 3,
    test_only = 4,
    forbidden = 5
};

enum class TPolicySourceIngestionState : std::uint8_t
{
    unknown = 0,
    not_ingested = 1,
    ingestion_requested = 2,
    ingestion_pending = 3,
    ingested = 4,
    ingestion_rejected = 5,
    ingestion_failed = 6,
    quarantined_source = 7,
    source_validation_pending = 8,
    source_validated = 9,
    source_invalid = 10,
    source_deprecated = 11,
    source_retired = 12,
    source_forbidden = 13
};

[[nodiscard]] constexpr bool IsKnownPolicySourceKind(TPolicySourceKind kind) noexcept
{
    return kind != TPolicySourceKind::unknown;
}

[[nodiscard]] constexpr bool IsForbiddenPolicySource(TPolicySourceKind kind, TPolicySourceTrustLevel trust) noexcept
{
    return kind == TPolicySourceKind::forbidden_source || trust == TPolicySourceTrustLevel::forbidden;
}

struct TPolicySourceDescriptor final
{
    std::uint64_t source_id{0};
    TPolicySourceKind source_kind{TPolicySourceKind::unknown};
    TPolicySource base_identity_source{TPolicySource::unspecified};
    TPolicySourceTrustLevel trust_level{TPolicySourceTrustLevel::unknown};
    TPolicySourceIngestionState ingestion_state{TPolicySourceIngestionState::unknown};
    std::string source_name{};
    std::string provenance_note{};
    std::string trace_ref{};

    [[nodiscard]] bool IsValidDescriptor() const noexcept
    {
        return source_id != 0 &&
               IsKnownPolicySourceKind(source_kind) &&
               IsSpecified(base_identity_source) &&
               trust_level != TPolicySourceTrustLevel::unknown &&
               ingestion_state != TPolicySourceIngestionState::unknown &&
               !source_name.empty();
    }

    [[nodiscard]] constexpr bool RequiresReview() const noexcept
    {
        return trust_level == TPolicySourceTrustLevel::review_required ||
               trust_level == TPolicySourceTrustLevel::untrusted ||
               source_kind == TPolicySourceKind::migration_source ||
               source_kind == TPolicySourceKind::imported_source;
    }

    [[nodiscard]] constexpr bool IsIngested() const noexcept
    {
        return ingestion_state == TPolicySourceIngestionState::ingested ||
               ingestion_state == TPolicySourceIngestionState::source_validation_pending ||
               ingestion_state == TPolicySourceIngestionState::source_validated;
    }

    [[nodiscard]] constexpr bool IsSourceValidated() const noexcept
    {
        return ingestion_state == TPolicySourceIngestionState::source_validated;
    }

    [[nodiscard]] constexpr bool IsDescriptorOnly() const noexcept { return true; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
