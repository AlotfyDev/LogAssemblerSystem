#pragma once
#include "assembler/circulation_mechanism/capacity/TCapacityProfileId.hpp"

/*
    TSlotsContainerModeratorConfig.hpp

    Responsibility:
        Production configuration for the per-container moderator.

    Production capabilities:
        - Binds the default-empty profile expected for reset.
        - Declares whether reset requires a safe point.
        - Declares whether readiness exposure requires default_empty state.

    Non-ownership:
        Does not own the BundleAgent profile itself.
*/
namespace assembler {
namespace circulation_mechanism {

struct TSlotsContainerModeratorConfig final {
    TCapacityProfileId default_empty_capacity_profile_id{};
    bool reset_requires_safe_point{true};
    bool readiness_requires_default_empty{true};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return default_empty_capacity_profile_id.is_valid();
    }
};
} // namespace circulation_mechanism
} // namespace assembler
