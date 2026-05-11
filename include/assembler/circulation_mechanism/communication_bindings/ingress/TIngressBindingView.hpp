#pragma once
#include "TEnvelopePlacementPortDescriptor.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TIngressBindingView final {
    TEnvelopePlacementPortDescriptor port{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return port.is_valid(); }
    [[nodiscard]] constexpr bool ready_and_safe() const noexcept { return port.ready() && port.boundary_safe(); }
};
} // namespace circulation_mechanism
} // namespace assembler
