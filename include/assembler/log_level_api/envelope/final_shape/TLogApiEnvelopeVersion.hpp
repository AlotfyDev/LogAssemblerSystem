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

struct TLogApiEnvelopeVersion final {
    std::uint32_t major{1};
    std::uint32_t minor{0};

    [[nodiscard]] bool IsValid() const noexcept {
        return major > 0;
    }

    [[nodiscard]] std::string ToString() const {
        return std::to_string(major) + "." + std::to_string(minor);
    }
};

} // namespace assembler::log_level_api::envelope::final_shape
