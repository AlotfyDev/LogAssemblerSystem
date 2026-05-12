#pragma once

/*
    LOGAPI-W07 — Envelope Carrier

    This header belongs to the Log Level API envelope carrier layer.

    Responsibility:
        Define the Log Level Envelope carrier and its compositional blocks:
        envelope identity/header/status, content reference, metadata block reference,
        stabilized timestamp, validation evidence reference, envelope view, and
        carrier result/report structures.

    Boundary:
        The envelope is a carrier, not an assembler.
        This wave must not define envelope assembly algorithms, concrete schemas,
        concrete validators, metadata injection logic, timestamp clock acquisition,
        API consuming behavior, communication bindings, circulation handoff, or
        policy assignment.

    Doctrine:
        Content, metadata struct, and stabilized timestamp remain independent
        until the envelope assembler composes them into a Log Level Envelope.
*/

#include <cstdint>
#include <string>

namespace assembler::log_level_api::envelope {

struct TLogApiEnvelopeId final {
    std::uint64_t value{0};

    constexpr TLogApiEnvelopeId() = default;
    constexpr explicit TLogApiEnvelopeId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-envelope-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::envelope
