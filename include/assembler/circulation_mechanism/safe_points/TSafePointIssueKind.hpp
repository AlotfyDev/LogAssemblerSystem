#pragma once

#include <cstdint>

/*
    TSafePointIssueKind.hpp

    Delivery:
        CME-SAFEPOINT-PROD-W01 — Production Guard And Claim Contract

    Current responsibility:
        Classifies why a safe-point claim or guard failed.

    Production capabilities:
        - Stable safe-point vocabulary.
        - constexpr-friendly guard semantics.
        - No guarded-operation execution.

    Explicit non-ownership:
        - Does not execute reset/scaling/eviction/rebuild/invalidation.
        - Does not own runtime component state.
        - Does not imply global process suspension.
*/

namespace assembler {
namespace circulation_mechanism {


enum class TSafePointIssueKind : std::uint8_t
{
    none,
        invalid_id,
        kind_mismatch,
        unavailable,
        expired,
        already_claimed,
        already_consumed,
        violated,
        unsafe_operation
};

} // namespace circulation_mechanism
} // namespace assembler
