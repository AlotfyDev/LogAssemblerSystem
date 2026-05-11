#pragma once
#include "assembler/circulation_mechanism/communication_bindings/TCirculationCommunicationBindingDescriptor.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace pre_bridge {

struct TPreBridgeBoundaryBinding final {
    TCirculationCommunicationBindingDescriptor ingress_binding{};
    TCirculationCommunicationBindingDescriptor dispatch_binding{};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return TCommunicationBindingCompatibilityPolicy::evaluate(ingress_binding).compatible()
            && TCommunicationBindingCompatibilityPolicy::evaluate(dispatch_binding).compatible()
            && ingress_binding.kind == TCommunicationBindingKind::ingress_placement
            && dispatch_binding.kind == TCommunicationBindingKind::dispatch_output;
    }
};
} // namespace pre_bridge
} // namespace circulation_mechanism
} // namespace assembler
