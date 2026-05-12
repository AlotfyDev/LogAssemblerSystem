#pragma once

#include <cstdint>

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyEvidenceRef.hpp
 * Wave: EG-POL-W05_Policy_Observation_And_Audit
 * Domain: ecosystem_governance / policy_type_system / observation
 *
 * Full architectural responsibility:
 *   TPolicyEvidenceRef is a lightweight reference to evidence associated with an observation. It allows policy observation to acknowledge evidence without owning evidence storage, audit databases, telemetry exporters, or log sinks.
 *
 * Why this file exists in W05:
 *   The policy model requires observation/audit capability, but W05 must keep that capability lightweight by default and avoid turning it into persistence or telemetry.
 *
 * Relationship to previous waves:
 *   - W01 provenance may later be expressed as evidence references.
 *   - W03 replacement decisions may later attach replacement evidence.
 *   - W04 lifecycle changes may later attach lifecycle evidence.
 *
 * Relationship to future waves:
 *   - W06 realization binding may attach realization evidence without executing the mechanism.
 *   - W07 graph observation nodes may carry evidence references.
 *   - W09 TPolicy views may expose evidence references without owning evidence storage.
 *
 * Explicit non-responsibilities:
 *   TPolicyEvidenceRef is not an evidence repository, not a file path contract, not a database row, not telemetry data, not a logging event, and not proof of target execution.
 *
 * Current implementation note:
 *   W05 intentionally provides compact C++17 value types and enums. The opening documentation records the full intended architecture even where the current code is only a foundation block for later waves.
 */

enum class TPolicyEvidenceKind : std::uint8_t
{
    none = 0,
    source_reference = 1,
    lifecycle_evidence = 2,
    replacement_evidence = 3,
    clause_evidence = 4,
    realization_evidence = 5,
    external_note = 6
};

struct TPolicyEvidenceRef final
{
    using token_type = std::uint64_t;

    token_type token{0};
    TPolicyEvidenceKind kind{TPolicyEvidenceKind::none};

    constexpr TPolicyEvidenceRef() noexcept = default;
    constexpr TPolicyEvidenceRef(token_type t, TPolicyEvidenceKind k) noexcept : token(t), kind(k) {}

    [[nodiscard]] static constexpr TPolicyEvidenceRef Empty() noexcept { return TPolicyEvidenceRef{}; }
    [[nodiscard]] constexpr bool IsPresent() const noexcept { return token != 0 && kind != TPolicyEvidenceKind::none; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
