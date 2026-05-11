#pragma once

#include <cstdint>

/*
    TReportKind.hpp

    Delivery:
        CME-REPORTS-PROD-W01 — Production Evidence Contract

    Current responsibility:
        Classifies what kind of evidence a report carries.

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


enum class TReportKind : std::uint8_t
{
    operational,
        transition,
        diagnostic,
        invariant,
        boundary,
        capacity,
        eviction,
        reference,
        safe_point,
        readiness
};

} // namespace circulation_mechanism
} // namespace assembler
