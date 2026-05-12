#pragma once

#include <cstdint>
#include "TPolicySource.hpp"

namespace assembler::ecosystem_governance::policy_type_system
{

/*
 * File: TPolicyProvenance.hpp
 * Wave: EG-POL-W01_Primitive_Policy_Identity
 * Domain: ecosystem_governance / policy_type_system / identity
 *
 * Full architectural responsibility:
 *   TPolicyProvenance is the primitive trace descriptor for where a policy came
 *   from and how it may be correlated with external governance evidence. It is
 *   intentionally lightweight in W01, but it establishes a stable home for
 *   provenance semantics before observation/audit, assignment, or registry
 *   layers are introduced.
 *
 * Why this file exists in W01:
 *   The Policy Object taxonomy requires source/provenance awareness as part of
 *   identity semantics. Provenance is needed for traceability, replacement
 *   discipline, governance linkage, and later auditability. It must exist
 *   before policies are assigned, replaced, or cataloged.
 *
 * Relationship to other files:
 *   - TPolicySource classifies the source kind.
 *   - TPolicyId and TPolicyFamilyId identify the policy being traced.
 *   - TPolicyVersion may be used with provenance to distinguish revisions.
 *   - TPolicyStatus, TPolicyIssue, and TPolicyResult can report provenance
 *     validity issues.
 *
 * Relationship to future waves:
 *   - W05 observation/audit may include or expand provenance records.
 *   - W09 TPolicy may expose provenance through TPolicyView.
 *   - W11 policy registry basics may use provenance as part of registry
 *     descriptors or lookup reports.
 *
 * Explicit non-responsibilities:
 *   TPolicyProvenance is not an audit trail, not a registry entry, not a file
 *   path contract, not a trust model, and not an external source connector. It
 *   only preserves primitive provenance tokens.
 *
 * Current implementation note:
 *   W01 stores source kind plus two numeric trace tokens. These tokens can be
 *   mapped later to richer source-trace, document, registry, or audit systems
 *   without forcing such systems into the primitive identity wave.
 */
struct TPolicyProvenance final
{
    using token_type = std::uint64_t;

    TPolicySource source{TPolicySource::unspecified};
    token_type source_token{0};
    token_type evidence_token{0};

    constexpr TPolicyProvenance() noexcept = default;

    constexpr TPolicyProvenance(TPolicySource src, token_type sourceTok, token_type evidenceTok = 0) noexcept
        : source(src), source_token(sourceTok), evidence_token(evidenceTok) {}

    [[nodiscard]] constexpr bool HasSource() const noexcept { return IsSpecified(source); }
    [[nodiscard]] constexpr bool HasSourceToken() const noexcept { return source_token != 0; }
    [[nodiscard]] constexpr bool HasEvidenceToken() const noexcept { return evidence_token != 0; }
};

} // namespace assembler::ecosystem_governance::policy_type_system
