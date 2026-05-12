#pragma once

/*
    LOGAPI-W28 — Diagnostics And Failure Model

    Responsibility:
        Define Log Level API diagnostics, failure classification, diagnostic
        records, diagnostic reports, and boundary-local failure ownership across
        configuration, content, parser, metadata, timestamp, envelope, handoff,
        and public API surfaces.

    Boundary:
        This wave does not implement a logging backend, telemetry exporter,
        persistence, recovery engine, policy assignment, circulation engine,
        bridge orchestration, or final receiver behavior.

    Doctrine:
        Diagnostics explain Log Level API-owned states and failures.
        Diagnostics must not become telemetry, database audit, receiver retry,
        or policy governance.
*/

#include <cstdint>
#include <string>

namespace assembler::log_level_api::diagnostics {

struct TLogApiDiagnosticId final {
    std::uint64_t value{0};

    constexpr TLogApiDiagnosticId() = default;
    constexpr explicit TLogApiDiagnosticId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-diagnostic-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::diagnostics
