#pragma once

/*
    LOGAPI-W24 — Envelope Readiness And Exposure View

    Responsibility:
        Define envelope readiness and exposure view/report types on top of the
        final envelope shape from LOGAPI-W23.

    Boundary:
        This wave does not assemble envelopes, mutate envelopes, perform
        circulation handoff, run validators, execute policy decisions, or persist
        envelope material.

    Doctrine:
        Readiness/exposure views are observational surfaces.
        They help later communication bindings and circulation integration decide
        whether an envelope is visible/ready, without owning downstream behavior.
*/

#include <cstdint>
#include <string>

namespace assembler::log_level_api::envelope::readiness_exposure {

struct TLogApiEnvelopeExposureId final {
    std::uint64_t value{0};

    constexpr TLogApiEnvelopeExposureId() = default;
    constexpr explicit TLogApiEnvelopeExposureId(std::uint64_t v) noexcept : value(v) {}

    [[nodiscard]] constexpr bool IsValid() const noexcept { return value != 0; }

    [[nodiscard]] std::string ToString() const {
        return "logapi-envelope-exposure-" + std::to_string(value);
    }
};

} // namespace assembler::log_level_api::envelope::readiness_exposure
