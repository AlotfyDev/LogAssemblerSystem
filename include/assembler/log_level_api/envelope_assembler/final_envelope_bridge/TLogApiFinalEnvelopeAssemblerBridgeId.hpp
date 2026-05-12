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

#include <cstdint>
#include <string>

namespace assembler::log_level_api::envelope_assembler::final_envelope_bridge {

struct TLogApiFinalEnvelopeAssemblerBridgeId final {
    std::uint64_t value{0};

    constexpr TLogApiFinalEnvelopeAssemblerBridgeId() = default;
    constexpr explicit TLogApiFinalEnvelopeAssemblerBridgeId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-final-envelope-assembler-bridge-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::envelope_assembler::final_envelope_bridge
