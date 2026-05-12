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

#include <string>

#include "TLogApiEnvelopeVersion.hpp"
#include "TLogApiFinalEnvelopeId.hpp"
#include "TLogApiFinalEnvelopeStatus.hpp"

namespace assembler::log_level_api::envelope::final_shape {

struct TLogApiEnvelopeHeaderFinal final {
    TLogApiFinalEnvelopeId id{};
    TLogApiEnvelopeVersion version{};
    TLogApiFinalEnvelopeStatus status{TLogApiFinalEnvelopeStatus::Unknown};

    std::string envelope_profile_name{};
    std::string content_profile_name{};
    std::string metadata_profile_name{};
    std::string timestamp_profile_name{};
    std::string validation_profile_name{};

    [[nodiscard]] bool IsPresent() const noexcept {
        return id.IsValid()
            && version.IsValid()
            && status != TLogApiFinalEnvelopeStatus::Unknown
            && !envelope_profile_name.empty()
            && !content_profile_name.empty()
            && !metadata_profile_name.empty()
            && !timestamp_profile_name.empty();
    }
};

} // namespace assembler::log_level_api::envelope::final_shape
