#pragma once

#include <cstdint>

/*
    TReportScopeKind.hpp

    Delivery:
        CME-REPORTS-PROD-W01 — Production Evidence Contract

    Current responsibility:
        Classifies the scope in which report evidence is meaningful.

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


enum class TReportScopeKind : std::uint8_t
{
    local_component,
        cross_component,
        boundary,
        diagnostic,
        test,
        readiness
};

} // namespace circulation_mechanism
} // namespace assembler
