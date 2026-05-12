#pragma once

/*
    LOGAPI-EXT-W02 — Final Envelope Assembler Bridge

    Responsibility:
        Bridge the W08 envelope assembler family inputs/profiles into the W23
        final envelope shape, producing TLogApiFinalEnvelopeResult.

    Boundary:
        This wave does not implement new parser behavior, metadata injection,
        timestamp stabilization, circulation handoff, policy assignment, bridge
        orchestration, or receiver behavior.

    Doctrine:
        W08 assembly profile remains the assembler-family selection surface.
        W23 final envelope remains the target carrier shape.
        Validation result slot remains evidence only; it does not decide payload
        acceptance or rejection.
*/

#include "assembler/log_level_api/api_configurator/TLogApiAssemblerFamilyKind.hpp"
#include "assembler/log_level_api/envelope/final_shape/TLogApiFinalEnvelopeSurface.hpp"
#include "assembler/log_level_api/content_parser/TLogApiContentParserSurface.hpp"

#include "TLogApiFinalEnvelopeAssemblyBridgeInput.hpp"
#include "TLogApiFinalEnvelopeAssemblyBridgeResult.hpp"
#include "TLogApiFinalEnvelopeAssemblerBridgeProfile.hpp"

namespace assembler::log_level_api::envelope_assembler::final_envelope_bridge::detail {

[[nodiscard]] inline TLogApiFinalEnvelopeAssemblyBridgeResult Reject(const char* code, const char* message) {
    TLogApiFinalEnvelopeAssemblyBridgeResult result{};
    result.status = TLogApiFinalEnvelopeAssemblerBridgeStatus::Rejected;
    result.issues.push_back({code, message, true});
    return result;
}

[[nodiscard]] inline assembler::log_level_api::envelope::final_shape::TLogApiFinalEnvelope BuildBaseFinalEnvelope(
    std::uint64_t envelope_sequence,
    const TLogApiFinalEnvelopeAssemblyBridgeInput& input
) {
    using namespace assembler::log_level_api::envelope::final_shape;

    const auto* active = input.assembly_input.accepted_content.active_profile;

    TLogApiFinalEnvelope envelope{};
    envelope.header.id = TLogApiEnvelopeIdentityFactory::FromSequence(envelope_sequence);
    envelope.header.version = {1, 0};
    envelope.header.status = TLogApiFinalEnvelopeStatus::Ready;
    envelope.header.envelope_profile_name = "default.final.envelope";
    envelope.header.content_profile_name = active ? active->content_profile_name : "";
    envelope.header.metadata_profile_name = active ? active->metadata_profile_name : "";
    envelope.header.timestamp_profile_name = active ? active->timestamp_profile_name : "";
    envelope.header.validation_profile_name = input.assembly_input.validation_present ? "validation.evaluated" : "not_evaluated";

    envelope.content_slot.content = input.assembly_input.accepted_content.content;
    envelope.content_slot.parsed_content.parsed_kind = assembler::log_level_api::content_parser::TLogApiParsedContentKind::OpaqueContentRef;
    envelope.content_slot.parsed_content.source_content = input.assembly_input.accepted_content.content;
    envelope.content_slot.parsed_content.parsed = false;

    envelope.metadata_slot.metadata = input.assembly_input.metadata;
    envelope.timestamp_slot.timestamp = input.assembly_input.timestamp;
    envelope.validation_slot = input.assembly_input.validation_present
        ? TLogApiEnvelopeValidationResultSlot::FromValidationResult(input.assembly_input.validation)
        : TLogApiEnvelopeValidationResultSlot::NotEvaluated();

    return envelope;
}

[[nodiscard]] inline TLogApiFinalEnvelopeAssemblyBridgeResult BuildResult(
    const TLogApiFinalEnvelopeAssemblerBridgeProfile&,
    const TLogApiFinalEnvelopeAssemblyBridgeInput& input,
    std::uint64_t envelope_sequence
) {
    TLogApiFinalEnvelopeAssemblyBridgeResult result{};
    result.status = TLogApiFinalEnvelopeAssemblerBridgeStatus::Bridged;
    result.final_envelope_result.envelope = BuildBaseFinalEnvelope(envelope_sequence, input);

    if (!result.final_envelope_result.envelope.IsWellShaped()) {
        result.status = TLogApiFinalEnvelopeAssemblerBridgeStatus::Rejected;
        result.final_envelope_result.issues.push_back({
            "LOGAPI_FINAL_ENVELOPE_BRIDGE_NOT_WELL_SHAPED",
            "Final envelope bridge produced a non-well-shaped envelope.",
            true
        });
    }

    return result;
}

} // namespace assembler::log_level_api::envelope_assembler::final_envelope_bridge::detail
