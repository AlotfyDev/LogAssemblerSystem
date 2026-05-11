#pragma once
#include "../TReadSideCirculationProfile.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TReadSideProfileView final {
    TReadSideCirculationProfile profile{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return profile.is_valid(); }
    [[nodiscard]] constexpr bool ready() const noexcept { return profile.ready(); }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
