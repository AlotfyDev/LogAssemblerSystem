#pragma once

/*
    LOGAPI-W23 — Envelope Final Shape And Identity

    Responsibility:
        Define final envelope identity/header shape, official envelope slots,
        validation result slot, readiness view, and final envelope carrier.

    Boundary:
        The envelope is a carrier and identity surface, not an assembler and not
        a policy decision maker. A validation result slot records valid/invalid
        evidence, but accepting or rejecting a payload based on that result is a
        separate user/policy concern.

    Doctrine:
        Envelope = identity/header + content slot + metadata slot + timestamp slot
                   + validation result slot.
*/

#include <cstdint>
#include <string>

namespace assembler::log_level_api::envelope::final_shape {

struct TLogApiFinalEnvelopeId final {
    std::uint64_t value{0};

    constexpr TLogApiFinalEnvelopeId() = default;
    constexpr explicit TLogApiFinalEnvelopeId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-final-envelope-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::envelope::final_shape
