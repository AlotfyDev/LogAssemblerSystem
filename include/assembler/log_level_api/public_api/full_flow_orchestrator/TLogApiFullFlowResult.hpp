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

#include <vector>

#include "assembler/log_level_api/content_parser/TLogApiContentParseResult.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataInjectionResult.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampStabilizationResult.hpp"
#include "assembler/log_level_api/envelope/final_shape/TLogApiFinalEnvelopeResult.hpp"
#include "assembler/log_level_api/envelope/readiness_exposure/TLogApiEnvelopeExposureResult.hpp"
#include "assembler/log_level_api/communication_bindings/circulation_handoff/TLogApiCirculationHandoffResult.hpp"

#include "TLogApiFullFlowIssue.hpp"
#include "TLogApiFullFlowStatus.hpp"

namespace assembler::log_level_api::public_api::full_flow_orchestrator {

struct TLogApiFullFlowResult final {
    TLogApiFullFlowStatus status{TLogApiFullFlowStatus::Unknown};

    assembler::log_level_api::content_parser::TLogApiContentParseResult parse_result{};
    assembler::log_level_api::metadata_injector::TLogApiMetadataInjectionResult metadata_result{};
    assembler::log_level_api::timestamp_stabilizer::TLogApiTimestampStabilizationResult timestamp_result{};
    assembler::log_level_api::envelope::final_shape::TLogApiFinalEnvelopeResult envelope_result{};
    assembler::log_level_api::envelope::readiness_exposure::TLogApiEnvelopeExposureResult exposure_result{};
    assembler::log_level_api::communication_bindings::circulation_handoff::TLogApiCirculationHandoffResult handoff_result{};

    std::vector<TLogApiFullFlowIssue> issues{};

    [[nodiscard]] bool HasBlockingIssue() const noexcept {
        for (const auto& issue : issues) {
            if (issue.blocking) return true;
        }
        return false;
    }

    [[nodiscard]] bool IsAccepted() const noexcept {
        return status == TLogApiFullFlowStatus::HandoffAccepted
            && parse_result.IsAccepted()
            && metadata_result.IsAccepted()
            && timestamp_result.IsAccepted()
            && envelope_result.IsAccepted()
            && exposure_result.IsAccepted()
            && handoff_result.IsAcceptedByContract()
            && !HasBlockingIssue();
    }
};

} // namespace assembler::log_level_api::public_api::full_flow_orchestrator
