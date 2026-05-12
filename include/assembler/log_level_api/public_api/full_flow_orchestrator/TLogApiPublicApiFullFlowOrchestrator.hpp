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

#include "assembler/log_level_api/content_parser/TLogApiOpaqueContentParser.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiMetadataInjector.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiTimestampStabilizer.hpp"
#include "assembler/log_level_api/envelope/readiness_exposure/TLogApiEnvelopeReadinessExposureSurface.hpp"
#include "assembler/log_level_api/communication_bindings/circulation_handoff/TLogApiCirculationHandoffContractSurface.hpp"

#include "TLogApiFinalEnvelopeBuilderForPublicFlow.hpp"
#include "TLogApiFullFlowRequest.hpp"
#include "TLogApiFullFlowResult.hpp"

namespace assembler::log_level_api::public_api::full_flow_orchestrator {

/*
    Public API full-flow orchestrator.

    This first extension supports the complete OpaqueNoParse path end-to-end.
    Specialized JSON/C-struct/MT5 public orchestration remains a later extension
    so that hot-path parser dispatch is not introduced here.
*/
class TLogApiPublicApiFullFlowOrchestrator final {
public:
    [[nodiscard]] static TLogApiFullFlowResult RunOpaqueNoParse(
        const TLogApiFullFlowRequest& request
    ) {
        using namespace assembler::log_level_api::content_parser;
        using namespace assembler::log_level_api::envelope::readiness_exposure;
        using namespace assembler::log_level_api::communication_bindings::circulation_handoff;

        TLogApiFullFlowResult result{};

        if (!request.IsReady()) {
            result.status = TLogApiFullFlowStatus::Rejected;
            result.issues.push_back({
                "LOGAPI_FULL_FLOW_REQUEST_NOT_READY",
                "Full flow requires resolved context, content-only request, and timestamp input.",
                true
            });
            return result;
        }

        if (!request.resolved_context.public_context.parser_binding->profile.IsOpaqueNoParse()) {
            result.status = TLogApiFullFlowStatus::Rejected;
            result.issues.push_back({
                "LOGAPI_FULL_FLOW_ONLY_OPAQUE_SUPPORTED",
                "This orchestrator wave only runs the complete OpaqueNoParse flow.",
                true
            });
            return result;
        }

        TLogApiContentParseRequest parse_request{};
        parse_request.content = request.public_call.ContentRef();
        parse_request.parser_binding = request.resolved_context.public_context.parser_binding;

        result.parse_result = TLogApiOpaqueContentParser::Parse(parse_request);
        if (!result.parse_result.IsAccepted()) {
            result.status = TLogApiFullFlowStatus::Rejected;
            result.issues.push_back({"LOGAPI_FULL_FLOW_PARSE_FAILED", "Opaque parsing failed.", true});
            return result;
        }
        result.status = TLogApiFullFlowStatus::Parsed;

        result.metadata_result = assembler::log_level_api::metadata_injector::TLogApiMetadataInjector::Prepare(
            *request.resolved_context.metadata_config
        );
        if (!result.metadata_result.IsAccepted()) {
            result.status = TLogApiFullFlowStatus::Rejected;
            result.issues.push_back({"LOGAPI_FULL_FLOW_METADATA_FAILED", "Metadata preparation failed.", true});
            return result;
        }
        result.status = TLogApiFullFlowStatus::MetadataPrepared;

        result.timestamp_result = assembler::log_level_api::timestamp_stabilizer::TLogApiTimestampStabilizer::Stabilize(
            *request.resolved_context.timestamp_config,
            request.timestamp_input
        );
        if (!result.timestamp_result.IsAccepted()) {
            result.status = TLogApiFullFlowStatus::Rejected;
            result.issues.push_back({"LOGAPI_FULL_FLOW_TIMESTAMP_FAILED", "Timestamp stabilization failed.", true});
            return result;
        }
        result.status = TLogApiFullFlowStatus::TimestampStabilized;

        result.envelope_result = TLogApiFinalEnvelopeBuilderForPublicFlow::Build(
            request.run_id.value,
            *request.resolved_context.public_context.active_profile,
            request.public_call.ContentRef(),
            result.parse_result.parsed_content,
            result.metadata_result.block,
            result.timestamp_result.timestamp,
            request.validation_result,
            request.validation_present
        );
        if (!result.envelope_result.IsAccepted()) {
            result.status = TLogApiFullFlowStatus::Rejected;
            result.issues.push_back({"LOGAPI_FULL_FLOW_ENVELOPE_FAILED", "Final envelope shaping failed.", true});
            return result;
        }
        result.status = TLogApiFullFlowStatus::EnvelopeShaped;

        TLogApiEnvelopeExposureRequest exposure_request{};
        exposure_request.exposure_id = TLogApiEnvelopeExposureId{request.run_id.value};
        exposure_request.exposure_kind = TLogApiEnvelopeExposureKind::BindingView;
        exposure_request.envelope = &result.envelope_result.envelope;

        result.exposure_result = TLogApiEnvelopeExposureBuilder::Build(exposure_request);
        if (!result.exposure_result.IsAccepted()) {
            result.status = TLogApiFullFlowStatus::Rejected;
            result.issues.push_back({"LOGAPI_FULL_FLOW_EXPOSURE_FAILED", "Envelope exposure failed.", true});
            return result;
        }
        result.status = TLogApiFullFlowStatus::EnvelopeExposed;

        TLogApiCirculationHandoffRequest handoff{};
        handoff.id = TLogApiCirculationHandoffId{request.run_id.value};
        handoff.status = TLogApiCirculationHandoffStatus::Ready;
        handoff.expectation = TLogApiCirculationAdmissionExpectationKind::EnvelopeIntake;
        handoff.envelope_exposure = result.exposure_result.view;
        handoff.target = request.resolved_context.public_context.circulation_target;

        result.handoff_result = TLogApiCirculationHandoffContract::Submit(handoff);
        if (!result.handoff_result.IsAcceptedByContract()) {
            result.status = TLogApiFullFlowStatus::Rejected;
            result.issues.push_back({"LOGAPI_FULL_FLOW_HANDOFF_FAILED", "Handoff contract rejected the envelope.", true});
            return result;
        }

        result.status = TLogApiFullFlowStatus::HandoffAccepted;
        return result;
    }
};

} // namespace assembler::log_level_api::public_api::full_flow_orchestrator
