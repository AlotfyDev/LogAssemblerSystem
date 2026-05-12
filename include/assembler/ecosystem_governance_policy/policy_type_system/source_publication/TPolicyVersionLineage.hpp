#pragma once

#include <cstdint>
#include <string>

#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyId.hpp"
#include "assembler/ecosystem_governance/policy_type_system/identity/TPolicyVersion.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyVersionLineage.hpp
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
 *   TPolicyVersionLineage records governed version and replacement relations among policy versions. It supports supersession, rollback candidate analysis, and auditability. It does not perform replacement or rollback.
 */

enum class TPolicyVersionLineageKind : std::uint8_t
{
    unknown = 0,
    derived_from = 1,
    supersedes = 2,
    superseded_by = 3,
    patches = 4,
    forked_from = 5,
    rollback_to = 6,
    rollback_from = 7,
    replaces = 8,
    incompatible_with = 9,
    equivalent_to = 10
};

enum class TPolicyReplacementLineageKind : std::uint8_t
{
    unknown = 0,
    planned_replacement = 1,
    approved_replacement = 2,
    active_replacement = 3,
    completed_replacement = 4,
    failed_replacement = 5,
    cancelled_replacement = 6,
    rollback_replacement = 7,
    forbidden_replacement = 8
};

struct TPolicyVersionLineage final
{
    std::uint64_t lineage_id{0};
    TPolicyId source_policy_id{};
    TPolicyVersion source_version{};
    TPolicyId target_policy_id{};
    TPolicyVersion target_version{};
    TPolicyVersionLineageKind version_relation{TPolicyVersionLineageKind::unknown};
    TPolicyReplacementLineageKind replacement_relation{TPolicyReplacementLineageKind::unknown};
    std::uint64_t authority_evidence_id{0};
    std::string reason{};
    std::string audit_marker{};

    [[nodiscard]] bool IsValidLineage() const noexcept
    {
        return lineage_id != 0 &&
               source_policy_id.IsValid() &&
               target_policy_id.IsValid() &&
               !source_version.IsZero() &&
               !target_version.IsZero() &&
               version_relation != TPolicyVersionLineageKind::unknown;
    }

    [[nodiscard]] constexpr bool IsRollbackRelated() const noexcept
    {
        return version_relation == TPolicyVersionLineageKind::rollback_to ||
               version_relation == TPolicyVersionLineageKind::rollback_from ||
               replacement_relation == TPolicyReplacementLineageKind::rollback_replacement;
    }

    [[nodiscard]] constexpr bool IsForbiddenReplacement() const noexcept
    {
        return replacement_relation == TPolicyReplacementLineageKind::forbidden_replacement;
    }

    [[nodiscard]] constexpr bool IsLineageOnly() const noexcept { return true; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
