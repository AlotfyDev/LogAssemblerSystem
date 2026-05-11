#pragma once

#include "../addon_boundary/TAddonBoundaryDescriptor.hpp"

namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TAddonBoundaryView final {
    TAddonBoundaryDescriptor descriptor{};

    [[nodiscard]] constexpr bool is_valid() const noexcept { return descriptor.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept { return descriptor.ready(); }
    [[nodiscard]] constexpr bool can_receive_runtime_material() const noexcept { return descriptor.can_receive_runtime_material(); }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
