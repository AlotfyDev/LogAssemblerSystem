#pragma once
#include "TCirculationConfigurationId.hpp"
#include "TCirculationConfigurationStatus.hpp"
#include "TCirculationProfileKind.hpp"
#include "../versioning/TCirculationApiVersion.hpp"
#include "../versioning/TCirculationProfileVersion.hpp"
#include "TCirculationConfigurationIssueKind.hpp"

/*
    TCirculationConfigurationDescriptor.hpp

    Delivery:
        CME-PROD-HARDEN-W02 — Shared Runtime Lifecycle And Configuration Core

    Current responsibility:
        Defines shared configuration descriptor used by PreBridge and ReadSide without owning either subsystem runtime.

    Production capabilities:
        - configuration identity
        - profile kind classification
        - API/profile version binding
        - validation helper
        - issue classification

    Explicit non-ownership:
        - Does not instantiate PreBridge engine.
        - Does not instantiate ReadSide engine.
        - Does not allocate containers.
        - Does not bind adapters.
*/
namespace assembler {
namespace circulation_mechanism {

struct TCirculationConfigurationDescriptor final {
    TCirculationConfigurationId configuration_id{};
    TCirculationConfigurationStatus status{TCirculationConfigurationStatus::undefined};
    TCirculationProfileKind profile_kind{TCirculationProfileKind::shared_core};
    TCirculationApiVersion api_version{};
    TCirculationProfileVersion profile_version{};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return configuration_id.is_valid()
            && api_version.is_valid()
            && profile_version.is_valid()
            && status != TCirculationConfigurationStatus::undefined
            && status != TCirculationConfigurationStatus::invalid;
    }

    [[nodiscard]] constexpr TCirculationConfigurationIssueKind validation_issue() const noexcept {
        if (!configuration_id.is_valid()) return TCirculationConfigurationIssueKind::invalid_configuration_id;
        if (!api_version.is_valid()) return TCirculationConfigurationIssueKind::invalid_version;
        if (!profile_version.is_valid()) return TCirculationConfigurationIssueKind::invalid_version;
        if (status != TCirculationConfigurationStatus::validated && status != TCirculationConfigurationStatus::active) {
            return TCirculationConfigurationIssueKind::profile_not_validated;
        }
        return TCirculationConfigurationIssueKind::none;
    }

    [[nodiscard]] constexpr bool ready_for_runtime() const noexcept {
        return validation_issue() == TCirculationConfigurationIssueKind::none;
    }
};
} // namespace circulation_mechanism
} // namespace assembler
