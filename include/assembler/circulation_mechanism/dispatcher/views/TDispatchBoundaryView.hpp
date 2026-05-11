#pragma once
#include "assembler/circulation_mechanism/dispatcher/boundary/TDispatchBoundaryDescriptor.hpp"
namespace assembler {
namespace circulation_mechanism {

struct TDispatchBoundaryView final {
    TDispatchBoundaryDescriptor descriptor{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return descriptor.is_valid(); }
    [[nodiscard]] constexpr bool ready_and_safe() const noexcept { return descriptor.ready() && descriptor.boundary_safe(); }
};
} // namespace circulation_mechanism
} // namespace assembler
