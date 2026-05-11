#pragma once
#include "TPreBridgeDefaultProfileId.hpp"
#include "TPreBridgeDefaultProfileStatus.hpp"
#include "assembler/circulation_mechanism/pre_bridge/config/TPreBridgeCirculationConfig.hpp"
#include "assembler/circulation_mechanism/pre_bridge/profile/TPreBridgeCirculationProfile.hpp"
#include "assembler/circulation_mechanism/pre_bridge/bindings/TPreBridgeBindingSet.hpp"
#include "assembler/circulation_mechanism/pre_bridge/reports/TPreBridgeConfigurationIssueKind.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

struct TPreBridgeDefaultInjectionProfile final {
    TPreBridgeDefaultProfileId profile_id{};
    TPreBridgeDefaultProfileStatus status{TPreBridgeDefaultProfileStatus::undefined};
    TPreBridgeBindingSet bindings{};

    [[nodiscard]] constexpr TPreBridgeConfigurationIssueKind validation_issue() const noexcept {
        if (!profile_id.is_valid()) return TPreBridgeConfigurationIssueKind::invalid_default_profile_id;
        if (status != TPreBridgeDefaultProfileStatus::ready && status != TPreBridgeDefaultProfileStatus::active) {
            return TPreBridgeConfigurationIssueKind::invalid_runtime_configuration;
        }
        if (!bindings.capacity.is_valid()) return TPreBridgeConfigurationIssueKind::invalid_capacity_binding;
        if (!TCommunicationBindingCompatibilityPolicy::evaluate(bindings.boundary.ingress_binding).compatible()) {
            return TPreBridgeConfigurationIssueKind::invalid_ingress_binding;
        }
        if (!TCommunicationBindingCompatibilityPolicy::evaluate(bindings.boundary.dispatch_binding).compatible()) {
            return TPreBridgeConfigurationIssueKind::invalid_dispatch_binding;
        }
        if (!bindings.reference_supply.is_valid()) return TPreBridgeConfigurationIssueKind::invalid_reference_supply_binding;
        if (!bindings.diagnostics.is_valid()) return TPreBridgeConfigurationIssueKind::invalid_diagnostics_binding;
        return TPreBridgeConfigurationIssueKind::none;
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return validation_issue() == TPreBridgeConfigurationIssueKind::none;
    }

    [[nodiscard]] constexpr TPreBridgeCirculationProfile to_pre_bridge_profile(TCirculationConfigurationDescriptor runtime_config) const noexcept {
        return TPreBridgeCirculationProfile{
            TPreBridgeCirculationConfig{
                runtime_config,
                bindings.capacity.capacity_profile,
                bindings.boundary.ingress_binding,
                bindings.boundary.dispatch_binding
            },
            true,
            true,
            false
        };
    }
};
} // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler
