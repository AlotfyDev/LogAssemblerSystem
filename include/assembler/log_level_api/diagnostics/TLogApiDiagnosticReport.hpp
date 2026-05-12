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

#include <vector>

#include "TLogApiDiagnosticRecord.hpp"

namespace assembler::log_level_api::diagnostics {

struct TLogApiDiagnosticReport final {
    std::vector<TLogApiDiagnosticRecord> records{};

    [[nodiscard]] bool HasDiagnostics() const noexcept {
        return !records.empty();
    }

    [[nodiscard]] bool HasBlockingDiagnostic() const noexcept {
        for (const auto& record : records) {
            if (record.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] std::size_t Count() const noexcept {
        return records.size();
    }
};

} // namespace assembler::log_level_api::diagnostics
