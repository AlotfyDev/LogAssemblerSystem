#pragma once

/*
    LOGAPI-W08 — Envelope Assembler Families

    This header belongs to the Log Level API envelope assembler family layer.

    Responsibility:
        Define envelope assembly input, assembly profile, assembly result, and
        two distinct assembler families:
            - plain envelope assembler
            - validator-composed envelope assembler

    Boundary:
        The assembler composes already prepared material into an envelope.
        It must not define content schemas, metadata field definitions, timestamp
        stabilization rules, concrete validators, API consuming behavior,
        communication bindings, circulation handoff, or policy assignment.

    Hot-path doctrine:
        Plain assembly and validator-composed assembly are separate types.
        The system must not branch inside one assembler flow to ask whether a
        validator exists. The assembler family is selected before the hot path.
*/

#include "assembler/log_level_api/api_facade/TLogApiFacadeAcceptedContent.hpp"
#include "assembler/log_level_api/metadata_injector/TLogApiPreparedMetadataBlock.hpp"
#include "assembler/log_level_api/timestamp_stabilizer/TLogApiStabilizedTimestamp.hpp"
#include "assembler/log_level_api/validator/TLogApiValidationResult.hpp"

namespace assembler::log_level_api::envelope_assembler {

/*
    Assembly input.

    This object receives already prepared independent artifacts:
        accepted content,
        prepared metadata block,
        stabilized timestamp,
        optional validation result.

    It does not carry schema definitions, metadata definitions, timestamp rules,
    validator bindings, or policy assignment material.
*/
struct TLogApiEnvelopeAssemblyInput final {
    assembler::log_level_api::api_facade::TLogApiFacadeAcceptedContent accepted_content{};
    assembler::log_level_api::metadata_injector::TLogApiPreparedMetadataBlock metadata{};
    assembler::log_level_api::timestamp_stabilizer::TLogApiStabilizedTimestamp timestamp{};

    assembler::log_level_api::validator::TLogApiValidationResult validation{};
    bool validation_present{false};

    [[nodiscard]] bool HasBaseMaterial() const noexcept {
        return accepted_content.IsValid()
            && metadata.IsReadyForEnvelope()
            && timestamp.IsPresent();
    }

    [[nodiscard]] bool HasAcceptedValidationWhenPresent() const noexcept {
        return !validation_present || validation.IsAccepted();
    }
};

} // namespace assembler::log_level_api::envelope_assembler
