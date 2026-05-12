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

#include <string>

#include "TLogApiEnvelopeAssemblyProfile.hpp"

namespace assembler::log_level_api::envelope_assembler {

struct TLogApiEnvelopeAssemblerView final {
    std::string assembler_id{};
    std::string family{};
    std::string envelope_profile_name{};
    bool resolved{false};

    [[nodiscard]] static TLogApiEnvelopeAssemblerView From(const TLogApiEnvelopeAssemblyProfile& profile) {
        TLogApiEnvelopeAssemblerView view{};
        view.assembler_id = profile.assembler_id.ToString();
        view.envelope_profile_name = profile.envelope_profile_name;
        view.resolved = profile.IsResolved();

        switch (profile.family) {
            case assembler::log_level_api::api_configurator::TLogApiAssemblerFamilyKind::PlainEnvelopeAssembler:
                view.family = "plain_envelope_assembler";
                break;
            case assembler::log_level_api::api_configurator::TLogApiAssemblerFamilyKind::ValidatorComposedEnvelopeAssembler:
                view.family = "validator_composed_envelope_assembler";
                break;
            default:
                view.family = "unknown";
                break;
        }

        return view;
    }
};

} // namespace assembler::log_level_api::envelope_assembler
