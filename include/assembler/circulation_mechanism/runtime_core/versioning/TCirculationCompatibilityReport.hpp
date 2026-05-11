#pragma once
#include "TCirculationApiVersion.hpp"
#include "TCirculationProfileVersion.hpp"
#include "TCirculationCompatibilityStatus.hpp"

/*
    TCirculationCompatibilityReport.hpp

    Responsibility:
        Reports compatibility between requested and supported API/profile versions.
*/
namespace assembler {
namespace circulation_mechanism {

struct TCirculationCompatibilityReport final {
    TCirculationApiVersion requested_api{};
    TCirculationApiVersion supported_api{};
    TCirculationProfileVersion requested_profile{};
    TCirculationProfileVersion supported_profile{};
    TCirculationCompatibilityStatus status{TCirculationCompatibilityStatus::unknown};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return requested_api.is_valid() && supported_api.is_valid()
            && requested_profile.is_valid() && supported_profile.is_valid();
    }

    [[nodiscard]] constexpr bool compatible() const noexcept {
        return is_valid()
            && (status == TCirculationCompatibilityStatus::compatible
                || status == TCirculationCompatibilityStatus::deprecated_compatible);
    }

    [[nodiscard]] static constexpr TCirculationCompatibilityReport evaluate(
        TCirculationApiVersion requested_api,
        TCirculationApiVersion supported_api,
        TCirculationProfileVersion requested_profile,
        TCirculationProfileVersion supported_profile) noexcept
    {
        const bool api_ok = requested_api.is_valid() && supported_api.is_valid() && requested_api.raw() <= supported_api.raw();
        const bool profile_ok = requested_profile.is_valid() && supported_profile.is_valid() && requested_profile.raw() <= supported_profile.raw();
        return TCirculationCompatibilityReport{
            requested_api,
            supported_api,
            requested_profile,
            supported_profile,
            (api_ok && profile_ok) ? TCirculationCompatibilityStatus::compatible : TCirculationCompatibilityStatus::incompatible
        };
    }
};
} // namespace circulation_mechanism
} // namespace assembler
