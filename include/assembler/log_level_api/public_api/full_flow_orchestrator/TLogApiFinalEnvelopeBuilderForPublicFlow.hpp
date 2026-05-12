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

#include "assembler/log_level_api/envelope/final_shape/TLogApiFinalEnvelopeSurface.hpp"

namespace assembler::log_level_api::public_api::full_flow_orchestrator {

class TLogApiFinalEnvelopeBuilderForPublicFlow final {
public:
    [[nodiscard]] static assembler::log_level_api::envelope::final_shape::TLogApiFinalEnvelopeResult Build(
        std::uint64_t envelope_sequence,
        const assembler::log_level_api::api_configurator::TLogApiActiveProfile& active_profile,
        const assembler::log_level_api::content::TLogApiContentInputRef& content_ref,
        const assembler::log_level_api::content_parser::TLogApiParsedContentRef& parsed_ref,
        const assembler::log_level_api::metadata_injector::TLogApiPreparedMetadataBlock& metadata,
        const assembler::log_level_api::timestamp_stabilizer::TLogApiStabilizedTimestamp& timestamp,
        const assembler::log_level_api::validator::TLogApiValidationResult& validation,
        bool validation_present
    ) {
        using namespace assembler::log_level_api::envelope::final_shape;

        TLogApiFinalEnvelopeResult result{};

        TLogApiFinalEnvelope envelope{};
        envelope.header.id = TLogApiEnvelopeIdentityFactory::FromSequence(envelope_sequence);
        envelope.header.version = {1, 0};
        envelope.header.status = TLogApiFinalEnvelopeStatus::Ready;
        envelope.header.envelope_profile_name = "default.final.envelope";
        envelope.header.content_profile_name = active_profile.content_profile_name;
        envelope.header.metadata_profile_name = active_profile.metadata_profile_name;
        envelope.header.timestamp_profile_name = active_profile.timestamp_profile_name;
        envelope.header.validation_profile_name = validation_present ? "validation.evaluated" : "not_evaluated";

        envelope.content_slot.content = content_ref;
        envelope.content_slot.parsed_content = parsed_ref;
        envelope.metadata_slot.metadata = metadata;
        envelope.timestamp_slot.timestamp = timestamp;
        envelope.validation_slot = validation_present
            ? TLogApiEnvelopeValidationResultSlot::FromValidationResult(validation)
            : TLogApiEnvelopeValidationResultSlot::NotEvaluated();

        result.envelope = envelope;

        if (!result.envelope.IsWellShaped()) {
            result.issues.push_back({
                "LOGAPI_FULL_FLOW_FINAL_ENVELOPE_NOT_WELL_SHAPED",
                "Full flow produced an envelope that is not well-shaped.",
                true
            });
        }

        return result;
    }
};

} // namespace assembler::log_level_api::public_api::full_flow_orchestrator
