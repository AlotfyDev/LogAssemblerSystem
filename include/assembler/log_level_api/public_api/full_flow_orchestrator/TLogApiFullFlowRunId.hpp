#pragma once

/*
    LOGAPI-EXT-W01 — Public API Full Flow Orchestrator

    Responsibility:
        Define a production-oriented public API orchestration skeleton that
        connects:
            public content-only request
            → parser
            → metadata preparation
            → timestamp stabilization
            → final envelope shaping
            → envelope exposure
            → circulation handoff contract

    Boundary:
        This wave does not implement specialized JSON/C-struct/MT5 parser routing,
        real circulation admission, envelope streaming, persistence, policy
        assignment, bridge orchestration, or external receiver behavior.

    Doctrine:
        Configure first. Consume content only.
        No per-call schema/metadata/validator/timestamp/assembler/circulation/policy
        configuration is allowed.
*/

#include <cstdint>
#include <string>

namespace assembler::log_level_api::public_api::full_flow_orchestrator {

struct TLogApiFullFlowRunId final {
    std::uint64_t value{0};

    constexpr TLogApiFullFlowRunId() = default;
    constexpr explicit TLogApiFullFlowRunId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-full-flow-run-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::public_api::full_flow_orchestrator
