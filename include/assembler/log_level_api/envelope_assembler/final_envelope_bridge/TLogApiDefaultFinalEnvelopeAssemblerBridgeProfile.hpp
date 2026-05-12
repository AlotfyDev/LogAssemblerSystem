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

#include "TLogApiFinalEnvelopeAssemblerBridgeProfile.hpp"

namespace assembler::log_level_api::envelope_assembler::final_envelope_bridge {

struct TLogApiDefaultFinalEnvelopeAssemblerBridgeProfile final {
    [[nodiscard]] static TLogApiFinalEnvelopeAssemblerBridgeProfile Make(
        const assembler::log_level_api::envelope_assembler::TLogApiEnvelopeAssemblyProfile& assembly_profile
    ) {
        TLogApiFinalEnvelopeAssemblerBridgeProfile profile{};
        profile.id = TLogApiFinalEnvelopeAssemblerBridgeId{1};
        profile.status = TLogApiFinalEnvelopeAssemblerBridgeStatus::Ready;
        profile.bridge_name = "default.final.envelope.assembler.bridge";
        profile.assembly_profile = assembly_profile;
        return profile;
    }
};

} // namespace assembler::log_level_api::envelope_assembler::final_envelope_bridge
