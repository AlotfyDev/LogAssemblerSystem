#pragma once
#include "assembler/circulation_mechanism/runtime_core/configuration/TCirculationConfigurationDescriptor.hpp"
#include "assembler/circulation_mechanism/capacity/TCirculationCapacityProfile.hpp"
#include "assembler/circulation_mechanism/communication_bindings/TCirculationCommunicationBindingDescriptor.hpp"
#include "assembler/circulation_mechanism/communication_bindings/TCommunicationBindingCompatibilityPolicy.hpp"

#include "../reports/TPreBridgeEngineIssueKind.hpp"

/*
    TPreBridgeCirculationConfig.hpp

    Current responsibility:
        Configuration surface for an injectable PreBridge engine.

    Production capabilities:
        - shared runtime configuration descriptor,
        - circulation capacity profile,
        - ingress binding descriptor,
        - dispatch binding descriptor,
        - validation helper.

    Explicit non-ownership:
        - Does not contain ReadSide profile.
        - Does not execute bridge or receiver runtime.
*/
namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

struct TPreBridgeCirculationConfig final {
    TCirculationConfigurationDescriptor runtime_configuration{};
    TCirculationCapacityProfile capacity_profile{};
    TCirculationCommunicationBindingDescriptor ingress_binding{};
    TCirculationCommunicationBindingDescriptor dispatch_binding{};

    [[nodiscard]] constexpr TPreBridgeEngineIssueKind validation_issue() const noexcept {
        if (!runtime_configuration.ready_for_runtime()) return TPreBridgeEngineIssueKind::invalid_configuration;
        if (!capacity_profile.is_valid()) return TPreBridgeEngineIssueKind::invalid_capacity;
        if (!TCommunicationBindingCompatibilityPolicy::evaluate(ingress_binding).compatible()) return TPreBridgeEngineIssueKind::boundary_not_ready;
        if (!TCommunicationBindingCompatibilityPolicy::evaluate(dispatch_binding).compatible()) return TPreBridgeEngineIssueKind::boundary_not_ready;
        if (runtime_configuration.profile_kind != TCirculationProfileKind::pre_bridge) return TPreBridgeEngineIssueKind::invalid_configuration;
        return TPreBridgeEngineIssueKind::none;
    }

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return validation_issue() == TPreBridgeEngineIssueKind::none;
    }
};
} // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler
