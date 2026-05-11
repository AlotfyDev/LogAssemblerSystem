#pragma once

#include <cstdint>

/*
    TSafePointKind.hpp

    Delivery:
        CME-SAFEPOINT-PROD-W01 — Production Guard And Claim Contract

    Current responsibility:
        Classifies the operation protected by a safe point.

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


enum class TSafePointKind : std::uint8_t
{
    container_reset,
        vertical_scaling,
        horizontal_scaling,
        profile_switch,
        registry_rebuild,
        reference_invalidation,
        eviction,
        dispatch_exposure_closure,
        round_closure,
        release_recycle
};

} // namespace circulation_mechanism
} // namespace assembler
