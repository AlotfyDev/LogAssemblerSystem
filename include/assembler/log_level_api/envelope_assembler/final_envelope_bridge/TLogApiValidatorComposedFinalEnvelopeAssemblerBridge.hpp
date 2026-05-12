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

#include "TLogApiFinalEnvelopeAssemblyBridgeDetail.hpp"

namespace assembler::log_level_api::envelope_assembler::final_envelope_bridge {

class TLogApiValidatorComposedFinalEnvelopeAssemblerBridge final {
public:
    [[nodiscard]] static TLogApiFinalEnvelopeAssemblyBridgeResult Assemble(
        const TLogApiFinalEnvelopeAssemblerBridgeProfile& profile,
        const TLogApiFinalEnvelopeAssemblyBridgeInput& input,
        std::uint64_t envelope_sequence
    ) {
        using Family = assembler::log_level_api::api_configurator::TLogApiAssemblerFamilyKind;

        if (!profile.IsReady()) {
            return detail::Reject("LOGAPI_FINAL_BRIDGE_PROFILE_NOT_READY", "Final envelope assembler bridge profile is not ready.");
        }

        if (profile.assembly_profile.family != Family::ValidatorComposedEnvelopeAssembler) {
            return detail::Reject("LOGAPI_FINAL_BRIDGE_WRONG_ASSEMBLER_FAMILY", "Validator-composed final envelope bridge requires ValidatorComposedEnvelopeAssembler family.");
        }

        if (!input.HasBaseMaterial()) {
            return detail::Reject("LOGAPI_FINAL_BRIDGE_BASE_MATERIAL_MISSING", "Content, metadata, and timestamp are required for final envelope bridge.");
        }

        if (!input.assembly_input.validation_present) {
            return detail::Reject("LOGAPI_FINAL_BRIDGE_VALIDATION_RESULT_MISSING", "Validator-composed final envelope bridge requires validation result evidence.");
        }

        return detail::BuildResult(profile, input, envelope_sequence);
    }
};

} // namespace assembler::log_level_api::envelope_assembler::final_envelope_bridge
