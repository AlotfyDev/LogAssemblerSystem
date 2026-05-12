#pragma once

#include <string>
#include <utility>

namespace assembler::ecosystem_governance::policy_production_readiness
{
/*
 * Wave: EG-POL-W34_Production_Readiness_Gate
 * Domain: ecosystem_governance / policy_production_readiness
 *
 * Architectural role:
 *   This header defines a lightweight evidence reference for production
 *   readiness review. It can point to compile reports, compliance reports,
 *   integration summaries, audit evidence, persistence-boundary reviews, or
 *   known-decision records without owning those records.
 *
 * Relationship to prior waves:
 *   W30-W33 introduced persistence, audit-export, failure/recovery, and
 *   compliance artifacts. W34 needs a neutral reference shape that can cite those
 *   artifacts while preserving ownership boundaries.
 *
 * Full intended picture:
 *   Future tooling may resolve these references into documents, generated test
 *   outputs, registry snapshots, or audit-export batches. This wave only records
 *   references.
 *
 * Explicit non-responsibilities:
 *   This file does not load files, query databases, export telemetry, dereference
 *   network resources, or validate the evidence content.
 */
struct TPolicyProductionReadinessEvidenceRef
{
    std::string kind;
    std::string ref;
    std::string note;

    TPolicyProductionReadinessEvidenceRef() = default;
    TPolicyProductionReadinessEvidenceRef(std::string k, std::string r)
        : kind(std::move(k)), ref(std::move(r)) {}

    [[nodiscard]] bool empty() const noexcept { return kind.empty() && ref.empty(); }
};

} // namespace assembler::ecosystem_governance::policy_production_readiness
