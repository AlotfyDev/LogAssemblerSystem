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

#include <string>

#include "TLogApiFinalEnvelopeAssemblyBridgeResult.hpp"
#include "TLogApiFinalEnvelopeAssemblerBridgeProfile.hpp"

namespace assembler::log_level_api::envelope_assembler::final_envelope_bridge {

struct TLogApiFinalEnvelopeAssemblerBridgeView final {
    std::string bridge_id{};
    std::string bridge_name{};
    std::string envelope_id{};
    bool ready{false};
    bool accepted{false};

    [[nodiscard]] static TLogApiFinalEnvelopeAssemblerBridgeView From(
        const TLogApiFinalEnvelopeAssemblerBridgeProfile& profile,
        const TLogApiFinalEnvelopeAssemblyBridgeResult& result
    ) {
        TLogApiFinalEnvelopeAssemblerBridgeView view{};
        view.bridge_id = profile.id.ToString();
        view.bridge_name = profile.bridge_name;
        view.envelope_id = result.final_envelope_result.envelope.header.id.ToString();
        view.ready = profile.IsReady();
        view.accepted = result.IsAccepted();
        return view;
    }
};

} // namespace assembler::log_level_api::envelope_assembler::final_envelope_bridge
