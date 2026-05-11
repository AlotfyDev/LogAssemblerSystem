#pragma once
#include "../backpressure/TReadSideBackpressureProfile.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TReadSideBackpressureView final {
    TReadSideBackpressureProfile profile{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return profile.is_valid(); }
    [[nodiscard]] constexpr bool pressure_active() const noexcept { return profile.pressure_active(); }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
