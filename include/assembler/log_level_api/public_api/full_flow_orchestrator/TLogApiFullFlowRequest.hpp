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

#include "assembler/log_level_api/public_api/TLogApiPublicCallRequest.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampStabilizationInput.hpp"
#include "assembler/log_level_api/validator/TLogApiValidationResult.hpp"

#include "TLogApiFullFlowResolvedContext.hpp"
#include "TLogApiFullFlowRunId.hpp"

namespace assembler::log_level_api::public_api::full_flow_orchestrator {

/*
    Full-flow request.

    The public_call remains content-only. Timestamp input is modeled here as
    already-captured preparation input, not as per-call timestamp configuration.
*/
struct TLogApiFullFlowRequest final {
    TLogApiFullFlowRunId run_id{};
    assembler::log_level_api::public_api::TLogApiPublicCallRequest public_call{};
    TLogApiFullFlowResolvedContext resolved_context{};
    assembler::log_level_api::timestamp_stabilizer::TLogApiTimestampStabilizationInput timestamp_input{};

    assembler::log_level_api::validator::TLogApiValidationResult validation_result{};
    bool validation_present{false};

    [[nodiscard]] bool IsReady() const noexcept {
        if (!run_id.IsValid()) return false;
        if (!resolved_context.IsReady()) return false;
        if (!public_call.IsReady()) return false;
        if (!timestamp_input.HasSystemEntryTimestamp()) return false;
        return true;
    }
};

} // namespace assembler::log_level_api::public_api::full_flow_orchestrator
