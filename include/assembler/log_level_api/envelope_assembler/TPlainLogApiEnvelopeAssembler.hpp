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

#include "assembler/log_level_api/envelope/TLogApiEnvelopeSurface.hpp"

#include "TLogApiEnvelopeAssemblyInput.hpp"
#include "TLogApiEnvelopeAssemblyProfile.hpp"
#include "TLogApiEnvelopeAssemblyResult.hpp"

namespace assembler::log_level_api::envelope_assembler {

/*
    Plain envelope assembler.

    This class represents the no-validation assembly family.
    It must not branch to discover or invoke a validator.
*/
class TPlainLogApiEnvelopeAssembler final {
public:
    [[nodiscard]] static TLogApiEnvelopeAssemblyResult Assemble(
        const TLogApiEnvelopeAssemblyProfile& profile,
        const TLogApiEnvelopeAssemblyInput& input
    ) {
        TLogApiEnvelopeAssemblyResult result{};

        if (!profile.IsResolved()) {
            result.issues.push_back({"LOGAPI_ASSEMBLY_PROFILE_NOT_RESOLVED", "Envelope assembly profile is not resolved.", true});
            return result;
        }

        if (profile.family != assembler::log_level_api::api_configurator::TLogApiAssemblerFamilyKind::PlainEnvelopeAssembler) {
            result.issues.push_back({"LOGAPI_ASSEMBLY_WRONG_FAMILY", "Plain assembler requires PlainEnvelopeAssembler family.", true});
            return result;
        }

        if (!input.HasBaseMaterial()) {
            result.issues.push_back({"LOGAPI_ASSEMBLY_BASE_MATERIAL_MISSING", "Content, metadata, and stabilized timestamp are required.", true});
            return result;
        }

        assembler::log_level_api::envelope::TLogApiEnvelope envelope{};
        envelope.header.envelope_id = assembler::log_level_api::envelope::TLogApiEnvelopeId{1};
        envelope.header.status = assembler::log_level_api::envelope::TLogApiEnvelopeStatus::Prepared;
        envelope.header.envelope_profile_name = profile.envelope_profile_name;
        envelope.header.content_profile_name = input.accepted_content.active_profile->content_profile_name;
        envelope.header.metadata_profile_name = input.accepted_content.active_profile->metadata_profile_name;
        envelope.header.timestamp_profile_name = input.accepted_content.active_profile->timestamp_profile_name;
        envelope.content.content = input.accepted_content.content;
        envelope.metadata.metadata = input.metadata;
        envelope.timestamp.timestamp = input.timestamp;
        envelope.validation.present = false;

        result.envelope_result.envelope = envelope;

        if (!result.envelope_result.envelope.IsComplete()) {
            result.envelope_result.issues.push_back({"LOGAPI_ENVELOPE_INCOMPLETE", "Plain assembly produced an incomplete envelope.", true});
        }

        return result;
    }
};

} // namespace assembler::log_level_api::envelope_assembler
