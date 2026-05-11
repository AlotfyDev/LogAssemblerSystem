#pragma once

#include <cstdint>

/*
    TReportStatus.hpp

    Delivery:
        CME-REPORTS-PROD-W01 — Production Evidence Contract

    Current responsibility:
        Classifies lifecycle/status of a report artifact.

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


enum class TReportStatus : std::uint8_t
{
    created,
        complete,
        incomplete,
        suppressed,
        invalid
};

} // namespace circulation_mechanism
} // namespace assembler
