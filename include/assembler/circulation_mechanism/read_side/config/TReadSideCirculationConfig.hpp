#pragma once

#include "assembler/circulation_mechanism/runtime_core/configuration/TCirculationConfigurationDescriptor.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile/TReadSideCirculationProfile.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile/post_bridge_capacity/TPostBridgeCapacityProfile.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile/backpressure/TReadSideBackpressureProfile.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile/delayed_release/TDelayedReleaseProfile.hpp"
#include "assembler/circulation_mechanism/read_side_circulation_profile/addon_boundary/TAddonBoundaryDescriptor.hpp"
#include "../reports/TReadSideEngineIssueKind.hpp"

/*
    TReadSideCirculationConfig.hpp

    Delivery:
        CME-READSIDE-PROD-W01 — ReadSide Engine Facade And Injection Surface

    Current responsibility:
        Configuration surface for an injectable ReadSide engine.

    Production capabilities:
        - shared runtime configuration descriptor
        - read-side profile descriptor
        - post-bridge capacity profile
        - backpressure profile
        - delayed-release profile
        - addon boundary descriptor
        - validation helper

    Explicit non-ownership:
        - Does not own PreBridge runtime.
        - Does not implement addon runtime.
        - Does not call receiver or bridge.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side {

struct TReadSideCirculationConfig final {
    TCirculationConfigurationDescriptor runtime_configuration{};
    read_side_circulation_profile::TReadSideCirculationProfile read_side_profile{};
    read_side_circulation_profile::TPostBridgeCapacityProfile capacity_profile{};
    read_side_circulation_profile::TReadSideBackpressureProfile backpressure_profile{};
    read_side_circulation_profile::TDelayedReleaseProfile delayed_release_profile{};
    read_side_circulation_profile::TAddonBoundaryDescriptor addon_boundary{};

    [[nodiscard]] constexpr TReadSideEngineIssueKind validation_issue() const noexcept {
        if (!runtime_configuration.ready_for_runtime()) return TReadSideEngineIssueKind::invalid_configuration;
        if (runtime_configuration.profile_kind != TCirculationProfileKind::read_side) return TReadSideEngineIssueKind::invalid_configuration;
        if (!read_side_profile.ready()) return TReadSideEngineIssueKind::invalid_read_side_profile;
        if (!capacity_profile.is_valid()) return TReadSideEngineIssueKind::invalid_configuration;
        if (!addon_boundary.is_valid()) return TReadSideEngineIssueKind::addon_boundary_not_ready;
        return TReadSideEngineIssueKind::none;
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return validation_issue() == TReadSideEngineIssueKind::none;
    }
};
} // namespace read_side
} // namespace circulation_mechanism
} // namespace assembler
