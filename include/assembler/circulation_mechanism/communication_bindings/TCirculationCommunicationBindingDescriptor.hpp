#pragma once
#include "TCommunicationBindingId.hpp"
#include "TCommunicationBindingKind.hpp"
#include "TCommunicationBindingStatus.hpp"
#include "ingress/TEnvelopePlacementPortDescriptor.hpp"
#include "dispatch_output/TBridgeFacingDispatchAdapterDescriptor.hpp"
#include "bridge_facing_boundary/TBridgeFacingBoundaryDescriptor.hpp"
/*
    TCirculationCommunicationBindingDescriptor.hpp

    Responsibility:
        Aggregate descriptor for CME communication binding direction.

    Non-ownership:
        Does not execute adapter behavior or bridge protocol.
*/
namespace assembler {
namespace circulation_mechanism {

struct TCirculationCommunicationBindingDescriptor final {
    TCommunicationBindingId binding_id{};
    TCommunicationBindingKind kind{TCommunicationBindingKind::ingress_placement};
    TCommunicationBindingStatus status{TCommunicationBindingStatus::unbound};
    TEnvelopePlacementPortDescriptor ingress_port{};
    TBridgeFacingDispatchAdapterDescriptor dispatch_adapter{};
    TBridgeFacingBoundaryDescriptor bridge_boundary{};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return binding_id.is_valid(); }
    [[nodiscard]] constexpr bool direction_descriptor_valid() const noexcept {
        switch(kind) {
            case TCommunicationBindingKind::ingress_placement: return ingress_port.is_valid();
            case TCommunicationBindingKind::dispatch_output: return dispatch_adapter.is_valid();
            case TCommunicationBindingKind::bridge_facing_boundary: return bridge_boundary.is_valid();
            case TCommunicationBindingKind::exposure_contract: return dispatch_adapter.exposure_contract.is_valid() || bridge_boundary.exposure_contract.is_valid();
            default: return true;
        }
    }
};
} // namespace circulation_mechanism
} // namespace assembler
