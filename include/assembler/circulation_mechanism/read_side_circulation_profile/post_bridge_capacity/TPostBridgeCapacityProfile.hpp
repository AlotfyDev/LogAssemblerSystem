#pragma once
#include <cstdint>
#include "TPostBridgeCapacityProfileId.hpp"
#include "TPostBridgeCapacityStatus.hpp"

/*
    TPostBridgeCapacityProfile.hpp

    Delivery:
        CME-RSCP-PROD-W03 — Backpressure And Delayed Release Profile

    Current responsibility:
        Defines the post-bridge/read-side capacity profile descriptor and validation logic.

    Production capabilities:
        - receiver container/slot capacity dimensions
        - failed-dispatch capacity
        - retry capacity
        - total receiver slots calculation
        - admission capacity check
        - failure capacity check

    Explicit non-ownership:
        - Does not allocate containers.
        - Does not implement waiting lists.
        - Does not throttle by itself.
*/
namespace assembler {
namespace circulation_mechanism {
namespace read_side_circulation_profile {

struct TPostBridgeCapacityProfile final {
    TPostBridgeCapacityProfileId profile_id{};
    TPostBridgeCapacityStatus status{TPostBridgeCapacityStatus::undefined};
    std::uint32_t receiver_container_count{0};
    std::uint32_t slots_per_receiver_container{0};
    std::uint32_t failed_dispatch_capacity{0};
    std::uint32_t retry_capacity{0};
    std::uint32_t current_receiver_load{0};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return profile_id.is_valid()
            && receiver_container_count > 0U
            && slots_per_receiver_container > 0U
            && status != TPostBridgeCapacityStatus::invalid
            && status != TPostBridgeCapacityStatus::undefined;
    }

    [[nodiscard]] constexpr std::uint64_t total_receiver_slots() const noexcept {
        return static_cast<std::uint64_t>(receiver_container_count) * static_cast<std::uint64_t>(slots_per_receiver_container);
    }

    [[nodiscard]] constexpr bool has_failure_capacity() const noexcept {
        return failed_dispatch_capacity > 0U || retry_capacity > 0U;
    }

    [[nodiscard]] constexpr bool receiver_has_room() const noexcept {
        return is_valid() && static_cast<std::uint64_t>(current_receiver_load) < total_receiver_slots();
    }

    [[nodiscard]] constexpr bool capacity_insufficient() const noexcept {
        return !is_valid() || status == TPostBridgeCapacityStatus::insufficient || !receiver_has_room();
    }
};
} // namespace read_side_circulation_profile
} // namespace circulation_mechanism
} // namespace assembler
