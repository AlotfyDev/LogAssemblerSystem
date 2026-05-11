#pragma once
#include "../post_bridge_capacity/TPostBridgeCapacityProfile.hpp"
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TPostBridgeCapacityView final {
    TPostBridgeCapacityProfile profile{};
    [[nodiscard]] constexpr bool is_valid() const noexcept { return profile.is_valid(); }
    [[nodiscard]] constexpr bool has_failure_capacity() const noexcept { return profile.has_failure_capacity(); }
    [[nodiscard]] constexpr bool receiver_has_room() const noexcept { return profile.receiver_has_room(); }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
