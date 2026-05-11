#pragma once
#include "TBridgeFacingDispatchAdapterDescriptor.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TDispatchOutputBindingView final {
    TBridgeFacingDispatchAdapterDescriptor adapter{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return adapter.is_valid(); }
    [[nodiscard]] constexpr bool ready_and_safe() const noexcept { return adapter.boundary_safe(); }
};
} // namespace circulation_mechanism
} // namespace assembler
