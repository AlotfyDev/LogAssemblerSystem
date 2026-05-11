#pragma once

#include <cstdint>

/*
    TReportContractIssueKind.hpp

    Delivery:
        CME-REPORTS-PROD-W01 — Production Evidence Contract

    Current responsibility:
        Classifies contract issues found while validating report descriptors.

    Production capabilities:
        - Stable report vocabulary.
        - constexpr-friendly classification support.
        - No runtime action or recovery behavior.

    Explicit non-ownership:
        - Does not execute behavior.
        - Does not export telemetry.
        - Does not mutate component state.
        - Does not prove downstream success.
*/

namespace assembler {
namespace circulation_mechanism {


enum class TReportContractIssueKind : std::uint8_t
{
    none,
        invalid_id,
        invalid_status,
        scope_kind_mismatch,
        downstream_proof_claim,
        authority_expansion_claim,
        unknown
};

} // namespace circulation_mechanism
} // namespace assembler
