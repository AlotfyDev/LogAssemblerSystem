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

#include "assembler/log_level_api/envelope_assembler/TLogApiEnvelopeAssemblyInput.hpp"

namespace assembler::log_level_api::envelope_assembler::final_envelope_bridge {

struct TLogApiFinalEnvelopeAssemblyBridgeInput final {
    assembler::log_level_api::envelope_assembler::TLogApiEnvelopeAssemblyInput assembly_input{};

    [[nodiscard]] bool HasBaseMaterial() const noexcept {
        return assembly_input.HasBaseMaterial();
    }
};

} // namespace assembler::log_level_api::envelope_assembler::final_envelope_bridge
