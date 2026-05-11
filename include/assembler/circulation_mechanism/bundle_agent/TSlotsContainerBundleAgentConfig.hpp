#pragma once
#include <cstdint>
#include "TContainerFamilyId.hpp"
#include "TContainerFamilyShape.hpp"

/*
    TSlotsContainerBundleAgentConfig.hpp

    Responsibility:
        Production configuration for BundleAgent topology/capacity contract.

    Production capabilities:
        - identifies container family
        - defines initial uniform shape
        - defines max container count
        - declares whether vertical scaling requires a safe point
        - declares whether horizontal scaling requires a safe point

    Non-ownership:
        Does not execute scaling and does not allocate registry storage.
*/
namespace assembler {
namespace circulation_mechanism {

struct TSlotsContainerBundleAgentConfig final {
    TContainerFamilyId family_id{};
    TContainerFamilyShape initial_shape{};
    std::uint32_t max_container_count{0};
    bool horizontal_scaling_requires_safe_point{false};
    bool vertical_scaling_requires_safe_point{true};

    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return family_id.is_valid()
            && initial_shape.is_valid()
            && max_container_count >= initial_shape.active_container_count;
    }
};
} // namespace circulation_mechanism
} // namespace assembler
