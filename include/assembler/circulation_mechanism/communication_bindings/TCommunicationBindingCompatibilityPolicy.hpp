#pragma once
#include "TCirculationCommunicationBindingDescriptor.hpp"
#include "TCommunicationBindingCompatibility.hpp"
/*
    TCommunicationBindingCompatibilityPolicy.hpp

    Responsibility:
        Validates communication binding descriptor without executing binding.
*/
namespace assembler {
namespace circulation_mechanism {

struct TCommunicationBindingCompatibilityPolicy final {
    [[nodiscard]] static constexpr TCommunicationBindingCompatibility evaluate(TCirculationCommunicationBindingDescriptor d) noexcept {
        if (!d.is_valid() || !d.direction_descriptor_valid()) {
            return {d.kind, TBindingCompatibilityStatus::incompatible};
        }
        if (d.status == TCommunicationBindingStatus::closed || d.status == TCommunicationBindingStatus::mismatch) {
            return {d.kind, TBindingCompatibilityStatus::blocked_by_boundary_rule};
        }
        if (d.kind == TCommunicationBindingKind::ingress_placement) {
            return d.ingress_port.ready() && d.ingress_port.boundary_safe()
                ? TCommunicationBindingCompatibility{d.kind, TBindingCompatibilityStatus::compatible}
                : TCommunicationBindingCompatibility{d.kind, TBindingCompatibilityStatus::blocked_by_boundary_rule};
        }
        if (d.kind == TCommunicationBindingKind::dispatch_output) {
            return d.dispatch_adapter.boundary_safe()
                ? TCommunicationBindingCompatibility{d.kind, TBindingCompatibilityStatus::compatible}
                : TCommunicationBindingCompatibility{d.kind, TBindingCompatibilityStatus::blocked_by_boundary_rule};
        }
        if (d.kind == TCommunicationBindingKind::bridge_facing_boundary) {
            return d.bridge_boundary.ready_and_safe()
                ? TCommunicationBindingCompatibility{d.kind, TBindingCompatibilityStatus::compatible}
                : TCommunicationBindingCompatibility{d.kind, TBindingCompatibilityStatus::blocked_by_boundary_rule};
        }
        return {d.kind, TBindingCompatibilityStatus::requires_profile_review};
    }
};
} // namespace circulation_mechanism
} // namespace assembler
